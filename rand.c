#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i = 0;
    FILE *p;
    p = fopen("num.txt", "w");
    for(i = 0; i < 10000; i++)
    {
        fprintf(p, "%d\n", rand() % 10000);
    }
    fclose(p);
}
