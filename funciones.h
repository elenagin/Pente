void VentanaLogo (gint *argc, gchar ***argv);
void StopTheApp(GtkWidget *ventana, gpointer data);
void Hide(GtkWidget *imagen, gpointer data);
void VentanaInstrucciones(GtkWidget *widget, gpointer data);
void VentanaNuevoAnterior(GtkWidget *widget, gpointer data);

//newstuff from here
void CargarPartida(ptrWidgets Widgets, char *NombreArchivo);
void GuardarPartida(ptrWidgets Widgets, char *NombreArchivo);
gboolean Juez(GtkWidget *Widget, ptrWidgets Widgets);
gboolean DialogoCerrar(ptrWidgets Widgets);
gboolean Ganador(ptrWidgets Widgets, int a);
int Heuristica(ptrTablero Nodo,int i,int j);
void VentanaJuego(GtkWidget *widget, gpointer data);
