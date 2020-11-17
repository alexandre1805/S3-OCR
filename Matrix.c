#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "Img-Proc.h"
#include "Matrix.h"

//convert a SDL surface into matrix
void Sdl_To_Matrix(SDL_Surface *image, int *array)
{
  int w = image->w;
  int h = image->h;
  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      Uint32 pix = Get_pixel(image, i, j);
      Uint8 r = 0;
      Uint8 g = 0;
      Uint8 b = 0;
      SDL_GetRGB(pix, image->format, &r, &g, &b);
      if (r == 0)
      {
        array[i * h + j] = 1;
      }
      else
      {
        array[i * h + j] = 0;
      }
    }
  }
  return;
}

// convert a matrix to SDL surface (for test)
void Matrix_To_Sdl(int *array, SDL_Surface *image, int w, int h)
{

  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      if (array[i * h + j] == 1)
      {
        Uint32 pix = SDL_MapRGB(image->format, 0, 0, 0);
        putpixel(image, i, j, pix);
      }
      else
      {
        Uint32 pix = SDL_MapRGB(image->format, 255, 255, 255);
        putpixel(image, i, j, pix);
      }
    }
  }
}

// function that creates one Matrix with two Matrix
// if the both matrix have a black pixel the matrix will have a black else white pixel
void merge_Matrix(int *res, int *mat1, int *mat2, int w, int h)
{
  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      if (mat1[i * h + j] == 1 && mat2[i * h + j] == 1)
      {
        res[i * h + j] = 1;
      }
      else
      {
        res[i * h + j] = 0;
      }
    }
  }
}
