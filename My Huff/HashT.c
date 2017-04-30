#include <string.h>
#include "huff.c"
#define TAM_HASH 256

typedef struct element
{
	unsigned char letter;
	int freq;
	char bitstring[30];
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
void preench_bit(Node *huff, HashT *ht)
{
	char bit[30];
	int i;
	for(i = 0; i < 30; ++i)//SETANDO TUDO COM CARACTER NULO; PRA NAO TER PROBLEMA COM LIXO;
		bit[i] = '\0';

	if(huff != NULL)
	{
		if(is_leaf(huff))
		{
			addCharBits(ht, huff->letter, bit);
		}else
		{
			int tam_bit = strlen(bit);
			bit[tam_bit] = '0';
			bit[tam_bit + 1] = '\0';
			preench_bit(huff -> left, ht);
			bit[tam_bit] = '1';
			bit[tam_bit + 1] = '\0';
			preench_bit(huff -> right, ht);
		}
	}
}