/*
 *@tablerocodigo.h
 *Este programa es el .h de tablerocodigo.c ya que son módulos.
 *Esto significa que incluye todas las funciones que no son static de 
 *tablerocodigo.h
 *Se hizo lo de indef y endif (es un if) para que si ya se declaro esta 
 *biblioteca, no se vuelva a declarar y haya problemas en el código
 *@Mariana
 *@01/05/2018
**/


#indef tablerocodigoDEFINIDO

extern void limpiartablero(void);
extern int ponerficha(char ficha, int i, int j, int guardar);

#define tablerocodigoDEFINIDO
#endif
