#include "util.c"

/*A função set_bit recebe um char que representará,
 * o byte que queremos alterar, e um inteiro i, que
 * representa qual bit queremos setar. A função retorna
 * um inteiro que será o valor do bit setado, e ela tem como
 * objetivo setar um bit especifico do nosso byte.
 * */
int set_bit(unsigned char c, int i);

/* A função recebe um char que representará
 * o byte que queremos analisar, e um inteiro i, que
 * representa qual bit queremos verificar desse byte.
 * A função retorna 0 para se o bit não estiver setado,
 * e 1 para se ele estiver setado.
 * */
int is_bit_i_set(unsigned char c, int i);

/* A função recebe uma string, o inteiro que serar
 * o número a ser convertido para binário, e a quantidade
 * de bits que ele deve ter.
 * tem como objetivo transformar o número inteiro em binário.
 * */
void int_bina(char* bin, int num, int bits);

/*A função recebe uma string, que representa
 * um número binário, e um inteiro, que é o tamanho
 * desse número, retorna um inteiro que será esse número em
 * decimal.
 * */
int bina_int(char *bin, int tam);

/* A função escreverBitsArquivo recebe um arquivo, onde iremos
 * escrever, uma string de bits, e o tamanho dessa string.
 * tem como objetivo escrever no arquivo esses bits.
 * */
void escreverBitsArquivo(FILE *arquivo, char *bits, int tam);

