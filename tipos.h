#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

typedef struct parametroVentana
{
  GtkWidget *VentanaLogo;
  GtkWidget *VentanaInstrucciones;
  GtkWidget *VentanaNuevoAnterior;
  GtkWidget *VentanaJuego;
}typeVentana, *typeVentanaPtr;

/*******Estructuras a utilizar*************/


typedef struct def_Ventanas
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
} tVentanas, *ptrVentanas;

typedef struct def_Tablero
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

}tTablero, *ptrTablero;

typedef struct def_Opciones
{
  GtkWidget *CHJ[3];
  GSList *Grupo;
  GtkWidget *Entry[2];
  const gchar *Jugadores[2];
  GtkWidget *BotonInicia[2];
}tOpciones, *ptrOpciones;

typedef struct def_Widgets
{
  ptrTablero Nodo;
  ptrOpciones Nodo2;
  ptrVentanas Nodo3;
}tWidgets, *ptrWidgets;

