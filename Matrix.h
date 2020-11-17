#include <stdint.h>
#include <SDL2/SDL.h>

void Sdl_To_Matrix(SDL_Surface *image, int *array);
void Matrix_To_Sdl(int *array, SDL_Surface *image, int w, int h);
void merge_Matrix(int *res, int *mat1, int *mat2, int w, int h);
