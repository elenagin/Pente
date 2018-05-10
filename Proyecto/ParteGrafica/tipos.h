/*******Estructuras a utilizar*************/

struct def_Ventanas
{
  GtkWidget *VenP;//Ventana Principal
  GtkWidget *M1;//Mensaje 1
  GtkWidget *M2;//Mensaje 2
  GtkWidget *M3;//Mensaje 3
  GtkWidget *Des1;//Dialogo 1
  GtkWidget *Des2;//Dialogo 2
  GtkWidget *VenJ;//Ventana Jugar
  GtkWidget *VenA;//Ventana Abrir
  GtkWidget *VenG;//Ventana Guardar
  GtkWidget *VenAy;//Ventana Ayuda
  GtkWidget *VenAd;//Ventana Acerca de
};

typedef struct def_Ventanas tVentanas;
typedef struct def_Ventanas *ptrVentanas;

struct def_Tablero
{
  GtkWidget *B[20][20];//Botones
  GtkWidget *Im[20][20]; //Botones Imagenes(Al boton se le agrega la imagen)
  int Estados[20][20];//0-Vacio,1-Juagador1, 2-Jugador2
  int Activo;//Partida Activa(Bandera)
  int Turno;//De quien es el turno
  int Inicia;//Que jugador inicia
  GtkWidget *NComidas;//Rojas comidas
  GtkWidget *BComidas;//Azules comidas
  GtkWidget *EJ[2];//Nombres de los jugadores
  FILE *Temporal;//Archivo

};

typedef struct def_Tablero tTablero;
typedef struct def_Tablero *ptrTablero;

struct def_Opciones
{
  GtkWidget *CHJ[3];//Caja Horizontal del Jugador
  GSList *Grupo;//Grupo de los radiobuttons
  GtkWidget *Entry[2];//entries de los nobres de jugadores
  const gchar *Jugadores[2];//Lugar donde se guarda el nombre del jugador
  GtkWidget *BotonInicia[2];//Radiobuttons
};

typedef struct def_Opciones tOpciones;
typedef struct def_Opciones *ptrOpciones;

struct def_Widgets//Estructura donde se incluyen las 3 estructuras
{
  ptrTablero SVentanas;
  ptrOpciones STablero;
  ptrVentanas SOpciones;
};

typedef struct def_Widgets tWidgets;
typedef struct def_Widgets *ptrWidgets;
