#include <stdio.h>
#include <gtk/gtk.h>

#include "tipos.h"
#include "funciones.h"

gint main (gint argc, gchar **argv)
{
  gtk_init(&argc, &argv);
  
  VentanaLogo(&argc, &argv);

  gtk_main();
  return 0;
}
