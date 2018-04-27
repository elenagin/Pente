#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "try.h"

gint main (gint argc, gchar **argv)
{


  /*1.INICIALIZAR EL AMBIENTE*/
  gtk_init(&argc, &argv);

  VentanaLogo(&argc, &argv);

  gtk_main();
  return 0;
}
