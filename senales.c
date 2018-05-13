/**
* @file senales.c *
* @brief Este programa permite capturar las señales que recibe el 
* programa gráfico y realiza las funciones necesarias para lo que
* piden dichos widgets gráficos.
* @author Karina Almazán, Elena Ginebra
* @date 01/05/2018 */

/**
 *ARCHIVOS DE INCLUSIÓN*/
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

/**
*MÓDULOS INCLUÍDOS*/
#include "tipos.h"
#include "funciones.h"
#include "ventanas.h"
#include "senales.h"
#include "tablerocodigo.h"
#include "listatablero.h"

/**
 *Función Pulsado: coloca la ficha en el tablero, manda a cada boton
 *toda la informacción que necesita saber, por ejemplo, turno,
 *si el juego se encuentra activo o no, si el botón se encuentra 
 *libre o no, el color (jugador) de la ficha, etc.
 *Regresa fichas en las casillas de la pantalla de juego
 *Regresa ventana de error en caso de ser necesario
 *Regresa turno actual
 *Regresa puntaje, incluyendo si come fichas ó gana/pierde.
 *@Elena
 *@Param GtkWidget *Widget  El botón a colocar
 *@Param gpointer data  Apuntador a todas las estructuras
 */
void Pulsado(GtkWidget *Widget, gpointer data)
{
  GtkWidget *imagen, *vbox, *boton, *label;
  int i, j, x;
  const gchar *text, *text2;
  ptrWidgets Widgets=(ptrWidgets)data;
  
  text = gtk_widget_get_name(Widget);
  sscanf(text,"%d,%d",&i,&j);
  if ((Widgets->STablero->Activo==1)&&(Widgets->STablero->Estados[i][j]==0))
    {
      if (Widgets->STablero->Turno==1)
	{
	  x= ponerficha(1,i,j,0);
	  g_print("%d ", x);
	  imagen=gtk_image_new();
	  gtk_button_set_image(GTK_BUTTON(Widget),imagen);
	  gtk_image_set_from_file(GTK_IMAGE(imagen),"Archivos/1.png");
	  Widgets->STablero->Estados[i][j]=1;
	  Widgets->STablero->Turno=2;
	  gtk_label_set_text(GTK_LABEL(Widgets->STablero->EJ[0]), "Turno actual:\nJugador 2");
	}
      else if (Widgets->STablero->Turno==2)
	{
	  x= ponerficha(2,i,j,0);
	  g_print("%d ", x);
	  imagen=gtk_image_new();
	  gtk_button_set_image(GTK_BUTTON(Widget),imagen);
	  gtk_image_set_from_file(GTK_IMAGE(imagen),"Archivos/2.png");
	  Widgets->STablero->Estados[i][j]=2;
	  Widgets->STablero->Turno=1;
	  gtk_label_set_text(GTK_LABEL(Widgets->STablero->EJ[0]), "Turno actual:\nJugador 1");
	}      
    }
  else
    {
      vbox= gtk_vbox_new(TRUE,5);
      Widgets->SVentanas->Error = gtk_window_new (GTK_WINDOW_TOPLEVEL);
      gtk_window_set_title(GTK_WINDOW (Widgets->SVentanas->Error), "Error");
      gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->Error), GTK_WIN_POS_CENTER);
      gtk_window_set_resizable(GTK_WINDOW(Widgets->SVentanas->Error), FALSE);
      gtk_container_border_width(GTK_CONTAINER(Widgets->SVentanas->Error),5);
      if (Widgets->STablero->Estados[i][j]!=0)
	label= gtk_label_new ("Error: Casilla ocupada.");
      if (Widgets->STablero->Activo==0)
	label= gtk_label_new ("Error: Para empezar a jugar\npresione botón \" Play \" ó \" Jugar \".");
      boton=gtk_button_new_from_stock(GTK_STOCK_OK); 
      gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(Esconder2), Widgets);
      gtk_signal_connect(GTK_OBJECT(Widgets->SVentanas->Error),"destroy",GTK_SIGNAL_FUNC(Esconder2), Widgets); 
      gtk_container_add(GTK_CONTAINER(vbox), label);
      gtk_container_add(GTK_CONTAINER(vbox), boton);
      gtk_container_add(GTK_CONTAINER(Widgets->SVentanas->Error), vbox);
      gtk_widget_show_all(Widgets->SVentanas->Error);
    }
}//pulsado


/**
 *Función Abrir_menu_juego:  se encarga de mandar en
 *la pantalla, la ventana del menu de juego.
 *Regresa ventana del menu del juego
 *@Karina, @Elena
 *@Param GtkToolButton *toolbutton  El botón seleccionado
 *@Param gpointer data  Apuntador a todas las estructuras
 */
void Abrir_menu_juego (GtkToolButton *toolbutton, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  if(gtk_widget_get_window(Widgets->SVentanas->VenJ)==NULL)
    VentanaJuego(Widgets);
  if(Widgets->STablero->Activo==0)
    gtk_widget_show_all(Widgets->SVentanas->VenJ);
}//Abrir_menu_juego

/**
 *Función MenuGuardar:  se encarga de mandar en
 *la pantalla, la ventana del menu guardar.
 *Regresa ventana del menu del juego
 *@Karina
 *@Param GtkWidget *Widget  El botón seleccionado del menú.
 *@Param gpointer data  Apuntador a todas las estructuras.
 */
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


/**
 *Función MenuAbrir:  se encarga de mandar en la
 *pantalla, la ventana del menu para cargar una partida
 *guardar.
 *Regresa ventana del menu del juego
 *@Karina
 *@Param GtkWidget *Widget El botón seleccionado del menú
 *@Param gpointer data  Apuntador a todas las estructuras
 */
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


/**
 *Función Manual: se encarga de mandar en la pantalla,
 *la ventana de ayuda del juego, explicando de manera detallada
 *cómo jugar apropiadamente el juego al usuario.
 *Regresa ventana en pantalla
 *@Karina
 *@Param GtkWidget *Widget El botón seleccionado del menú
 *@Param gpointer data  Apuntador a todas las estructuras
 */
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


/**
 *Función on_button_clicked: se encarga de destruir la ventana.
 *Regresa destrucción de ventana.
 *@Karina, @Elena
 *@Param GtkWidget *Widget  El botón seleccionado
 *@Param gpointer data  Apuntador a todas las estructuras
 */
void on_button_clicked(GtkWidget *Widget, gpointer data)
{
  gtk_widget_destroy(data);
}//on_button_clicked

/**
 *Función TerminarPartida: se encarga de mandar en la pantalla
 *la última ventana del juego donde puede guardar la partida
 *antes de finalizar el juego, si acepta guardar, se manda
 *a llamar la función guardar, en caso contrario, se finaliza
 *el juego y se borran los datos necesarios.
 *@Karina
 *@Param GtkWidget *Widget El botón seleccionado del menú
 *@Param gpointer data  Apuntador a todas las estructuras
 */
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

/**
 *Función IniciarPartida: se encarga de inicializar
 *todo el juego, ya sea en ceros el tablero del juego ó
 *los turnos de los jugadores.
 *Regresa valores inicializados del juego.
 *@Elena
 *@Param GtkWidget *Widget El botón seleccionado del menú
 *@Param gpointer data  Apuntador a todas las estructuras
 */
void IniciarPartida(GtkWidget *Widget, gpointer data)
{
 ptrWidgets Widgets=(ptrWidgets)data;
 int i, j;
 
 limpiartablero();
 Widgets->STablero->Inicia=1;
 Widgets->STablero->Activo=1; //SEGMENTATION AL APRETAR CANCELAR Ó QUIT
 Widgets->STablero->Turno=1;
 Widgets->SOpciones->Jugadores[1]=gtk_entry_get_text(GTK_ENTRY(Widgets->SOpciones->Entry[0])); //guardamos nombre del jugador
 Widgets->SOpciones->Jugadores[2]=gtk_entry_get_text(GTK_ENTRY(Widgets->SOpciones->Entry[1])); //guardamos nombre del jugador
 gtk_label_set_text(GTK_LABEL(Widgets->STablero->EJ[1]),Widgets->SOpciones->Jugadores[1]);
 gtk_label_set_text(GTK_LABEL(Widgets->STablero->EJ[2]),Widgets->SOpciones->Jugadores[2]);
 gtk_widget_hide(Widgets->SVentanas->VenJ);
}//IniciarPartida

/**
 *Función Esconder: se encarga de esconder la ventana
 *de juego.
 *Regresa destrucción de ventana juego.
 *@Karina
 *@Param GtkWidget *Widget El botón apuntador
 *@Param gpointer data  Apuntador a todas las estructuras
 */
void Esconder(GtkWidget *Widget, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  gtk_widget_hide(Widgets->SVentanas->VenJ);
}//esconder

/**
 *Función Esconder2: se encarga de esconder de la pantalla
 *la ventana que marcar errores del juego.
 *Regresa destrucción de ventana error.
 *@Elena
 *@Param GtkWidget *Widget El botón apuntador
 *@Param gpointer data  Apuntador a todas las estructuras
 */
void Esconder2(GtkWidget *Widget, gpointer data)
{
  ptrWidgets Widgets=(ptrWidgets)data;
  gtk_widget_hide(Widgets->SVentanas->Error);
}//esconder2


/**
 *Función Acerca_de: se encarga de mandar en la pantalla
 *Los nombres de los desarrolladores del juego Pente.
 *Regresa ventana con los nombres de los desarrolladores  .
 *@Karina
 *@Param GtkWidget *Widget El botón apuntador
 *@Param gpointer data  Apuntador a todas las estructuras
 */
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

/**
 *Función CerrarJuego: se encarga de finalizar el juego
 *desde la barra de ayuda.
 *Regresa finalización del juego.
 *@Karina
 *@Param GtkWidget *Widget El botón apuntador
 *@Param gpointer data  Apuntador a todas las estructuras
 */
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

/**
 *Función CerrarJuego1: se encarga de finalizar el juego
 *desde el botono para cerrar la ventana del juego.
 *Regresa finalización del juego.
 *@Karina
 *@Param GtkWidget *Widget El botón apuntador
 *@Param gpointer data  Apuntador a todas las estructuras
 */
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


/**
 *Función CerrarJuego2: se encarga de finalizar el juego
 *para destruir la ventana donde se junta con CerrarJuego
 *y CerrarJuego1.
 *@Karina
 *@Param GtkWidget *Widget El botón apuntador
 *@Param gpointer data  Apuntador a todas las estructuras
 */
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

/**
 *Función RecorreHistorial: se encarga de recorrer todo el juego
 *Regresa el recorrido de todo el historial del juego
 *@
 *@Param GtkWidget *Widget El botón apuntador
 *@Param gpointer data  Apuntador a todas las estructuras
 */
void RecorreHistorial(GtkWidget *Widget, gpointer data)
{

}//RecorreHistorial
