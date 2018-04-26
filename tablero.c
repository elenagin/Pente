/**
 *@tablero.c
 *Este programa crea el tablero del juego usando una matriz tipo char, coloca la ficha recibida en la posic *ión indicada, las cuales son char e int en ese respectivo orden, checa si se comen fichas, si se gana el  *juego, si la posición estaba ocupada, si los datos recibidos no son correctos y la salida son returns.
 *@Mariana
 *@25/04/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIMTABLERO 20

char tablero[DIMTABLERO][DIMTABLERO];
static int comidas1, comidas2; //Para saber cuantas fichas de cada tipo se han consumido.

/**
 *Esta función prepara el tablero para iniciar un juego nuevo (lo "limpia")
 *Esta función no recibe ningún parámetro ni manda ningún resultado.
 *@Mariana 
 *@return void
 */
void limpiartablero(void)
{
  int i, j;
  for(i=0; i<DIMTABLERO; i++)
    {
      for(j=0; j<DIMTABLERO; j++)
	{
	  tablero[i][j]='0';
	}
    }
  comidas1=0;
  comidas2=0;
}

/**
 *Esta función determina si se juntó una fila de 5 fichas en cualquier dirección.
 *Recibe una n ya que esta función también se utiliza para la función de ganar2, donde se checan 4 fichas,  *no 5.
 *Regresando 1 si sí gana un jugador.
 *Regresa 0 si todavía nadie gana.
 *@Mariana
 *@Param char ficha Color de ficha
 *@Param int i Posición del tablero
 *@Param int j Posición del tablero
 *@Param int n Número de posiciones consecutivas deseadas
 *@return int 
 */
static int ganar1(char ficha, int i, int j, int n, int *x1, int *y1, int *x2, int *y2)
{
  int j1, j2, i1, i2;
  if (tablero[i][j] != ficha)
    return 0;
  //vemos si hay n en horizontal
  j1=j;
  j2=j;
  while((j1>0) && (tablero[i][j1-1]==ficha)) //j1 recorre j a la izquierda
    {
      --j1;
    }
  while((j2<(DIMTABLERO-1)) && (tablero[i][j2+1]==ficha)) //j2 recorre j a la derecha
    {
      j2++;
    }
  if((j2-j1+1)>=n)
    {
      if(x1 && y1 && x2 && y2)
	{
	  *x1=i;
	  *y1=j1;
	  *x2=i;
	  *y2=j2;
	}
      return 1;
    }
  //vemos si hay n en vertical
  i1=i;
  i2=i;
  while((i1>0) && (tablero[i1-1][j]==ficha))//i1 recorre abajo
    {
      --i1;
    }
  while((i2<(DIMTABLERO-1)) && (tablero[i2+1][j]==ficha))//i2 recorre arriba
    {
      i2++;
    }
  if((i2-i1+1)>=n)
    {
      if(x1 && y1 && x2 && y2)
	{
	  *x1=i1;
	  *y1=j;
	  *x2=i2;
	  *y2=j;
	}
      return 1;
    }
  //vemos si hay n en primera diagonal
  i1=i;
  i2=i;
  j1=j;
  j2=j;
  while((i1>0) && (j1>0) && (tablero[i1-1][j1-1]==ficha))//i1 recorre abajo y j1 a izquierda
    {
      --i1;
      --j1;
    }
  while((i2<(DIMTABLERO-1)) && (j2<(DIMTABLERO-1)) && (tablero[i2+1][j2+1]==ficha))//i2 recorre arriba y j2 a derecha
    {
      i2++;
      j2++;
    }
  if((i2-i1+1)>=n)
    {
      if(x1 && y1 && x2 && y2)
	{
	  *x1=i1;
	  *y1=j1;
	  *x2=i2;
	  *y2=j2;
	}
      return 1;
    }
  //vemos si hay n en segunda diagonal
  i1=i;
  i2=i;
  j1=j;
  j2=j;
  while((i1>0) && (j2<(DIMTABLERO-1)) && (tablero[i1-1][j2+1]==ficha))//i1 recorre abajo y j2 a derecha
    {
      --i1;
      j2++;
    }
  while((i2<(DIMTABLERO-1)) && (j1>0) && (tablero[i2+1][j1-1]==ficha))//i2 recorre arriba y j1 a izquierda
    {
      i2++;
      --j1;
    }
  if((i2-i1+1)>=n)
    {
      if(x1 && y1 && x2 && y2)
	{
	  *x1=i1;
	  *y1=j1;
	  *x2=i2;
	  *y2=j2;
	}
      return 1;
    }
  return 0;
}

/**
 *Esta función determina si se han juntado 5 filas de 4 fichas consecutivas en cualquier dirección, llama a *ganar1, donde se ve si hay 4 fichas consecutivas, y aqui se lleva un contador para saber si hay 5 filas d *e dicha condición.
 *Regresa 1 si alguien gana.
 *Regresa 0 si nadie ha ganado.
 *@Mariana
 *@Param char ficha Color de ficha
 *@return int 
 */
int ganar2(char ficha)
{
  int i, j, k;
  int posiciones[5][4]; //posiciones de 4 fichas
  int totposiciones;
  int i1, i2, j1, j2;
  totposiciones=0;
  for(i=0; i<DIMTABLERO; i++)
    {
      for(j=0; j<DIMTABLERO; j++)
	{
	  if(ganar1(ficha, i, j, 4, &i1, &j1, &i2, &j2)==1)
	    {
	      for(k=0; k<totposiciones; k++)
		{
		  if((posiciones[k][0]==i1) &&
		     (posiciones[k][1]==j1) &&
		     (posiciones[k][2]==i2) &&
		     (posiciones[k][3]==j2))/*aquí estamos checando que las 5 hileras de 4 fichas sean diferentes, si alguna ficha se intersecta en dos hileras, la cuenta dos veces, entonces para no confundir y saber que realmente las 5 hileras son diferentes.*/
		    {
		      break;
		    }
		}
	      if(k==totposiciones)
		{
		  if(k==4)
		    {
		      return 1;
		    }
		  posiciones[k][0]=i1;
		  posiciones[k][1]=j1;
		  posiciones[k][2]=i2;
		  posiciones[k][3]=j2; /*Estamos guardando la primera y la última coordenada*/
		  totposiciones++;
		}
	    }
	}
    }
  return 0;
}

/**
 *Esta función coloca la ficha en el tablero.
 *Recibe la ficha ya sea 1 o 2 y la posiciona en el tablero i, j.
 *Regresa -1 si ya estaba ocupado
 *Regresa -2 con coordenadas inválidas
 *Regresa -3 si las fichas son inválidas
 *Regresa -4 si es empate
 *Regresa 1 si fue aceptado el movimiento
 *Regresa 2 si gana el juego
 *Regresa 3 si come fichas y 4 si gana y come.
 *@Mariana
 *@Param char ficha  La ficha a colocar
 *@Param int i  La posición del talero
 *@Param int j  Posición del tablero
 *@return int  
 */
int ponerficha(char ficha, int i, int j)
{
  int x, y;
  int cont=0;
  if(i<0 || i>=DIMTABLERO)
    {
      return -2; 
    }
  if(j<0 ||  j>=DIMTABLERO)
    {
      return -2;
    }
  if(ficha!='1' && ficha!='2')
    {
      return -3;
    }
  for(x=0; x<DIMTABLERO; x++)
    {
      for(y=0; y<DIMTABLERO; y++)
	{
	  if(tablero[x][y]!='0')
	    {
	      cont++;
	    }
	}
    }
  if(cont==(DIMTABLERO*DIMTABLERO))
    {
      return -4;
    }
  if(tablero[i][j]!='0')
    {
      return -1;
    }
  tablero[i][j]=ficha;
  if(ganar1(ficha, i, j, 5, NULL, NULL, NULL, NULL)==1)
    return 4;
  if(ganar2(ficha)==1)
    return 4;
  return 1;
}

/*int main(void)
{
  limpiartablero();
  printf("resultado: %d\n", ponerficha('1', 1, 1));
  printf("resultado: %d\n", ponerficha('1', 2, 2));
  printf("resultado: %d\n", ponerficha('1', 3, 3));
  printf("resultado: %d\n", ponerficha('1', 4, 4));
  printf("resultado: %d\n", ponerficha('1', 5, 14));
  printf("resultado: %d\n", ponerficha('1', 6, 13));
  printf("resultado: %d\n", ponerficha('1', 7, 12));
  printf("resultado: %d\n", ponerficha('1', 8, 11));
  printf("resultado: %d\n", ponerficha('1', 7, 8));
  printf("resultado: %d\n", ponerficha('1', 8, 8));
  printf("resultado: %d\n", ponerficha('1', 9, 8));
  printf("resultado: %d\n", ponerficha('1', 10, 8));
  printf("resultado: %d\n", ponerficha('1', 8, 8));
  printf("resultado: %d\n", ponerficha('1', 8, 9));
  printf("resultado: %d\n", ponerficha('1', 8, 10));
  printf("resultado: %d\n", ponerficha('1', 8, 11));
  printf("resultado: %d\n", ponerficha('1', 13, 4));
  printf("resultado: %d\n", ponerficha('1', 13, 5));
  printf("resultado: %d\n", ponerficha('1', 13, 6));
  printf("resultado: %d\n", ponerficha('1', 13, 7));
}
*/
