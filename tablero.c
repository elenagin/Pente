#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

void StopTheApp(GtkWidget *ventana, gpointer data);

gint main ( gint argc, gchar *argv[])
{
  
  GtkWidget *ventana, *imagen;
  GdkPixbuf *pixbuf;
  
  gtk_init(&argc, &argv);
  
  ventana = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (ventana), "PENTE");
  gtk_window_set_position(GTK_WINDOW(ventana), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(ventana),320,320);
  gtk_container_border_width(GTK_CONTAINER(ventana),5);

  pixbuf = gdk_pixbuf_new_from_file_at_scale("logo.png", 500, 500, FALSE, NULL);
  imagen = gtk_image_new_from_pixbuf(pixbuf);

  
  gtk_container_add (GTK_CONTAINER (ventana), imagen);
  gtk_widget_show (imagen);
			       
  gtk_signal_connect(GTK_OBJECT(ventana),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  
  gtk_widget_show_all(ventana);

  
  gtk_main();

  return 0;

}

void StopTheApp(GtkWidget *ventana, gpointer data)
{
    gtk_main_quit();
}
