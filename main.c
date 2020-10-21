#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "GUI.h"
#include "Img-Proc.h"
#include "Matrix.h"
#include "Segmentation.h"
int main ()
{
  
  char *dir = "test.png";
  SDL_Surface *image = Load_Image(dir);
  int h = image -> h;
  int w = image -> w;
  Binarize(image);
  int* array = malloc(h*w*sizeof(int)); 
  Sdl_To_Matrix(image,array);
  int* res = malloc(h*w*sizeof(int));
  Block_Segmentation(array,res,h,w);
  int nb = find_size(res,h,w);
  int* L = malloc(nb*sizeof(int));
  int* l = malloc(nb*sizeof(int));
  int* coord = malloc(nb*2*sizeof(int));
  find_coord(res,L,l,coord,h,w);
  int L1 = 0;
  int l1= 0;
  for(int x = 0; x<nb;x++){
   if(l[x] > l1){
    l1 = l[x];
   }
   L1 = L1 +L[x];
  }
  int *car = malloc(L1*l1*sizeof(int));
  create_line(array,car,coord,L1,L,l,nb,h);
  detect_char(car,L1,l,L,nb);
  SDL_Surface *surface = SDL_CreateRGBSurface(0,l1,L1,32,0,0,0,0);
  Matrix_To_Sdl(car,surface,l1,L1);
  IMG_SavePNG(surface,"out.png");
  free(array);
  free(car);
  free(res);
  free(l);
  free(L);
  /*
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
  */
}

