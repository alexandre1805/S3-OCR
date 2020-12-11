all = main

main : main.o GUI.o Img-Proc.o Matrix.o Segmentation.o Convolution.o neuron.o sigmoid.o whicharacter.o finalocr.o
	gcc main.o GUI.o Img-Proc.o Matrix.o Segmentation.o Convolution.o neuron.o sigmoid.o whicharacter.o finalocr.o -o test `sdl2-config --cflags --libs` `pkg-config --cflags --libs gtk+-3.0` -lSDL2_image -g -lm

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

neuron.o : neuron.c neuron.h
	gcc -Wall -Wextra -Werror -std=c99 -g -c neuron.h neuron.c

sigmoid.o : sigmoid.c sigmoid.h
	gcc -Wall -Wextra -Werror -std=c99 -g -c sigmoid.h sigmoid.c

whicharacter.o :whicharacter.c whicharacter.c
	gcc -Wall -Wextra -Werror -std=c99 -g -c whicharacter.c whicharacter.c

finalocr.o:
	gcc -Wall -Wextra -Werror -std=c99 -g -c finalocr.c

clean :
	rm *.o *.gch
	rm test
