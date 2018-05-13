#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "funciones.h"
#include "ventanas.h"
#include "senales.h"

/********************************************************
 *Funcion Pulsado: se encarga de mandar a cada boton de *
 * la pantalla de juego la ficha correspondiente a cada *
 * jugador, en base a su respectivo turno, en cuaquier  *
 * modo de juego,jugador vs jugador o jugador vs maquina*
 *                                                      *
 *  Retorno:                                            *
 *  fichas en las casillas de la pantalla de juego      *
 ********************************************************/
void Pulsado(GtkWidget *Widget, gpointer data)
{
//Lo que sucede cuando se pulsa una casilla
}//pulsado
  

/********************************************************
 *Funcion Abrir_menu_juego: se encarga de mandar en     *
 * la pantalla, la ventana del menu de juego.           *
 *                                                      *
 *  Retorno:                                            *
 *   ventana del menu de juego                          *
 ********************************************************/
void Abrir_menu_juego (GtkToolButton *toolbutton, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  if(gtk_widget_get_window(Widgets->SVentanas->VenJ)==NULL)
    VentanaJuego(Widgets);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Widgets->SOpciones->BotonInicia[0]),TRUE);
  if(Widgets->STablero->Activo==0)
    gtk_widget_show_all(Widgets->SVentanas->VenJ);
}//Abrir_menu_juego

/********************************************************
 *Funcion MenuGuardar: se encarga de mandar en pantalla *
 * la ventana del menu  guardar.                        *
 *                                                      *
 *  Retorno:                                            *
 *   ventana del menu guardar                           *
 ********************************************************/
void MenuGuardar(GtkWidget *Widget, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  int l;
  if(Widgets->STablero->Activo!=0)
    {
      GtkFileChooser *chooser;
      GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
      gint res;
      
      Widgets->SVentanas->VenG= gtk_file_chooser_dialog_new ("Guardar Partida",
							 GTK_WINDOW(Widgets->SVentanas->VenP),
							 action,
							 ("_Cancelar"),
							 GTK_RESPONSE_CANCEL,
							 ("_Guardar"),
							 GTK_RESPONSE_ACCEPT,
							 NULL);
      chooser=GTK_FILE_CHOOSER (Widgets->SVentanas->VenG);
      gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
      res=gtk_dialog_run(GTK_DIALOG(Widgets->SVentanas->VenG));
      if (res==GTK_RESPONSE_ACCEPT)
	{
	  char *NombreArchivo;
	  char Extension[]=".pte";
	  NombreArchivo=gtk_file_chooser_get_filename (chooser);
	  l=strlen(NombreArchivo);
	  if(NombreArchivo[l-1]!='e' || NombreArchivo[l-2]!='t' || NombreArchivo[l-3]!='p' || NombreArchivo[l-4]!='.')
	    strcat(NombreArchivo,Extension);
	  GuardarPartida(Widgets,NombreArchivo);
	}//if
      gtk_widget_destroy (Widgets->SVentanas->VenG);
    }//if
  else
    {
      GtkWidget *dialog;
      dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets->SVentanas->VenP),
				      GTK_DIALOG_DESTROY_WITH_PARENT,
				      GTK_MESSAGE_ERROR,
				      GTK_BUTTONS_OK,
				      "Error: No hay partida que guardar");
      gtk_window_set_title(GTK_WINDOW(dialog), "Error");
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);      
    }//else
}//MenuGuardar



/********************************************************
 *Funcion MenuAbrir: se encarga de mandar en     *
 * la pantalla, la ventana del menu para cargar una     *
 * partida guardada                                     *
 *                                                      *
 *  Retorno:                                            *
 *  ventana del menu para cargar partida                *
 ********************************************************/
void MenuAbrir(GtkWidget *Widget, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  if(Widgets->STablero->Activo==0)
    {
      GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
      gint res;
      Widgets->SVentanas->VenA=gtk_file_chooser_dialog_new ("Cargar Partida",
							GTK_WINDOW(Widgets->SVentanas->VenP),
							action,
							("_Cancelar"),
							GTK_RESPONSE_CANCEL,
							("_Abrir"),
							GTK_RESPONSE_ACCEPT,
							NULL);
      
      res=gtk_dialog_run(GTK_DIALOG(Widgets->SVentanas->VenA));
      if(res==GTK_RESPONSE_ACCEPT)
	{
	  char *NombreArchivo;
	  int l;
	  GtkFileChooser *chooser = GTK_FILE_CHOOSER (Widgets->SVentanas->VenA);
	  NombreArchivo=gtk_file_chooser_get_filename(chooser);
	  gtk_widget_destroy (Widgets->SVentanas->VenA);
	  l=strlen(NombreArchivo);
	  if(NombreArchivo[l-1]=='e' && NombreArchivo[l-2]=='t' && NombreArchivo[l-3]=='p' && NombreArchivo[l-4]=='.')
	    CargarPartida(Widgets, NombreArchivo);
	  else
	    {
	      GtkWidget *dialog;
	      dialog = gtk_message_dialog_new(GTK_WINDOW(Widgets->SVentanas->VenP),
					      GTK_DIALOG_DESTROY_WITH_PARENT,
					      GTK_MESSAGE_ERROR,
					      GTK_BUTTONS_OK,
					      "Error: No se pudo cargar el archivo");
	      gtk_window_set_title(GTK_WINDOW(dialog), "Error");
	      gtk_dialog_run(GTK_DIALOG(dialog));
	      gtk_widget_destroy(dialog);
	    }//else
	}//if
      gtk_widget_destroy (Widgets->SVentanas->VenA);
    }//if
  else
    TerminarPartida(Widget,Widgets);
}//MenuAbrir


/********************************************************
 *Funcion Manual: se encarga de mandar en pantalla, la  *
 * ventana manual de juego, explicando de manera        *
 * detallada cada funcion u opcion de juego al jugador  *
 *                                                      *
 *  Retorno:                                            *
 *  ventana del manual de juego                         *
 ********************************************************/
void Manual(GtkWidget *Widget,gpointer data)  
{
ptrWidgets Widgets=(ptrWidgets)data;
  GdkPixbuf *pixbuf;
GtkWidget *picture;
   GtkWidget *imagen, *boton, *vbox;

  /* Create a Window. */
  Widgets->SVentanas->VenAy = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (Widgets->SVentanas->VenAy), "Ayuda");
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->VenAy), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(Widgets->SVentanas->VenAy),500,500);
  gtk_window_set_resizable(GTK_WINDOW(Widgets->SVentanas->VenAy), FALSE);
  gtk_container_border_width(GTK_CONTAINER(Widgets->SVentanas->VenAy),5);

  pixbuf = gdk_pixbuf_new_from_file_at_scale("Archivos/instrucciones.png", 500, 500, FALSE, NULL);
  imagen = gtk_image_new_from_pixbuf(pixbuf); 
  gtk_widget_show (imagen);

  gtk_container_add(GTK_CONTAINER(Widgets->SVentanas->VenAy), imagen);  
  gtk_widget_show_all(Widgets->SVentanas->VenAy);
}//manual


/********************************************************
 *Funcion on_button_clicked:se encarga de destruir la   *
 * ventana.                                             *
 *                                                      *
 *  Retorno:                                            *
 *  Finaliza la ventana                                 *
 ********************************************************/
void on_button_clicked(GtkWidget *Widget, gpointer data)
{
  gtk_widget_destroy(data);
}//on_button_clicked


/********************************************************
 *Funcion TerminarPartida: se encarga de mandar en      *
 * pantalla, la ventana en la que se pregunta al jugador*
 * si desea guardar la partida antes de finalizar el    *
 * juego, si acepta guardar, se manda a llamar la funcion
 * guardar, en caso contrario, se finaliza el juego     *
 *                                                      *
 *  Retorno:                                            *
 *  ventana de guardar partida para finalizar           *
 ********************************************************/
void TerminarPartida(GtkWidget *Widget, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  int i,j;
  if(Widgets->STablero->Activo!=0)
    {
      GtkWidget *Dialog2;
      int Desicion;
      Dialog2=gtk_message_dialog_new(GTK_WINDOW(Widgets->SVentanas->VenP),
				     GTK_DIALOG_DESTROY_WITH_PARENT,
				     GTK_MESSAGE_QUESTION,
				     GTK_BUTTONS_YES_NO,
				     "¿Desea guardar la partida actual?");
      gtk_window_set_position(GTK_WINDOW(Dialog2),GTK_WIN_POS_CENTER);
      gtk_window_set_title(GTK_WINDOW(Dialog2), "Partida en marcha");
      Desicion=gtk_dialog_run(GTK_DIALOG(Dialog2));
      gtk_widget_destroy(Dialog2);
      if(Desicion==GTK_RESPONSE_YES)
	MenuGuardar(Dialog2,Widgets);
      if(Desicion==GTK_RESPONSE_NO || Desicion==GTK_RESPONSE_YES)
        {
	  Widgets->STablero->Activo=0;
	  Widgets->STablero->Turno=0;
	  for(i=0;i<20;i++)
            {
	      for(j=0;j<20;j++)
                {
		  if(Widgets->STablero->Estados[i][j]!=0)
                    {
		      gtk_image_set_from_file(GTK_IMAGE(Widgets->STablero->Im[i][j]),"Archivos/0.png");
		      Widgets->STablero->Estados[i][j]=0;
                    }//if
                }//for
            }//for
	  gtk_label_set_text(GTK_LABEL(Widgets->STablero->EJ[0]),"Jugador1");
	  gtk_label_set_text(GTK_LABEL(Widgets->STablero->EJ[1]),"Jugador2");
      gtk_label_set_text(GTK_LABEL(Widgets->STablero->RComidas),"00");
      gtk_label_set_text(GTK_LABEL(Widgets->STablero->AComidas),"00");
	  if((strcasecmp(gtk_widget_get_name(Widget),"Abrir"))==0)
	    MenuAbrir(Dialog2,Widgets);
        }//if
    }//if
}//TerminarPartida


/********************************************************
 *Funcion IniciarPartida: se encarga de mandar en       *
 * pantalla, la ventana en la que se pregunta al jugador*
 * el modo de juego que desea comenzar, presentando las *
 *opciones de jugador vs jugador
 *                                                      *
 * En caso de elegir jugador vs jugador:                *
 * se pide que se introduzca los nombres de cada uno y  *
 * que se seleccione el jugador que va a iniciar        *
 *                                                      *
 *                                                      *
 *  Retorno:                                            *
 *  pantalla de iniciar partida                         *
 ********************************************************/
void IniciarPartida(GtkWidget *Widget, gpointer data)
{
 ptrWidgets Widgets=(ptrWidgets)data;
 Widgets->STablero->Inicia=1;
 limpiartablero();
}//IniciarPartida

/********************************************************
 *Funcion Esconder: se encarga de esconder la ventana   *
 * de juego, mandando a la terminal la cancelacion      *
 * de la partida.                                       *
 *                                                      *
 *  Retorno:                                            *
 *  Esconder la ventana del juego                       *
 ********************************************************/
void Esconder(GtkWidget *Widget, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  gtk_widget_hide(Widgets->SVentanas->VenJ);
}//esconder


/********************************************************
 *Funcion Acerca_de: se encarga de mandar en pantalla,  *
 * Los nombres de los desarrolladores del juego         *
 *                                                      *
 *  Retorno:                                            *
 *  ventana con los nombres de los desarrolladores      *
 ********************************************************/
void Acerca_de(GtkWidget *Widget, gpointer data)
{
  ptrVentanas SVentanas=(ptrVentanas)data;
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("Archivos/logo_peque.png", NULL);
  const gchar *Nombres[100]={"Mariana Martinez Kobeh","Elena Ginebra","Karina Almazán"};
  SVentanas->VenAd=gtk_about_dialog_new();
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(SVentanas->VenAd), "PENTE");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(SVentanas->VenAd), "1.0"); 
  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(SVentanas->VenAd), Nombres);
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(SVentanas->VenAd),"(c) Universidad IberoAmericana");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(SVentanas->VenAd), 
				"PENTE es la aplicacion que te permite jugar el juego de manera electronica");
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(SVentanas->VenAd), pixbuf);
  g_object_unref(pixbuf), pixbuf = NULL;
  gtk_window_set_position(GTK_WINDOW(SVentanas->VenAd),GTK_WIN_POS_CENTER);
  gtk_dialog_run(GTK_DIALOG (SVentanas->VenAd));
  gtk_widget_destroy(SVentanas->VenAd);
}//Acerca_de

/********************************************************
 *Funcion CerrarJuego: se encarga de finalizar el juego *
 * desde el icono de la barra de ayuda                  *
 *                                                      *
 *  Retorno:                                            *
 *  Finaliza el juego                                   *
 ********************************************************/
void CerrarJuego(GtkWidget *Widget, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  gboolean Desicion;
  if(Widgets->STablero->Activo!=0)
    {
      Desicion=DialogoCerrar(Widgets);
      if(Desicion!=-99)
	gtk_widget_destroy(Widgets->SVentanas->VenP);
    }//if
  else
    gtk_widget_destroy(Widgets->SVentanas->VenP);
}//CerrarJuego

/********************************************************
 *Funcion CerrarJuego1: se encarga de finalizar el juego*
 * desde el boton de cerrar ventana.                    *
 *                                                      *
 *  Retorno:                                            *
 *  Finaliza el juego                                   *
 ********************************************************/
gboolean CerrarJuego1(GtkWidget *Widget, GdkEvent *event, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  gboolean Desicion;
  if(Widgets->STablero->Activo!=0)
    {
      Desicion=DialogoCerrar(Widgets);
      if(Desicion==-99)
	return TRUE;
    }//if
  return FALSE;
}//CerrarJuego1

/********************************************************
 *Funcion CerrarJuego2: se encarga de finalizar el juego*
 * ddonde se juntan CerrarJuego y CerrarJuego1 para     *
 * destruir la ventana                                  *
 *                                                      *
 *  Retorno:                                            *
 *  Finaliza el juego                                   *
 ********************************************************/
void CerrarJuego2(GtkWidget *Widget, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  if(Widgets->STablero->Activo!=0)
    fclose(Widgets->STablero->Temporal);
  free(Widgets->STablero);
  free(Widgets->SOpciones);
  free(Widgets->SVentanas);
  free(Widgets);
  gtk_main_quit();
}//CerrarJuego2


/********************************************************
 *Funcion RecorreHistorial: se encarga de recorrer el   *
 * historial de juego                                   *
 *                                                      *
 *  Retorno:                                            *
 *  Historial el juego                                  *
 ********************************************************/
void RecorreHistorial(GtkWidget *Widget, gpointer data)
{

}//RecorreHistorial
