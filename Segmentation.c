#include <stdio.h>
#include <stdlib.h>
#include "Segmentation.h"
#include "Matrix.h"
#include "Img-Proc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Convolution.h"
#include "finalocr.h"
void Segmentation(char *filename, int angle,int detection)
{
  SDL_Surface *image = Load_Image(filename);
  int h = image->h;
  int w = image->w;
  Binarize(image);
  int *array = malloc(h * w * sizeof(int));
  Sdl_To_Matrix(image, array);
  if(detection == 1){
   //angle = detectAngle(array, w, h);
  }
  printf("Segmentation active");
  Rotation(angle, array, w, h);
  Matrix_To_Sdl(array, image, w, h);
  IMG_SavePNG(image, "angle.png");
  Convolution(array, w, h);
  int *res = malloc(h * w * sizeof(int));
  Block_Segmentation(array, res, h, w);
  int nb = find_size(res, h, w);
  int *L = malloc(nb * sizeof(int));
  int *l = malloc(nb * sizeof(int));
  int *coord = malloc(nb * 2 * sizeof(int));
  find_coord(res, L, l, coord, h, w);
  int L1 = 0;
  int l1 = 0;
  for (int x = 0; x < nb; x++)
  {
    if (l[x] > l1)
    {
      l1 = l[x];
    }
    L1 = L1 + L[x];
  }
  int *car = malloc(L1 * l1 * sizeof(int));
  create_line(array, car, coord, L1, L, l, nb, h);
  int nbchar = detect_char(car, L1, l, L, nb);
  int *cuts_coord = malloc(nbchar*nb*sizeof(int));
  find_cuts(cuts_coord,car,L1,l,L,nb);
  SDL_Surface *surface = SDL_CreateRGBSurface(0, l1, L1, 32, 0, 0, 0, 0);
  Matrix_To_Sdl(car, surface, l1, L1);
  IMG_SavePNG(surface, "out.png");
  free(array);
  free(car);
  free(res);
  free(l);
}
//execute vertical and horizontal Segementation functions and merge it into one matrix
void Block_Segmentation(int *array, int *res, int h, int w)
{
  int *harray = malloc(h * w * sizeof(int));
  int *varray = malloc(h * w * sizeof(int));
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      harray[x * h + y] = array[x * h + y];
      varray[x * h + y] = array[x * h + y];
    }
  }
  vertical_Segmentation(varray, h, w);
  horizontal_Segmentation(harray, h, w);
  merge_Matrix(res, varray, harray, w, h);

  free(harray);
  free(varray);
}

//watch if on each line there is a black pixel and color the line
void horizontal_Segmentation(int *array, int h, int w)
{
  for (int x = 0; x < h; x++)
  {
    int black_line = 0;
    for (int y = 0; y < w; y++)
    {
      if (array[y * h + x] == 1)
      {
        black_line = 1;
      }
    }
    if (black_line == 1)
    {
      for (int y = 0; y < w; y++)
      {
        array[y * h + x] = 1;
      }
    }
  }
  for (int x = 0; x < h; x++)
  {
    for (int y = 2; y < w - 2; y++)
    {
      if ((array[(y - 1) * h + x] == 1 && array[(y + 1) * h + x] == 1) || (array[(y - 2) * h + x] == 1 && array[(y + 2) * h + x] == 1))
      {
        for (int y = 0; y < w; y++)
        {
          array[y * h + x] = 1;
        }
      }
    }
  }
}

//watch if on each column there is a black pixel and color the column
void vertical_Segmentation(int *array, int h, int w)
{
  for (int y = 0; y < w; y++)
  {
    int black_line = 0;
    for (int x = 0; x < h; x++)
    {
      if (array[y * h + x] == 1)
      {
        black_line = 1;
      }
    }
    if (black_line == 1)
    {
      for (int x = 0; x < h; x++)
      {
        array[y * h + x] = 1;
      }
    }
  }
  for (int y = 0; y < w; y++)
  {
    for (int x = 2; x < h - 2; x++)
    {
      if ((array[y * h + (x - 1)] == 1 && array[y * h + (x + 1) == 1]) || (array[y * h + (x - 2)] == 1 && array[y * h + (x + 2)] == 1))
      {
        for (int x = 0; x < h; x++)
        {
          array[y * h + x] = 1;
        }
      }
    }
  }
}

//retrun the number of line found
int find_size(int *res, int h, int w)
{
  int nb_elt = 0;
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      if (res[x * h + y] == 1 && res[x * h + (y - 1)] == 0 && res[(x - 1) * h + y] == 0 && res[(x - 1) * h + (y - 1)] == 0)
      {
        nb_elt++;
      }
    }
  }
  return nb_elt;
}

//put in matrix each coordonate, the weight and the height of each line
void find_coord(int *res, int *L, int *l, int *coord, int h, int w)
{
  int n = 0;
  int n2 = 0;
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      if (res[x * h + y] == 1 && res[x * h + (y - 1)] == 0 && res[(x - 1) * h + y] == 0 && res[(x - 1) * h + (y - 1)] == 0)
      {
        int l1 = 0;
        while (res[(l1 + x) * h + y] == 1)
        {
          l1++;
        }
        int L1 = 0;
        while (res[x * h + (L1 + y)] == 1)
        {
          L1++;
        }
        l[n] = l1;
        L[n] = L1;
        coord[n2] = x;
        coord[n2 + 1] = y;
        n2 = n2 + 2;
        n++;
      }
    }
  }
}

// put each line of the original matrix and put it into an smaller matrix
void create_line(int *array, int *car, int *coord, int L1, int *L, int *l, int nb, int h)
{
  int biais = 0;
  int n2 = 0;
  for (int n = 0; n < nb; n++)
  {
    for (int x = 0; x < l[n]; x++)
    {
      for (int y = 0; y < L[n]; y++)
      {
        car[x * L1 + (biais + y)] = array[(coord[n2] + x) * h + (coord[n2 + 1] + y)];
      }
    }
    biais = biais + L[n];
    n2 = n2 + 2;
  }
}

// watch in each colmune of each if there is an column with only white pixel and color it
// able to detect spaces
int detect_char(int *car, int L1, int *l, int *L, int nb)
{
  int nb_cuts = 0;
  int biais = 0;
  for (int n = 0; n < nb; n++)
  {
    int nb_tmp = 0;
    for (int x = 0; x < l[n]; x++)
    {
      if (car[x * L1 + biais] == 0)
      {
        int blank = 0;
        int black_before = 0;
        int black_after = 0;
        for (int y = 0; y < L[n]; y++)
        {
          if (car[x * L1 + y + biais] == 1)
          {
            blank++;
          }
          if (x > 0 && car[(x - 1) * L1 + y + biais] == 1)
          {
            black_before++;
          }
          if (x < (l[n] - 1) && car[(x + 1) * L1 + y + biais] == 1)
          {
            black_after++;
          }
        }
        if (((float)blank / (float)L[n]) <= 0 && black_before != L[n] && (black_before != 0 || (black_after != 0 && black_after != L[n])))
        {
          for (int y = 0; y < L[n]; y++)
          {
            car[x * L1 + y + biais] = 1;
          }
	  nb_tmp++;
        }
      }
    }
    biais = biais + L[n];
    nb_cuts = fmax(nb_cuts,nb_tmp);
  }
  return nb_cuts;
}

void find_cuts(int *cut_coords,int *car,int L1, int *l, int *L, int nb)
{
  init_Reseau();
  int h =0;
  cut_coords[0] = 0;
  int biais = 0;
  for (int n = 0; n < nb; n++)
  {
    int len = 0;
    for (int x = 0; x < l[n]; x++)
    {
     int black_line = 1;
     for (int y = 0; y < L[n]; y++)
      {
       if(car[x * L1 + y + biais] == 0){
        black_line = 0;
       }
      }
     if(black_line == 1 && len != 0){
       int *incar = calloc((x-len)*L[n],sizeof(int));
       for (int y1 = 0; y1 < L[n]; y1++)
       {
        int x2 = 0;
        for(int x1 = x-(x-len)+1;x1<x;x1++)
        {
         incar[x2*L[n]+y1] = car[x1*L1+y1+biais];
	 x2++;
        }
       }
      if((float)(x-len)/(float)L[n] > 0.12){
       int *resolt = calloc(28*28,sizeof(int));
       if(L[n] <= 28 && (x-len) <= 28)
       {
        for(int i = 0;i<(x-len);i++){
         for(int j = 0;j<L[n];j++){
          resolt[((28-(x-len))/2+i)*28+j+(28-L[n])/2] = incar[i*L[n]+j];
         }
        }
       }
       else if((x-len) <= 28)
       {
        for(int i = 0;i<(x-len);i++){
         for(int j = 0;j<28;j++){
          resolt[((28-(x-len))/2+i)*28+j] = incar[i*L[n]+((j*L[n])/28)];
         }
       	}
       }
       else{
        for(int i = 0;i<28;i++){
         for(int j = 0;j<28;j++){
	   resolt[i*28+j] = incar[((i*(x-len))/28)*L[n]+((j*L[n])/28)];
	 }
        }
       }
       SDL_Surface *surface = SDL_CreateRGBSurface(0, 28, 28, 32, 0, 0, 0, 0);
       Matrix_To_Sdl(resolt, surface, 28, 28);
       char *result = malloc(sizeof(char)*4);
       sprintf(result, "%i", h); 
       //IMG_SavePNG(surface, result);
       printf("%c",answer(resolt));
       h++;
       len = x;
       free(incar);
       free(result);
       SDL_FreeSurface(surface);
       }
       else {
        len = x;
       }
      }
      if(len == 0 && black_line == 1){
       len = x;
      }
    }
    len = 0;
    biais = biais + L[n];
  }
}
