#include "expansor.h"

void inicializaarquivos() {

	arq_entrada = fopen(entrada, "r");
	arq_saida = fopen(saida, "w");

}

void finalizaarquivos() {
	fclose(arq_entrada);
	fclose(arq_saida);
}

void inicializaabela_macros(tabela_macros** tabela) {
	(*tabela) = (tabela_macros*) malloc(sizeof(tabela_macros));

	(*tabela)->primeiro = (apontador_macros) malloc(sizeof(celula_macros));
	(*tabela)->primeiro->prox = NULL;
	(*tabela)->ultimo = (*tabela)->primeiro;

	(*tabela)->tamanho = 0;
}

void insere_macro(item_macro item, tabela_macros *tabela) {
	tabela->ultimo->prox = (apontador_macros) malloc(sizeof(celula_macros));
	tabela->ultimo = tabela->ultimo->prox;

	tabela->ultimo->item = item;
	tabela->ultimo->prox = NULL;

	tabela->tamanho++;
}

item_macro gera_item_macro(char* nome, int parametro) {
	item_macro item;
	int tamanho;

	tamanho = strlen(nome) + 1;
	item.nome_macro = (char*) malloc(tamanho * sizeof(char));

//	strcpy( item.nome_macro, nome );
	item.nome_macro = strdup(nome);
	item.parametro = parametro;

	faz_lista_vazia(&(item.lista_comandos));

	return item;
}

apontador_macros busca_macro(char* nome, tabela_macros * macros) {
	apontador_macros aux;

	aux = macros->primeiro->prox;

	while (aux != NULL) {
		if (strcmp(aux->item.nome_macro, nome) == 0)
			return aux;

		aux = aux->prox;
	}

	return aux;
}

void imprime_macro(apontador_macros macro, char *parametro_atual) {
	char *inst, *operando, *rotulo;
	int param;

	apontador aux;

	inst = (char*) malloc( TAMANHO_INST * sizeof(char));
	operando = (char*) malloc( TAMANHO_ROT * sizeof(char));
	rotulo = (char*) malloc( TAMANHO_OPND * sizeof(char));

	aux = obtem_cabeca(macro->item.lista_comandos);

	aux = obtem_proximo(aux);
	while (aux != NULL) {

		strcpy(inst, obtem_comando(aux->item));
		strcpy(rotulo, obtem_rotulo(aux->item));
		strcpy(operando, obtem_operando(aux->item));
		param = parametro(aux->item);

		if (param) {
			if (strcmp(inst, "!") == 0)
				strcpy(inst, parametro_atual);
			if (strcmp(rotulo, "!") == 0)
				strcpy(rotulo, parametro_atual);
			if (strcmp(operando, "!") == 0)
				strcpy(operando, parametro_atual);
		}

		if (strlen(rotulo))
			fprintf(arq_saida, "%s: ", rotulo);

		fprintf(arq_saida, "%s ", inst);
		fprintf(arq_saida, "%s\n", operando);

		aux = obtem_proximo(aux);
	}

	free(inst);
	free(rotulo);
	free(operando);
}

void quebra_linha(char *linha, char **rotulo, char **inst, char **operando) {
	char *p_rot, *p_coment;

	(*inst) = (char*) malloc( TAMANHO_INST * sizeof(char));
	(*operando) = (char*) malloc( TAMANHO_OPND * sizeof(char));
	(*rotulo) = (char*) malloc( TAMANHO_ROT * sizeof(char));

	strcpy(*rotulo, "");
	strcpy(*operando, "");

	p_rot = strchr(linha, ':');
	p_coment = strchr(linha, ';');
	if (p_rot != NULL
			&& (p_coment == NULL || (p_rot - linha) < (p_coment - linha))) {
		sscanf(linha, "%s %s %s", *rotulo, *inst, *operando);
		(*rotulo)[strlen(*rotulo) - 1] = '\0';

	}

	else {
		sscanf(linha, "%s %s", *inst, *operando);
	}

}

void le_comandos_macro(item_macro *item_macro, char *parametro) {
	char *inst, *operando, *rotulo, *linha;
	int param = 0;
	item item_lista;

	linha = (char*) malloc( TAMANHO_LINHA * sizeof(char));

	fgets(linha, TAMANHO_LINHA, arq_entrada);
	while (strstr(linha, "ENDMACRO") == NULL) {
		if (linha[0] != 10) {
			quebra_linha(linha, &rotulo, &inst, &operando);

			if (item_macro->parametro) {
				param = 1;
				if (strcmp(rotulo, parametro) == 0)
					strcpy(rotulo, "!");

				if (strcmp(operando, parametro) == 0)
					strcpy(operando, "!");

				if (strcmp(inst, parametro) == 0)
					strcpy(inst, "!");
			}

			item_lista = gera_item(rotulo, inst, operando, param);
			insere(item_lista, item_macro->lista_comandos);

			free(inst);
			free(operando);
			free(rotulo);
		}
		fgets(linha, TAMANHO_LINHA, arq_entrada);
	}
}

tabela_macros* gera_tabela_macros() {
	tabela_macros* macros;
	item_macro item;

	int ret_scanf;
	char *inst, *rotulo, *linha, *parametro;
	int param;

	inicializaabela_macros(&macros);

	inst = (char*) malloc( TAMANHO_INST * sizeof(char));
	linha = (char*) malloc( TAMANHO_LINHA * sizeof(char));
	rotulo = (char*) malloc( TAMANHO_ROT * sizeof(char));
	parametro = (char*) malloc( TAMANHO_PARAM * sizeof(char));

	while (1) {
		fgets(linha, TAMANHO_LINHA, arq_entrada);
		param = 0;

		if (feof(arq_entrada)) {
			break;
		}
		if (linha[0] != 10) {
			if (strstr(linha, "BEGINMACRO") != NULL) {
				strcpy(rotulo, "");
				strcpy(parametro, "");

				ret_scanf = sscanf(linha, "%s %s %s", rotulo, inst, parametro);
				rotulo[strlen(rotulo) - 1] = '\0';

				if (strlen(parametro) && ret_scanf == 3)
					param = 1;

				item = gera_item_macro(rotulo, param);
				le_comandos_macro(&item, parametro);
				insere_macro(item, macros);

			}
		}
	}
	free(parametro);
	free(rotulo);
	free(inst);
	free(linha);
	return macros;
}

void expande_macros(tabela_macros* macros) {
	char *inst, *operando, *rotulo, *linha, *parametro;
	apontador_macros p_macro;

	linha = (char *) malloc( TAMANHO_LINHA * sizeof(char));
	parametro = (char *) malloc( TAMANHO_PARAM * sizeof(char));

	while (1) {
		fgets(linha, TAMANHO_LINHA, arq_entrada);

		if (feof(arq_entrada)) {
			break;
		}

		if (strstr(linha, "BEGINMACRO") != NULL) {
			fgets(linha, TAMANHO_LINHA, arq_entrada);

			while (strstr(linha, "ENDMACRO") == NULL)
				fgets(linha, TAMANHO_LINHA, arq_entrada);

			continue;
		}
		if (linha[0] != 10) {
			quebra_linha(linha, &rotulo, &inst, &operando);

		if (strlen(rotulo)) {
			fprintf(arq_saida, "%s: ", rotulo);
		}
		p_macro = busca_macro(inst, macros);
		if (p_macro != NULL) {

			//operando é o parametro
			if (p_macro->item.parametro)
				strcpy(parametro, operando);

			imprime_macro(p_macro, parametro);
		}

		else {
			fprintf(arq_saida, "%s ", inst);
			fprintf(arq_saida, "%s\n", operando);

		}

		free(rotulo);
		free(operando);
		free(inst);

	}}

}

