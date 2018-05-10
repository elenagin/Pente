#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "funciones.h"

void VentanaLogo (gint *argc, gchar ***argv)
{
  GtkWidget *imagen, *boton, *vbox;
  GdkPixbuf *pixbuf;
  typeVentanaPtr ventanas; 

  ventanas = malloc(sizeof(typeVentana));
  vbox = gtk_vbox_new(TRUE,5);
  ventanas->VentanaLogo = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (ventanas->VentanaLogo), "Pente");
  gtk_window_set_position(GTK_WINDOW(ventanas->VentanaLogo), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(ventanas->VentanaLogo),500,500);
    gtk_window_set_resizable(GTK_WINDOW(ventanas->VentanaLogo), FALSE);
  gtk_container_border_width(GTK_CONTAINER(ventanas->VentanaLogo),5);

  pixbuf = gdk_pixbuf_new_from_file_at_scale("logo.png", 500, 500, FALSE, NULL);
  imagen = gtk_image_new_from_pixbuf(pixbuf);
  boton= gtk_button_new();
  
  gtk_widget_show (imagen);

  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(VentanaInstrucciones), ventanas);
  gtk_signal_connect(GTK_OBJECT(ventanas->VentanaLogo),"destroy",GTK_SIGNAL_FUNC(StopTheApp),ventanas);
  gtk_container_add(GTK_CONTAINER(ventanas->VentanaLogo), boton);
  gtk_container_add(GTK_CONTAINER(boton), vbox);
  gtk_container_add(GTK_CONTAINER(vbox), GTK_WIDGET(imagen));
  
  gtk_widget_show_all(ventanas->VentanaLogo); 
}

void VentanaInstrucciones(GtkWidget *widget, gpointer data)
{ 
  GtkWidget *imagen, *boton, *hbox;
  GdkPixbuf *pixbuf;
  typeVentanaPtr ventanas=(typeVentana*)data;
  
  gtk_widget_hide_all(ventanas->VentanaLogo);
  hbox= gtk_hbox_new (TRUE, 5);
  ventanas->VentanaInstrucciones = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (ventanas->VentanaInstrucciones), "Pente");
  gtk_window_set_position(GTK_WINDOW(ventanas->VentanaInstrucciones), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(ventanas->VentanaInstrucciones),500,500);
  gtk_container_border_width(GTK_CONTAINER(ventanas->VentanaInstrucciones),5);
  
  pixbuf = gdk_pixbuf_new_from_file_at_scale("instrucciones.png", 500, 500, FALSE, NULL);
  imagen = gtk_image_new_from_pixbuf(pixbuf);
  boton= gtk_button_new();  
  gtk_widget_show (imagen);

  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(VentanaNuevoAnterior), ventanas);
  gtk_signal_connect(GTK_OBJECT(ventanas->VentanaInstrucciones),"destroy",GTK_SIGNAL_FUNC(StopTheApp), ventanas);
  
  gtk_container_add(GTK_CONTAINER(ventanas->VentanaInstrucciones), boton);
  gtk_container_add(GTK_CONTAINER(boton), hbox);
  gtk_container_add(GTK_CONTAINER(hbox), GTK_WIDGET(imagen));
  
  gtk_widget_show_all(ventanas->VentanaInstrucciones); 
}

void VentanaNuevoAnterior(GtkWidget *widget, gpointer data)
{ 
  GtkWidget *vbox, *hbox, *boton1, *boton2;
  typeVentana *ventanas=(typeVentana*)data;
  
  gtk_widget_hide_all(ventanas->VentanaInstrucciones);

  ventanas->VentanaNuevoAnterior = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (ventanas->VentanaNuevoAnterior), "Pente");
  gtk_window_set_position(GTK_WINDOW(ventanas->VentanaNuevoAnterior), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(ventanas->VentanaNuevoAnterior),500,500);
  gtk_container_border_width(GTK_CONTAINER(ventanas->VentanaNuevoAnterior),5);
  
  vbox= gtk_vbox_new (TRUE, 5);
  hbox= gtk_hbox_new (TRUE, 5);

  boton1 = gtk_button_new_with_label("Nuevo Juego");
  gtk_signal_connect(GTK_OBJECT(boton1),"clicked",GTK_SIGNAL_FUNC(Hide), NULL);
  gtk_widget_show(boton1);
  
  boton2 = gtk_button_new_with_label("Partida Anterior");
  gtk_signal_connect(GTK_OBJECT(boton2),"clicked",GTK_SIGNAL_FUNC(Hide), NULL);
  gtk_widget_show(boton2);
  
  gtk_box_pack_start(GTK_BOX(vbox),boton1,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(vbox),boton2,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(hbox),vbox,TRUE,TRUE,5);
  gtk_widget_show_all(hbox);

  gtk_signal_connect(GTK_OBJECT(ventanas->VentanaNuevoAnterior),"destroy",GTK_SIGNAL_FUNC(StopTheApp), ventanas);
  gtk_container_add(GTK_CONTAINER(ventanas->VentanaNuevoAnterior), hbox);
  
  gtk_widget_show_all(ventanas->VentanaNuevoAnterior); 
}
