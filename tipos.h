#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

typedef struct parametroventana
{
  GtkWidget *VentanaLogo;
  GtkWidget *VentanaInstrucciones;
  GtkWidget *VentanaJuego;
}typeVentana;

void VentanaLogo (gint *argc, gchar ***argv);
void StopTheApp(GtkWidget *ventana, gpointer data);
void Hide(GtkWidget *imagen, gpointer data);
void Hide2(GtkWidget *imagen, gpointer data);
void VentanaInstrucciones(GtkWidget *ventana, gpointer data);
