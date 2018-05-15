/*
 *@senales.h
 *Este programa es el .h de senales.c ya que son módulos.
 *Esto significa que incluye todas las funciones que no son static de
 *senales.h
 *Se hizo lo de indef y endif (es un if) para que si ya se declaró esta
 *biblioteca, no se vuelva a declarar y haya problemas en el código
 *@Karina
 *@Elena
 *@01/05/2018
**/

#ifndef senalesDEFINIDO

void Pulsado(GtkWidget *Widget, gpointer data);
void Abrir_menu_juego (GtkToolButton *toolbutton, gpointer data);
void MenuGuardar(GtkWidget *Widget, gpointer data);
void MenuAbrir(GtkWidget *Widget, gpointer data);
void Manual(GtkWidget *Widget, gpointer data);
void TerminarPartida(GtkWidget *Widget, gpointer data);
void IniciarPartida(GtkWidget *Widget, gpointer data);
void Esconder(GtkWidget *Widget, gpointer data);
void Esconder2(GtkWidget *Widget, gpointer data);
void Esconder3(GtkWidget *Widget, gpointer data);
void Esconder4(GtkWidget *Widget, gpointer data);
void Esconder5(GtkWidget *Widget, gpointer data);
void EsconderVentana(GtkWidget *Widget, gpointer data);
void CerrarJuego(GtkWidget *Widget, gpointer data);
gboolean CerrarJuego1(GtkWidget *Widget, GdkEvent *event, gpointer data);
void CerrarJuego2(GtkWidget *Widget, gpointer data);
void Acerca_de(GtkWidget *Widget, gpointer data);
void RecorreHistorial(GtkWidget *Widget, gpointer data);
void on_button_clicked(GtkWidget *Widget, gpointer data);
void SeguirAMano(GtkWidget *Widget, gpointer data);

#define senalesDEFINIDO
#endif
