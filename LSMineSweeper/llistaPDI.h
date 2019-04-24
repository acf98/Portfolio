/***********************************************
*
* @Proposit: Procediments i funcions que s'encarreguen de gestionar una llistaPDI.
* @Autor/s: Marc Cespedes i Alex Cabezas
* @Data creacio: 6/5/2018
* @Data ultima modificacio: 14/05/2018
*
************************************************/

#ifndef _LLISTAPDI_H_
#define _LLISTAPDI_H_

#include "tipus.h"

typedef struct n{
    Bandera b;
    struct n *seg;
} Node;

typedef struct {
    Node *pri;
    Node *ant;
} LlistaPDI;

LlistaPDI LLISTAPDI_crea();
void LLISTAPDI_insereix(LlistaPDI *l, Cursor c);
Bandera LLISTAPDI_consulta(LlistaPDI l);
void LLISTAPDI_esborra(LlistaPDI *l);
void LLISTAPDI_avanca(LlistaPDI *l);
void LLISTAPDI_vesinici(LlistaPDI *l);
int LLISTAPDI_fi(LlistaPDI l);
int LLISTAPDI_buida(LlistaPDI l);
void LLISTAPDI_destrueix(LlistaPDI *l);

#endif