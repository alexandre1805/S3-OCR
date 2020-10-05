#include <SDL2/SDL.h>
#include <stdio.h>


int main (int    argc, char **argv)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stdout,"Echec de l'initialisation de SDL");
		return -1;
	}
	SDL_Window* pWindow = NULL;
	SDL_Renderer* ren = NULL;
	pWindow = SDL_CreateWindow("fenetre nulle", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);

	if(pWindow == NULL)
  	{
		fprintf(stderr,"Erreur lors de la creation de la fenetre");
		return -1;
  	}

	ren = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(ren == NULL)
	{
		fprintf(stdout,"Erreur lors de la creation du renderer ");
	}
	SDL_Delay(3000);

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(pWindow);
  	SDL_Quit();
}

