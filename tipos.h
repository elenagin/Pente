#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

typedef struct parametroVentana
{
  gint BanderaDeInicio;
  GtkWidget *VentanaLogo;
  GtkWidget *VentanaInstrucciones;
  GtkWidget *VentanaJuego;
}typeVentana, *typeVentanaPtr;

