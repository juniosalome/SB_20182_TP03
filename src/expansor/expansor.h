#ifndef EXPANSOR_H
#define EXPANSOR_H

#include <stdint.h>
#include <stdio.h>
#include "lista.h"
#include "constantes.h"

typedef struct item_macro{
	char* nome_macro;
	int parametro;
	lista* lista_comandos;
	
}item_macro;

typedef struct celula_macros* apontador_macros;

typedef struct celula_macros{
	item_macro item;
	apontador_macros prox;
} celula_macros;

typedef struct tabela_macros{
	apontador_macros primeiro, ultimo;
	int tamanho;
}tabela_macros;

void inicializaarquivos();

void finalizaarquivos();

tabela_macros* gera_tabela_macros();

void expande_macros(tabela_macros* macros);

void le_comandos_macro(item_macro *item_macro, char *parametro );
#endif
