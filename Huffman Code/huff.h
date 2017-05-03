#include "huff.c"

//cria uma fila nula
Node* create_empty_queue();

//cria uma arvore nula
Node* create_empty_tree();

/*Função recebe um Node, se ele apontar pra
* nulo, retorna 1; Função pra chega se o Node
* é nulo/vazio
* */
int is_empty(Node *node);

//uma inserção normal de fila de prioridade 
Node* insert_node(Node *queue, Node *newqueue);


//crio o nó (com a letra e a frequencia) e já insiro em uma lista
Node* create_node(Node *queue, unsigned char letra, int frequency);

/* Cria um novo node e faz com que o primeiro da fila de prioridade seja o filho
 * à esquerda e com que o segundo seja o filho à direita
 * esse node vai ter como caractere o * e sua frequência vai ser a soma da
 * frequência dos filhos, e então ele é inserido novamente na fila
 */
Node *merge_node(Node *queue);

//Recebe a fila e a transforma em arvore huffman
Node *huff_tree(Node *queue);

//recebe uma arvore e printa ela em Pre order
void print_tree(Node* tree);

//Recebe uma arvore e retorna seu tamanho
int size_huff(Node *huff);

//Recebe uma arvore e retorna TRUE se tal nó for uma folha
int is_leaf(Node *huff);
