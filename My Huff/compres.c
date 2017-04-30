#include "util.c"
#include "HashT.c"

void freq_count(FILE* file, HashT *ht)
{
	unsigned int c;
	while(c = getc(file) != EOF)
	{
		ht -> table[c] -> freq++;
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
}

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
	char *bitshuff;
	int bit_index = 7;
	int lixo, i;
	rewind(arquivoCompactar);
	while(fscanf(arquivoCompactar, "%c", &byteLido) > 0)
	{
		bitshuff = getCharBits(ht, byteLido);//retorna o bit que representa esse caracter
		for(i = 0 ; i < strlen(bitshuff); ++i)
		{
			if(bitshuff[i] != '0')
				byte = set_bit(byte, bit_index);
			bit_index--;
			if(bit_index < 0)
			{
				bit_index = 7;
				fprintf(arquivoCompactado, "%c", byte);
				byte = 0;
			}
		}
	}
	lixo = bit_index + 1;
	if(lixo == 8)
		lixo = 0;
	else
		fprintf(arquivoCompactado, "%c", byte);

	return lixo;
}//RETORNA O TAMANHO DO LIXO


void compress(char* file_name)
{
	FILE *old_file, *new_file;
	Node *queue = create_empty_queue();
	HashT *hasht = create_hash();
	Node* huffman_tree = create_empty_tree();//---inicialização

	old_file = fopen(file_name, "rb");
	new_file = fopen("new_file.huff", "wb");

	freq_count(old_file, hasht);

	int i;
	for(i = 0; i < 256; i++)
	{
		if(hasht -> table[i] -> freq > 0)
			queue = create_node(queue, i, hasht -> table[i] -> freq);
	}//Inserindo todos os elementos que aparecem pelo menos uma vez na fila de prioridade

	huffman_tree = huff_tree(queue);//transformando fila em arvore
	fprintf(new_file, "00");//ocupando os dois primeiros bytes para guarda lugar pro lixo e size_tree
	preench_bit(huffman_tree, hasht);//criando as strings 1 e 0
	unsigned int tree_size = size_huff(huffman_tree) + escape(huffman_tree, 0);//pegando o tamanho da arvore
	print_tree_header(new_file, huffman_tree);//tratando os *

	char *tree_header_tam = (char*)malloc(13*sizeof(char));
	int_bina(tree_header_tam, tree_size, 13);//transformando o tamanho da arvore em binario

	unsigned int lixo = escreverArquivoCompactado(old_file, new_file, hasht);//pegando o tamanho do lixo

	char *qtdLixo = (char*)malloc(4*sizeof(char));
	int_bina(qtdLixo, lixo, 3);
	qtdLixo[3] = '\0';//transformando o tamanho da lixo em binario

	//montando o cabeçario
	char header[17] = "";
	strcpy(header, qtdLixo);
	header[3] = '\0';
	strcat(header, tree_header_tam);
	header[16] = '\0';
	printf("header-> %s\n", header);

	rewind(new_file);
	escreverBitsArquivo(new_file, header, 16);//coloca o header no incio do arquivo

	printf("\nCompactacao Finalizada!!");
	fclose(old_file);
	fclose(new_file);
}
