#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "senales.h"
#include "funciones.h"
#include "ventanas.h"

/********************************************************
 * Funcion CargarPartida: Se carga el historial de una  *
 * partida de un juego previamente guardado, manteniendo*
 * todos los cambios del juego,en cuestion de posiciones*
 * marcadas por cada jugador                            *
 *                                                      *
 *  Retorno:                                            *
 *  Partida guardada en Pantalla del juego              *
 ********************************************************/
void CargarPartida(ptrWidgets Widgets, char *NombreArchivo)
{

}//CargarPartida


/********************************************************
 * Funcion GuardarPartida: Se encarga de guardar el     *
 * historial de una partida de un juego, manteniendo    *
 * todos los cambios realizados,en cuestion de posiciones*
 * marcadas por cada jugador                            *
 *                                                      *
 *  Retorno:                                            *
 *  Partida guardada en un archivo tipo ".pte"          *
 ********************************************************/

void GuardarPartida(ptrWidgets Widgets, char *NombreArchivo)
{

}//GuardarPArtida


/********************************************************
 * Funcion Juez: se encarga de hacer que la computadora *
 * funja como juez en la partida de un jugador contra   *
 * otro jugador, de manera que pueda detectar al jugador*
 * ganador, al mismo tiempo que manda a pantalla el     *
 * nombre del jugador ganador.                          *
 * los jugadores podran comerse fichas entre si.        *
 *                                                      *
 *  Retorno:                                            *
 *  mensaje en pantalla de aviso sobre quien fue el     *
 *  ganador del juego, ya sea jugador 1 o jugador 2     *
 ********************************************************/
gboolean Juez(GtkWidget *Widget, ptrWidgets Widgets)
{
  }//Juez



/********************************************************
 *Funcion DialogoCerrar:se encarga de mandar en pantalla*
 * una ventana, para preguntar al jugador si desea      *
 * guardar la partida, dependiendo la desicion, se      *
 * ejecuta la opcion guardar partida, o se cierra el    *
 * juego si no se desea guardar.                        *
 *                                                      *
 *  Retorno:                                            *
 *  ventana de opcion guardar o no guardar partida      *
 ********************************************************/
gboolean DialogoCerrar(ptrWidgets Widgets)
{
  gboolean Desicion;
  Widgets->SVentanas->Des1=gtk_message_dialog_new(GTK_WINDOW(Widgets->SVentanas->VenP),
					      GTK_DIALOG_DESTROY_WITH_PARENT,
					      GTK_MESSAGE_QUESTION,
					      GTK_BUTTONS_YES_NO,
					      "¿Desea guardar la partida?");
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->Des1),GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(Widgets->SVentanas->Des1), "Partida en marcha");
  Desicion=gtk_dialog_run(GTK_DIALOG(Widgets->SVentanas->Des1));
  gtk_widget_destroy(Widgets->SVentanas->Des1);
  if(Desicion==GTK_RESPONSE_YES)
    {
      MenuGuardar(Widgets->SVentanas->VenP,Widgets);
      Desicion=TRUE;
    }//if
  if(Desicion==GTK_RESPONSE_NO)
    Desicion=FALSE;
  if(Desicion==GTK_RESPONSE_DELETE_EVENT)
    Desicion=-99;
  return Desicion;
}//DialogoCerrar


/********************************************************
 *Funcion Ganador:es la funcion donde se manda una      *
 * ventana con el nombre del jugador, y otra donde se   *
 * le da la opcion de guardar o no la partida al jugador*
 *                                                      *
 *  Retorno:                                            *
 *  mensaje en pantalla del nombre del ganador del juego*
 ********************************************************/
gboolean Ganador(ptrWidgets Widgets, int a)
{
  const gchar *Nombre;
  gboolean Desicion;
  if (a==1)
    Nombre=gtk_label_get_text(GTK_LABEL(Widgets->STablero->EJ[0]));
  else
    Nombre=gtk_label_get_text(GTK_LABEL(Widgets->STablero->EJ[1]));
  Widgets->SVentanas->Des2=gtk_message_dialog_new(GTK_WINDOW(Widgets->SVentanas->VenP),
					      GTK_DIALOG_DESTROY_WITH_PARENT,
					      GTK_MESSAGE_QUESTION,
					      GTK_BUTTONS_YES_NO,
					      "Ganador: %s\n¿Desea jugar otra vez?",Nombre);
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->Des2),GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(Widgets->SVentanas->Des2), "Ganador");
  Desicion=gtk_dialog_run(GTK_DIALOG(Widgets->SVentanas->Des2));
  gtk_widget_destroy(Widgets->SVentanas->Des2);
  if(Desicion==GTK_RESPONSE_YES)
    Desicion=TRUE;
  if(Desicion==GTK_RESPONSE_NO || Desicion==GTK_RESPONSE_DELETE_EVENT)
    Desicion=FALSE;
  return Desicion;
}//Ganador
