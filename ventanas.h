/*
 *@ventanas.h
 *Este programa es el .h de ventanas.c ya que son módulos.
 *Esto significa que incluye todas las funciones que no son static de
 *ventanas.h
 *Se hizo lo de indef y endif (es un if) para que si ya se declaro esta
 *biblioteca, no se vuelva a declarar y haya problemas en el código
 *@Elena
 *@Karina
 *@01/05/2018
**/

#ifndef ventanasDEFINIDO


void VentanaPrincipal(GtkWidget *widget, gpointer data);
void VentanaJuego(ptrWidgets Widgets);
void VentanaBienvenida(ptrWidgets Widgets);
void VentanaInstrucciones(GtkWidget *widget, gpointer data);
void VentanaGanador(ptrWidgets Widgets);
void VentanaEmpate(ptrWidgets Widgets);



#define ventanasDEFINIDO
#endif
