/* 6339682 */ // sustituiir con los 7 dígitos de la cédula
#include "../include/linea.h"
#include "../include/cadena.h"
#include "../include/version.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _rep_linea
{
    unsigned int numero;
    Cadena cadena;
    _rep_linea *siguiente;
    _rep_linea *anterior;
};

Linea crearLineaVacia();

void insertarLinea(Linea &linea, char *texto, unsigned int numLinea);

Linea siguienteLinea(Linea linea);

Linea anteriorLinea(Linea linea);

unsigned int cantidadLineas(Linea linea);

unsigned int getNumeroLinea(Linea linea);

char *obtenerTextoLinea(Linea linea, unsigned int numLinea);

bool esVaciaLinea(Linea linea);

bool existeNumeroLinea(Linea linea, unsigned int numLinea);

bool sonIgualesLineas(Linea linea1, Linea linea2);

void eliminarLinea(Linea &linea, unsigned int numLinea);

void destruirLinea(Linea &linea);

Linea crearLineaVacia()
{
    Linea nuevaLinea = new _rep_linea;
    nuevaLinea->siguiente = NULL;
    nuevaLinea->anterior = NULL;
    nuevaLinea->numero = 0;
    nuevaLinea->cadena = NULL;
    return nuevaLinea;
}

void insertarLinea(Linea &linea, char *texto, unsigned int numLinea)
{
    if (linea->numero == 0)
    {
        if (numLinea != 1)
            return;
        linea->cadena = crearCadenaVacia();
        agregarCaracteresCadena(linea->cadena, texto);
        linea->numero = 1;
        return;
    }

    Linea actual = linea;

    Linea nueva = crearLineaVacia();

    nueva->cadena = crearCadenaVacia();
    agregarCaracteresCadena(nueva->cadena, texto);
    nueva->numero = numLinea;

    if (nueva->numero == actual->numero)
    {
        nueva->siguiente = actual;
        nueva->anterior = NULL;
        actual->anterior = nueva;
        linea = nueva;
    }

    else
    {
        while (actual->siguiente != NULL && actual->numero != numLinea)
            actual = actual->siguiente;

        if (nueva->numero == 2 && actual->numero == 1)
        {
            nueva->siguiente = actual->siguiente;
            nueva->anterior = actual;
            actual->siguiente = nueva;
        }
        else
        {
            if (actual->siguiente != NULL)
                actual->siguiente->anterior = nueva;
            actual->anterior->siguiente = nueva;
            nueva->anterior = actual->anterior;
            actual->anterior = nueva;
            nueva->siguiente = actual;
        }
    }

    Linea proxima = nueva->siguiente;
    while (proxima != NULL)
    {
        proxima->numero += 1;
        proxima = proxima->siguiente;
    }
}

Linea siguienteLinea(Linea linea)
{
    return linea->siguiente;
}

Linea anteriorLinea(Linea linea)
{
    return linea->anterior;
}

unsigned int cantidadLineas(Linea linea)
{
    unsigned int contador = 1;
    Linea lineaAnterior = linea->anterior;
    Linea lineaSiguiente = linea->siguiente;
    while (lineaAnterior != NULL)
    {
        contador++;
        lineaAnterior = lineaAnterior->anterior;
    }

    while (lineaSiguiente != NULL)
    {
        contador++;
        lineaSiguiente = lineaSiguiente->siguiente;
    }

    return contador;
}

unsigned int getNumeroLinea(Linea linea)
{
    return linea->numero;
}

char *obtenerTextoLinea(Linea linea, unsigned int numLinea)
{
    if (linea->numero == numLinea)
        return convertirCadenaArregloChar(linea->cadena);
    Linea lineaActual = linea;
    while (lineaActual != NULL)
    {
        if (lineaActual->numero == numLinea)
            return convertirCadenaArregloChar(lineaActual->cadena);
        lineaActual = lineaActual->siguiente;
    }

    return NULL;
}

bool esVaciaLinea(Linea linea)
{
    return linea->cadena == NULL;
}

bool existeNumeroLinea(Linea linea, unsigned int numLinea)
{
    if (linea == NULL)
        return false;
    char *verificador = obtenerTextoLinea(linea, numLinea);
    bool check = verificador != NULL;
    delete[] verificador;
    return check;
}

bool sonIgualesLineas(Linea linea1, Linea linea2)
{
    char *verificadorLinea1 = obtenerTextoLinea(linea1, linea1->numero);
    char *verificadorLinea2 = obtenerTextoLinea(linea2, linea2->numero);
    unsigned int contador = 0;
    while (verificadorLinea1[contador] != '\0' && verificadorLinea2[contador] != '\0')
    {
        if (verificadorLinea1[contador] != verificadorLinea2[contador])
        {
            delete[] verificadorLinea1;
            delete[] verificadorLinea2;
            return false;
        }
        contador++;
    }
    bool iguales = verificadorLinea1[contador] == '\0' && verificadorLinea2[contador] == '\0';
    delete[] verificadorLinea1;
    delete[] verificadorLinea2;
    return iguales;
}

void eliminarLinea(Linea &linea, unsigned int numLinea)
{
    if (!existeNumeroLinea(linea, numLinea))
    {
        printf("La linea no existe\n");
        return;
    }
    Linea actual = linea;

    while (actual != NULL && actual->numero != numLinea)
        actual = actual->siguiente;

    if (actual == NULL)
        return;

    if (actual->anterior != NULL)
        actual->anterior->siguiente = actual->siguiente;
    else if (actual->siguiente != NULL)
    {
        actual->siguiente->anterior = actual->anterior;
        Linea proxima = actual->siguiente;
        while (proxima != NULL)
        {
            proxima->numero -= 1;
            proxima = proxima->siguiente;
        }
        actual = linea->siguiente;
        destruirCadena(linea->cadena);
        delete linea;
        linea = actual;
        return;
    }
    else
    {
        destruirCadena(actual->cadena);
        delete linea;
        linea = NULL;
        return;
    }

    Linea proxima = actual->siguiente;
    while (proxima != NULL)
    {
        proxima->numero -= 1;
        proxima = proxima->siguiente;
    }
    destruirCadena(actual->cadena);
    delete actual;
}

void destruirLinea(Linea &linea)
{
    Linea lineaAEliminar = linea;
    while (lineaAEliminar != NULL)
    {
        Linea siguiente = lineaAEliminar->siguiente;
        destruirCadena(lineaAEliminar->cadena);
        delete lineaAEliminar;
        lineaAEliminar = siguiente;
    }
    linea = NULL;
}
