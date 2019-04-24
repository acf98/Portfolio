/***********************************************
*
* @Proposit: Procediments que gestionen la lectura i escriptura de fitxers.
* @Autor/s: Marc Cespedes i Alex Cabezas
* @Data creacio: 23/4/2018
* @Data ultima modificacio: 14/05/2018
*
************************************************/

#ifndef _FITXERS_H_
#define _FITXERS_H_

#include "tipus.h"
#include "memoria.h"

void FITXERS_Ranking();
void FITXER_llegeixFitxer(FILE *f,char nom_f[50], Partida *game);
void FITXERS_guardaRanking(Jugador jug);
#endif

