#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Img-Proc.h"


//Get the value of a (x,y) pixel with a Uint32 format (BytesPerPixel)
Uint32 Get_pixel(SDL_Surface *surface,int x,int y){ 	
   int bpp = surface -> format->BytesPerPixel;
   Uint8 *p = (Uint8 *)surface->pixels+ y * surface->pitch + x * bpp;
   switch(bpp){
   case 1:
    return *p;
   case 2:
    return *(Uint16 *)p;
   case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
     return p[0] << 16 | p[1] << 8 | p[2];
    else
     return p[0] | p[1] << 8 | p[2] << 16;
   case 4:
     return *(Uint32 *)p;
   default:
     return  0;
   }
}
//put the value of a (x,y) pixel with a Uint32 format
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
 int bpp = surface->format->BytesPerPixel;
 Uint8 *p = (Uint8 *)surface->pixels+y*surface->pitch+x*bpp;

 switch(bpp) {
  case 1:
   *p = pixel;
   break;
  case 2:
   *(Uint16 *)p = pixel;
   break;
  case 3:
   if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
    p[0] = (pixel >> 16) & 0xff;
    p[1] = (pixel >> 8) & 0xff;
    p[2] = pixel & 0xff;
   }
   else {
    p[0] = pixel & 0xff;
    p[1] = (pixel >> 8) & 0xff;
    p[2] = (pixel >> 16) & 0xff;
   }
   break;
  case 4:
   *(Uint32 *)p = pixel;
   break;
 }

}
//Load image with a pointer on the path.
SDL_Surface *Load_Image(char *dir){
 SDL_Surface *image = NULL;
 image = IMG_Load(dir);
 if(!image)
 {
  printf("Error when loading image : %s",SDL_GetError());
  return image;
 }
}

void Img_Proc(char *dir){
 SDL_Surface *image = Load_Image(dir);
 int h = image -> h;
 int w = image -> w;
 for(int x = 0; x < w; x++){
  for(int y = 0; y < h; y++){
   Uint32 pix = Get_pixel(image,x,y);
   Uint8 r = 0;
   Uint8 g = 0;
   Uint8 b = 0;

   SDL_GetRGB(pix,image->format,&r,&g,&b);

   Uint8 rn = 0;
   Uint8 gn = 0;
   Uint8 bn = 0;

   if((0.3*r)+(0.59*g)+(0.11*b)>127){
    rn = 255;
    gn = 255;
    bn = 255;
   }

   Uint32 npix = SDL_MapRGB(image->format,rn,gn,bn);
  putpixel(image,x,y,npix);
  }
 }
 IMG_SavePNG(image,"out.png");
}
