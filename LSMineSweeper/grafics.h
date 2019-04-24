/***********************************************
*
* @Proposit: Funcions i procediments que s'ocupen de pintar la partida per pantalla.
* @Autor/s: Marc Cespedes i Alex Cabezas
* @Data creacio: 23/4/2018
* @Data ultima modificacio: 14/05/2018
*
************************************************/

#ifndef _GRAFICS_H_
#define _GRAFICS_H_

#include "tipus.h"
#include "llistaPDI.h"
#include "LS_allegro.h"

int GRAFICS_comprovaCoordGrafics(int i,int p,LlistaPDI l);
void GRAFICS_imprimeixTauler(Partida game, LlistaPDI l,int fi);
void GRAFICS_inicialitzaAllegro();
void GRAFICS_imprimeixCap(Partida game,Jugador jug);
void GRAFICS_imprimeix(Partida game, Jugador jug, Cursor cur, int fi, LlistaPDI l);
#endif