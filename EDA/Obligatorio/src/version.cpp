/* 6339682 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/version.h"
#include "../include/linea.h"
#include "../include/cadena.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _rep_version
{
    Cadena numero_version;
    Linea inicioLineas;
    _rep_version *siguiente;
    _rep_version *anterior;
};

Version crearVersionVacia();

void crearVersion(Version &version, char *num_version);

Version obtenerVersion(Version &version, char *numVersion);

void agregarFilaVersion(Version &version, char *numeroVersion, char *textoFila, unsigned int numLinea);

void imprimirVersion(Version version, char *numeroVersion);

Version siguienteVersion(Version version);

char *nombreVersion(Version version);

int numeroUltimaVersion(Version version);

int numeroUltimaLineaVersion(Version version);

bool esVaciaVersion(Version version);

bool existeVersion(Version version, char *numeroVersion);

void eliminarLineaVersion(Version &version, char *numeroVersion, unsigned int numLinea);

void destruirVersion(Version &version, char *numeroVersion);

void destruirTodasLasVersiones(Version &version);

Version crearVersionVacia()
{
    Version version = new _rep_version;
    version->numero_version = NULL;
    version->inicioLineas = NULL;
    version->siguiente = NULL;
    version->anterior = NULL;
    return version;
}

void crearVersion(Version &version, char *num_version)
{
    Version actual = obtenerVersion(version, num_version);
    if (version->anterior == NULL && strcmp(num_version, "1") != 0)
        return;
    agregarCaracteresCadena(version->numero_version, num_version);
    int contador = 1;
    bool iguales = false;

    while (actual != NULL && !iguales)
    {
        char *numeroTemporal = convertirCadenaArregloChar(actual->numero_version);
        iguales = (strcmp(num_version, numeroTemporal) == 0);
        delete[] numeroTemporal;
        if (!iguales)
            actual = actual->siguiente;
    }
    Version ultimo = NULL;
    if (actual != NULL)
    {
        while (actual != NULL)
        {
            char *charNumero = convertirCadenaArregloChar(actual->numero_version);
            int numero = atoi(charNumero);
            numero -= 1;
            int necesario = snprintf(nullptr, 0, "%d", numero) + 1;
            char *nuevoNumero = new char[necesario];
            snprintf(nuevoNumero, necesario, "%d", numero);
            destruirCadena(actual->numero_version);
            actual->numero_version = crearCadenaVacia();
            agregarCaracteresCadena(actual->numero_version, nuevoNumero);
            delete[] nuevoNumero;
            delete[] charNumero;
            ultimo = actual;
            actual = actual->siguiente;
        }
    }
    if (ultimo != NULL)
    {
        version->siguiente = ultimo;
        version->anterior = ultimo->anterior;

        if (ultimo->anterior != NULL)
        {
            ultimo->anterior->siguiente = version;
        }

        ultimo->anterior = version;
    }
    else
    {
        version->siguiente = NULL;
        version->anterior = NULL;
    }
}

Version obtenerVersion(Version &version, char *numVersion)
{
    Version actual = version;
    while (actual != NULL)
    {
        char *numeroActual = convertirCadenaArregloChar(actual->numero_version);
        bool existe = (strcmp(numVersion, numeroActual) == 0);
        delete[] numeroActual;

        if (existe)
            return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

void agregarFilaVersion(Version &version, char *numeroVersion, char *textoFila, unsigned int numLinea)
{
    Version actual = obtenerVersion(version, numeroVersion);

    if (actual->inicioLineas == NULL && numLinea == 1)
    {
        Linea linea = crearLineaVacia();
        actual->inicioLineas = linea;
    }
    insertarLinea(actual->inicioLineas, textoFila, numLinea);
}

void imprimirVersion(Version version, char *numeroVersion)
{
    Version actual = obtenerVersion(version, numeroVersion);
    if (actual == NULL)
        return;
    char *charNumVersion = nombreVersion(actual);
    printf("%s\n", charNumVersion);
    delete[] charNumVersion;
}

Version siguienteVersion(Version version)
{
    Version actual = obtenerVersion(version, nombreVersion(version));
    return actual->siguiente;
}

char *nombreVersion(Version version)
{
    char *numVersionTemporal = convertirCadenaArregloChar(version->numero_version);
    if (numVersionTemporal == NULL)
        return NULL;
    Version actual = obtenerVersion(version, numVersionTemporal);
    if (actual == NULL)
        return NULL;
    delete[] numVersionTemporal;

    return convertirCadenaArregloChar(actual->numero_version);
}

int numeroUltimaVersion(Version version)
{
    Version actual = obtenerVersion(version, convertirCadenaArregloChar(version->numero_version));
    Version ultima = actual;
    while (ultima->siguiente != NULL)
    {
        ultima = ultima->siguiente;
    }
    char *num_version = convertirCadenaArregloChar(ultima->numero_version);
    int numero = atoi(num_version);
    delete[] num_version;
    return numero;
}

int numeroUltimaLineaVersion(Version version)
{
    Version actual = obtenerVersion(version, convertirCadenaArregloChar(version->numero_version));
    Linea lineaActual = actual->inicioLineas;
    while (lineaActual != NULL)
    {
        lineaActual = siguienteLinea(lineaActual);
    }
    lineaActual = anteriorLinea(lineaActual);
    return getNumeroLinea(lineaActual);
}

bool esVaciaVersion(Version version)
{
    Version actual = obtenerVersion(version, convertirCadenaArregloChar(version->numero_version));
    return actual == NULL;
}

bool existeVersion(Version version, char *numeroVersion)
{
    Version actual = obtenerVersion(version, numeroVersion);
    return actual != NULL;
}

void eliminarLineaVersion(Version &version, char *numeroVersion, unsigned int numLinea)
{
    Version actual = obtenerVersion(version, numeroVersion);
    if (actual != NULL)
        eliminarLinea(actual->inicioLineas, numLinea);
}

void destruirVersion(Version &version, char *numeroVersion)
{
    Version actual = obtenerVersion(version, numeroVersion);
    if (actual == NULL)
        return;
    if (actual->anterior != NULL)
        actual->anterior->siguiente = actual->siguiente;
    else
        version = actual->siguiente;

    if (actual->siguiente != NULL)
        actual->siguiente->anterior = actual->anterior;

    destruirCadena(actual->numero_version);
    destruirLinea(actual->inicioLineas);

    Version siguiente = actual->siguiente;
    while (siguiente != NULL)
    {
        char *charNumero = convertirCadenaArregloChar(siguiente->numero_version);
        int numero = atoi(charNumero);
        numero -= 1;
        int necesario = snprintf(nullptr, 0, "%d", numero) + 1;
        char *nuevoNumero = new char[necesario];
        snprintf(nuevoNumero, necesario, "%d", numero);
        destruirCadena(siguiente->numero_version);
        siguiente->numero_version = crearCadenaVacia();
        agregarCaracteresCadena(siguiente->numero_version, nuevoNumero);
        delete[] charNumero;
        delete[] nuevoNumero;
        siguiente = siguiente->siguiente;
    }
    delete actual;
}

void destruirTodasLasVersiones(Version &version)
{
    Version actual = version;
    while (actual != NULL)
    {
        Version aEliminar = actual;
        actual = actual->siguiente;
        destruirCadena(aEliminar->numero_version);
        destruirLinea(aEliminar->inicioLineas);
        delete aEliminar;
    }
    version = NULL;
}
