main : main.c
	gcc Img-Proc.h Img-Proc.c GUI.h GUI.c main.c -o test `sdl2-config --cflags --libs` `pkg-config --cflags --libs gtk+-3.0` -lSDL2_image
