#include "logica.h"

/************************************
*
*@Finalitat: Mostra el menu del programa.
*@Parametres:	----.
*@Retorn: ----.
*
**********************************/
void LOGICA_mostraMenu() {
	printf("Menu:\n");
	printf("\t1- Nova partida\n");
	printf("\t2- Mostrar ranquing\n");
	printf("\t3- Sortir\n");	
	printf("\tOpcio: ");
}

/************************************
*
*@Finalitat: Inicialitza totes les dades del cursor.
*@Parametres:	in: cur = guarda la posició de cada moment al tauler.
*@Retorn: ----.
*
**********************************/
void LOGICA_inicialitzaCursor(Cursor *cur) {
		cur->x = 0;
		cur->y = INTERV;
		cur->cy = 0;
		cur->cx = 0;
	
	}

/************************************
*
*@Finalitat: Mostra la pantalla al finalitzar el joc.
*@Parametres:	in: fi = Indica la forma de la que ha acabat el joc.
* 				in: game = Variable amb totes les dades del joc.
* 				in: l = Llista amb les dades sobre les banderes.
* 				in: jug = Variable que conte la informació referent al jugador.
* 				in: cur = Variable amb la informacio del cursor del joc.
*@Retorn: ------.
*
**********************************/
void LOGICA_gameOver(int fi, Partida game, LlistaPDI l,Jugador *jug, Cursor cur){
	int nSortir = 0;
	
	while(!nSortir){
		GRAFICS_imprimeix(game, *jug,cur, fi, l);
	//Escoltem el teclat esperant la tecla ESC
		if(LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)){	//Esperem a que el jugador digui de sortir
			nSortir = 1;
		}
	}	
}


/************************************
*
*@Finalitat: Gira totes les caselles.
*@Parametres:	in/out: game = Variable que conte la informació referent al joc
*@Retorn: Retorna un '1'.
*
**********************************/
int LOGICA_minaTocada(Partida *game) {
	int i, p;
    for (i = 0; i < game->fila; i++) {
        for (p = 0; p < game->col; p ++) {
			game->tauler[p][i].girat = 1;
		}
	} 
	return 1;
}

/************************************
*
*@Finalitat: Comprova, si s'ha col·locat una bandera en aquella casella
*@Parametres:	in: cur = tipus format per una posició fila i columna.
* 				in: l = llista encarregada de guardar la posicio de cada casella on hem col·locat una bandera.
*@Retorn: 1 o 0 en funció de si troba la casella en la que estem a la llista o no.
*
**********************************/
int LOGICA_comprovaCoord(Cursor cur,LlistaPDI l) {
	int ok = 0;
	Bandera b;
	if (!LLISTAPDI_buida(l)) {
			LLISTAPDI_vesinici(&l);
            while(!LLISTAPDI_fi(l) && ok != 1){
                b = LLISTAPDI_consulta(l);
                if(b.f != cur.cy || b.c != cur.cx){
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
*@Finalitat: Controla el moviment del cursor.
*@Parametres:	in: game = variable que conte la informació referent al joc
* 				in/out: cur = posicio del cursor del joc.
*@Retorn: ---------.
*
**********************************/
void LOGICA_moureCursor(Cursor *cur, Partida game){
	
	//Si es prem la tecla W o la fletxa cap adalt, i no estem a un limit del tauler, el cursor puja
	if((LS_allegro_key_pressed(ALLEGRO_KEY_W) || LS_allegro_key_pressed(ALLEGRO_KEY_UP)) && cur->cy > 0){
		cur->cy--;
		cur->y= cur->y - CAS;
	}
	
	//Si es prem la tecla S o la fletxa cap abaix, i no estem a un limit del tauler, el cursor baixa
	if((LS_allegro_key_pressed(ALLEGRO_KEY_S) || LS_allegro_key_pressed(ALLEGRO_KEY_DOWN)) && cur->cy < game.fila -1){
		cur->cy++;
		cur->y= cur->y + CAS;
	}

	//Si es prem la tecla A o la fletxa cap esquerra, i no estem a un limit del tauler, el cursor va a l'esquerra
	if((LS_allegro_key_pressed(ALLEGRO_KEY_A) || LS_allegro_key_pressed(ALLEGRO_KEY_LEFT)) && cur->cx > 0){
		cur->cx--;
		cur->x= cur->x - CAS;
	}
	
	//Si es prem la tecla D o la fletxa cap a la dreta, i no estem a un limit del tauler, el cursor va a la dreta
	if((LS_allegro_key_pressed(ALLEGRO_KEY_D) || LS_allegro_key_pressed(ALLEGRO_KEY_RIGHT)) && cur->cx < game.col -1){
		cur->cx++;
		cur->x= cur->x + CAS;
	}
}

/************************************
*
*@Finalitat: Fer les interaccions del jugador amb el joc, exceptuant el moviment del cursor.
*@Parametres:	in/out: nSortir = Quan te el valor de 1, el jugador surt de la partida.
* 				in/out: game = Variable amb les dades de la partida.
* 				in/out: l = punter a la llista que guarda les banderes.
* 				in/out: girades = Recompte de les caselles girades.
* 				in: cur = posicio del cursor del joc.
*@Retorn: Estat amb el que el jugador acaba la partida.
*
**********************************/
int LOGICA_accions(int* nSortir,Partida *game,LlistaPDI* l,int* girades,Cursor cur){
	int fi=0;
	
	//Si es prem ESC, es sortira de la partida.
	if(LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)){
		*nSortir = 1;
		fi = 0;
	}
	
	//Si es prem B, s'inserira una bandera. Si ja n'hi ha una, es treura.
	if(LS_allegro_key_pressed(ALLEGRO_KEY_B) && game->tauler[cur.cx][cur.cy].girat == 0){
		LOGICA_insereixBandera(l,cur);
	}
	
	//Si es prem la barra espaiadora, es girara la casella
	if(LS_allegro_key_pressed(ALLEGRO_KEY_SPACE) && game->tauler[cur.cx][cur.cy].girat == 0 && !LOGICA_comprovaCoord(cur,*l)){
		game->tauler[cur.cx][cur.cy].girat = 1;
		if (game->tauler[cur.cx][cur.cy].mina == 1){	//Si hi ha una mina, es giraran totes i es perdra la partida.
			fi = LOGICA_minaTocada(game);
		}
		else{
			*girades = *girades + 1; //Comptem que s'ha girat una casella més
		}
	}
	
	//Si es giren totes les caselles que no son mines, s'acaba el joc amb el codi de victoria
	if(*girades == game->col*game->fila - game->mina){	
		fi = 2;
	}
	
	return fi;
}

/************************************
*
*@Finalitat: Inserir una bandera, o treurela si ja n'hi ha una a la casella.
*@Parametres:	in/out: l = punter a la llista que guarda les banderes.
* 				in: cur = posicio del cursor del joc.
*@Retorn: ---------.
*
**********************************/
void LOGICA_insereixBandera(LlistaPDI *l,Cursor cur){
	int bandera = 0;
	Bandera b;
			if (!LLISTAPDI_buida(*l)){
				LLISTAPDI_vesinici(l);
				while(!LLISTAPDI_fi(*l)){
					b = LLISTAPDI_consulta(*l);
					if(b.c != cur.cx || b.f != cur.cy){

						LLISTAPDI_avanca(l);
					}
					else{
						bandera = 1;
						LLISTAPDI_esborra(l);
						
					}
				}
				if (bandera == 0){
					LLISTAPDI_insereix(l, cur); 
				}
			}
			else{
			LLISTAPDI_insereix(l, cur);
			}
}

/************************************
*
*@Finalitat: Inicia la partida.
*@Parametres:	in: game = variable que conte la informació referent al joc
* 				in/out: jug = informacio del jugador (nom, nom del fitxer i punts)
*@Retorn: Forma en la que ha acabat la partida.
*
**********************************/
int LOGICA_partida(Partida game,Jugador *jug){
	int nSortir = 0, girades = 0;
	int fi; //0 = el jugador ha sortit //1 = el jugador ha tocat una mina //2 = el jugador ha guanyat
	Cursor cur;
	LlistaPDI l;	jug->punts = 0;
	
	//Inicialitzem totes les variables
	l = LLISTAPDI_crea();
	LOGICA_inicialitzaCursor(&cur);
	GRAFICS_inicialitzaAllegro(CAS*game.col + INTERH,CAS*game.fila + INTERV); //Inicialitzem la finestra grafica
	TEMPS_inicialitzaTemps(&game);
	
	//Bucle infinit del joc
	while(!nSortir && !fi){
		//Comprovem quines accions fa el jugador
		LOGICA_moureCursor(&cur,game);
		fi = LOGICA_accions(&nSortir,&game,&l,&girades,cur);
		
		TEMPS_pintaTemps(&game);
		GRAFICS_imprimeix(game, *jug,cur, fi, l);
	}
	//Agafem la puntuacio
	jug->punts = game.temps*game.mina;
	LLISTAPDI_destrueix(&l);
	if(fi!=0){									//Si el jugador no surt voluntariament, anem a la pantalla de GameOver
		LOGICA_gameOver(fi,game,l, jug, cur);
	}
	//Tanquem la finestra gràfica
	LS_allegro_exit();
	
	return fi;
}

/************************************
*
*@Finalitat: Mostra  els missatges del final de la partida.
*@Parametres:	in: fi = Nombre que marca com ha acabat la partida.
* 				in/out: jug = informacio del jugador (nom, nom del fitxer i punts).
*@Retorn: -------.
*
**********************************/
void LOGICA_final(Jugador jug,int fi){
	switch (fi){
		case 0:
			printf("Partida finalitzada per jugador\n(..)\n");
		break;
		
		case 1:
			printf("\nHas perdut la partida!\n");
		break;
		
		case 2:
			printf("El jugador: %s\n",jug.nom);
			printf("Puntuacio: %d\n",jug.punts);
			printf("\nPartida finalitzada correctament\n(..)\n");
			FITXERS_guardaRanking(jug);
		break;
		
		default:
			printf("Error, codi de sortida incorrecte\n");
	}
	
}

/************************************
*
*@Finalitat: Inicia l'opcio 1 del menu principal.
*@Parametres:----.
*@Retorn: ----.
*
**********************************/
void LOGICA_opcio1(){
	Jugador jug;
	Partida game;
	FILE *f;
	int fi = 0; //Nombre de files i columnes
    
	printf("\nIntrodueix el nom del jugador:");						//Agafem nom del jugador
	LS_allegro_console_fflush();
	gets(jug.nom);
    
	while(strlen(jug.nom) > MAXC) {
		LS_allegro_console_fflush();
		printf("Error, nom del jugador massa llarg\n\nIntrodueix el nom del jugador:");
		gets(jug.nom);
	}
	printf("Introdueix nom del fitxer:");							//Agafem nom del fitxer
	LS_allegro_console_fflush();
	gets(jug.fitxer);
	f = fopen(jug.fitxer,"r");
     
	while(f == NULL) {												//Si no existeix, el tornem a demanar
		printf("\nError, no es troba el fitxer!\n");
		printf("Introdueix nom del fitxer:");
		LS_allegro_console_fflush();
		scanf("%s",jug.fitxer);
		f = fopen(jug.fitxer,"r");
	}
	
	FITXER_llegeixFitxer(f,jug.fitxer, &game);	
	fclose(f);
    
	//Aqui comença la partida
	
	fi = LOGICA_partida(game,&jug);
	//Depenent de com hagi acabat la partida, mostrem una informacio per pantalla
	
	LOGICA_final(jug,fi);
}