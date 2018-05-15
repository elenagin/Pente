/**
* @file funciones.c
* @brief Este programa tiene tres funciones, una inicializa 
* el tablero cuando se abre una jugada pasada, otra guarda 
* la jugada y la otra abre una ventana de diálogo cuando se 
* pica el botón de quit.
* @author Karina Almazán, Elena Ginebra
* @date 01/05/2018 
*/

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

/**
 *Función CargarPartida: Se carga el historial de una  
 * partida de un juego previamente guardado, manteniendo
 * todos los cambios del juego,en cuestion de posiciones
 * marcadas por cada jugador. También limpia el teclado.
 *@Elena
 *@Param ptrWidget Widgets  Pointer a estructura para saber
 * turno 
 *@Param char *NombreArchivo  Nombre del archivo que se desea abrir
 */
void CargarPartida(ptrWidgets Widgets, char *NombreArchivo)
{
  Widgets->STablero->BanderaNext=1;
  limpiartablero();
  Widgets->STablero->Inicia=1;
  Widgets->STablero->Turno=1;
  LeerLista(NombreArchivo);  
  Widgets->STablero->Num1Comidas=0;//pone numero de comidas en cero
  Widgets->STablero->Num2Comidas=0;//pone numero de comidas en cero
}//CargarPartida


/**
 *Función GuardarPartida:  Se encarga de guardar el     
 * historial de una partida de un juego, manteniendo    
 * todos los cambios realizados,en cuestion de posiciones
 * marcadas por cada jugador  
 *@Elena
 *@Param ptrWidget Widgets  
 *@Param char *NombreArchivo  Nombre del archivo que se 
 * desea guardar, será tipo ".pte"
 */
void GuardarPartida(ptrWidgets Widgets, char *NombreArchivo)
{
  GuardarLista(NombreArchivo);

}//GuardarPArtida


/********************************************************
 *Funcion DialogoCerrar:.                        *
 *                                                      *
 *  Retorno:                                            *
 *  ventana de opcion guardar o no guardar partida      *
 ********************************************************/
/**
 *Función DialogoCerrar:  Se encarga de mandar en pantalla
 * una ventana, para preguntar al jugador si desea      
 * guardar la partida, dependiendo la desicion, se      
 * ejecuta la opcion guardar partida, o se cierra el    
 * juego si no se desea guardar.
 *@Karina
 *@Param ptrWidget Widgets  
 */
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
