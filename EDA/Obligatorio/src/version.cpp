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
    int numeroVersion = atoi(num_version);

    if (version->numero_version == NULL)
    {
        if (numeroVersion == 1)

        {
            Version nueva = crearVersionVacia();
            nueva->numero_version = crearCadenaVacia();
            agregarCaracteresCadena(nueva->numero_version, num_version);
            nueva->siguiente = NULL;
            nueva->anterior = NULL;
            version = nueva;
        }
    }
    else
    {
        Version actual = version;
        Version nueva = crearVersionVacia();
        nueva->numero_version = crearCadenaVacia();
        agregarCaracteresCadena(nueva->numero_version, num_version);
        nueva->siguiente = NULL;
        nueva->anterior = NULL;
        int versionActual = atoi(convertirCadenaArregloChar(actual->numero_version));

        while (actual->siguiente != NULL && versionActual != numeroVersion)
        {
            actual = actual->siguiente;
            versionActual = atoi(convertirCadenaArregloChar(actual->numero_version));
        }
        if ((numeroVersion - versionActual) == 1)
        {
            nueva->anterior = actual;
            actual->siguiente = nueva;
        }

        else if (versionActual == numeroVersion)
        {
            nueva->anterior = actual->anterior;
            actual->anterior->siguiente = nueva;
            actual->anterior = nueva;
            nueva->siguiente = actual;
            Version proxima = nueva->siguiente;
            while (proxima != NULL)
            {
                int versionActual = atoi(convertirCadenaArregloChar(proxima->numero_version));
                versionActual++;
                char versionArray[20];
                snprintf(versionArray, sizeof(versionArray), "%d", versionActual);
                destruirCadena(proxima->numero_version);
                proxima->numero_version = crearCadenaVacia();
                agregarCaracteresCadena(proxima->numero_version, versionArray);
                proxima = proxima->siguiente;
            }
        }
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

    if (actual->inicioLineas == NULL)
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
    unsigned int numLinea = getNumeroLinea(actual->inicioLineas);
    if (numLinea == 0)
    {
        printf("No hay lineas en la version\n");
    }
    Linea lineaActual = actual->inicioLineas;
    numeroVersion = convertirCadenaArregloChar(actual->numero_version);
    printf("%s\n", numeroVersion);
    delete[] numeroVersion;
    while (lineaActual != NULL)
    {
        char *contenidoLinea = obtenerTextoLinea(lineaActual, numLinea);
        printf("%d   ", numLinea);
        printf("%s\n", contenidoLinea);
        numLinea++;
        delete[] contenidoLinea;
        lineaActual = siguienteLinea(lineaActual);
    }
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
    Version actual = version;
    Linea lineaActual = actual->inicioLineas;
    if (lineaActual == NULL)
        return 0;
    Linea siguiente = siguienteLinea(lineaActual);
    while (siguiente != NULL)
    {
        lineaActual = siguiente;
        siguiente = siguienteLinea(lineaActual);
    }

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
        int necesario = snprintf(NULL, 0, "%d", numero) + 1;
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
