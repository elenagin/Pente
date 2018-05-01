pente: final.o senales.o funciones.o
	gcc -o pente final.o senales.o funciones.o `pkg-config --libs gtk+-2.0`

final.o: final.c
	gcc -c final.c `pkg-config --cflags gtk+-2.0`

senales.o: senales.c
	gcc -c senales.c `pkg-config --cflags gtk+-2.0`

funciones.o: funciones.c
	gcc -c funciones.c `pkg-config --cflags gtk+-2.0`

borra:
	rm *.o

todo:
	gcc -g -o pente final.c senales.c funciones.c `pkg-config --cflags --libs gtk+-2.0`