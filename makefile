ventanas: pente.o ventanas.o funciones.o
	gcc -o ventanas pente.o ventanas.o funciones.o `pkg-config --libs gtk+-2.0`

pente.o: pente.c
	gcc -c pente.c `pkg-config --cflags gtk+-2.0`

ventanas.o: ventanas.c
	gcc -c ventanas.c `pkg-config --cflags gtk+-2.0`

funciones.o: funciones.c
	gcc -c funciones.c `pkg-config --cflags gtk+-2.0`

borra:
	rm *.o

todo:
	gcc -g -o ventanas pente.c ventanas.c funciones.c `pkg-config --cflags --libs gtk+-2.0`
