#include "compres.c"
//#include "descompres.c"

int main()
{
	int esc;
	char file_name[100];
	printf("O que deseja:\n 1 - Compactar Arquivo\n 2 - Descompactar Arquivo\n");
	scanf("%d", &esc);
	switch(esc)
	{
		case 1:
			printf("Digite o nome do arquivo a ser compactado:\n");
			scanf("%s", file_name);
			printf("Iniciando Compactacao...\n");
			compress(file_name);
			break;
		case 2:
			printf("Digite o nome escolhido para o arquivo de saida:\n");
			scanf("%s", file_name);
			printf("Iniciando Descompactacao...\n");
			//descompress(file_name);
			break;
		default:
			printf("Opcao invalida! Tente novamente.\n");
	}

	return 0;
}