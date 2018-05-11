void CargarPartida(ptrWidgets Widgets, char *NombreArchivo);
void GuardarPartida(ptrWidgets Widgets, char *NombreArchivo);
gboolean Juez(GtkWidget *Widget, ptrWidgets Widgets);
gboolean DialogoCerrar(ptrWidgets Widgets);
gboolean Ganador(ptrWidgets Widgets, int a);
int Heuristica(ptrTablero Nodo,int i,int j);

void VentanaLogo (ptrWidgets Widgets);
void StopTheApp(GtkWidget *ventana, gpointer data);
void Hide(GtkWidget *imagen, gpointer data);
void VentanaInstrucciones(GtkWidget *widget, gpointer data);
void VentanaNuevoAnterior(GtkWidget *widget, gpointer data);
