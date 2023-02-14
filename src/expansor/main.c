#include "expansor.h"

int main( int argc, char* argv[] )
{

	/*Inicialização dos argumentos*/


		//Nome arquivo de entrada
		entrada = argv[1];
		//Nome arquivo de saida
		saida = argv[2];
	
	tabela_macros* macros;
	inicializaarquivos();
	macros = gera_tabela_macros();
	rewind( arq_entrada );
	expande_macros(macros);

	return 0;
}
