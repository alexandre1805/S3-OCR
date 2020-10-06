main : main.c
	gcc GUI.h GUI.c main.c -o test `sdl2-config --cflags --libs` `pkg-config --cflags --libs gtk+-3.0`
