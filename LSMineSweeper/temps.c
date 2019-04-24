#include "temps.h"

/************************************
*
*@Finalitat: Inicialitza els valors del temps.
*@Parametres:	in/out: game = Variable amb la informacio de la partida.
*@Retorn: -----.
*
**********************************/
void TEMPS_inicialitzaTemps(Partida *game) {
		game->temps = 0;
		game->tempspas = (float)clock();
	}

/************************************
*
*@Finalitat: Calcula el temps actual.
*@Parametres:	in/out: game = Variable amb la informacio de la partida.
*@Retorn: -----.
*
**********************************/
void TEMPS_pintaTemps(Partida *game) {
		game->tempsnou = (float)clock();
		if((game->tempsnou-game->tempspas)/(float)CLOCKS_PER_SEC >= 1) {
			game->temps ++;
			game->tempspas = (float)clock();
		}
}