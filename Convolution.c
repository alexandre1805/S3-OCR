#include <SDL2/SDL.h>
#include "Img-Proc.h"
#include "Convolution.h"
#include <stdio.h>

void Convolution(int *image, int w, int h)
{
  int *copy = malloc(w * h * sizeof(int));
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      copy[x * h + y] = image[x * h + y];
    }
  }
  Median(image, copy, w, h);
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      copy[x * h + y] = image[x * h + y];
    }
  }
  float *Gaussian = malloc(w * h * sizeof(int));
  Gauss(Gaussian, copy, w, h);
  Contrast(image, Gaussian, w, h);
}

void Median(int *image, int *copy, int w, int h)
{
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      if (x == 0 && y == 0)
      {

        int L[4];

        L[0] = copy[x * h + y];
        L[1] = copy[(x + 1) * h + y];
        L[2] = copy[x * h + (y + 1)];
        L[3] = copy[(x + 1) * h + y + 1];

        array_select_sort(L, 4);

        image[x * h + y] = L[2];
      }
      else if (x == 0)
      {
        int L[6];

        L[0] = copy[x * h + y];
        L[1] = copy[(x + 1) * h + y];
        L[2] = copy[x * h + (y + 1)];
        L[3] = copy[(x + 1) * h + (y + 1)];
        L[4] = copy[x * h + (y - 1)];
        L[5] = copy[(x + 1) * h + (y - 1)];

        array_select_sort(L, 6);

        image[x * h + y] = L[3];
      }
      else if (y == 0)
      {
        int L[6];

        L[0] = copy[x * h + y];
        L[1] = copy[(x + 1) * h + y];
        L[2] = copy[x * h + (y + 1)];
        L[3] = copy[(x + 1) * h + (y + 1)];
        L[4] = copy[(x - 1) * h + (y + 1)];
        L[5] = copy[(x - 1) * h + y];

        array_select_sort(L, 6);

        image[x * h + y] = L[3];
      }
      else if (x == w - 1 && y == h - 1)
      {
        int L[4];

        L[0] = copy[x * h + y];
        L[1] = copy[(x - 1) * h + y];
        L[2] = copy[x * h + (y - 1)];
        L[3] = copy[(x - 1) * h + (y - 1)];

        array_select_sort(L, 4);

        image[x * h + y] = L[2];
      }
      else if (x == w - 1)
      {
        int L[6];

        L[0] = copy[x * h + y];
        L[1] = copy[x * h + (y + 1)];
        L[2] = copy[x * h + (y - 1)];
        L[3] = copy[(x - 1) * h + (y - 1)];
        L[4] = copy[(x - 1) * h + y];
        L[5] = copy[(x - 1) * h + (y + 1)];

        array_select_sort(L, 6);

        image[x * h + y] = L[3];
      }
      else if (y == h - 1)
      {
        int L[6];

        L[0] = copy[x * h + y];
        L[1] = copy[(x - 1) * h + y];
        L[2] = copy[(x + 1) * h + y];
        L[3] = copy[(x - 1) * h + (y - 1)];
        L[4] = copy[x * h + (y - 1)];
        L[5] = copy[x * h + (y + 1)];

        array_select_sort(L, 6);

        image[x * h + y] = L[3];
      }
      else
      {
        int L[9];

        L[0] = copy[(x - 1) * h + (y - 1)];
        L[1] = copy[(x - 1) * h + y];
        L[2] = copy[(x - 1) * h + (y + 1)];
        L[3] = copy[x * h + (y - 1)];
        L[4] = copy[x * h + y];
        L[5] = copy[x * h + (y + 1)];
        L[6] = copy[(x + 1) * h + (y - 1)];
        L[7] = copy[(x + 1) * h + y];
        L[8] = copy[(x + 1) * h + (y + 1)];

        array_select_sort(L, 9);

        if (image[x * h + y] == 1 && L[7] == 0)
        {
          image[x * h + y] = 0;
        }
        if (image[x * h + y] == 0 && L[1] == 1)
        {
          image[x * h + y] = 1;
        }
      }
    }
  }
}

void Gauss(float *image, int *copy, int w, int h)
{
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      if (x == 0 && y == 0)
      {
        if (((copy[x * h + y] / 4) + (copy[(x + 1) * h + y] / 8) + (copy[(x + 1) * h + (y + 1)] / 16)) >= 0.5)
        {
        }
      }
      else if (x == 0)
      {
        if (((copy[x * h + y] / 4) + (copy[(x + 1) * h + y] / 8) + (copy[(x + 1) * h + (y + 1)] / 16) + (copy[(x * h + (y - 1))] / 8) + (copy[(x + 1) * h + (y - 1)] / 16)) >= 0.5)
        {
        }
      }
      else if (y == 0)
      {
        if (((copy[(x - 1) * h + y] / 8) + (copy[(x - 1) * h + (y + 1)] / 8) + (copy[x * h + y] / 4) + (copy[x * h + (y + 1)] / 8) + (copy[(x + 1) * h + y] / 8) + (copy[(x + 1) * h + (y + 1)] / 16)) >= 0.5)
        {
        }
      }
      else if (x == w - 1 && y == h - 1)
      {
      }
      else if (x == w - 1)
      {
      }
      else if (y == h - 1)
      {
      }
      else
      {
        image[x * h + y] = (((float)copy[(x - 1) * h + (y - 1)]) / 16) + (((float)copy[(x - 1) * h + y]) / 8) + (((float)copy[(x - 1) * h + (y + 1)]) / 16) + (((float)copy[x * h + (y - 1)]) / 8) + (((float)copy[x * h + y]) / 4) + (((float)copy[x * h + (y + 1)]) / 8) + (((float)copy[(x + 1) * h + (y - 1)]) / 16) + (((float)copy[(x + 1) * h + y]) / 8) + (((float)copy[(x + 1) * h + (y + 1)]) / 16);
      }
    }
  }
}

void Contrast(int *image, float *copy, int w, int h)
{
  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      if (x == 0 && y == 0)
      {
      }
      else if (x == 0)
      {
      }
      else if (y == 0)
      {
      }
      else if (x == w - 1 && y == h - 1)
      {
      }
      else if (x == w - 1)
      {
      }
      else if (y == h - 1)
      {
      }
      else
      {
        if (((copy[x * h + y] * 8) - copy[(x - 1) * h + y] - copy[(x + 1) * h + y] - copy[x * h + (y - 1)] - copy[x * h + (y - 1)]) >= 0.5)
        {
          image[x * h + y] = 1;
        }
        else
        {
          image[x * h + y] = 0;
        }
      }
    }
  }
}

void array_swap(int array[], size_t i, size_t j)
{
  int e = array[i];
  array[i] = array[j];
  array[j] = e;
}

size_t array_min_index(int array[], size_t len)
{
  int index = 0;
  for (size_t i = 1; i < len; i++)
  {
    if (array[i] < array[index])
    {
      index = (int)i;
    }
  }
  return index;
}

void array_select_sort(int array[], size_t len)
{
  for (size_t i = 0; i < len; i++)
  {
    int temp_array[len - i];
    for (size_t a = 0; a < (len - i); a++)
    {
      temp_array[a] = array[a + i];
    }
    size_t min = array_min_index(temp_array, len - i);
    array_swap(array, i, min + i);
  }
}
