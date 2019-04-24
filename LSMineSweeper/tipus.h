/***********************************************
*
* @Proposit: Definir tots els tipus i constants per al funcionament del joc.
* @Autor/s: Marc Cespedes i Alex Cabezas
* @Data creacio: 23/4/2018
* @Data ultima modificacio: 14/05/2018
*
************************************************/

#ifndef _TIPUS_H_
#define _TIPUS_H_

#define MAXC 30	//Maxim nombre de caracter d'alguns camps
#define CAS 80	//Dimensio de les caselles quadrades
#define INTERH 10	//Dimensio de la part horitzontal de la interficie
#define INTERV 100	//Dimensio de la part vertical de la interficie

#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Tipus que guarda les dades del jugador
typedef struct{
	char nom[MAXC + 1];
	char fitxer[MAXC + 1];
	int punts;
}Jugador;

//Tipus que guarda les dades de cada casella
typedef struct {
	int num;
	int mina;	//1 = hi ha mina
	int girat;	//1 = Casella girada
	int cursor;	//1 = cursor a sobre de la casella
	int x;
	int y;
} Casella;

//Tipus que guarda les dades de la partida
typedef struct{
	Casella** tauler;
	int col;
	int fila;
	int mina;
	int temps;
	float tempsnou;
	float tempspas;
} Partida;

//Tipus que guarda les dades del cursor
typedef struct{
	int x;		//Posicio de x(en pixels)
	int y;		//Posicio de y(en pixels)
	int cx;		//Posicio de x(en caselles)
	int cy;		//Posicio de y(en caselles)
} Cursor;

//Tipus que guarda les dades d'una bandera
typedef struct{
    int c;
    int f;
} Bandera;

#endif