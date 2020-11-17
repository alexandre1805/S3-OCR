all = main

main : main.o GUI.o Img-Proc.o Matrix.o Segmentation.o Convolution.o
	gcc main.o GUI.o Img-Proc.o Matrix.o Segmentation.o Convolution.o -o test `sdl2-config --cflags --libs` `pkg-config --cflags --libs gtk+-3.0` -lSDL2_image -g -lm

main.o : main.c GUI.h Img-Proc.h Matrix.h Segmentation.h
	gcc -Wall -Wextra -Werror -std=c99 -g -c main.c GUI.h Img-Proc.h Matrix.h Segmentation.h `pkg-config --cflags --libs gtk+-3.0`

GUI.o: GUI.c
	gcc -Wall -Wextra -Werror -std=c99 -g -c GUI.c `pkg-config --cflags --libs gtk+-3.0`

Img-Proc.o: Img-Proc.c Img-Proc.h Convolution.h
	gcc -Wall -Wextra -Werror -std=c99 -g -c Img-Proc.c Img-Proc.h Convolution.h

Matrix.o : Matrix.c Matrix.h Img-Proc.h
	gcc -Wall -Wextra -Werror -std=c99 -g -c Matrix.c Matrix.h Img-Proc.h

Segmentation.o : Segmentation.c Segmentation.h Matrix.h
	gcc -Wall -Wextra -Werror -std=c99 -g -c Segmentation.c Segmentation.h Matrix.h

Convolution.o : Convolution.c Convolution.h Img-Proc.h Img-Proc.c
	gcc -Wall -Wextra -Werror -std=c99 -g -c Convolution.c Convolution.h Img-Proc.h Img-Proc.c
clean :
	rm *.o *.gch
	rm test
