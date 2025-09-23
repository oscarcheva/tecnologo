/* 6339682 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"
#include <stddef.h>

struct _nodoCadena
{
    char letra;
    _nodoCadena *siguiente;
} typedef *NodoCadena;

struct _rep_cadena
{
    _nodoCadena *inicio;
};

Cadena crearCadenaVacia();

void agregarCaracteresCadena(Cadena &cadena, char *texto);

bool esVaciaCadenaCaracteres(Cadena cadena);

bool sonIgualesCadenas(Cadena cadena1, Cadena cadena2);

char *convertirCadenaArregloChar(Cadena cadena);

void destruirCadena(Cadena &cadena);

Cadena crearCadenaVacia()
{
    Cadena nuevaCadena = new _rep_cadena;
    nuevaCadena->inicio = NULL;
    return nuevaCadena;
}

void agregarCaracteresCadena(Cadena &cadena, char *texto)
{

    if (!esVaciaCadenaCaracteres(cadena))
        return;
    int contador = 0;
    NodoCadena anterior = NULL;
    while (texto[contador] != '\0')
    {
        NodoCadena nodo = new _nodoCadena;
        nodo->letra = texto[contador];
        if (contador == 0)
            cadena->inicio = nodo;
        else
            anterior->siguiente = nodo;
        nodo->siguiente = NULL;
        anterior = nodo;
        contador++;
    }
}

bool esVaciaCadenaCaracteres(Cadena cadena)
{
    return cadena->inicio == NULL;
}

bool sonIgualesCadenas(Cadena cadena1, Cadena cadena2)
{
    NodoCadena nodo1 = cadena1->inicio;
    NodoCadena nodo2 = cadena2->inicio;

    while (nodo1 != NULL && nodo2 != NULL)
    {
        if (nodo1->letra != nodo2->letra)
            return false;
        nodo1 = nodo1->siguiente;
        nodo2 = nodo2->siguiente;
    }
    return nodo1 == NULL && nodo2 == NULL;
}
char *convertirCadenaArregloChar(Cadena cadena)
{
    int largo = 0;
    if (esVaciaCadenaCaracteres(cadena))
        return NULL;
    NodoCadena nodo = cadena->inicio;
    while (nodo != NULL)
    {
        largo++;
        nodo = nodo->siguiente;
    }
    char *arregloChar = new char[largo + 1];

    nodo = cadena->inicio;
    largo = 0;
    while (nodo != NULL)
    {
        arregloChar[largo] = nodo->letra;
        nodo = nodo->siguiente;
        largo++;
    }
    arregloChar[largo] = '\0';
    return arregloChar;
}

void destruirCadena(Cadena &cadena)
{
    if (esVaciaCadenaCaracteres(cadena))
        delete cadena;
    else
    {
        NodoCadena nodo = cadena->inicio;
        while (nodo != NULL)
        {
            cadena->inicio = nodo->siguiente;
            delete nodo;
            nodo = cadena->inicio;
        }
        delete cadena;
    }
}
