/**
 *@pente.c
 *Codigo Fuente para implementar el programa de Pente en base 
 *a funciones de GTK+ desarrollando un ambiente grafico 
 *para que los usuarios puedan jugar.
 *@Elena
 *@09/05/2018
 */

/*Archivos de Inclusion*/
#include <gtk/gtk.h>
#include <stdlib.h>
#include "tipos.h"
#include "senales.h"
#include "funciones.h"
#include "ventanas.h"
#include "listatablero.h"
#include "tablerocodigo.h"

/**
 *Esta función es el main del programa, manda a llamar las ventanas necesarias
 *para que el usuario pueda empezar a jugar el juego.
 *Regresa fin de programa.
 *@Mariana
 *@Param int argc
 *@Param char *argv
 *@return int 
 */
int main(int argc, char *argv[])
{
  ptrWidgets Widgets;/*Apuntada a estructura*/
  /*Inicializamos el ambiente*/
  gtk_init(&argc,&argv);
  Widgets=(ptrWidgets)malloc(sizeof(tWidgets));/*Creamos nuestro paquete de Widgets*/
  Widgets->SVentanas=(ptrVentanas)malloc(sizeof(tVentanas));
  Widgets->STablero=(ptrTablero)malloc(sizeof(tTablero));
  Widgets->SOpciones=(ptrOpciones)malloc(sizeof(tOpciones));//creacion de widgets
  VentanaBienvenida(Widgets);//Se crea la ventana de presentacion y se espera a que se le de aceptar
  VentanaJuego(Widgets);//Se crea la ventana de nueva partida
  gtk_main();/*funcion inicio iterada*/
}//main
