#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

long[][] Sdl_To_Matrix(SDL_SURFACE image)
{
	int w = image->w;
	int h = image->h;
	long mat[w][h];
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			Uint32 pix = Get_pixel(image, i, j);
			Uint8 r = 0;
			Uint8 g = 0;
			Uint8 b = 0;
			SDL_GetRGB(pix, image->format, &r, &g, &b);
			if (r == 0)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
	return mat;
}
