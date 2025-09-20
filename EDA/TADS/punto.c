#include "punto.h"

#include <stdio.h>
#include <stdlib.h>


struct _punto
{
    int* A;
};

Punto construirPunto1()
{
    Punto p = malloc(sizeof(*p));
    p->A = (int*)malloc(2 * sizeof(int));
    int x = 0;
    int y = 0;
    printf("Ingrese el valor del punto x\n");
    scanf("%d",&x);
    printf("Ingrese el valor del punto y\n");
    scanf("%d",&    y);
    p->A[0] = x;
    p->A[1] = y;
    return p;
}

Punto construirPunto2(int x, int y)
{
    Punto p = malloc(sizeof(*p));
    p->A = (int*)malloc(2 * sizeof(int));
    p->A[0] = x;
    p->A[1] = y;
    return p;
}

int coordenadaXPunto(Punto p)
{
    return p->A[0];
}

int coordenadaYPunto(Punto p)
{
    return p->A[1];
}

int sonIgualesPuntos(Punto p1, Punto p2)
{
    return (p1->A[0] == p2->A[0] && p1->A[1] == p2->A[1]);
}

void destruirPunto(Punto p)
{
    free(p->A);
    free(p);
}
