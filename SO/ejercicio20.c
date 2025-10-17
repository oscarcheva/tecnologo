#include <stdio.h>
#include <unistd.h>

int main()
{
    int p, valor;
    printf("Ingrese un valor\n");
    scanf("%d", &valor);
    p = fork();
    if (p == 0)
    {
        printf("Proceso hijo valor mas 4: %d\n", valor + 4);
    }
    else
    {
        printf("Proceso padre valor mas 2: %d\n", valor + 2);
    }
}