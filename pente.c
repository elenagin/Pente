#include <stdio.h>
#include <gtk/gtk.h>

#include "tipos.h"
#include "funciones.h"
#include "senales.h"

gint main (gint argc, gchar **argv)
{
  ptrWidgets Widgets;
    
  gtk_init(&argc, &argv);
  
  VentanaLogo(&argc, &argv);
  Widgets=(ptrWidgets)malloc(sizeof(tWidgets));/*Creamos nuestro paquete de Widgets*/
  Widgets->Nodo3=(ptrVentanas)malloc(sizeof(tVentanas));
  Widgets->Nodo=(ptrTablero)malloc(sizeof(tTablero));
  Widgets->Nodo2=(ptrOpciones)malloc(sizeof(tOpciones));//creacion de widgets
 
  gtk_main();
  return 0;
}
