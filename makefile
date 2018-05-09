ventanas: pente.o ventanainstrucciones.o ventanalogo.o funciones.o
	gcc -o ventanas pente.o ventanainstrucciones.o ventanalogo.o funciones.o `pkg-config --libs gtk+-2.0`

pente.o: pente.c
	gcc -c pente.c `pkg-config --cflags gtk+-2.0`

ventanainstrucciones.o: ventanainstrucciones.c
	gcc -c ventanainstrucciones.c `pkg-config --cflags gtk+-2.0`

ventanalogo.o: ventanalogo.c
	gcc -c ventanalogo.c `pkg-config --cflags gtk+-2.0`

funciones.o: funciones.c
	gcc -c funciones.c `pkg-config --cflags gtk+-2.0`

borra:
	rm *.o

todo:
	gcc -g -o ventanas pente.c ventanalogo.c ventanainstrucciones.c funciones.c `pkg-config --cflags --libs gtk+-2.0`
