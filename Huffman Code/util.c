#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int set_bit(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask | c;
}// seta bit na posicao i

int is_bit_i_set(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask & c;
}//verifica se o bit 1 está setado (definido) na posicao i

int getUniqueBit(unsigned int c, int i)
{
	unsigned char mask = c >> i;
	return mask & 1;
}

void int_bina(char* bin, int num, int bits)
{
	int i;
	for(i=0; i<bits; i++)
	{
		bin[bits-i-1] = getUniqueBit(num,i)+'0';
	}
	bin[strlen(bin)] = '\0';
}//transforma int em binario

int bina_int(char *bin, int tam)
{
	int valor = 0;
	while(tam>0)
	{
		if(*bin == '1')
			valor += pow(2,(tam-1));
		tam--;
		bin = bin+1;
	}
	return valor;
}//transforma binario em inteiro

void escreverBitsArquivo(FILE *arquivo, char *bits, int tam)
{
	int i;
	unsigned char byte = 0;
	int bit_index = 7;
	for(i = 0 ; i<tam; i++)
	{
		if(bits[i] != '0')
			byte = set_bit(byte, bit_index);
		bit_index--;
		if(bit_index < 0)
		{
			bit_index = 7;
			fprintf(arquivo, "%c", byte);
			byte = 0;
		}
	}
}
