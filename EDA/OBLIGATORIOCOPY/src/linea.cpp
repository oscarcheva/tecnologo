/* 6339682 */ // sustituiir con los 7 dígitos de la cédula
#include "../include/linea.h"
#include "../include/cadena.h"

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
    if (linea != NULL)
    {
        if (linea->numero == 0)
        {
            if (numLinea == 1)
                linea->cadena = crearCadenaVacia();
            agregarCaracteresCadena(linea->cadena, texto);
            linea->numero = 1;
        }
        else
        {
            Linea actual = linea;

            while (actual->siguiente != NULL && actual->numero != numLinea)
                actual = actual->siguiente;

            if (numLinea - actual->numero <= 1)
            {
                Linea nueva = crearLineaVacia();
                nueva->cadena = crearCadenaVacia();
                agregarCaracteresCadena(nueva->cadena, texto);
                nueva->numero = numLinea;

                if (numLinea == actual->numero)
                {
                    nueva->siguiente = actual;
                    nueva->anterior = actual->anterior;
                    if (actual->anterior != NULL)
                        actual->anterior->siguiente = nueva;
                    actual->anterior = nueva;
                    if (numLinea == 1)
                        linea = nueva;
                }
                else
                {
                    actual->siguiente = nueva;
                    nueva->anterior = actual;
                    nueva->siguiente = NULL;
                }

                Linea proxima = nueva->siguiente;
                while (proxima != NULL)
                {
                    proxima->numero += 1;
                    proxima = proxima->siguiente;
                }
            }
        }
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

void eliminarLinea(Linea &linea, unsigned int numLinea)
{
    if (existeNumeroLinea(linea, numLinea))
    {
        Linea actual = linea;
        if (actual != NULL)
        {

            if (actual->numero == 1 && actual->numero == numLinea)
            {
                linea = actual->siguiente;
                if (linea != NULL)
                    linea->anterior = NULL;
            }
            else
            {
                while (actual != NULL && actual->numero != numLinea)
                    actual = actual->siguiente;

                if (actual != NULL)
                {
                    if (actual->siguiente != NULL)
                    {
                        actual->anterior->siguiente = actual->siguiente;
                        if (actual->anterior != NULL)
                            actual->siguiente->anterior = actual->anterior;
                    }
                    else if (actual->siguiente == NULL)
                    {
                        actual->siguiente = NULL;
                        actual->anterior->siguiente = NULL;
                        if (numLinea == 1)
                            linea = linea->siguiente;
                    }
                }
            }

            Linea proxima = actual->siguiente;
            while (proxima != NULL)
            {
                proxima->numero -= 1;
                proxima = proxima->siguiente;
            }
            destruirLinea(actual);
        }
    }
    else
        printf("La linea no existe\n");
}

void destruirLinea(Linea &linea)
{
    destruirCadena(linea->cadena);
    linea->anterior = NULL;
    linea->siguiente = NULL;
    delete linea;
    linea = NULL;
}

void destruirLineas(Linea &linea)
{
    Linea lineaAEliminar = linea;
    while (lineaAEliminar != NULL)
    {
        Linea siguiente = lineaAEliminar->siguiente;
        destruirLinea(lineaAEliminar);
        lineaAEliminar = siguiente;
    }
    linea = NULL;
}

void cambiosEnLinea(Linea linea1, Linea linea2)
{
    Linea base = linea1;
    Linea comparadora = linea2;

    if (base != NULL && comparadora != NULL)
    {
        bool cambios = false;
        bool existe = false;

        while (base != NULL)
        {
            existe = false;
            comparadora = linea2;
            while (comparadora != NULL && !existe)
            {
                existe = sonIgualesCadenas(base->cadena, comparadora->cadena);
                comparadora = comparadora->siguiente;
            }
            if (!existe)
            {
                cambios = true;
                printf("BL  %d \n", base->numero);
            }
            base = base->siguiente;
        }
        base = linea1;
        comparadora = linea2;
        while (comparadora != NULL)
        {
            existe = false;
            base = linea1;
            while (base != NULL && !existe)
            {
                existe = sonIgualesCadenas(comparadora->cadena, base->cadena);
                base = base->siguiente;
            }
            if (!existe)
            {
                cambios = true;
                char *texto = obtenerTextoLinea(comparadora, comparadora->numero);
                printf("IL  %d  %s \n", comparadora->numero, texto);
                delete[] texto;
            }
            comparadora = comparadora->siguiente;
        }
        if (!cambios)
            printf("No se realizaron modificaciones\n");
    }
}

bool sonLineasIguales(Linea linea1, Linea linea2)
{
    while (linea1 != NULL && linea2 != NULL)
    {
        bool iguales = sonIgualesCadenas(linea1->cadena, linea2->cadena);
        if (!iguales)
            return false;
        linea1 = linea1->siguiente;
        linea2 = linea2->siguiente;
    }
    return linea1 == NULL && linea2 == NULL;
}