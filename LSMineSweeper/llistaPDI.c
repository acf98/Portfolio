#include "llistaPDI.h"

/************************************
*
*@Finalitat: Crea una nova llista.
*@Parametres:	------.
*@Retorn: Retorna la llista que es crea.
*
**********************************/
LlistaPDI LLISTAPDI_crea() {
        LlistaPDI l;
        
        l.pri = (Node*)malloc(sizeof(Node));
        
        if(l.pri == NULL) {
            printf("Error!\n");
        }
        else {
            l.ant = l.pri;
            l.pri->seg = NULL;
        }
        return l;
}

/************************************
*
*@Finalitat: Inserir un nou element a la llista.
*@Parametres:	in/out: l = punter a la llista que modifiquem.
* 				in = dades del cursor del joc.
*@Retorn: -------.
*
**********************************/
void LLISTAPDI_insereix(LlistaPDI *l, Cursor cur) {
    Node *aux;
    aux = (Node*)malloc(sizeof(Node));
    
    if (aux == NULL) {
        printf("Error!\n");
    }
    else {
        aux->b.f = cur.cy;
        aux->b.c = cur.cx;
        aux->seg = l->ant->seg;
        l->ant->seg = aux;
        l->ant = aux;
    }
}

/************************************
*
*@Finalitat: Agafa informacio d'un element de la llista.
*@Parametres:	in: l = Llista de la qual agafem informacio.
*@Retorn: Retorna informacio del element de la llista actual.
*
**********************************/
Bandera LLISTAPDI_consulta(LlistaPDI l) {
    Bandera b;
    b.f = -1;
    b.c= -1;
    
    if (l.ant->seg != NULL) {
        b.f = l.ant->seg->b.f;
		b.c = l.ant->seg->b.c;
    }
    return b;
}

/************************************
*
*@Finalitat: Esborra l'element actual de la llista.
*@Parametres:	in/out: l = punter a la llista que modifiquem.
*@Retorn: ------.
*
**********************************/
void LLISTAPDI_esborra(LlistaPDI *l) {
    Node *aux;
    
    if(l->ant->seg == NULL) {
        printf("Error!\n");
    }
    else{
        aux = l->ant->seg;
        l->ant->seg = aux->seg;
        free(aux);
    }
}

/************************************
*
*@Finalitat: Apuntem al seguent element de la llista.
*@Parametres:	in/out: l = punter a la llista que modifiquem.
*@Retorn: -------.
*
**********************************/
void LLISTAPDI_avanca(LlistaPDI *l) {
   if(l->ant->seg == NULL){
        printf("Error!\n");
    }
    else {
        l->ant = l->ant->seg;
    }
}

/************************************
*
*@Finalitat: Apuntem al primer element de la llista.
*@Parametres:	in/out: l = punter a la llista que modifiquem.
*@Retorn: ------.
*
**********************************/
void LLISTAPDI_vesinici(LlistaPDI *l) {
    l->ant = l->pri;
}

/************************************
*
*@Finalitat: Comprovem si hi ha un element mes a la llista.
*@Parametres:	in: l = Llista de la que comprovem la informacio.
*@Retorn: Retorna un 1 si s'esta al final de la llista, i un 0 si hi ha un altre element.
*
**********************************/
int LLISTAPDI_fi(LlistaPDI l) {
    int a=0;
	
    if(l.ant->seg == NULL) {
		a = 1;
	}
    
	return a;
}

/************************************
*
*@Finalitat: Comprovem si la llista esta buida.
*@Parametres:	in: l = Llista de la que comprovem la informacio.
*@Retorn: Retorna un 1 si la llista esta buida, i un 0 si hi ha elements.
*
**********************************/
int LLISTAPDI_buida(LlistaPDI l) {
    return l.pri->seg == NULL;
}

/************************************
*
*@Finalitat: Eliminem la llista.
*@Parametres:	in/out: l = punter a la llista que modifiquem.
*@Retorn: -------.
*
**********************************/
void LLISTAPDI_destrueix(LlistaPDI *l) {
    Node *aux;
    
    while(l->pri != NULL){
        aux = l->pri;
        l->pri = aux->seg;
        free(aux);
    }
    
    l->ant = NULL;
}