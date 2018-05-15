#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tipos.h"
#include "senales.h"
#include "funciones.h"
#include "ventanas.h"
#include "listatablero.h"
#include "tablerocodigo.h"

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
  int num;

  Widgets->STablero->BanderaNext=1;
  limpiartablero();
  Widgets->STablero->Inicia=1;
  Widgets->STablero->Turno=1;
  num = LeerLista(NombreArchivo);
  Widgets->STablero->Comidas1=gtk_label_new("00");//creacion de label que indicara las jugadas o comidas
  Widgets->STablero->Comidas2=gtk_label_new("00");//creacion de label que indicara las jugadas o comidas
  
  Widgets->STablero->Num1Comidas=0;//creacion de label que indicara las jugadas o comidas
  Widgets->STablero->Num2Comidas=0;//creacion de label que indicara las jugadas o comidas
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
  GuardarLista(NombreArchivo);

}//GuardarPArtida


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
  gboolean Decision;
  Widgets->SVentanas->Des1=gtk_message_dialog_new(GTK_WINDOW(Widgets->SVentanas->VenP),
					      GTK_DIALOG_DESTROY_WITH_PARENT,
					      GTK_MESSAGE_QUESTION,
					      GTK_BUTTONS_YES_NO,
					      "¿Desea guardar la partida?");
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->Des1),GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(Widgets->SVentanas->Des1), "Partida en marcha");
  Decision=gtk_dialog_run(GTK_DIALOG(Widgets->SVentanas->Des1));
  gtk_widget_hide(Widgets->SVentanas->Des1);
  if(Decision==GTK_RESPONSE_YES)
    {
      MenuGuardar(Widgets->SVentanas->VenP,Widgets);
      Decision=TRUE;
    }//if
  if(Decision==GTK_RESPONSE_NO)
    Decision=FALSE;
  if(Decision==GTK_RESPONSE_DELETE_EVENT)
    Decision=-99;
  return Decision;
}//DialogoCerrar
