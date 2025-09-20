#include <iostream>
#include <string.h>

#include "pila.h"


int main()
{
    Pila pila = crearPilaVacia(5);
    insertarElementoPila(pila, 2);
    insertarElementoPila(pila, 4);
    insertarElementoPila(pila, 6);
    insertarElementoPila(pila, 8);
    insertarElementoPila(pila, 10);

    Pila copiaPila = crearPilaVacia(5);

    int array [5];
    int x = 0;

    while (!esVaciaPila(pila))
    {
        array[x] = obtenerTopePila(pila);
        eliminarTopePila(pila);
        x++;
    };

    while (!esLLenaPila(pila))
    {
        insertarElementoPila(pila, array[x]);
        insertarElementoPila(copiaPila, array[x]);
    }

    printf("Original     Copia\n");
    while (!esVaciaPila(pila))
    {
        printf("%d      ", obtenerTopePila(pila));
        printf("%d \n", obtenerTopePila(copiaPila));
        eliminarTopePila(pila);
        eliminarTopePila(copiaPila);
    };

    return 0;
}
