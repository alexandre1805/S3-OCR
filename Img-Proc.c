#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Img-Proc.h"
#include "Convolution.h"
#include <math.h>
//Get the value of a (x,y) pixel with a Uint32 format (BytesPerPixel)
Uint32 Get_pixel(SDL_Surface *surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel;
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  switch (bpp)
  {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  default:
    return 0;
  }
}
//put the value of a (x,y) pixel with a Uint32 format
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  int bpp = surface->format->BytesPerPixel;
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp)
  {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    }
    else
    {
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
SDL_Surface *Load_Image(char *dir)
{
  SDL_Surface *image = NULL;
  image = IMG_Load(dir);
  if (!image)
  {
    printf("Error when loading image : %s", SDL_GetError());
    return NULL;
  }
  return image;
}

//take the average of each color and turn pixel in black or white
void Binarize(SDL_Surface *image)
{

  int h = image->h;
  int w = image->w;
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      Uint32 pix = Get_pixel(image, x, y);
      Uint8 r = 0;
      Uint8 g = 0;
      Uint8 b = 0;

      SDL_GetRGB(pix, image->format, &r, &g, &b);

      Uint8 rn = 0;
      Uint8 gn = 0;
      Uint8 bn = 0;

      if ((0.3 * r) + (0.59 * g) + (0.11 * b) > 127)
      {
        rn = 255;
        gn = 255;
        bn = 255;
      }

      Uint32 npix = SDL_MapRGB(image->format, rn, gn, bn);
      putpixel(image, x, y, npix);
    }
  }
}

float detectAngle(int *array, int w, int h)
{
  printf("%i,%i,%i", array[0], w, h);
  return 90;
}

void Rotation(float teta, int *image, int w, int h)
{
  teta = teta * 0.0174533;
  int px = w / 2;
  int py = h / 2;
  int *copy = malloc(h * w * sizeof(int));
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      copy[x * h + y] = image[x * h + y];
      image[x * h + y] = 0;
    }
  }
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      int X = (int)((double)(x - px)) * cos((double)teta) - ((double)(y - py)) * sin((double)teta) + px;
      int Y = (int)((double)(x - px)) * sin((double)teta) + ((double)(y - py)) * cos((double)teta) + py;
      if (X >= 0 && X < w && Y >= 0 && Y < h)
      {
        image[X * h + Y] = copy[x * h + y];
      }
    }
  }
  free(copy);
}
