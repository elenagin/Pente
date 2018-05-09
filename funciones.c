#include <gtk/gtk.h>
#include "tipos.h"
#include "funciones.h"

void StopTheApp(GtkWidget *ventana, gpointer data)
{
  free(data);
  gtk_main_quit();
}

void Hide (GtkWidget *imagen, gpointer data)
{
  gtk_widget_hide(imagen);
}


