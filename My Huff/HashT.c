#include <string.h>
#include "huff.c"
#define TAM_HASH 256

typedef struct element
{
	unsigned char letter;
	int freq;
	char bitstring[256];
}Element;

typedef struct hash_table
{
	Element *table[TAM_HASH];
}HashT;

//cria hash
HashT *create_hash()
{
	int i;
	HashT *ht = (HashT*) malloc(sizeof(HashT));
	for (i = 0; i < TAM_HASH; ++i)
	{
		ht -> table[i] = (Element*) malloc(sizeof(Element));
		ht -> table[i] -> letter = i;
		ht -> table[i] -> freq = 0;
	}
	return ht;
}

//copia a string do bit para a hash
void addCharBits(HashT *ht, unsigned char c, char *bits)
{
	strcpy(ht -> table[(int)c] -> bitstring, bits);
}

//retorna o bit que representa esse caracter
char *getCharBits(HashT *ht, unsigned char c)
{
	return ht -> table[(int)c] -> bitstring;
}

/*PECORRE A ARVORE E CRIA STRING COM O CAMINHO DE CADA LETRA; adicionando sempre na hash
 *DIREITA 1, ESQUERDA 0;
 *tem o esquema de corta o ultimo bit quando chamar a recussão(não to me lembrando bem)
 */
void build_representations(Node *tree, unsigned char *bit_string, int index, unsigned char bit, HashT *ht)
{
	if(index > -1)//Se estiver em -1 foi a primeira chamada da função, portanto tree ainda é a raiz da árvore
	{
		bit_string[index] = bit;//vai sempre salvando o bit passado na pos correta da string
		if(is_leaf(tree))
		{
			bit_string[index + 1] = '\0';
			strcpy(ht -> table[(int)tree->letter] -> bitstring, bit_string);
			//printf("%s\n", bit_string);
		}
	}
	//As chamadas recursivas vão para esquerda ou para direita, passando respectivamente 0 ou 1 como bits
	//e incrementando o index para avançar na string, quando for feito o backtrack o index volta para o anterior
	if(tree->left != NULL)
		build_representations(tree->left, bit_string, index + 1, '0', ht);
	if(tree->right != NULL)
		build_representations(tree->right, bit_string, index + 1, '1', ht);
	return;
}