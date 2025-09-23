/* 6339682 */ // sustituiir con los 7 dígitos de la cédula
#include "../include/linea.h"
#include "../include/cadena.h"
#include "../include/version.h"

#include <stddef.h>

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
    return nuevaLinea;
}

void insertarLinea(Linea &linea, char *texto, unsigned int numLinea)
{
    if (linea->siguiente == NULL && numLinea != 1)
        return;
    Linea actual = linea;
    int contador = 1;
    while (actual != NULL && contador != numLinea - 1)
    {
        actual = actual->siguiente;
        contador++;
    }
    if (actual == NULL || actual->numero != numLinea - 1)
        return;

    linea->cadena = crearCadenaVacia();
    agregarCaracteresCadena(linea->cadena, texto);
    linea->numero = numLinea;
    unsigned int posicion = numLinea;
    linea->anterior = actual;
    linea->siguiente = actual->siguiente;
    if (actual->siguiente != NULL)
        actual->siguiente->anterior = linea;
    actual->siguiente = linea;

    Linea proxima = linea->siguiente;
    while (proxima != NULL)
    {
        if (proxima->numero == posicion)
        {
            proxima->numero = proxima->numero + 1;
            posicion++;
        }
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
    Linea lineaActual = linea->anterior;
    while (lineaActual != NULL)
    {
        lineaActual = lineaActual->anterior;
    }

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
    char *verificador = obtenerTextoLinea(linea, numLinea);
    bool check = verificador != NULL;
    delete[] verificador;
    return check;
}

bool sonIgualesLineas(Linea linea1, Linea linea2)
{
    char *verificadorLinea1 = obtenerTextoLinea(linea1, linea1->numero);
    char *verificadorLinea2 = obtenerTextoLinea(linea2, linea2->numero);
    int contador = 0;
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
        return;
    Linea lineaAEliminar = linea;
    int contador = 1;
    while (lineaAEliminar != NULL && contador != numLinea)
    {
        lineaAEliminar = lineaAEliminar->siguiente;
        contador++;
    }
    if (lineaAEliminar == NULL || lineaAEliminar->numero != numLinea)
        return;

    if (lineaAEliminar->siguiente != NULL)
        lineaAEliminar->siguiente->anterior = lineaAEliminar->anterior;
    if (lineaAEliminar->anterior != NULL)
        lineaAEliminar->anterior->siguiente = lineaAEliminar->siguiente;
    else
        linea = lineaAEliminar->siguiente;

    unsigned int posicion = numLinea;
    Linea proxima = lineaAEliminar->siguiente;
    while (proxima != NULL)
    {

        proxima->numero--;
        proxima = proxima->siguiente;
    }

    destruirCadena(lineaAEliminar->cadena);
    delete lineaAEliminar;
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
