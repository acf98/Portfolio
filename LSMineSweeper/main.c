#include "grafics.h"
#include "logica.h"
#include "fitxers.h"


int main(void){
	char opcio = '0';
	
    while(opcio != '3'){
        LOGICA_mostraMenu();								//Mostrem el menu
		opcio = '0';
		LS_allegro_console_fflush();
		scanf("%c",&opcio);									//Agafem l'opcio del menu
		switch(opcio){
			
			case '1':
				LOGICA_opcio1();
			break;

			case '2':
				FITXERS_Ranking();
			break;
			case '3':
				printf("\nGracies per utilitzar el nostre programa!\n");
			break;
				
			default:
				if((opcio >= 'a' && opcio <= 'z') || (opcio >='A' && opcio <= 'Z')){
					printf("\nOpcio incorrecta!(L'opcio ha de ser un nombre)\n\n");
				} 
				else{
					printf("\nOpcio incorrecta!\n\n");
				}
		}
	}
	
	return 0;
}
