#include "memoria.h"

/************************************
*
*@Finalitat: Demana memoria per el tauler dinamic.
*@Parametres:	in/out: game = Dades referents a la partida
*@Retorn: -------.
*
**********************************/
void MEMORIA_demanaMemoria(Partida *game) {
	int i;
    
	game->tauler = (Casella**)malloc(game->col*sizeof(Casella*));		//Demanem memoria per les columnes

	for(i=0;i<game->col;i++) {
		game->tauler[i] = (Casella*)malloc(game->fila*sizeof(Casella));	//Demanem memoria per a les files de cada columna
	}  
}


/************************************
*
*@Finalitat: Allibera memoria del tauler dinamic.
*@Parametres:	in/out: game = Dades referents a la partida
*@Retorn: -------.
*
**********************************/
void MEMORIA_alliberaMemoria(Partida *game) {
	int i;
    
	for(i=0;i<game->fila;i++) {				//Alliberem la memoria de les columnes de cada fila
		free(game->tauler[i]);
	}  
    free(game->tauler);						//Alliberem la memoria de les files
}
