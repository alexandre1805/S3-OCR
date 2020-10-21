#include <stdio.h>
#include "Segmentation.h"
#include "Matrix.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Block_Segmentation(int *array, int *res,int h, int w){
 int* harray = malloc(h*w*sizeof(int));
 int* varray = malloc(h*w*sizeof(int));
 for(int x = 0;x<w;x++){
  for(int y = 0;y<h;y++){
  harray[x*h+y] = array[x*h+y];
  varray[x*h+y] = array[x*h+y];
  }
 }
 vertical_Segmentation(varray,h,w);
 horizontal_Segmentation(harray,h,w);
 composeMatrix(res,varray,harray,w,h);

 free(harray);
 free(varray);
}

void horizontal_Segmentation(int *array,int h, int w){
 for(int x = 1;x < h;x++){
 int black_line = 0;
  for(int y = 0;y<w;y++){
   if(array[y*h+x] == 1){
    black_line = 1;
   }
  }
  if(black_line == 1){
   for(int y = 0;y<w;y++){
   array[y*h+x] = 1;
   }
  }
 }
}


void vertical_Segmentation(int *array,int h,int w){
for(int y = 1;y < w;y++){
 int black_line = 0;
  for(int x = 0;x<h;x++){
   if(array[y*h+x] == 1){
    black_line = 1;
   }
  }
  if(black_line == 1){
   for(int x = 0;x<h;x++){
   array[y*h+x] = 1;
   }
  }
 }
}

int find_size(int *res,int h, int w){
 int nb_elt = 0;
 for(int x = 0;x<w;x++){
  for(int y = 0; y<h;y++){
   if(res[x*h+y] == 1 && res[x*h+(y-1)] == 0 && res[(x-1)*h+y] == 0 && res[(x-1)*h+(y-1)] == 0 )
   {
          nb_elt++;
   }
  }
 }
 return nb_elt;
}
void find_coord(int *res, int *L,int *l,int *coord, int h, int w){
 int n = 0;
 int n2 = 0;
 for(int x = 0;x<w;x++){
  for(int y = 0; y<h;y++){
   if(res[x*h+y] == 1 && res[x*h+(y-1)] == 0 && res[(x-1)*h+y] == 0 && res[(x-1)*h+(y-1)] == 0 )
   {
    int l1 = 0;
    while(res[(l1+x)*h+y] == 1){
     l1++;
    }
    int L1 = 0;
    while(res[x*h+(L1+y)] == 1){
     L1++;
    }
    l[n] = l1;
    L[n] = L1;
    coord[n2] = x;
    coord[n2+1] = y;
    n2 = n2 +2; 
    n++;
   }
  }
 }
}

void create_line(int *array,int *car,int *coord,int L1,int *L,int *l, int nb,int h){
 int biais = 0;
 int n2 = 0;
 for(int n = 0; n < nb;n++){
  for(int x = 0;x<l[n];x++){
   for(int y = 0;y<L[n];y++){
    car[x*L1+(biais+y)] = array[(coord[n2]+x)*h+(coord[n2+1]+y)];
   }
  }
 biais = biais + L[n];
 n2 = n2 + 2;
 }
}


void detect_char(int *car,int L1,int *l,int *L,int nb){
 int biais = 0;
 for(int n = 0;n<nb;n++){
  for(int x = 0;x<l[n];x++){
   if(car[x*L1+biais] == 0){
   int blank = 1;
   int black_before = 0;
   int black_after = 0;
    for(int y = 0;y<L[n];y++){
     if(car[x*L1+y+biais] == 1){
      blank = 0;
     }
     if(x > 0  && car[(x-1)*L1+y+biais] == 1){
      black_before++;
     }
     if(x < (l[n]-1) && car[(x+1)*L1+y+biais] == 1){
     black_after++;
     }     
    }
    if(blank == 1 && black_before != L[n] && (black_before != 0 || (black_after != 0 && black_after != L[n]))){
     for(int y = 0;y<L[n];y++){
      car[x*L1+y+biais] = 1;
     }
    }
   }
  }
  biais = biais + L[n];
 }
}
