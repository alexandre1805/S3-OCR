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
  SDL_Surface *surface = SDL_CreateRGBSurface(0, w, h, 32,0,0,0,0);
  Matrix_To_Sdl(res,surface,w,h);
  IMG_SavePNG(surface,"out.png");
  free(array);
  free(res);
  
  /*GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;*/
}

