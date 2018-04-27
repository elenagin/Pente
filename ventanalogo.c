#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"

void VentanaLogo (gint *argc, gchar ***argv)
{
  
  GtkWidget *imagen, *boton;
  GdkPixbuf *pixbuf;
  typeVentana ventanas; 
  
  ventanas.VentanaLogo = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (ventanas.VentanaLogo), "Pente");
  gtk_window_set_position(GTK_WINDOW(ventanas.VentanaLogo), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(ventanas.VentanaLogo),320,320);
  gtk_container_border_width(GTK_CONTAINER(ventanas.VentanaLogo),5);

  pixbuf = gdk_pixbuf_new_from_file_at_scale("logo.png", 500, 500, FALSE, NULL);
  imagen = gtk_image_new_from_pixbuf(pixbuf);
  boton= gtk_button_new();
  
  gtk_widget_show (imagen);

  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(Hide2), &ventanas);
  gtk_signal_connect(GTK_OBJECT(ventanas.VentanaLogo),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);

  gtk_container_add(GTK_CONTAINER(ventanas.VentanaLogo), boton);
  gtk_container_add(GTK_CONTAINER(boton), imagen);

  gtk_widget_show_all(ventanas.VentanaLogo); 
}

void StopTheApp(GtkWidget *ventana, gpointer data)
{
  gtk_main_quit();
}

void Hide2(GtkWidget *imagen, gpointer data)
{
  gtk_widget_hide(imagen);
  VentanaInstrucciones(imagen, &data);
}
