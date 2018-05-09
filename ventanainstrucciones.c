#include <gtk/gtk.h>
#include <stdlib.h>
#include "tipos.h"
#include "funciones.h"

void VentanaInstrucciones(GtkWidget *widget, gpointer data)
{ 
  GtkWidget *imagen, *boton, *hbox;
  GdkPixbuf *pixbuf;
  typeVentana *ventanas=(typeVentana*)data;
  
  gtk_widget_hide(ventanas->VentanaLogo);
  hbox= gtk_hbox_new (TRUE, 5);
  ventanas->VentanaInstrucciones = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (ventanas->VentanaInstrucciones), "Pente");
  gtk_window_set_position(GTK_WINDOW(ventanas->VentanaInstrucciones), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(ventanas->VentanaInstrucciones),320,320);
  gtk_container_border_width(GTK_CONTAINER(ventanas->VentanaInstrucciones),5);
  
  pixbuf = gdk_pixbuf_new_from_file_at_scale("instrucciones.png", 500, 500, FALSE, NULL);
  imagen = gtk_image_new_from_pixbuf(pixbuf);
  boton= gtk_button_new();
  
  gtk_widget_show (imagen);

  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(Hide), NULL);
  gtk_signal_connect(GTK_OBJECT(ventanas->VentanaInstrucciones),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  
  gtk_container_add(GTK_CONTAINER(ventanas->VentanaInstrucciones), boton);
  gtk_container_add(GTK_CONTAINER(boton), hbox);
  gtk_container_add(GTK_CONTAINER(hbox), GTK_WIDGET(imagen));
  
  gtk_widget_show_all(ventanas->VentanaInstrucciones); 
}
