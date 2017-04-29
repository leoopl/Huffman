#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;

struct node
{
	unsigned char letter;
	int freq;
	Node *next;
	Node *left;
	Node *right;
};

Node* create_empty_queue()
{
    return NULL;
}

Node* create_empty_tree()
{
	return NULL;
}

int is_empty(Node *node)
{
	return (node == NULL);
}

Node* insert_node(Node *queue, Node *newqueue)
//um normal enqueue de priority queue
{
	if(queue == newqueue)
	{
		newqueue -> next = NULL;
		return newqueue;
	}else if(is_empty(queue) || newqueue->freq <= queue->freq)
	{
		newqueue -> next = queue;
		return newqueue;
	}else
	{
		Node *aux = queue;
		while(aux->next != NULL && newqueue ->freq > aux->next->freq)
			aux = aux->next;
		newqueue->next = aux->next;
		aux->next = newqueue;
		return queue;
	}
}

Node* create_node(Node *queue, unsigned char letra, int frequency)
//crio o nó (com a letra e a frequencia) e já insiro em uma lista
{
	Node *new_node = (Node*) malloc(sizeof(Node));
	new_node -> letter = letra;
	new_node -> freq = frequency;
	new_node -> next = NULL;
	new_node -> left = NULL;
	new_node -> right = NULL;
	queue = insert_node(queue, new_node);
	return queue;
}

Node *merge_node(Node *queue)
//função no qual eu dou merge com os dois nó de menor freguencia
{
	Node *new_node = (Node*) malloc(sizeof(Node));
	new_node -> left = queue;
	new_node -> right = queue -> next;
	if(new_node->right->next != NULL)
		queue = new_node->right->next;
	else
		queue = new_node;
	new_node -> left -> next = NULL;
	new_node -> right -> next = NULL;
	new_node -> letter = '*';
	new_node -> freq = (new_node->left->freq) + (new_node->right->freq);
	queue = insert_node(queue, new_node);
	return queue;
}

Node *huff_tree(Node *queue)
//função que chama merge na fila toda até se torna uma arvore
{
	//caso só tem 1 nó, não preciso da merge, só preciso criar um novo nó no qual vai ter a mesma frequencia do anterior
	if(queue->next == NULL)
	{
		Node *new_node = (Node*) malloc(sizeof(Node));
		new_node -> left = queue;
		new_node -> right = NULL;
		new_node -> letter = '*';
		new_node -> freq = queue -> freq;
		queue = new_node;
	}else
	{
		while(queue->next != NULL)
			queue = merge_node(queue);
	}
	return queue;
}

void print_tree(Node* tree)
{
	if(tree != NULL)
	{
		printf("%c", tree -> letter);
		print_tree(tree -> left);
		print_tree(tree -> right);
	}
}

//TAMANHO DA ARVORE HUFFMAN
int size_huff(Node *huff)
{
	if(huff == NULL)
		return 0;
	else
		return 1 + size_huff(huff->left) + size_huff(huff->right);
}

int is_leaf(Node *huff)
{
	return (huff -> left == NULL && huff -> right == NULL);
}

int main()
{
	Node *queue = create_empty_queue();
	char A,B,C,D,E,F,G,H,I,J,K,L,M;
	queue = create_node(queue, 'A', 4);
	queue = create_node(queue, 'B', 2);
	queue = create_node(queue, 'C', 7);
	queue = create_node(queue, 'D', 2);
	queue = huff_tree(queue);
	print_tree(queue);
	printf("\n%d\n", size_huff(queue));

	return 0;
}
