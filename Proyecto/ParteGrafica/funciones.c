#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "senales.h"
#include "funciones.h"


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
  const gchar *A,*B;
  gchar D[4];
  int i,j,x,y;
  int C;
  int a,b;
  int Come, Come1, Come2;
  int LN=0;
  int LB=0;
  GtkToolButton *Basura;
  gboolean Desicion;
  A=gtk_widget_get_name(Widget);
  sscanf(A,"%d,%d",&i,&j);
  a=Widgets->Nodo->Estados[i][j];
  if(a==1)
    b=2;
  else
    b=1;
  
  C=0;
  x=i-1;
  y=j;
  while(x>=0)
    {
      if(Widgets->Nodo->Estados[x][y]==b)
	{
	  C++;
	  x--;
	}//if
      else
	break;
      if(C==2)
	break;
    }//while
  if(x>=0)
    {
      if(C==2)
	{
	  if(Widgets->Nodo->Estados[x][y]==a)
	    {
	      if(a==1)
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->NComidas));
	      else
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->BComidas));
	      sscanf(B,"%d",&Come);
	      Come=Come+C;
	      sprintf(D,"%d",Come);
	      if(a==1)
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->NComidas),D);
	      else
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->BComidas),D);
	      for(C=0;C<2;C++)
		{
		  x++;
		  Widgets->Nodo->Estados[x][y]=0;
		  if(a==1)
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
		  else
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
		}//for
	    }//if
	}//if
    }//if
   
  C=0;
  x=i+1;
  y=j;
  while(x<20)
    {
      if(Widgets->Nodo->Estados[x][y]==b)
	{
	  C++;
	  x++;
	}//if
      else
	break;
      if(C==2)
	break;
    }//while
  if(x<20)
    {
      if(C==2)
	{
	  if(Widgets->Nodo->Estados[x][y]==a)
	    {
	      if(a==1)
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->NComidas));
	      else
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->BComidas));
	      sscanf(B,"%d",&Come);
	      Come=Come+C;
	      sprintf(D,"%d",Come);
	      if(a==1)
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->NComidas),D);
	      else
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->BComidas),D);
	      for(C=0;C<2;C++)
		{
		  x--;
		  Widgets->Nodo->Estados[x][y]=a;
		  if(a==1)
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/1.png");
		  else
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/2.png");
		}//for
	    }//if
	}//if
    }//if

  C=0;
  x=i;
  y=j-1;
  while(y>=0)
    {
      if(Widgets->Nodo->Estados[x][y]==b)
	{
	  C++;
	  y--;
	}//if
      else
	break;
      if(C==2)
	break;
    }//while
  if(y>=0)
    {
      if(C==2)
	{
	  if(Widgets->Nodo->Estados[x][y]==a)
	    {
	      if(a==1)
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->NComidas));
	      else
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->BComidas));
	      sscanf(B,"%d",&Come);
	      Come=Come+C;
	      sprintf(D,"%d",Come);
	      if(a==1)
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->NComidas),D);
	      else
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->BComidas),D);
	      for(C=0;C<2;C++)
		{
		  y++;
		  Widgets->Nodo->Estados[x][y]=0;
		  if(a==1)
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
		  else
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
		}//for
	    }//if
	}//if
    }//if
    
  C=0;
  x=i;
  y=j+1;
  while(y<20)
    {
      if(Widgets->Nodo->Estados[x][y]==b)
	{
	  C++;
	  y++;
	}//if
      else
	break;
      if(C==2)
	break;
    }//while
  if(y<20)
    {
      if(C==2)
	{
	  if(Widgets->Nodo->Estados[x][y]==a)
	    {
	      if(a==1)
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->NComidas));
	      else
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->BComidas));
	      sscanf(B,"%d",&Come);
	      Come=Come+C;
	      sprintf(D,"%d",Come);
	      if(a==1)
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->NComidas),D);
	      else
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->BComidas),D);
	      for(C=0;C<2;C++)
		{
		  y--;
		  Widgets->Nodo->Estados[x][y]=0;
		  if(a==1)
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
		  else
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
		}//for
	    }//if
	}//if
    }//if
    
  C=0;
  x=i-1;
  y=j-1;
  while(x>=0 && y>=0)
    {
      if(Widgets->Nodo->Estados[x][y]==b)
        {
	  C++;
	  x--;
	  y--;
        }//if
      else
	break;
      if(C==2)
	break;
    }//while
  if(x>=0 && y>=0)
    {
      if(C==2)
        {
	  if(Widgets->Nodo->Estados[x][y]==a)
            {
	      if(a==1)
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->NComidas));
	      else
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->BComidas));
	      sscanf(B,"%d",&Come);
	      Come=Come+C;
	      sprintf(D,"%d",Come);
	      if(a==1)
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->NComidas),D);
	      else
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->BComidas),D);
	      for(C=0;C<2;C++)
                {
		  x++;
		  y++;
		  Widgets->Nodo->Estados[x][y]=0;
		  if(a==1)
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
		  else
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
                }//for
            }//if
        }//if
    }//if
    
  C=0;
  x=i+1;
  y=j-1;
  while(x<20 && y>=0)
    {
      if(Widgets->Nodo->Estados[x][y]==b)
        {
	  C++;
	  x++;
	  y--;
        }//if
      else
	break;
      if(C==2)
	break;
    }//if
  if(x<20 && y>=0)
    {
      if(C==2)
        {
	  if(Widgets->Nodo->Estados[x][y]==a)
            {
	      if(a==1)
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->NComidas));
	      else
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->BComidas));
	      sscanf(B,"%d",&Come);
	      Come=Come+C;
	      sprintf(D,"%d",Come);
	      if(a==1)
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->NComidas),D);
	      else
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->BComidas),D);
	      for(C=0;C<2;C++)
                {
		  x--;
		  y++;
		  Widgets->Nodo->Estados[x][y]=0;
		  if(a==1)
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
		  else
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
                }//for
            }//if
        }//if
    }//if
  
  C=0;
  x=i+1;
  y=j+1;
  while(x<20 && y<20)
    {
      if(Widgets->Nodo->Estados[x][y]==b)
        {
	  C++;
	  x++;
	  y++;
        }//if
      else
	break;
      if(C==2)
	break;
    }//while
  if(x<20 && y<20)
    {
      if(C==2)
        {
	  if(Widgets->Nodo->Estados[x][y]==a)
            {
	      if(a==1)
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->NComidas));
	      else
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->BComidas));
	      sscanf(B,"%d",&Come);
	      Come=Come+C;
	      sprintf(D,"%d",Come);
	      if(a==1)
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->NComidas),D);
	      else
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->BComidas),D);
	      for(C=0;C<2;C++)
                {
		  x--;
		  y--;
		  Widgets->Nodo->Estados[x][y]=0;
		  if(a==1)
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
		  else
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
                }//for
            }//if
        }//if
    }//if
  
  C=0;
  x=i-1;
  y=j+1;
  while(x>=0 && y<20)
    {
      if(Widgets->Nodo->Estados[x][y]==b)
        {
	  C++;
	  x--;
	  y++;
        }//if
      else
	break;
      if(C==2)
	break;
    }//while
  if(x>=0 && y<20)
    {
      if(C==2)
        {
	  if(Widgets->Nodo->Estados[x][y]==a)
            {
	      if(a==1)
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->NComidas));
	      else
		B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->BComidas));
	      sscanf(B,"%d",&Come);
	      Come=Come+C;
	      sprintf(D,"%d",Come);
	      if(a==1)
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->NComidas),D);
	      else
		gtk_label_set_text(GTK_LABEL(Widgets->Nodo->BComidas),D);
	      for(C=0;C<2;C++)
                {
		  x++;
		  y--;
		  Widgets->Nodo->Estados[x][y]=0;
		  if(a==1)
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
		  else
		    gtk_image_set_from_file(GTK_IMAGE(Widgets->Nodo->Im[x][y]),"Archivos/0.png");
                }//for
            }//if
        }//if
    }//if

  A=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->NComidas));
  B=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->BComidas));
  sscanf(A,"%d",&Come1);
  sscanf(B,"%d",&Come2);
  if (Come1>=12 || Come2>=12)
    {
      if (Come1>=5)
	Desicion=Ganador(Widgets,1);
      else
	Desicion=Ganador(Widgets,2);
      if (Desicion==TRUE)
        {
	  TerminarPartida(Widget,Widgets);
	  Abrir_menu_juego(Basura,Widgets);
        }//if
      else
        {
	  gtk_widget_destroy(Widgets->Nodo3->VenP);
        }//else
      return TRUE;
    }//if
  else
    {
      for (x=0; x<20; x++)
        {
	  a=0;
	  b=0;
	  for (y=0; y<20; y++)
            {
	      if (Widgets->Nodo->Estados[x][y]==1)
		{
		  if (b>0)
		    b=0;
		  a++;
		}//if
	      if (Widgets->Nodo->Estados[x][y]==2)
		{
		  if (a>0)
		    a=0;
		  b++;
		}//if
	      if (Widgets->Nodo->Estados[x][y]==0)
                {
		  a=0;
		  b=0;
                }//if
	      if(a==4)
		LB++;
	      if(b==4)
		LN++;
	      if (a>=5 || b>=5 || LB==5 || LN==5)
                {
		  gboolean Desicion;
		  if (a>=5 || LB==5)
		    Desicion=Ganador(Widgets,1);
		  else
		    Desicion=Ganador(Widgets,2);
		  if (Desicion==TRUE)
                    {
		      TerminarPartida(Widget,Widgets);
		      Abrir_menu_juego(Basura,Widgets);
                    }//if
		  else
                    {
		      gtk_widget_destroy(Widgets->Nodo3->VenP);
                    }//else
		  return TRUE;
                }//if
            }//for
        }//for
        
      for (y=0; y<20; y++)
        {
	  a=0;
	  b=0;
	  for (x=0; x<20; x++)
            {
	      if (Widgets->Nodo->Estados[x][y]==1)
                {
		  if (b>0)
		    b=0;
		  a++;
                }//if
	      if (Widgets->Nodo->Estados[x][y]==2)
                {
		  if (a>0)
		    a=0;
		  b++;
                }//if
	      if (Widgets->Nodo->Estados[x][y]==0)
                {
		  a=0;
		  b=0;
                }//if
	      if(a==4)
		LB++;
	      if(b==4)
		LN++;
	      if (a>=5 || b>=5 || LB==5 || LN==5)
                {
		  gboolean Desicion;
		  if (a>=5 || LB==5)
		    Desicion=Ganador(Widgets,1);
		  else
		    Desicion=Ganador(Widgets,2);
		  if (Desicion==TRUE)
                    {
		      TerminarPartida(Widget,Widgets);
		      Abrir_menu_juego(Basura,Widgets);
                    }//if
		  else
                    {
		      gtk_widget_destroy(Widgets->Nodo3->VenP);
                    }//else
		  return TRUE;
                }//if
            }//for
        }//for
      a=0;
      b=0;
        
      for (j=19; j>=0; j--)
        {
	  x=0;
	  y=j;
	  while (y<20 && x<20)
            {
	      if (Widgets->Nodo->Estados[x][y]==1)
                {
		  if (b>0)
		    b=0;
		  a++;
                }//if
	      if (Widgets->Nodo->Estados[x][y]==2)
                {
		  if (a>0)
		    a=0;
		  b++;
                }//if
	      if (Widgets->Nodo->Estados[x][y]==0)
                {
		  a=0;
		  b=0;
                }//if
	      if(a==4)
		LB++;
	      if(b==4)
		LN++;
	      if (a>=5 || b>=5 || LB==5 || LN==5)
                {
		  gboolean Desicion;
		  if (a>=5 || LB==5)
		    Desicion=Ganador(Widgets,1);
		  else
		    Desicion=Ganador(Widgets,2);
		  if (Desicion==TRUE)
                    {
		      TerminarPartida(Widget,Widgets);
		      Abrir_menu_juego(Basura,Widgets);
                    }//if
		  else
                    {
		      gtk_widget_destroy(Widgets->Nodo3->VenP);
                    }//else
		  return TRUE;
                }//if
	      y++;
	      x++;
            }//while
        }//for
        
      for (i=1; i<20; i++)
        {
	  y=0;
	  x=i;
	  while (y<20 && x<20)
            {
	      if (Widgets->Nodo->Estados[x][y]==1)
                {
		  if (b>0)
		    b=0;
		  a++;
                }//if
	      if (Widgets->Nodo->Estados[x][y]==2)
                {
		  if (a>0)
		    a=0;
		  b++;
                }//if
	      if (Widgets->Nodo->Estados[x][y]==0)
                {
		  a=0;
		  b=0;
                }//if
	      if(a==4)
		LB++;
	      if(b==4)
		LN++;
	      if (a>=5 || b>=5 || LB==5 || LN==5)
                {
		  gboolean Desicion;
		  if (a>=5 || LB==5)
		    Desicion=Ganador(Widgets,1);
		  else
		    Desicion=Ganador(Widgets,2);
		  if (Desicion==TRUE)
                    {
		      TerminarPartida(Widget,Widgets);
		      Abrir_menu_juego(Basura,Widgets);
                    }//if
		  else
                    {
		      gtk_widget_destroy(Widgets->Nodo3->VenP);
                    }//else
		  return TRUE;
                }//if
	      y++;
	      x++;
            }//while
        }//for
        
      for (i=0; i<20; i++)
        {
	  y=0;
	  x=i;
	  while (y<20 && x>=0)
            {
	      if (Widgets->Nodo->Estados[x][y]==1)
                {
		  if (b>0)
		    b=0;
		  a++;
                }//if
	      if (Widgets->Nodo->Estados[x][y]==2)
                {
		  if (a>0)
		    a=0;
		  b++;
                }//if
	      if (Widgets->Nodo->Estados[x][y]==0)
                {
		  a=0;
		  b=0;
                }//if
	      if(a==4)
		LB++;
	      if(b==4)
		LN++;
	      if (a>=5 || b>=5 || LB==5 || LN==5)
                {
		  gboolean Desicion;
		  if (a>=5 || LB==5)
		    Desicion=Ganador(Widgets,1);
		  else
		    Desicion=Ganador(Widgets,2);
		  if (Desicion==TRUE)
                    {
		      TerminarPartida(Widget,Widgets);
		      Abrir_menu_juego(Basura,Widgets);
                    }//if
		  else
                    {
		      gtk_widget_destroy(Widgets->Nodo3->VenP);
                    }//else
		  return TRUE;
                }//if
	      y++;
	      x--;
            }//while
	}//for
      for (j=1; j<20; j++)
	{
	  x=0;
	  y=j;
	  while (y<20 && x>=0)
	    {
	      if (Widgets->Nodo->Estados[x][y]==1)
		{
		  if (b>0)
		    b=0;
		  a++;
		}//if
	      if (Widgets->Nodo->Estados[x][y]==2)
		{
		  if (a>0)
		    a=0;
		  b++;
		}//if
	      if (Widgets->Nodo->Estados[x][y]==0)
		{
		  a=0;
		  b=0;
		}//if
	      if(a==4)
		LB++;
	      if(b==4)
		LN++;
	      if (a>=5 || b>=5 || LB==5 || LN==5)
		{
		  gboolean Desicion;
		  if (a>=5 || LB==5)
		    Desicion=Ganador(Widgets,1);
		  else
		    Desicion=Ganador(Widgets,2);
		  if (Desicion==TRUE)
		    {
		      TerminarPartida(Widget,Widgets);
		      Abrir_menu_juego(Basura,Widgets);
		    }//if
		  else
		    {
		      gtk_widget_destroy(Widgets->Nodo3->VenP);
		    }//else
		  return TRUE;
		}//if
	      y++;
	      x--;
	    }//if
	}//while
    }//for
  for(i=0;i<20;i++)
    {
      for(j=0;j<20;j++)
	{
	  if(Widgets->Nodo->Estados[i][j]==0)
	    return FALSE;
	}//for
    }//for
  TerminarPartida(Widget,Widgets);
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
  Widgets->Nodo3->Des1=gtk_message_dialog_new(GTK_WINDOW(Widgets->Nodo3->VenP),
					      GTK_DIALOG_DESTROY_WITH_PARENT,
					      GTK_MESSAGE_QUESTION,
					      GTK_BUTTONS_YES_NO,
					      "¿Desea guardar la partida?");
  gtk_window_set_position(GTK_WINDOW(Widgets->Nodo3->Des1),GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(Widgets->Nodo3->Des1), "Partida en marcha");
  Desicion=gtk_dialog_run(GTK_DIALOG(Widgets->Nodo3->Des1));
  gtk_widget_destroy(Widgets->Nodo3->Des1);
  if(Desicion==GTK_RESPONSE_YES)
    {
      MenuGuardar(Widgets->Nodo3->VenP,Widgets);
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
  const gchar *Nombre, *Tiempo;
  gboolean Desicion;
  if (a==1)
    Nombre=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->EJ[0]));
  else
    Nombre=gtk_label_get_text(GTK_LABEL(Widgets->Nodo->EJ[1]));
  Widgets->Nodo3->Des2=gtk_message_dialog_new(GTK_WINDOW(Widgets->Nodo3->VenP),
					      GTK_DIALOG_DESTROY_WITH_PARENT,
					      GTK_MESSAGE_QUESTION,
					      GTK_BUTTONS_YES_NO,
					      "Ganador: %s\n¿Desea jugar otra vez?",Nombre);
  gtk_window_set_position(GTK_WINDOW(Widgets->Nodo3->Des2),GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(Widgets->Nodo3->Des2), "Ganador");
  Desicion=gtk_dialog_run(GTK_DIALOG(Widgets->Nodo3->Des2));
  gtk_widget_destroy(Widgets->Nodo3->Des2);
  if(Desicion==GTK_RESPONSE_YES)
    Desicion=TRUE;
  if(Desicion==GTK_RESPONSE_NO || Desicion==GTK_RESPONSE_DELETE_EVENT)
    Desicion=FALSE;
  return Desicion;
}//Ganador

void StopTheApp(GtkWidget *ventana, gpointer data)
{
  ptrVentanas ventanas=(tVentanas*)data;
  
  free(data);
  gtk_main_quit();
}

void Hide (GtkWidget *imagen, gpointer data)
{
  gtk_widget_hide(imagen);
}
