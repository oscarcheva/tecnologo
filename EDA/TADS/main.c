#include <stdio.h>
#include "punto.h"

int main()
{
    Punto p1 = construirPunto1();
    Punto p2 = construirPunto2(3, 2);
    int sonIguales = sonIgualesPuntos(p1, p2);
    if (sonIguales)
        printf("Los puntos son iguales\n");
    else
        printf("Los puntos no son iguales\n");

    destruirPunto(p1);

    return 0;
}