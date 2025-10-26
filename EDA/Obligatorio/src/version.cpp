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
    _rep_version *siguienteHermano;
    _rep_version *primerHijo;
};

struct _nodo_lista_version
{
    Version raizVersion;
    NodoListaVersion siguienteNodo;
};

Version crearVersionVacia();

NodoListaVersion crearNodoListaVersion();

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

Version buscarVersionPadre(NodoListaVersion NodoListaVersion, char *numeroVersion);

void crearSubversion(NodoListaVersion NodoListaVersion, char *numeroVersion);

int obtenerUltimoNumeroSubVersion(Cadena numero_version);

Version crearVersionVacia()
{
    Version version = new _rep_version;
    version->numero_version = NULL;
    version->inicioLineas = NULL;
    version->siguienteHermano = NULL;
    version->primerHijo = NULL;
    return version;
}

NodoListaVersion crearNodoListaVersion()
{
    NodoListaVersion nuevo = new _nodo_lista_version;
    nuevo->raizVersion = NULL;
    nuevo->siguienteNodo = NULL;
    return nuevo;
}

void crearVersion(NodoListaVersion &nodoLista, char *num_version)
{
    int numeroVersion = atoi(num_version);
    if (num_version[1] != '\0')
    {
        char *versionPadre = strrchr(num_version, '.');
        if (versionPadre != NULL)
        {
            *versionPadre = '\0';
        }
        Version padre = buscarVersionPadre(obtenerVersion(nodoLista, num_version), versionPadre);
        Version hijo = crearVersionVacia();
        hijo->numero_version = crearCadenaVacia();
        agregarCaracteresCadena(hijo->numero_version, num_version);
        crearSubVersion(padre, hijo, num_version);
    }
    NodoListaVersion nodoActual = nodoLista;
    if (nodoLista->raizVersion == NULL)
    {
        Version nuevaVersion = crearVersionVacia();
        nuevaVersion->numero_version = crearCadenaVacia();
        agregarCaracteresCadena(nuevaVersion->numero_version, num_version);
        nodoLista->raizVersion = nuevaVersion;
    }
    else if (nodoActual == NULL)
    {
        NodoListaVersion nuevoNodo = crearNodoListaVersion();
        Version nuevaVersion = crearVersionVacia();
        nuevaVersion->numero_version = crearCadenaVacia();
        agregarCaracteresCadena(nuevaVersion->numero_version, num_version);
        nuevoNodo->raizVersion = nuevaVersion;
        nodoLista->siguienteNodo = nuevoNodo;
    }
    else
    {
        NodoListaVersion nuevoNodo = crearNodoListaVersion();
        Version nuevaVersion = crearVersionVacia();
        nuevaVersion->numero_version = crearCadenaVacia();
        agregarCaracteresCadena(nuevaVersion->numero_version, num_version);
        nuevoNodo->raizVersion = nuevaVersion;

        int numVersionActual = 2;
        if (numeroVersion == 1)
        {
            nuevoNodo->siguienteNodo = nodoLista;
            nuevoNodo->raizVersion = nuevaVersion;
            nodoLista = nuevoNodo;
        }
        else
        {
            while (nodoActual->siguienteNodo != NULL && numVersionActual != numeroVersion)
            {
                nodoActual = nodoActual->siguienteNodo;
                numVersionActual++;
            }
            if (numeroVersion - numVersionActual <= 1)
            {
                nuevoNodo->siguienteNodo = nodoActual->siguienteNodo;
                nodoActual->siguienteNodo = nuevoNodo;
                nodoActual = nuevoNodo->siguienteNodo;

                while (nodoActual != NULL)
                {
                    Version versionActual = nodoActual->raizVersion;

                    int numeroVersionActual = atoi(convertirCadenaArregloChar(versionActual->numero_version));
                    numeroVersionActual++;

                    int length = snprintf(NULL, 0, "%d", numeroVersionActual) + 1;
                    char *versionArray = (char *)malloc(length * sizeof(char));
                    snprintf(versionArray, length, "%d", numeroVersionActual);

                    destruirCadena(versionActual->numero_version);
                    versionActual->numero_version = crearCadenaVacia();
                    agregarCaracteresCadena(versionActual->numero_version, versionArray);
                    nodoActual = nodoActual->siguienteNodo;
                    free(versionArray);
                }
            }
        }
    }
}

Version buscarVersionPadre(Version version, char *numeroVersionPadre)
{
    if (version == NULL)
        return NULL;

    char *numVersion = convertirCadenaArregloChar(version->numero_version);
    printf("Visiting: %s\n", numVersion);

    if (strcmp(numVersion, numeroVersionPadre) == 0)
    {
        delete[] numVersion;
        return version;
    }

    delete[] numVersion;

    Version encontrado = buscarVersionPadre(version->primerHijo, numeroVersionPadre);
    if (encontrado != NULL)
        return encontrado;

    return buscarVersionPadre(version->siguienteHermano, numeroVersionPadre);
}

Version obtenerVersion(NodoListaVersion &nodoLista, char *numVersion)
{
    int numeroVersion = atoi(numVersion);
    char versionStr[2];
    sprintf(versionStr, "%d", numeroVersion);
    NodoListaVersion actual = nodoLista;
    while (actual != NULL)
    {
        Version versionActual = actual->raizVersion;
        char *numeroActual = convertirCadenaArregloChar(versionActual->numero_version);
        bool existe = (strcmp(versionStr, numeroActual) == 0);
        if (existe)
        {
            delete[] numeroActual;
            return versionActual;
        }
        actual = actual->siguienteNodo;
    }
    delete[] versionStr;
    return NULL;
}

void crearSubVersion(Version padre, Version hijo, char *numeroVersion)
{
    if (padre != NULL)
        if (padre->primerHijo == NULL)
            padre->primerHijo = hijo;
        else
        {
            Version actual = padre->primerHijo;
            while (actual->siguienteHermano != NULL)
                actual = actual->siguienteHermano;

            int ultimoNumeroHijo = obtenerUltimoNumeroSubVersion(hijo->numero_version);
            int ultimoNumeroActual = obtenerUltimoNumeroSubVersion(actual->numero_version);
            if (ultimoNumeroHijo - ultimoNumeroActual == 1)
            {
                if (actual->siguienteHermano != NULL)
                    hijo->siguienteHermano = actual->siguienteHermano;
                actual->siguienteHermano = hijo;
            }
        }
}

int obtenerUltimoNumeroSubVersion(Cadena numero_version)
{
    char *str = convertirCadenaArregloChar(numero_version);
    char *ultimoPunto = strrchr(str, '.');
    int numero = (ultimoPunto != NULL) ? atoi(ultimoPunto + 1) : atoi(str);
    delete[] str;
    return numero;
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
    return actual->siguienteHermano;
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
    while (ultima->siguienteHermano != NULL)
    {
        ultima = ultima->siguienteHermano;
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
    int num_version = atoi(numeroVersion);
    Version actual = obtenerVersion(version, numeroVersion);
    if (actual != NULL)
    {
        if (actual->primerHijo == NULL && num_version == 1)
        {
            actual->siguienteHermano->primerHijo = NULL;
            version = actual->siguienteHermano;
        }
        else
        {
            actual->primerHijo->siguienteHermano = actual->siguienteHermano;
            actual->siguienteHermano->primerHijo = actual->primerHijo;
        }
        Version proxima = actual->siguienteHermano;
        while (proxima != NULL)
        {
            int versionActual = atoi(convertirCadenaArregloChar(proxima->numero_version));
            versionActual--;
            char versionArray[20];
            snprintf(versionArray, sizeof(versionArray), "%d", versionActual);
            destruirCadena(proxima->numero_version);
            proxima->numero_version = crearCadenaVacia();
            agregarCaracteresCadena(proxima->numero_version, versionArray);
            proxima = proxima->siguienteHermano;
        }
        delete actual;
    }
}

void destruirTodasLasVersiones(Version &version)
{
    Version actual = version;
    while (actual != NULL)
    {
        Version aEliminar = actual;
        actual = actual->siguienteHermano;
        destruirCadena(aEliminar->numero_version);
        destruirLinea(aEliminar->inicioLineas);
        delete aEliminar;
    }
    version = NULL;
}
