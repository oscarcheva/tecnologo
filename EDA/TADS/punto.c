#include "punto.h"
#include <stdlib.h>


struct _punto
{
    int x;
    int y;
};

Punto construirPunto1()
{
    Punto p = malloc(sizeof(*p));
    int x = 5;
    int y = 7;
    p->x = x;
    p->y = y;
    return p;
}

Punto construirPunto2(int x, int y)
{
    Punto p = malloc(sizeof(*p));
    p->x = x;
    p->y = y;
    return p;
}

int coordenadaXPunto(Punto p)
{
    return p->x;
}

int coordenadaYPunto(Punto p)
{
    return p->y;
}

int sonIgualesPuntos(Punto p1, Punto p2)
{
    return (p1->x == p2->x && p1->y == p2->y);
}

void destruirPunto(Punto p)
{
    free(p);
}
