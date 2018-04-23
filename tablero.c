#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

void StopTheApp(GtkWidget *window, gpointer data);

gint main ( gint argc, gchar *argv[])
{
  
  GtkWidget *window;
  
  gtk_init(&argc, &argv);
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL); //crear ventana de texto
  gtk_window_set_title(GTK_WINDOW (window), "PENTE");
  gtk_window_set_default_size(GTK_WINDOW(window),500,500);
  gtk_container_border_width(GTK_CONTAINER(window),5);
  
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  
  gtk_widget_show_all(window);
  
  gtk_main();

  return 0;

}

void StopTheApp(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}
