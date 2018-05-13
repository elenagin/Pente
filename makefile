pente: pente.o ventanas.o senales.o funciones.o tablerocodigo.o listatablero.o
	gcc -o Pente.exe pente.o ventanas.o senales.o funciones.o tablerocodigo.o listatablero.o `pkg-config --libs gtk+-2.0`

pente.o: pente.c
	gcc -c pente.c `pkg-config --cflags gtk+-2.0`

ventanas.o: ventanas.c
	gcc -c ventanas.c `pkg-config --cflags gtk+-2.0`

senales.o: senales.c
	gcc -c senales.c `pkg-config --cflags gtk+-2.0`

funciones.o: funciones.c
	gcc -c funciones.c `pkg-config --cflags gtk+-2.0`

tablerocodigo.o: tablerocodigo.c
	gcc -c tablerocodigo.c `pkg-config --cflags gtk+-2.0`

listatablero.o: listatablero.c
	gcc -c listatablero.c `pkg-config --cflags gtk+-2.0`

borra:
	rm *.o

todo:
	gcc -g -o Pente.exe pente.c ventanas.c senales.c funciones.c tablerocodigo.c listatablero.c `pkg-config --cflags --libs gtk+-2.0`
