#include "grafics.h"


/************************************
*
*@Finalitat: Comprova, si s'ha col·locat una bandera en aquella casella
*@Parametres:	in: i = enter que ens indica la fila a la que esta la casella.
*               in: p = enter que ens indica la columna a la que esta la casella.
* 				in: l = llista encarregada de guardar la posicio de cada casella on hem col·locat una bandera.
*@Retorn: 1 o 0 en funció de si troba la casella en la que estem a la llista o no.
*
**********************************/
int GRAFICS_comprovaCoordGrafics(int i,int p,LlistaPDI l) {
	int ok = 0;
	Bandera b;
	if (!LLISTAPDI_buida(l)){
			LLISTAPDI_vesinici(&l);
            while(!LLISTAPDI_fi(l) && ok != 1){
                b = LLISTAPDI_consulta(l);
                if(b.f != i || b.c != p){
                    LLISTAPDI_avanca(&l);
                }
				else{
					ok = 1;
				}
            }
	}	

	return ok;
}

/************************************
*
*@Finalitat: Pinta per pantalla el taulell.
*@Parametres:	in: game = variable amb les dades de la partida
* 				in: l = llista encarregada de guardar la posicio de cada casella on hem col·locat una bandera.
*               in: fi = Boolea, per saber si es el final de la partida.
*@Retorn: ----.
*
**********************************/
void GRAFICS_imprimeixTauler(Partida game, LlistaPDI l,int fi) {
	int i,p;
	//Dibuixem, per cada fila i columna, la seva casella
    for (i = 0; i < game.fila; i++) {
        for (p = 0; p < game.col; p ++) {
			if(game.tauler[p][i].girat == 0) {			//Si no esta girada o amb bandera, dibuixem la imatge de terra
				al_draw_filled_rectangle(p*CAS + 5,INTERV + i*CAS,p*CAS + CAS + 5,INTERV + i*CAS + CAS, LS_allegro_get_color(GRAY));
				if(fi == 0){
					if (GRAFICS_comprovaCoordGrafics(i,p,l)) {
						al_draw_filled_rectangle(p*CAS + 5,INTERV + i*CAS,p*CAS + CAS + 5,INTERV + i*CAS + CAS, LS_allegro_get_color(GRAY));
						al_draw_filled_triangle(p*CAS + 15,INTERV + i*CAS + 10,p*CAS + 15,INTERV + i*CAS + 70,p*CAS + 70, INTERV + i*CAS +40,LS_allegro_get_color(DARK_GREEN));					
					}
				}
			}
			else {										//Si esta girada, dibuixem el que conte la casella
				if(game.tauler[p][i].mina == 1) {
					if(fi == 0) {						//Si no s'ha perdut la partida, es mostra normal
                        al_draw_filled_rectangle(p*CAS+ 5,100 + i*CAS ,p*CAS + CAS+ 5,100 + i*CAS + CAS ,LS_allegro_get_color(RED));
                    }
					else {
								//Si s'ha perdut la partida, es mostren les caselles vermelles
							al_draw_filled_rectangle(p*CAS+ 5,100 + i*CAS ,p*CAS + CAS+ 5,100 + i*CAS + CAS ,LS_allegro_get_color(RED));
					}
				}
				else {
					al_draw_filled_rectangle(p*CAS+ 5,100 + i*CAS ,p*CAS + CAS + 5,100 + i*CAS + CAS ,LS_allegro_get_color(WHITE));
					al_draw_textf(LS_allegro_get_font(EXTRA_LARGE),LS_allegro_get_color(BLACK),p*CAS + 25 + 5,100 + i*CAS + 25,0,"%d",game.tauler[p][i].num);
				}
			}
			al_draw_rectangle(p*CAS + 5,INTERV + i*CAS,p*CAS + CAS + 5,INTERV + i*CAS + CAS,LS_allegro_get_color(BLACK), 3);  //Pintem bordes de les caselles
		}
    } 
}

/************************************
*
*@Finalitat: Inicialitza la finestra grafica.
*@Parametres:	in: amplada = amplada de la finestra grafica (en pixels).
* 				in: altura = altura de la finestra grafica (en pixels).
*@Retorn: ----.
*
**********************************/
void GRAFICS_inicialitzaAllegro(int amplada, int altura) {
		LS_allegro_init(amplada,altura,"PGM1 - PRS 2");
	}
	

/************************************
*
*@Finalitat: Imprimeix la capsalera del joc.
*@Parametres:	in: game = variable amb les dades de la partida.
* 				in:jug = variable amb les dades del jugador.
*@Retorn: ----.
*
**********************************/
void GRAFICS_imprimeixCap(Partida game,Jugador jug){
		al_draw_filled_rectangle(0,0,CAS*game.col, INTERV, LS_allegro_get_color(BLACK));
		al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),5 + 5,5,0,"%s","Nom:");								//Imprimim "Nom"
		al_draw_textf(LS_allegro_get_font(EXTRA_LARGE),LS_allegro_get_color(WHITE),35 + 5, 45, 0,"%s",jug.nom);					//Imprimim el nom del jugador
		al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),(80*game.col)/2 + 5,5, 0,"%s","TEMPS:");				//Imprimim "Temps"
		al_draw_textf(LS_allegro_get_font(EXTRA_LARGE),LS_allegro_get_color(WHITE),(80*game.col)/2 + 160 + 5,45, 0,"%d",game.temps);	//Imprimim el temps que portem jugant
	}
	
	
/************************************
*
*@Finalitat: Imprimeix per pantalla el joc.
*@Parametres:	in: game = variable amb les dades de la partida.
* 				in: jug = variable amb les dades del jugador.
* 				in: cur = variable amb les dades del cursor.
*@Retorn: ----.
*
**********************************/
void GRAFICS_imprimeix(Partida game, Jugador jug, Cursor cur, int fi, LlistaPDI l) {
	GRAFICS_imprimeixCap(game,jug);
	GRAFICS_imprimeixTauler(game,l,fi);
	al_draw_rectangle(cur.x + 5,cur.y ,cur.x + CAS + 5,cur.y + CAS ,LS_allegro_get_color(GREEN), 3);  //Pintem el cursor
	//Si s'ha acabat  la partida, mostrem el missatge de fi de partida corresponent
	if (fi==1){
		al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(BLUE),100,130,0,"%s","GAME OVER!");
		al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(BLUE),100,160,0,"%s","Prem ESC per sortir!");
    }
	else{
		if(fi == 2){
			al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(BLUE),100,130,0,"%s","HAS GUANYAT!");
			al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(BLUE),100,160,0,"%s","Prem ESC per sortir!");
		}
	}
	//Pintem la pantalla de la finestra grfica
	LS_allegro_clear_and_paint(BLACK);
}

