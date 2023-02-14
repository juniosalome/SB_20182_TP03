#include "lista.h"

char* obtem_operando(item item){
	return item.operando;
}

char* obtem_comando(item item){
	return item.comando;
}

char* obtem_rotulo(item item){
	return item.rotulo;
}

int parametro(item item){
	return item.parametro;
}

item gera_item( char* rotulo, char* comando, char* operando, int parametro ){
	item item;
	int tamanho;

	tamanho = strlen( rotulo ) + 1;
	item.rotulo = ( char* ) malloc ( tamanho * sizeof( char ));

	tamanho = strlen( comando ) + 1;
	item.rotulo = ( char* ) malloc ( tamanho * sizeof( char ));
	
	tamanho = strlen( operando ) + 1;
	item.rotulo = ( char* ) malloc ( tamanho * sizeof( char ));
	
	item.rotulo = strdup( rotulo );
	item.comando = strdup( comando );
	item.operando = strdup( operando );
	item.parametro = parametro;

	return item;
}

void faz_lista_vazia(lista **lista)
{
	(*lista)=malloc(sizeof(lista));
	(*lista)->primeiro=(apontador)malloc(sizeof(celula));
	(*lista)->primeiro->prox = NULL;
	(*lista)->ultimo=(*lista)->primeiro;
	(*lista)->tamanho = 0;
}

int vazia(lista *lista){
	return (lista->primeiro==lista->ultimo);
}

void insere(item item,lista *lista){
	apontador aux;

	aux=(apontador)malloc(sizeof(celula));
	
	lista->ultimo->prox=(apontador)malloc(sizeof(celula));
	lista->ultimo=lista->ultimo->prox;

	lista->ultimo->item=item;
	lista->ultimo->prox=NULL;
	
	lista->tamanho++;
}

apontador obtem_cabeca(lista* lista){
	return lista->primeiro;
}

apontador obtem_proximo(apontador celula){
	return celula->prox;
}
