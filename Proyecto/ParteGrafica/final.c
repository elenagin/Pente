/*****************************************************************
 *
 * Archivo:	final.c
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

/*Funciones Prototipo*/
void VentanaPrincipal(ptrWidgets Widgets);
void VentanaJuego(ptrWidgets Widgets);
void VentanaBienvenida(ptrWidgets Widgets);

/*Funcion principal*/
int main(int argc, char *argv[])
{
  ptrWidgets Widgets;/*Apuntada a estructura*/
  /*Inicializamos el ambiente*/
  gtk_init(&argc,&argv);
  Widgets=(ptrWidgets)malloc(sizeof(tWidgets));/*Creamos nuestro paquete de Widgets*/
  Widgets->SVentanas=(ptrVentanas)malloc(sizeof(tVentanas));
  Widgets->STablero=(ptrTablero)malloc(sizeof(tTablero));
  Widgets->SOpciones=(ptrOpciones)malloc(sizeof(tOpciones));//creacion de widgets

  //VentanaBienvenida(Widgets);
  VentanaPrincipal(Widgets);//Se crea la ventana principal
  VentanaJuego(Widgets);//Se crea la ventana de nueva partida
  VentanaBienvenida(Widgets);//Se crea la ventana de presentacion y se espera a que se le de aceptar
  gtk_widget_show_all(Widgets->Nodo3->VentanaLogo);//Mostramos todos los widgests incluidos en la ventana
  gtk_main();/*funcion inicio iterada*/
  
}//main

/****************************************************
 * Funcion VentanaPrincipal:Se establecen todos los *
 * widgets para poder abrir la ventana principal    *
 * para empezar a jugar el juego de pente.          *
 *                                                  *
 *  Retorno:                                        *
 *  Ventana en Pantalla                             *
 ****************************************************/ 

void VentanaPrincipal(ptrWidgets Widgets)
{
  /*Variables a utilizar*/
  GtkWidget *CV, *CH,*CPartida;
  int i,j;
  gchar NombreBoton[6];
  GtkWidget *MenuB,*MenuI1,*MenuI2,*Menu1,*Menu2,*MenuIJ,*MenuIG,*MenuIR,*MenuIT,*MenuIM,*MenuIAd;
  GtkWidget *Tool;
  GtkToolItem *TJ, *TG, *TA, *Sep1, *TAy, *TAd, *Sep2, *TS;
  GtkWidget *Tabla;
  GdkColor Tablero={0,0xF200,0xEB00,0xD500};/*Declara un color*/
  GtkWidget *CHPartida[3], *Im1, *Im2;

  /*2. Creamos widgets*/
  //Cajas
  CV=gtk_vbox_new(FALSE,0);//Creamos caja vertical
  CH=gtk_hbox_new(FALSE,0);//Creamos caja Horizontal
  CPartida=gtk_vbox_new(FALSE, 10);//Creamos caja partida
  Tabla=gtk_table_new(20,20,TRUE);//Creamos tabla

  //Ventana
  Widgets->SVentanas->VenP=gtk_window_new(GTK_WINDOW_TOPLEVEL);//Creamos ventana principal, esta se encuentra en una estructura
  gtk_window_set_resizable(GTK_WINDOW(Widgets->SVentanas->VenP),FALSE);//fijamos atributo de la ventana 
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->VenP),GTK_WIN_POS_CENTER);//fijamos posicion de la ventana
  //Registramos la llamada a funciones con g_signal_connect, usaremos la funcion salir
  g_signal_connect(Widgets->Nodo3->VenP,"delete_event",G_CALLBACK(CerrarJuego1), Widgets);
  g_signal_connect(Widgets->Nodo3->VenP,"destroy",G_CALLBACK(CerrarJuego2), Widgets);
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
  g_signal_connect(MenuIAd,"activate",G_CALLBACK(Acerca_de),Widgets->Nodo3);//llamada a la funcion acerca de
  
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
  g_signal_connect(TAd,"clicked",G_CALLBACK(Acerca_de),Widgets->Nodo3);//llamada a la funcion Acerca de
  Sep2=gtk_separator_tool_item_new();//creamos un segundo separador
  TS=gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);//cracion del icono salir
  g_signal_connect(TS,"clicked",G_CALLBACK(CerrarJuego),Widgets);//llamada a la funcion Salir

  
  /*Definimos la jerarquia para meter los iconos en la TOOLBAR*/
  gtk_toolbar_set_style(GTK_TOOLBAR(Tool), GTK_TOOLBAR_ICONS);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TJ, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TG, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TA, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), Sep1, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TAy, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TAd, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), Sep2, -1);
  gtk_toolbar_insert(GTK_TOOLBAR(Tool), TS, -1);
  gtk_box_pack_start (GTK_BOX(CV),Tool,FALSE,TRUE,0);//incluimos la toolbar en la caja vertical
  
  //Tablero de juego e inizializacion de datos
  gtk_box_pack_start_defaults (GTK_BOX(CV),CH);//Caja de tablero y cuadro
  Widgets->STablero->Activo=0;//Significa si hay una partida en juego
  Widgets->STablero->Turno=0;//Significa el turno correspondiente
  Tabla=gtk_table_new(20,20,TRUE);//creacion de tabla
  for(i=0;i<20;i++)
    {
      for(j=0;j<20;j++)//inicializamos la imagen poniendola vacia
	{
	  Widgets->STablero->Estados[i][j]=0;
	  Widgets->STablero->B[i][j]=gtk_button_new();//nuevo boton
	  Widgets->STablero->Im[i][j]=gtk_image_new();//nueva imagen
	  gtk_button_set_image(GTK_BUTTON(Widgets->STablero->B[i][j]),Widgets->STablero->Im[i][j]);
	  gtk_image_set_from_file(GTK_IMAGE(Widgets->STablero->Im[i][j]),"Archivos/0.png");
	  sprintf(NombreBoton,"%d,%d",i,j);//modificar una cadena que sera nuestro nombre de boton
	  gtk_widget_set_name(Widgets->STablero->B[i][j],NombreBoton);//dar nombre al boton
	  gtk_widget_modify_bg(Widgets->STablero->B[i][j],GTK_STATE_NORMAL,&Tablero);      
	  gtk_table_attach_defaults(GTK_TABLE(Tabla),Widgets->STabero->B[i][j],i,i+1,j,j+1);
	  g_signal_connect(Widgets->STablero->B[i][j],"clicked",G_CALLBACK(Pulsado), Widgets);//llamada a la funcion dando click
	}//for
    }//for
  gtk_box_pack_start_defaults (GTK_BOX(CH),Tabla);//agregamos tabla a la caja vertical

  //Cuadro de la partida
  CPartida=gtk_vbox_new(FALSE,0);//Creamos caja vertical que sera nuestro cuadro de partida
  gtk_box_pack_start (GTK_BOX(CH),CPartida,FALSE,FALSE,0);//definimos jerarquia

  CHPartida[0]=gtk_hbox_new(FALSE,10);//creacion de caja horizontal
  gtk_box_pack_start_defaults (GTK_BOX(CPartida),CHPartida[0]);//caja horizontal en caja vertical
  Widgets->STablero->BComidas=gtk_label_new("00");//creacion de label que indicara las jugadas o comidas
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[0]),Widgets->STablero->BComidas);//incluimos en la caja vertical el label
  Im1=gtk_image_new_from_file("Archivos/1.png");//creamos imagen
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[0]),Im1);//agregamos imagen en la caja horizontal
  Widgets->STablero->EJ[0]=gtk_label_new("Jugador1");//creamos label
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[0]),Widgets->STablero->EJ[0]);//agregamos label en caja horizontal

  CHPartida[1]=gtk_hbox_new(FALSE,10);//creacion de segunda caja horizontal
  gtk_box_pack_start_defaults (GTK_BOX(CPartida),CHPartida[1]);//agregamos caja horizontal en caja de partida
  Widgets->STablero->NComidas=gtk_label_new("00");//jugadas del jugador 2
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[1]),Widgets->STablero->NComidas);//agregamos comidas a la caja horizontal
  Im2=gtk_image_new_from_file("Archivos/2.png");//creamos imagen para jugador 2
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[1]),Im2);//agregamos imagen a la caja horizontal
  Widgets->STablero->EJ[1]=gtk_label_new("Jugador2");//creamos label
  gtk_box_pack_start_defaults (GTK_BOX(CHPartida[1]),Widgets->STablero->EJ[1]);//agregamos label en la caja horizontal

  CHPartida[2]=gtk_fixed_new();//centramos el tiempo
  gtk_box_pack_start_defaults (GTK_BOX(CPartida),CHPartida[2]);//incluimos la caja de tiempo en la caja de partida
  
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
  gtk_container_add(GTK_CONTAINER(Widgets->Nodo3->VenJ),CVJ);//agregamos la caja vertical de jugador a la ventana
  gtk_window_set_resizable(GTK_WINDOW(Widgets->SVentanas->VenJ),FALSE);//definimos tamaño de ventana
  
  //Nombre Jugador1
  gtk_box_pack_start_defaults (GTK_BOX(CVJ),Widgets->SOpciones->CHJ[0]);
  EtiquetasJ[1]=gtk_label_new("Jugador1:");//nueva etiqueta
  Widgets->SOpciones->Entry[0]=gtk_entry_new();//nuevo entry
  gtk_entry_set_max_length(GTK_ENTRY(Widgets->SOpciones->Entry[0]),30);//tamaño de entry
  gtk_box_pack_start_defaults (GTK_BOX(Widgets->SOpciones->CHJ[0]),EtiquetasJ[1]);//agregamos etiqueta a caja horizontal
  gtk_box_pack_start_defaults (GTK_BOX(Widgets->SOpciones->CHJ[0]),Widgets->Nodo2->Entry[0]);//agregamos entry a caja horizontal

  //Nombre Jugador2
  gtk_box_pack_start_defaults (GTK_BOX(CVJ),Widgets->SOpciones->CHJ[1]);
  EtiquetasJ[2]=gtk_label_new("Jugador2");//nueva etiqueta
  Widgets->SOpciones->Entry[1]=gtk_entry_new();//nuevo entry
  gtk_entry_set_max_length(GTK_ENTRY(Widgets->SOpciones->Entry[1]),30);//tamaño de entry
  gtk_box_pack_start_defaults (GTK_BOX(Widgets->SOpciones->CHJ[1]),EtiquetasJ[2]);//agregamos etiqueta a caja horizontal
  gtk_box_pack_start_defaults (GTK_BOX(Widgets->SOpciones->CHJ[1]),Widgets->SOpciones->Entry[1]);//agregamos entry a caja horizontal
  
  //Orden de tiro
  EtiquetasJ[3]=gtk_label_new("¿Quien empieza el juego?");//nuevo label
  Widgets->SOpciones->BotonInicia[0]=gtk_radio_button_new_with_label(NULL,"Jugador 1");//nuevo boton radio
  Widgets->SOpciones->Grupo=gtk_radio_button_get_group(GTK_RADIO_BUTTON(Widgets->SOpciones->BotonInicia[0]));//definimos orden de boton
  Widgets->SOpciones->BotonInicia[1]=gtk_radio_button_new_with_label(Widgets->SOpciones->Grupo,"Jugador 2");//agregamos nombre a boton
  gtk_box_pack_start_defaults (GTK_BOX(CVJ),EtiquetasJ[3]);//agregamos label a caja vertical
  gtk_box_pack_start_defaults (GTK_BOX(CVJ),Widgets->SOpciones->BotonInicia[0]);//agregamos bton iniciala caja vertical
  gtk_box_pack_start_defaults (GTK_BOX(CVJ),Widgets->SOpciones->BotonInicia[1]);//agregamos los radios boton a la caja vertical

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
//  GtkWidget *imagen, *boton, *vbox;
  //GdkPixbuf *pixbuf;
  //ptrVentanas ventanas;
  //Widgets->SVentanas->VentanaLogo = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  Widgets->SVentanas->M1=gtk_message_dialog_new(GTK_WINDOW(Widgets->SVentanas->VenP), GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Bienvenido jugador:\nEste programa fue elaborado por:\nMariana Martinez Kobeh\nElena Ginebra\nKarina Almazán");//nuevo mensaje de Dialogo, en este mismo esta ya incluido en el mensaje de dialogo los botones
  gtk_window_set_position(GTK_WINDOW(Widgets->SVentanas->M1),GTK_WIN_POS_CENTER);//establecer posicion al centro
  gtk_window_set_title(GTK_WINDOW(Widgets->SVentanas->M1), "Bienvenido");//nombre de la ventana
  gtk_dialog_run(GTK_DIALOG(Widgets->SVentanas->M1));//correr el cuadro de dialogo
  gtk_widget_destroy(Widgets->SVentanas->M1);//destruir cuadro de dialogo 
/*
  vbox = gtk_vbox_new(TRUE,5);
  //ventanas->VentanaLogo = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  //gtk_window_set_title(GTK_WINDOW (ventanas->VentanaLogo), "Pente");
  //gtk_window_set_position(GTK_WINDOW(ventanas->VentanaLogo), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(Widgets->Nodo3->VentanaLogo),500,500);
  gtk_window_set_resizable(GTK_WINDOW(Widgets->Nodo3->VentanaLogo), FALSE);
  gtk_container_border_width(GTK_CONTAINER(Widgets->Nodo3->VentanaLogo),5);

  pixbuf = gdk_pixbuf_new_from_file_at_scale("logo.png", 500, 500, FALSE, NULL);
  imagen = gtk_image_new_from_pixbuf(pixbuf);
  boton= gtk_button_new();
  
  gtk_widget_show (imagen);

  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(Hide), Widgets);
  gtk_signal_connect(GTK_OBJECT(Widgets->Nodo3->VentanaLogo),"destroy",GTK_SIGNAL_FUNC(StopTheApp), Widgets);
  gtk_container_add(GTK_CONTAINER(Widgets->Nodo3->VentanaLogo), boton);
  gtk_container_add(GTK_CONTAINER(boton), vbox);
  gtk_container_add(GTK_CONTAINER(vbox), GTK_WIDGET(imagen));
  
  gtk_widget_show_all(Widgets->Nodo3->VentanaLogo);*/ 
}
/*
void VentanaInstrucciones(GtkWidget *widget, gpointer data)
{ 
  GtkWidget *imagen, *boton, *hbox;
  GdkPixbuf *pixbuf;
  ptrVentanas ventanas=(tVentanas*)data;
  
  gtk_widget_hide_all(ventanas->VentanaLogo);
  hbox= gtk_hbox_new (TRUE, 5);
  ventanas->VentanaInstrucciones = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (ventanas->VentanaInstrucciones), "Pente");
  gtk_window_set_position(GTK_WINDOW(ventanas->VentanaInstrucciones), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(ventanas->VentanaInstrucciones),500,500);
  gtk_container_border_width(GTK_CONTAINER(ventanas->VentanaInstrucciones),5);
  
  pixbuf = gdk_pixbuf_new_from_file_at_scale("instrucciones.png", 500, 500, FALSE, NULL);
  imagen = gtk_image_new_from_pixbuf(pixbuf);
  boton= gtk_button_new();  
  gtk_widget_show (imagen);

  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(Hide), ventanas);
  gtk_signal_connect(GTK_OBJECT(ventanas->VentanaInstrucciones),"destroy",GTK_SIGNAL_FUNC(StopTheApp), ventanas);
  
  gtk_container_add(GTK_CONTAINER(ventanas->VentanaInstrucciones), boton);
  gtk_container_add(GTK_CONTAINER(boton), hbox);
  gtk_container_add(GTK_CONTAINER(hbox), GTK_WIDGET(imagen));
  
  gtk_widget_show_all(ventanas->VentanaInstrucciones); 
}*/
*/
