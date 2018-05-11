/*******Estructuras a utilizar*************/


struct def_Ventanas
{
  GtkWidget *VenP;
  GtkWidget *M1;
  GtkWidget *M2;
  GtkWidget *M3;
  GtkWidget *Des1;
  GtkWidget *Des2;
  GtkWidget *VenJ;
  GtkWidget *VenA;
  GtkWidget *VenG;
  GtkWidget *VenAy;
  GtkWidget *VenAd;
  GtkWidget *VentanaLogo;
  GtkWidget *VentanaInstrucciones;
  GtkWidget *VentanaNuevoAnterior;
  GtkWidget *VentanaJuegoEle;
};

typedef struct def_Ventanas tVentanas;
typedef struct def_Ventanas *ptrVentanas;

struct def_Tablero
{
  GtkWidget *B[20][20];
  GtkWidget *Im[20][20];
  int Estados[20][20];
  int Activo;
  int Turno;
  int Inicia;
  int Min;
  int Seg;
  GtkWidget *NComidas;
  GtkWidget *BComidas;
  GtkWidget *EJ[2];
  GtkWidget *Reloj;
  FILE *Temporal;

};

typedef struct def_Tablero tTablero;
typedef struct def_Tablero *ptrTablero;

struct def_Opciones
{
  GtkWidget *CHJ[3];
  GSList *Grupo;
  GtkWidget *Entry[2];
  const gchar *Jugadores[2];
  GtkWidget *BotonInicia[2];
};

typedef struct def_Opciones tOpciones;
typedef struct def_Opciones *ptrOpciones;

struct def_Widgets
{
  ptrTablero Nodo;
  ptrOpciones Nodo2;
  ptrVentanas Nodo3;
};

typedef struct def_Widgets tWidgets;
typedef struct def_Widgets *ptrWidgets;

/*typedef struct parametroVentana
{
  GtkWidget *VentanaLogo;
  GtkWidget *VentanaInstrucciones;
  GtkWidget *VentanaNuevoAnterior;
  GtkWidget *VentanaJuego;
}typeVentana, *typeVentanaPtr;
*/
