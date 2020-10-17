#include <stdio.h>
#include "Segmentation.h"
#include "Matrix.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int threeholdH = 100;
const int threeholdV = 600;

void Block_Segmentation(int *array, int *res,int h, int w){
 int* harray = malloc(h*w*sizeof(int));
 int* varray = malloc(h*w*sizeof(int));
 vertical_Segmentation(array,varray,h,w);
 horizontal_Segmentation(array,harray,h,w);
 composeMatrix(res,varray,harray,w,h);

 /*SDL_Surface *surface1 = SDL_CreateRGBSurface(0, w, h, 32,0,0,0,0);
 Matrix_To_Sdl(varray,surface1,w,h);
 IMG_SavePNG(surface1,"outv.png");

 SDL_Surface *surface = SDL_CreateRGBSurface(0, w, h, 32,0,0,0,0);
 Matrix_To_Sdl(harray,surface,w,h);
 IMG_SavePNG(surface,"outh.png");*/


}

void horizontal_Segmentation(int *array, int *vertical_array,int h,int w){
 for(int x = 0;x < w;x++){
  for(int y= 0;y < h;y++){
   if(array[x*h+y] == 1){
    vertical_array[x*h+y] = 1;
   }
   else{
    int found = 0;
    int e = x;
    while (e >= 0 && x-e <= threeholdH ){
     if(array[e*h+y] == 1)
      found = 1;
     e = e-1;
    }
    if(found == 1) {
     int e = x;
     while(e < w  && e-x <= threeholdH ){
     if(array[e*h+y]){
      vertical_array[x*h+y] = 1;
      }
     e = e+1;
     }
    }
   }
  }
 }
}

void vertical_Segmentation(int *array, int *vertical_array,int h,int w){
 for(int x = 0;x < w;x++){
  for(int y= 0;y < h;y++){
   if(array[x*h+y] == 1){
    vertical_array[x*h+y] = 1;
   }
   else{
    int found = 0;
    int e = y;
    while (e >= 0 && y-e <= threeholdV ){
     if(array[x*h+e] == 1)
      found = 1;
     e = e-1;
    }
    if(found == 1) {
     int e = y;
     while(e < h && e-y <= threeholdV){
     if(array[x*h+e]){
      vertical_array[x*h+y] = 1;
      }
     e = e+1;
     }
    }
   }
  }
 }
}
