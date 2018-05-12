/*****************************************************************
 *
 * Archivo:	pente.c
 * Autores:
 * Descripcion: Codigo Fuente para implementar el programa
 *		        de Pente en base a funciones de GTK+
 *              desarrollando un ambiente grafico para que los
 *              usuarios puedan jugar
 * Uso: Iniciar el programa.
 * Fecha:
 *
 ****************************************************************/

/*Archivos de Inclusion*/
#include <gtk/gtk.h>
#include <stdlib.h>
#include "tipos.h"
#include "senales.h"
#include "funciones.h"

/*Funcion principal*/
int main(int argc, char *argv[])
{
  ptrWidgets Widgets;/*Apuntada a estructura*/
  /*Inicializamos el ambiente*/
  gtk_init(&argc,&argv);
  Widgets=(ptrWidgets)malloc(sizeof(tWidgets));/*Creamos nuestro paquete de Widgets*/
  Widgets->SVentanas=(ptrVentanas)malloc(sizeof(tVentanas));
  Widgets->STablero=(ptrTablero)malloc(sizeof(tTablero));
  Widgets->SOpciones=(ptrOpciones)malloc(sizeof(tOpciones));//creacion de widgets
  VentanaJuego(Widgets);//Se crea la ventana de nueva partida
  VentanaBienvenida(Widgets);//Se crea la ventana de presentacion y se espera a que se le de aceptar
  gtk_main();/*funcion inicio iterada*/
}//main
