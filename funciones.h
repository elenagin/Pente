/*
 *@funciones.h
 *Este programa es el .h de funciones.c ya que son módulos.
 *Esto significa que incluye todas las funciones que no son static de
 *funciones.h
 *Se hizo lo de indef y endif (es un if) para que si ya se declaró esta
 *biblioteca, no se vuelva a declarar y haya problemas en el código
 *@Karina
 *@Elena
 *@01/05/2018
**/

#indef funcionesDEFINIDO

void CargarPartida(ptrWidgets Widgets, char *NombreArchivo);
void GuardarPartida(ptrWidgets Widgets, char *NombreArchivo);
gboolean Juez(GtkWidget *Widget, ptrWidgets Widgets);
gboolean DialogoCerrar(ptrWidgets Widgets);
gboolean Ganador(ptrWidgets Widgets, int a);
int Heuristica(ptrTablero Nodo,int i,int j);

#define funcionesDEFINIDO
#endif

