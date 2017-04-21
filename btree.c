#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

int posicaoarray = 0;

typedef struct BinaryTree
{
    int value;
    struct BinaryTree *left;
    struct BinaryTree *right;
} BinaryTree;

int isEmpty(BinaryTree *bt)
{
    return (bt == NULL);
}
BinaryTree *createBinaryTree(int value)
{
    BinaryTree *bt = (BinaryTree*)malloc(sizeof(BinaryTree));
    bt->value = value;
    bt->left = NULL;
    bt->right = NULL;
    return bt;
}

BinaryTree *insert(BinaryTree *bt, int value)
{
    if (bt == NULL)
    {
        return createBinaryTree(value);
    }

    if (value < bt->value)
        bt->left  = insert(bt->left, value);
    else
    {
        bt->right = insert(bt->right, value);
    }
    return bt;
}

void search(BinaryTree *bt, int nivel,  int *array)
{
    if (!isEmpty(bt))
    {
        array[posicaoarray] = nivel;
        posicaoarray++;
        search(bt->left, nivel+1, array);
        search(bt->right, nivel+1, array);
    }
}

int main ()
{
    BinaryTree *bt;
    bt = NULL;
    int i, j, aux;
    int array[MAX];
    FILE *arq;
    arq = fopen("num.txt", "r");
    for(i=0; fscanf(arq, "%d", &j) != EOF; i++)
    {
        bt = insert(bt, j);
    }
    FILE *busca;
    busca = fopen("buscaarv.txt", "w");
    fprintf(busca,"(");
    search(bt, 1, array);
    for(i = 0; i < posicaoarray; i++)
    	for(j = i; j < posicaoarray; j++)
    		{
    			if(array[i] > array[j])
    			{
    				aux = array[i];
    				array[i] = array[j];
    				array[j] = aux;
    			}
    		}

    for(i = 0; i < posicaoarray; i++)fprintf(busca, "%d , ", array[i]);
    fprintf(busca, ")");
    fclose(busca);
    fclose(arq);
    return 0;
}
