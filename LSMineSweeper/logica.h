/***********************************************
*
* @Proposit: Funcions i procediments que s'ocupen de la logica general de la partida.
* @Autor/s: Marc Cespedes i Alex Cabezas
* @Data creacio: 23/4/2018
* @Data ultima modificacio: 14/05/2018
*
************************************************/

#ifndef _LOGICA_H_
#define _LOGICA_H_

#include "fitxers.h"
#include "grafics.h"
#include "LS_allegro.h"
#include "memoria.h"
#include "temps.h"
#include "llistaPDI.h"


void LOGICA_mostraMenu();
void LOGICA_inicialitzaCursor(Cursor *cur);
void LOGICA_gameOver(int fi, Partida game, LlistaPDI l,Jugador *jug, Cursor cur);
int LOGICA_minaTocada(Partida *game);
int LOGICA_comprovaCoord(Cursor cur,LlistaPDI l);
void LOGICA_moureCursor(Cursor *cur, Partida game);
int LOGICA_accions(int* nSortir,Partida *game,LlistaPDI* l,int* girades,Cursor cur);
void LOGICA_insereixBandera(LlistaPDI *l,Cursor cur);
void LOGICA_opcio1();
void LOGICA_final(Jugador jug,int fi);
int LOGICA_partida(Partida game,Jugador *jug);
#endif