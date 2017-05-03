#include "util.c"
#include "HashT.c"
#include <string.h>

void freq_count(FILE* file, HashT *ht)
{
	unsigned char *buffer;
	fseek(file , 0 , SEEK_END);
	int file_size = ftell(file);//ler o arquivo e diz o tamanho dele
	rewind(file);
	buffer = (unsigned char*) malloc(sizeof(char)*file_size);
	fread(buffer, 1, file_size, file);
	int i;
	for(i=0; i<file_size; i++)
	{
		ht -> table[buffer[i]] -> freq++;
	}

}//conta a frequencia e ja manda pra hash

int escape(Node* huff, int escapes)
{
	if(huff != NULL)
	{
    	if((huff -> letter == 42 || huff -> letter == '\\') && is_leaf(huff))
    		++escapes;
		escapes = escape(huff -> left, escapes);
		escapes = escape(huff -> right, escapes);
	}
  return escapes;
}//CONTA A FREQUENCIA DOS SCAPES PRA COLOCAR NO TAMANHO DA ARVORE

void print_tree_header(FILE* file, Node* huff)
{
	if(huff != NULL)
	{
    	if((huff -> letter == 42 || huff -> letter == '\\') && is_leaf(huff))
    	{
    	  fprintf(file, "\\%c", huff -> letter);
    	}else
    	{
    	  fprintf(file, "%c", huff -> letter);
    	}
		print_tree_header(file, huff -> left);
		print_tree_header(file, huff -> right);
	}
}//trata o caso dos *

int escreverArquivoCompactado(FILE *arquivoCompactar, FILE *arquivoCompactado, HashT* ht)
{
	unsigned char byteLido;
	unsigned char byte = 0;
	char *bitshuff = NULL;
	int bit_index = 7;
	int i;
	rewind(arquivoCompactar);

	while(fscanf(arquivoCompactar, "%c", &byteLido) > 0)
	{
		bitshuff = getCharBits(ht, byteLido);//retorna o bit que representa esse caracter
		//printf("%s\n", bitshuff);
		for(i = 0 ; i < strlen(bitshuff); ++i)
		{
			if(bit_index == -1)
			{
				fprintf(arquivoCompactado, "%c", byte);
				byte = 0;
				bit_index = 7;
			}
			if(bitshuff[i] == '1')
			{
				byte = set_bit(byte, bit_index);
			}
			bit_index--;
		}
	}
	if(bit_index <= 7)
	{
		fprintf(arquivoCompactado, "%c", byte);
	}
	bit_index++;

	return bit_index;
}//RETORNA O TAMANHO DO LIXO



void compress(char* file_name)
{
	FILE *old_file, *new_file;
	Node *queue = create_empty_queue();
	HashT *hasht = create_hash();
	Node* huffman_tree = create_empty_tree();//---inicialização
	int i;

	old_file = fopen(file_name, "rb");
	new_file = fopen("new_file.huff", "wb");

	freq_count(old_file, hasht);

	for(i = 0; i < 256; i++)
	{
		if(hasht -> table[i] -> freq > 0)
			queue = create_node(queue, i, hasht -> table[i] -> freq);
	}//Inserindo todos os elementos que aparecem pelo menos uma vez na fila de prioridade

	huffman_tree = huff_tree(queue);//transformando fila em arvore

	//preinta a arvore em pre orden
	//print_tree(huffman_tree);

	fprintf(new_file, "00");//ocupando os dois primeiros bytes para guarda lugar pro lixo e size_tree

	unsigned char bit_string[255];
	build_representations(huffman_tree, bit_string, -1, '0', hasht);


	unsigned int tree_size = size_huff(huffman_tree) + escape(huffman_tree, 0);//pegando o tamanho da arvore
	print_tree_header(new_file, huffman_tree);//tratando os *

	char *tree_header_tam = (char*)malloc(13*sizeof(char));
	int_bina(tree_header_tam, tree_size, 13);//transformando o tamanho da arvore em binario


	//printa o binario da arvore
	//printf("\nbin %s\n", tree_header_tam);
	//printf("tamanho arvore %d\n", tree_size);


	unsigned int lixo = escreverArquivoCompactado(old_file, new_file, hasht);//pegando o tamanho do lixo


	char *qtdLixo = (char*)malloc(4*sizeof(char));
	int_bina(qtdLixo, lixo, 3);
	qtdLixo[3] = '\0';//transformando o tamanho da lixo em binario


	//printa tamnhao do lixo, o binario do lixo
	//printf("\n%d lixo %s\n", lixo, qtdLixo);



	//montando o cabeçario
	char header[17] = "";
	strcpy(header, qtdLixo);
	header[3] = '\0';
	strcat(header, tree_header_tam);
	header[16] = '\0';

	//printa o cabeçario
	//printf("header-> %s\n", header);

	rewind(new_file);
	escreverBitsArquivo(new_file, header, 16);//coloca o header no incio do arquivo

	printf("\nCompactacao Finalizada!!");
	fclose(old_file);
	fclose(new_file);
}
