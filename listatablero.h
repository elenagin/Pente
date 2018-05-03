/*
 *@listatablero.h
 *Este programa es el .h de listatablero.c ya que son módulos.
 *Esto significa que incluye la declaraciones de estructuras y 
 *todas las funciones que no son static de listatablero.h
 *Se hizo lo de indef y endif (es un if) para que si ya se declaro esta 
 *biblioteca, no se vuelva a declarar y haya problemas en el código
 *@Mariana
 *@01/05/2018
**/

#ifndef listatableroDEFINIDO


typedef struct movimientos
{
  int num; //número de movimiento
  int i, j; //Posición
  char color;
  struct movimientos *siguiente;
}Movimiento, *PtrMovimiento;

extern PtrMovimiento raiz;


extern int AgregarMov(int i, int j, char color);
extern int GuardarLista(char *NombreArchivo);
extern void EliminarLista();
extern int LeerLista(char *NombreArchivo);
extern void TruncarLista(int num);

#define listatableroDEFINIDO
#endif
