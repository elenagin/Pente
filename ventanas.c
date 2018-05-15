/*****************************************************************
 *
 * Archivo:	ventanas.c
 * Autores:
 * Descripcion: Codigo Fuente para implementar el programa
 *		        de Pente en base a funciones de GTK+
 *              desarrollando un ambiente grafico para que los
 *              usuarios puedan jugar
 * Uso: Iniciar el programa, abrir el menu, agregar Widgets
 *      inicializar el ambiente.
 * Fecha:
 *
 ****************************************************************/

/*Archivos de Inclusion*/
#include <gtk/gtk.h>
#include <stdlib.h>
#include "tipos.h"
#include "senales.h"
#include "funciones.h"
#include "ventanas.h"
#include "tablerocodigo.h"
#include "listatablero.h"

/****************************************************
 * Funcion VentanaPrincipal:Se establecen todos los *
 * widgets para poder abrir la ventana principal    *
 * para empezar a jugar el juego de pente.          *
 *                                                  *
 *  Retorno:                                        *
 *  Ventana en Pantalla                             *
 ****************************************************/ 

void VentanaPrincipal(GtkWidget *widget, gpointer data)
{
  /*Variables a utilizar*/
  GtkWidget *CV, *CH,*CPartida;
  int i,j;
  gchar NombreBoton[6];
  GtkWidget *MenuB,*MenuI1,*MenuI2,*Menu1,*Menu2,*MenuIJ,*MenuIG,*MenuIR,*MenuIT,*MenuIM,*MenuIAd;
  GtkWidget *Tool;
  GtkToolItem *TJ, *TG, *TA, *Sep1, *TAy, *TAd, *Sep2;
  GtkToolItem *TS, *ToolNext, *ToolStop, *Separador3;
  GtkWidget *Tabla;
  GdkColor Tablero={0, 0xe000, 0xe000, 0xe000};/*Declara un color*/
  GtkWidget *CHPartida[3], *IVenB, *Im2, *ImagenTurnoActual;
  ptrWidgets Widgets=(ptrWidgets)data;
  gtk_widget_hide(Widgets->SVentanas->VenI);

  //Cajas
  CV=gtk_vbox_new(FALSE,0);//Creamos caja vertical
  CH=gtk_hbox_new(FALSE,0);//Creamos caja Horizontal
  CPartida=gtk_vbox_new(FALSE, 10);//Creamos caja partida
  Tabla=gtk_table_new(20,20,TRUE);//Creamos tabla

  //Ventana
  Widgets->SVentanas->VenP=gtk_window_new(GTK_WINDOW_TOPLEVEL);//Creamos ventana principal, esta se encuentra en una estructura
  gtk_window_set_resizable(GTK_WINDOW(Widgets->SVentanas->VenP),FALSE);//fijamos atributo de la ventana 
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->VenP),GTK_WIN_POS_CENTER);//fijamos posicion de la ventana
  gtk_window_set_title(GTK_WINDOW (Widgets->SVentanas->VenP), "Pente");
  g_signal_connect(Widgets->SVentanas->VenP,"delete_event",G_CALLBACK(CerrarJuego1), Widgets);
  g_signal_connect(Widgets->SVentanas->VenP,"destroy",G_CALLBACK(CerrarJuego2), Widgets);
  gtk_container_add(GTK_CONTAINER(Widgets->SVentanas->VenP),CV);//definimos jerarquia, quien contiene a quien
  
  //Barra de menu
  MenuB=gtk_menu_bar_new();//creamos barra de menu
  MenuI1=gtk_menu_item_new_with_mnemonic("_Juego");//creacion de item
  MenuI2=gtk_menu_item_new_with_mnemonic("_Ayuda");//creacion de item ayuda
  Menu1=gtk_menu_new();//creacion de menu 1
  Menu2=gtk_menu_new();//creacion de menu2
  MenuIJ=gtk_menu_item_new_with_mnemonic("J_ugar"); //creacion de item en menu
  g_signal_connect(MenuIJ,"activate",G_CALLBACK(Abrir_menu_juego),Widgets);//llamada a funcion para poder abrir funcion abrir_menu_juego
  MenuIG=gtk_menu_item_new_with_mnemonic("_Guardar");//creacion de item guardar
  g_signal_connect(MenuIG,"activate",G_CALLBACK(MenuGuardar),Widgets);//llamada a funcion para poder guardar el juego
  MenuIR=gtk_menu_item_new_with_mnemonic("_Restaurar");//creacion de item Restaurar
  gtk_widget_set_name(MenuIR,"Abrir");//Fijamos nombre al item de la linea anterior
  g_signal_connect(MenuIR,"activate",G_CALLBACK(MenuAbrir),Widgets);//llamada a funcion para poder abrir el juego
  MenuIT=gtk_menu_item_new_with_mnemonic("_Terminar la partida");//El Menu tendra el texto
  g_signal_connect(MenuIT,"activate",G_CALLBACK(TerminarPartida),Widgets);//llamada a la funcion terminar partida
  MenuIM=gtk_menu_item_new_with_mnemonic("_Manual");//el menu tiene el texto manual
  g_signal_connect(MenuIM,"activate",G_CALLBACK(Manual),Widgets);//llamada a la funcion Manual
  MenuIAd=gtk_menu_item_new_with_mnemonic("A_cerca de");//Creacion de Item  Acerca de
  g_signal_connect(MenuIAd,"activate",G_CALLBACK(Acerca_de),Widgets->SVentanas);//llamada a la funcion acerca de
  
  /*Definimos jerarquia para poder meter los items en los menus*/
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu1), MenuIJ);
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu1), MenuIG);
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu1), MenuIR);
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu1), MenuIT);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuI1), Menu1);
  gtk_menu_bar_append(GTK_MENU_BAR(MenuB), MenuI1);
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu2), MenuIM);
  gtk_menu_shell_append(GTK_MENU_SHELL(Menu2), MenuIAd);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(MenuI2), Menu2);
  gtk_menu_bar_append(GTK_MENU_BAR(MenuB), MenuI2);
  gtk_box_pack_start (GTK_BOX(CV),MenuB,FALSE,TRUE,0);//Agregamos la barra de menu a la caja vertical
  
  //Barra de accesos directos
  Tool=gtk_toolbar_new();//definimos tool bar
  TJ=gtk_tool_button_new_from_stock(GTK_STOCK_MEDIA_PLAY);//creacion de icono de jugar
  g_signal_connect(TJ,"clicked",G_CALLBACK(Abrir_menu_juego),Widgets);//llamada a la funcion para abrir juego
  TG=gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);//creacion de icono guardar
  g_signal_connect(TG,"clicked",G_CALLBACK(MenuGuardar),Widgets);//llamada a la funcion para guardar juego
  TA=gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);//creacion de icono abrir
  gtk_widget_set_name(GTK_WIDGET(TA),"Abrir");//Damos nombre al icono anterior
  g_signal_connect(TA,"clicked",G_CALLBACK(MenuAbrir),Widgets);//llamada a la funcion para abrir juego
  Sep1=gtk_separator_tool_item_new();//creamos separador
  TAy=gtk_tool_button_new_from_stock(GTK_STOCK_HELP);//creacion del boton ayuda
  g_signal_connect(TAy,"clicked",G_CALLBACK(Manual),Widgets);//llamada a la funcion Manual
  TAd=gtk_tool_button_new_from_stock(GTK_STOCK_ABOUT);//creacion del icono acerca de
  g_signal_connect(TAd,"clicked",G_CALLBACK(Acerca_de),Widgets->SVentanas);//llamada a la funcion Acerca de
  Sep2=gtk_separator_tool_item_new();//creamos un segundo separador
  ToolNext=gtk_tool_button_new_from_stock(GTK_STOCK_MEDIA_NEXT);//creación del icono salir
  g_signal_connect(ToolNext,"clicked",G_CALLBACK(RecorreHistorial),Widgets);//llamada a la funcion Salir
  ToolStop=gtk_tool_button_new_from_stock(GTK_STOCK_MEDIA_STOP);//creación del icono salir
  g_signal_connect(ToolStop,"clicked",G_CALLBACK(SeguirAMano),Widgets);//llamada a la funcion Salir
  Separador3=gtk_separator_tool_item_new();//creamos un tercer separador
  TS=gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);//cracion del icono salir
  g_signal_connect(TS,"clicked",G_CALLBACK(CerrarJuego),Widgets);//llamada a la funcion Salir

  
  /*Definimos la jerarquia para meter los iconos en la TOOLBAR*/
  gtk_toolbar_set_style(GTK_TOOLBAR(Tool), GTK_TOOLBAR_BOTH);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TJ, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TG, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TA, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), Sep1, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), ToolNext, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), ToolStop, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), Sep2, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TAy, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TAd, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), Separador3, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TS, -1);
  gtk_box_pack_start (GTK_BOX(CV),Tool,FALSE,TRUE,0);//incluimos la toolbar en la caja vertical
  
  //Tablero de juego e inicializacion de datos
  gtk_box_pack_start_defaults (GTK_BOX(CV),CH);//Caja de tablero y cuadro
  Widgets->STablero->Activo=0;//Significa si hay una partida en juego
  Widgets->STablero->Turno=0;//Significa el turno correspondiente
  Tabla=gtk_table_new(20,20,TRUE);//creacion de tabla
  for(i=0;i<20;i++)
    {
      for(j=0;j<20;j++)//inicializamos la imagen poniéndola vacia
	{
	  Widgets->STablero->Estados[i][j]=0;
	  Widgets->STablero->B[i][j]=gtk_button_new();//nuevo boton
	  Widgets->STablero->Im[i][j]=gtk_image_new();//nueva imagen
	  gtk_button_set_image(GTK_BUTTON(Widgets->STablero->B[i][j]),Widgets->STablero->Im[i][j]);
	  gtk_image_set_from_file(GTK_IMAGE(Widgets->STablero->Im[i][j]),"Archivos/0.png");
	  sprintf(NombreBoton,"%d,%d",i,j);//modificar una cadena que sera nuestro nombre de boton
	  gtk_widget_set_name(Widgets->STablero->B[i][j],NombreBoton);//dar nombre al boton
	  gtk_widget_modify_bg(Widgets->STablero->B[i][j],GTK_STATE_NORMAL,&Tablero);
	  gtk_table_attach_defaults(GTK_TABLE(Tabla),Widgets->STablero->B[i][j],i,i+1,j,j+1);
	  g_signal_connect(Widgets->STablero->B[i][j],"clicked",G_CALLBACK(Pulsado), Widgets);//llamada a la funcion dando click
	}//for
    }//for
  gtk_box_pack_start_defaults (GTK_BOX(CH),Tabla);//agregamos tabla a la caja vertical

  //Cuadro de la partida
  CPartida=gtk_vbox_new(FALSE,0);//Creamos caja vertical que sera nuestro cuadro de partida
  gtk_box_pack_start (GTK_BOX(CH),CPartida,FALSE,FALSE,0);//definimos jerarquia

  CHPartida[0]=gtk_hbox_new(FALSE,10);//creacion de caja horizontal
  gtk_box_pack_start_defaults (GTK_BOX(CPartida),CHPartida[0]);//caja horizontal en caja vertical
  ImagenTurnoActual=gtk_image_new();
  gtk_image_set_from_file(GTK_IMAGE(ImagenTurnoActual), "Archivos/1.png");//creamos imagen
  Widgets->STablero->BotonTurnoActual=gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(Widgets->STablero->BotonTurnoActual),ImagenTurnoActual);
  Widgets->STablero->EJ[0]=gtk_label_new("Turno actual:\nJugador 1");//creamos label
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[0]),Widgets->STablero->BotonTurnoActual);//agregamos imagen a la caja horizontal
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[0]),Widgets->STablero->EJ[0]);//agregamos label en caja horizontal
  
  CHPartida[1]=gtk_hbox_new(FALSE,10);//creacion de caja horizontal
  gtk_box_pack_start_defaults (GTK_BOX(CPartida),CHPartida[1]);//caja horizontal en caja vertical
  Widgets->STablero->Num1Comidas=0;
  Widgets->STablero->Comidas1=gtk_label_new("00");//creacion de label que indicara las jugadas o comidas
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[1]),Widgets->STablero->Comidas1);//incluimos en la caja vertical el label
  IVenB=gtk_image_new_from_file("Archivos/1.png");//creamos imagen
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[1]),IVenB);//agregamos imagen en la caja horizontal
  Widgets->STablero->EJ[1]=gtk_label_new("Jugador 1");//creamos label
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[1]),Widgets->STablero->EJ[1]);//agregamos label en caja horizontal

  CHPartida[2]=gtk_hbox_new(FALSE,10);//creacion de segunda caja horizontal
  gtk_box_pack_start_defaults (GTK_BOX(CPartida),CHPartida[2]);//agregamos caja horizontal en caja de partida
  Widgets->STablero->Num2Comidas=0;
  Widgets->STablero->Comidas2=gtk_label_new("00");//jugadas del jugador 2
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[2]),Widgets->STablero->Comidas2);//agregamos comidas a la caja horizontal
  Im2=gtk_image_new_from_file("Archivos/2.png");//creamos imagen para jugador 2
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[2]),Im2);//agregamos imagen a la caja horizontal
  Widgets->STablero->EJ[2]=gtk_label_new("Jugador 2");//creamos label
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[2]),Widgets->STablero->EJ[2]);//agregamos label en la caja horizontal

  gtk_widget_show_all(Widgets->SVentanas->VenP);  
}//VentanaPrincipal


/****************************************************
 * Funcion VentanaJuego:Se establecen todos los     *
 * widgets para poder abrir ventana de juego        *
 * para empezar a jugar el juego de pente.          *
 *                                                  *
 *  Retorno:                                        *
 *  Ventana en Pantalla                             *
 ****************************************************/ 
void VentanaJuego(ptrWidgets Widgets)
{

  /*Variables que usaremos*/
  GtkWidget *CVJ;
  int i;
  const gchar *NombreBoton2;
  GtkWidget *EtiquetasJ[4], *BotonJOK, *BotonJCancel;

  //Cajas
  CVJ=gtk_vbox_new(FALSE,5);//nueva caja vertical
  for(i=0;i<4;i++)//creacion de cajas horizontales
    Widgets->SOpciones->CHJ[i]=gtk_hbox_new(FALSE,3);

  //Ventana
  Widgets->SVentanas->VenJ=gtk_window_new(GTK_WINDOW_TOPLEVEL);//creacion de ventana principal
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->VenJ),GTK_WIN_POS_CENTER);//definicion de la posicion
  gtk_window_set_title(GTK_WINDOW(Widgets->SVentanas->VenJ),"Modo de juego");//damos nombre a la ventana
  gtk_container_add(GTK_CONTAINER(Widgets->SVentanas->VenJ),CVJ);//agregamos la caja vertical de jugador a la ventana
  gtk_window_set_resizable(GTK_WINDOW(Widgets->SVentanas->VenJ),FALSE);//definimos tamaño de ventana
  
  //Nombre Jugador1
  gtk_box_pack_start_defaults (GTK_BOX(CVJ),Widgets->SOpciones->CHJ[0]);
  EtiquetasJ[1]=gtk_label_new("Jugador1:");//nueva etiqueta
  Widgets->SOpciones->Entry[0]=gtk_entry_new();//nuevo entry
  gtk_entry_set_max_length(GTK_ENTRY(Widgets->SOpciones->Entry[0]),30);//tamaño de entry
  gtk_box_pack_start_defaults (GTK_BOX(Widgets->SOpciones->CHJ[0]),EtiquetasJ[1]);//agregamos etiqueta a caja horizontal
  gtk_box_pack_start_defaults (GTK_BOX(Widgets->SOpciones->CHJ[0]),Widgets->SOpciones->Entry[0]);//agregamos entry a caja horizontal

  //Nombre Jugador2
  gtk_box_pack_start_defaults (GTK_BOX(CVJ),Widgets->SOpciones->CHJ[1]);
  EtiquetasJ[2]=gtk_label_new("Jugador2");//nueva etiqueta
  Widgets->SOpciones->Entry[1]=gtk_entry_new();//nuevo entry
  gtk_entry_set_max_length(GTK_ENTRY(Widgets->SOpciones->Entry[1]),30);//tamaño de entry
  gtk_box_pack_start_defaults (GTK_BOX(Widgets->SOpciones->CHJ[1]),EtiquetasJ[2]);//agregamos etiqueta a caja horizontal
  gtk_box_pack_start_defaults (GTK_BOX(Widgets->SOpciones->CHJ[1]),Widgets->SOpciones->Entry[1]);//agregamos entry a caja horizontal
  
  //Orden de tiro
  EtiquetasJ[3]=gtk_label_new("Nota: El jugador 1 siempre\n empieza el juego.");//nuevo label
  gtk_box_pack_start_defaults (GTK_BOX(CVJ),EtiquetasJ[3]);//agregamos label a caja vertical

  //Botones
  BotonJOK=gtk_button_new_from_stock(GTK_STOCK_OK);//nuevo boton OK
  g_signal_connect(BotonJOK,"clicked",G_CALLBACK(IniciarPartida),Widgets);//llamada a la funcion iniciar partida
  BotonJCancel=gtk_button_new_from_stock(GTK_STOCK_CANCEL);//nuevo boton CANCEL
  g_signal_connect(BotonJCancel,"clicked",G_CALLBACK(Esconder),Widgets);//llamada a la funcion esconder
  
  gtk_box_pack_start_defaults (GTK_BOX(CVJ),Widgets->SOpciones->CHJ[2]);//agregamos caja horizontal a caja verticalJ
  gtk_box_pack_start_defaults (GTK_BOX(Widgets->SOpciones->CHJ[2]),BotonJOK);//boton OK  a caja horizontal 
  gtk_box_pack_start_defaults (GTK_BOX(Widgets->SOpciones->CHJ[2]),BotonJCancel);//boton cancel a caja horizontal
}//VentanaJuego



/****************************************************
 * Funcion VentanaBienvenida:Se establecen todos lo *
 * widgets para poder abrir ventana de Bienvenida   *
 * para empezar a jugar el juego de pente.          *
 *                                                  *
 *  Retorno:                                        *
 *  Ventana en Pantalla                             *
 ****************************************************/
void VentanaBienvenida(ptrWidgets Widgets)
{
  GtkWidget *imagen, *boton, *vbox;
  GdkPixbuf *pixbuf; 

  vbox = gtk_vbox_new(TRUE,5);
  Widgets->SVentanas->VenB = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (Widgets->SVentanas->VenB), "Pente");
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->VenB), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(Widgets->SVentanas->VenB),500,500);
  gtk_window_set_resizable(GTK_WINDOW(Widgets->SVentanas->VenB), FALSE);
  gtk_container_border_width(GTK_CONTAINER(Widgets->SVentanas->VenB),5);

  pixbuf = gdk_pixbuf_new_from_file_at_scale("Archivos/logo.png", 500, 500, FALSE, NULL);
  imagen = gtk_image_new_from_pixbuf(pixbuf);
  boton= gtk_button_new();
  
  gtk_widget_show (imagen);

  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(VentanaInstrucciones), Widgets);
  gtk_signal_connect(GTK_OBJECT(Widgets->SVentanas->VenB),"destroy",GTK_SIGNAL_FUNC(CerrarJuego2), Widgets);
  gtk_container_add(GTK_CONTAINER(Widgets->SVentanas->VenB), boton);
  gtk_container_add(GTK_CONTAINER(boton), vbox);
  gtk_container_add(GTK_CONTAINER(vbox), GTK_WIDGET(imagen));
  
  gtk_widget_show_all(Widgets->SVentanas->VenB);

}//VentanaBienvenida

void VentanaInstrucciones(GtkWidget *widget, gpointer data)
{
  GtkWidget *imagen, *boton, *vbox;
  GdkPixbuf *pixbuf; 
  ptrWidgets Widgets=(ptrWidgets)data;
  
  gtk_widget_hide(Widgets->SVentanas->VenB);
  vbox = gtk_vbox_new(TRUE,5);

  Widgets->SVentanas->VenI = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (Widgets->SVentanas->VenI), "Pente");
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->VenI), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(Widgets->SVentanas->VenI),500,500);
  gtk_window_set_resizable(GTK_WINDOW(Widgets->SVentanas->VenI), FALSE);
  gtk_container_border_width(GTK_CONTAINER(Widgets->SVentanas->VenI),5);

  pixbuf = gdk_pixbuf_new_from_file_at_scale("Archivos/instrucciones.png", 500, 500, FALSE, NULL);
  imagen = gtk_image_new_from_pixbuf(pixbuf);
  boton= gtk_button_new();
  
  gtk_widget_show (imagen);

  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(VentanaPrincipal), Widgets);
  gtk_signal_connect(GTK_OBJECT(Widgets->SVentanas->VenI),"destroy",GTK_SIGNAL_FUNC(CerrarJuego2), Widgets);
  gtk_container_add(GTK_CONTAINER(Widgets->SVentanas->VenI), boton);
  gtk_container_add(GTK_CONTAINER(boton), vbox);
  gtk_container_add(GTK_CONTAINER(vbox), GTK_WIDGET(imagen));
  
  gtk_widget_show_all(Widgets->SVentanas->VenI);
}//VentanaInstrucciones

void VentanaGanador(ptrWidgets Widgets)
{
  GtkWidget *boton, *vbox, *label;

  vbox= gtk_vbox_new(TRUE,5);
  Widgets->SVentanas->VenGan = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (Widgets->SVentanas->VenGan), "Ganador");
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->VenGan), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(Widgets->SVentanas->VenGan),500,500);
  gtk_window_set_resizable(GTK_WINDOW(Widgets->SVentanas->VenGan), FALSE);
  gtk_container_border_width(GTK_CONTAINER(Widgets->SVentanas->VenGan),5);
  if (Widgets->STablero->Turno==1)
    {
      label= gtk_label_new ("¡Felicidades  Jugador 1!\n                GANASTE");
      Widgets->STablero->Turno=2;
    }
  else if (Widgets->STablero->Turno==2)
    {
    label= gtk_label_new ("¡Felicidades  Jugador 2!\n                GANASTE");
    Widgets->STablero->Turno=1;
    }
  boton=gtk_button_new_from_stock(GTK_STOCK_OK);
  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(TerminarPartida), Widgets);
  gtk_signal_connect(GTK_OBJECT(Widgets->SVentanas->VenGan),"destroy",GTK_SIGNAL_FUNC(Esconder3), Widgets); 
  gtk_container_add(GTK_CONTAINER(vbox), label);
  gtk_container_add(GTK_CONTAINER(vbox), boton);
  gtk_container_add(GTK_CONTAINER(Widgets->SVentanas->VenGan), vbox);
  gtk_widget_show_all(Widgets->SVentanas->VenGan);
}
