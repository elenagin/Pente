/*******************************************
*  @file tipos.h                           *
*                                          *
*  @brief Este archivo incluye todas las   *
*         estructuras a utilizar en la     *
*         desarrollo de la parte grafica   *
*         de este proyecto.                *
*  @Elena Ginebra                          *
*  @Karina Almazán                         *
*  @date 24/04/2018                        *
*******************************************/

/*******************************************
*   Estructura en donde se inluyen todos   *
*   los elementos a ocupar en las ventanas *
*******************************************/
typedef struct def_Ventanas
{
  GtkWidget *VenP;//Ventana Principal
  GtkWidget *VenB;//Ventana Bienvenida
  GtkWidget *VenI;//Ventana instrucciones
  GtkWidget *VenAy;//Ventana Ayuda
  GtkWidget *VenAd;//Ventana Acerca de
  GtkWidget *Error;//Ventana de error
  GtkWidget *VenGan; //Ventana ganador
  GtkWidget *M2;//Mensaje 2
  GtkWidget *M3;//Mensaje 3
  GtkWidget *Des1;//Diálogo 1
  GtkWidget *Des2;//Diálogo 2
  GtkWidget *VenJ;//Ventana jugar
  GtkWidget *VenA;//Ventana Abrir
  GtkWidget *VenG;//Ventana Guardar
  GtkWidget *VentanaErrorArchivos;
} tVentanas, *ptrVentanas;

/*******************************************
*   Estructura en donde se inluyen todos   *
*   los elementos a ocupar en el tablero   *
*******************************************/
typedef struct def_Tablero
{
  GtkWidget *B[20][20];//Botones
  GtkWidget *Im[20][20];//Botones imagenes(al boton se le agrega la imagen)
  int Estados[20][20];//0-Vacio,1-Jugador1, 2-Jugador2
  int Activo;//Partida activa(bandera)
  int Turno;//De quien es el turno 
  int Inicia;//Que jugador inicia
  GtkWidget *Comidas1;//Jugador 1 comidas
  GtkWidget *Comidas2;//Jugador 2 comidas
  int Num1Comidas;//Jugador 1 comidas
  int Num2Comidas;//Jugador 2 comidas
  GtkWidget *EJ[3];//Nombres de los jugadores
  FILE *Temporal;//Archivo
  GtkWidget *BotonTurnoActual;
  int BanderaNext;
} tTablero, *ptrTablero;

/*******************************************
*   Estructura en donde se inluyen todos   *
*   los elementos a ocupar en las opciones *
*******************************************/
typedef struct def_Opciones
{
  GtkWidget *CHJ[3];//Caja Horizontal del Jugador
  GSList *Grupo;//Grupo de los radiobuttons
  GtkWidget *Entry[2];//Entries de los nombres de jugadores
  const gchar *Jugadores[2];//Lugar donde se guarda el nombre del jugador
  GtkWidget *BotonInicia[2];//Radiobuttons
} tOpciones, *ptrOpciones;

/*******************************************
*   Estructura en donde se inluyen las 3   *
*        estructuras anteriores            *
*******************************************/
typedef struct def_Widgets
{
  ptrTablero  STablero;
  ptrOpciones SOpciones;
  ptrVentanas SVentanas;
} tWidgets, *ptrWidgets;
