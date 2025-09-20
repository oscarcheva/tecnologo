#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int main()
{
    Lista lista = crearListaVacia();
    insertarElemento(lista, 1);
    insertarElemento(lista, 5);
    insertarElemento(lista, 2);
    insertarElemento(lista, 8);
    insertarElemento(lista, 4);

    Lista listaAuxiliar = crearListaVacia();

    while (!esListaVacia(lista))
    {
        int elemento = eliminarPrimerElemento(lista);
        printf("%d ", elemento);
        insertarElemento(listaAuxiliar, elemento);
    }

    lista = listaAuxiliar;


    return 0;
}
