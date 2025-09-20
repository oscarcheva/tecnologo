#include "racional.h"
#include <stdio.h>
#include <stdlib.h>

struct _racional
{
    int p;
    int q;
};

Racional construirRacional1()
{
    Racional r = malloc(sizeof(*r));
    printf("Ingrese el numerador");
    int p;
    scanf("%d",&p);
    printf("Ingrese el denominador");
    int q;
    scanf("%d",&q);
    if (q==0)
    {
        printf("El numerador no puede ser 0");
        exit(0);
    }
    r->p = p;
    r->q =  q;

    return  r;

}

Racional construirRacional2(int p, int q)
{
    Racional r = malloc(sizeof(*r));
    r->p = p;
    r->q =  q;
    return r;
}

int retornarNumerador(Racional r)
{
    return r->p;
}

int retornarDenominador(Racional r)
{
    return r->q;
}

Racional sumarRacionales(Racional r1, Racional r2)
{
    Racional res = malloc(sizeof(res));
    if (!res)
    {
        perror("malloc");
        exit(1);
    }
    res->p = r1-> p * r2->q + r1->q * r2->p;
    res->q = r1->q * r2->q;

    simplicarRacional(res);

    return res;
}

Racional restarRacionales(Racional r1, Racional r2)
{
    Racional res = malloc(sizeof(res));
    if (!res)
    {
        perror("malloc");
        exit(1);
    }
    res->p = r1-> p * r2->q - r1->q * r2->p;
    res->q = r1->q * r2->q;

    simplicarRacional(res);

    return res;
}

Racional multiplicarRacionales(Racional r1, Racional r2)
{
    Racional res = malloc(sizeof(res));
    if (!res)
    {
        perror("malloc");
        exit(1);
    }
    res->p = r1-> p * r2->q;
    res->q = r1->q * r2->q;

    simplicarRacional(res);

    return res;
}

void imprimirRacional(Racional r)
{
    printf(r->p);
    printf("-");
    printf("\n"r->q);

}


