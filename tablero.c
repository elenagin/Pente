#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

void StopTheApp(GtkWidget *ventana, gpointer data);

gint main ( gint argc, gchar *argv[])
{
  
  GtkWidget *ventana;
  GtkWidget *MenuPrincipal;
  
  gtk_init(&argc, &argv);
  
  //crear ventana de texto
  ventana = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (ventana), "PENTE");
  gtk_window_set_default_size(GTK_WINDOW(ventana),500,500);
  gtk_container_border_width(GTK_CONTAINER(ventana),5);

  //crear menu princicpal
  MenuPrincipal = gtk_menu_bar_new ();
  
  gtk_signal_connect(GTK_OBJECT(ventana),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  gtk_signal_connect(GTK_OBJECT(MenuPrincipal),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  
  gtk_widget_show_all(ventana);
  gtk_widget_show_all(MenuPrincipal);
  
  gtk_main();

  return 0;

}

void StopTheApp(GtkWidget *ventana, gpointer data)
{
    gtk_main_quit();
}
