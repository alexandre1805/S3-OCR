#include <stdint.h>
#include <SDL2/SDL.h>

void IMG_Processing(char *dir);
Uint32 Get_pixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void Binarize(SDL_Surface *image);
SDL_Surface *Load_Image(char *dir);
float detectAngle(int *array, int w, int h);
void Rotation(float teta, int *image, int w, int h);
