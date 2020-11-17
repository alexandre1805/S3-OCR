#include <stddef.h>
#include <SDL2/SDL.h>
void Convolution(int *image, int w, int h);
void Median(int* image, int *copy,int w, int h);
void Gauss(float *image, int *copy, int w, int h);
void Contrast(int *image,float *copy,int w,int h);
void array_swap(int array[], size_t i, size_t j);
size_t array_min_index(int array[], size_t len);
void array_select_sort(int array[], size_t len);
