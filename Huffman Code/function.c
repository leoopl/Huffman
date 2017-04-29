void freq_count(FILE* file, HashT *ht)
{
	fopen(file, "rb");
	unsigned int c;
	while(c = gets(file) != EOF)
	{
		ht -> table[c] -> freq++;
	}
	fclose(file);
}//conta a frequencia e ja manda pra hash

int i;
for(i = 0; i < 256; i++)
{
	if(table[i] -> freq > 0)
		queue = create_node(queue, i, table[i] -> freq);
}//Inserindo todos os elementos que aparecem pelo menos uma vez na fila de prioridade

char *tree_header_tam = (char*)malloc(13*sizeof(char));
int_bina(tree_header_tam, size_huff(ARVORE), 13);//transformando o tamanho da arvore em binario

void print_tree_header(FILE* file, Node* huff){
  if(huff != NULL){
    if((huff -> data == 42 || huff -> data == '\\') && is_leaf(huff)){
      fprintf(file, "\\%c", huff -> data);
    } else {
      fprintf(file, "%c", huff -> data);
    }
		print_tree_header(file, huff -> left);
		print_tree_header(file, huff -> right);
	}
}//trata o caso dos * e do \\ 

int escreverArquivoCompactado(FILE *arquivoCompactar, FILE *arquivoCompactado, HashT* ht)
{
	unsigned char byteLido;
	unsigned char byte = 0;
	char *bitshuff;
	int bit_index = 7;
	int lixo;
	int i;
	rewind(arquivoCompactar);
	while(fscanf(arquivoCompactar, "%c", &byteLido) > 0)
	{
		bitshuff = getCharBits(ht, byteLido);
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

char *qtdLixo = (char*)malloc(4*sizeof(char));
int_bina(qtdLixo, lixoqtd, 3);
qtdLixo[3] = '\0';-----------




int getFrequencia(HTable *table, int posicao){
	return table->elementos[posicao]->frequencia;
}

int getTamHTable(){
	return TAM_HTABLE;
}
