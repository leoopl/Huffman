#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

typedef struct Node
{
    int item;
    struct Node *nextNode;
} Node;

Node* createLinkedList()
{
    return NULL;
}

int isEmpty(Node *first)
{
    return (first == NULL);
}

Node* insertNode(Node *node, int item)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->item = item;
    newNode->nextNode = node;
    return newNode;
}

int search(Node *first, int item, int c)
{
    Node *p;
    p = first;
    if(p->item == item)
    {
        return c;
    }
    else
    {
        search(p->nextNode, item, c+1);
    }
}

int main()
{
    Node *list;
    list = createLinkedList();
    int i, x, l, aux;
    int array[MAX], array2[MAX];
    FILE *arq, *busca;
    arq = fopen("num.txt", "r");
    busca = fopen("buscalista.txt", "w");
    for(i = 0; fscanf(arq, "%d", &x) != EOF; i++)
    {
        array[i] = x;
        list = insertNode(list, x);
    }
    int j, y, p;
    for(j = 0; j < i; j++)
    {
        y = 1;
        p = search(list, array[j], y);
        array2[j] = p;
    }
    for(j = 0; j < i; j++)
    {
        for(l = j; l < i; l++)
        {
            if(array2[j] > array2[l])
            {
                aux = array2[j];
                array2[j] = array2[l];
                array2[l] = aux;
            }
        }
    }
    fprintf(busca, "(");
    for(j = 0; j < i; j++)
        fprintf(busca, " %d ,", array2[j]);
    fprintf(busca, ")");
    fclose(arq);
    fclose(busca);
}
