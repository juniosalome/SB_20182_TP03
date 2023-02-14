#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constantes.h"

typedef struct{
	char* rotulo;
	char* comando;
	char* operando;
	int parametro;
} item;

typedef struct celula *apontador;

typedef struct celula {
	item item;
	apontador prox;
} celula;

typedef struct{
	apontador primeiro,ultimo;
	int tamanho;
} lista;


void faz_lista_vazia( lista** lista );
void insere( item item, lista* lista );

int vazia( lista* lista );

item gera_item( char* rotulo, char* comando, char* operando, int parametro );

char* obtem_comando ( item item );
char* obtem_rotulo  ( item item );
char* obtem_operando( item item );
int parametro( item item );

apontador obtem_cabeca ( lista * lista );
apontador obtem_proximo( apontador celula );

#endif 
