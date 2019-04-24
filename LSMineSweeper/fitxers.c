#include "fitxers.h"


/************************************
*
*@Finalitat: Mostra el ranquing del fitxer ranquing.txt.
*@Parametres:	----.
*@Retorn: ----.
*
**********************************/
	void FITXERS_Ranking() {
	FILE *f;
	char car;
	
		printf("####################################\n");
		printf("#  NOM  -  TAULELL  -  PUNTS  #\n");
		printf("####################################\n");
		f = fopen("ranquing.txt","r");								//Obrim el fitxer
		if(f == NULL) {												//Si no s'obre, no mostrem res
			printf("---------  --------- ---------\n");
		}
		else{
			fscanf(f,"%c",&car);									//LLegim la primera lletra
			if(feof(f)) {											//Si el fitxer ja s'ha acabat(esta buit), no mostrem res
				printf("-----  --------- ---------\n");
			}
			else{
				while(!feof(f)) {									//Anem mostrant fins que s'acabi el fitxer
					if(car == '#') {								//Si esta '#', posem el '-' per separar els diferents camps
						printf(" - ");
					}
					else{											//Mostrem l'ultim caracter guardat
						printf("%c", car);
					}
					fscanf(f,"%c",&car);							//Guardem el seguent caracter
				}
					printf("\n");
			}
			printf("\n");
			fclose(f);
		}
	}
	
	
	/**********************************************************************************************************************
*
*@Finalitat: Llegim el fitxer de text i guardem les dades del nivell
*@Parametres: 	in: f = Fitxer de text que hem de llegir, per poder extreure las nostres dades.
				in: nom_f = Nom del fitxer amb les dades del nivell.
				in/out: game = Variable on es guarden les dades de la partida.
*@Retorn: ------.
*
**********************************************************************************************************************/
void FITXER_llegeixFitxer(FILE *f,char nom_f[50],Partida *game) {
	char casell = 'a';
	int i = 0, j = 0;
 
	f = fopen(nom_f, "r");
	//Obrim el fitxer i mirem si existeix o no.
	if (f == NULL){
		printf("\nError! Aquest fitxer no existeix!\n");
	}
	else {
		printf("\nProcessant informacio...\n");
		game->col = 0;                              //Inicialitzem variables
        game->fila = 0;
		game->mina = 0;
		
		while (casell < '0' || casell > '9') {		//Busquem el primer nombre (columnes)
				fscanf(f,"%c",&casell);
		}

		while (casell != '\n') {						//Guardem el nombre de columnes
			game->col = game->col*10 + (casell - '0');
			fscanf(f,"%c",&casell);
		}
        
		fscanf(f,"%c",&casell);
		
		while (casell < '0' || casell > '9') {		//Busquem el segon nombre (files)
			fscanf(f,"%c",&casell);
		}
		
		while (casell != '\n') {						//Guardem el nombre de files
			game->fila = game->fila*10 + (casell - '0');
			fscanf(f,"%c",&casell);
		}
        
		fscanf(f,"%c",&casell);
	
		while (casell < '0' || casell > '9') {		//Busquem el tercer nombre (mines)
			fscanf(f,"%c",&casell);
		}

		while (casell != '\n') {						//Guardem el nombre de mines
			game->mina = game->mina * 10 + (casell - '0');
			fscanf(f,"%c",&casell);
		}
        
		fscanf(f,"%c",&casell);
		MEMORIA_demanaMemoria(game);				//Demanem memoria per a tot el taulell
        
		while (j <= (game->fila - 1)) {				//Bucle per les columnes
			while (i <= (game->col - 1)) {			//Bucle per les files
                if(casell > '0' || casell < '9') {	//Inicialitzem tot el tauler a partir de les dades del fitxer
					game->tauler[i][j].num = casell - '0';
                    game->tauler[i][j].mina = 0;
                    game->tauler[i][j].girat = 0;
				}

				if(casell == 'M') {
					game->tauler[i][j].num = 0;
					game->tauler[i][j].mina = 1;
					game->tauler[i][j].girat = 0;
				}
				i++;
				fscanf(f,"%c",&casell);
			}
			fscanf(f,"%c",&casell);
			i = 0;
			j++;
		}
		fclose(f);								//Tanquem el fitxer amb les dades del tauler
		printf("\nPartida iniciada correctament!\n");
	}
}

/**********************************************************************************************************************
*
*@Finalitat: Guardem la puntuacio del jugador al ranking.txt
*@Parametres: 	in: jug = Variable amb les dades del jugador.
*@Retorn: ------.
*
**********************************************************************************************************************/

void FITXERS_guardaRanking(Jugador jug) {
	FILE* f;
	
	f = fopen("ranquing.txt", "a");	//Obrim el fitxer
	
	fprintf(f,"\n%s#%s#%d",jug.nom,jug.fitxer,jug.punts);
	
	fclose(f);
}

