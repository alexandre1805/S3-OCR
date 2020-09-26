main : main.c
	gcc `pkg-config --cflags gtk+-3.0` main.c -o test `pkg-config --libs gtk+-3.0`
