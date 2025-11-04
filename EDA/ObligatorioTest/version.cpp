/* 6339682 */ // sustituiir con los 7 dígitos de la cédula

#include "./version.h"
#include "./cadena.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _rep_version
{
    Cadena numero_version;
    _rep_version* siguienteHermano;
    _rep_version* primerHijo;
    _rep_version* padre;
};

struct _nodo_lista_version
{
    Version raizVersion;
    NodoListaVersion siguienteNodo;
};

Version crearVersionVacia();

NodoListaVersion crearNodoListaVersion();

void crearVersion(Version& version, char* num_version);

Version obtenerRaiz(NodoListaVersion nodoListaVersion, char** numeroVersion);

void agregarFilaVersion(Version& version, char* numeroVersion, char* textoFila, unsigned int numLinea);

void imprimirVersion(Version version, char* numeroVersion);

Version siguienteVersion(Version version);

char* nombreVersion(Version version);

int numeroUltimaVersion(Version version);

int numeroUltimaLineaVersion(Version version);

bool esVaciaVersion(Version version);

bool existeVersion(Version version, char* numeroVersion);

void eliminarLineaVersion(Version& version, char* numeroVersion, unsigned int numLinea);

void destruirVersion(Version& version, char* numeroVersion);

void destruirTodasLasVersiones(Version& version);

Version buscarVersionPadre(NodoListaVersion NodoListaVersion, char* numeroVersion);

void crearSubVersion(Version padre, Version hijo, char* numeroVersion);

Version crearVersionVacia()
{
    Version version = new _rep_version;
    version->numero_version = NULL;
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

void crearVersion(NodoListaVersion& nodoLista, char* num_version)
{
    if (num_version[1] != '\0')
    {
        Version padre = obtenerVersionPadre(obtenerRaiz(nodoLista, &num_version), &num_version);
        Version hijo = crearVersionVacia();
        crearSubVersion(padre, hijo, num_version);
    }
    else
    {
        int numeroVersion = atoi(num_version);
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
                        char* versionArray = (char*)malloc(length * sizeof(char));
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
}

Version buscarVersionPadre(Version version, char* numeroVersionPadre)
{
    if (version == NULL)
        return NULL;

    char* numVersion = convertirCadenaArregloChar(version->numero_version);
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

Version obtenerRaiz(NodoListaVersion nodoLista, char** numVersion)
{
    if (numVersion == NULL || **numVersion == '\0')
        return NULL;

    int valor = strtol(*numVersion, numVersion, 10);
    if (**numVersion == '.')
        (*numVersion)++;

    NodoListaVersion actual = nodoLista;
    while (actual != NULL)
    {
        int numeroRaiz = atoi(convertirCadenaArregloChar(actual->raizVersion->numero_version));
        if (numeroRaiz == valor)
            return actual->raizVersion;
        actual = actual->siguienteNodo;
    }

    return NULL;
}


Version obtenerVersionPadre(Version nodo, char** numVersion)
{
    if (nodo == NULL || **numVersion == '\0')
        return nodo; // reached end of stringplam

    if (*(*numVersion + 1) == '\0')
        return nodo;

    int valor = strtol(*numVersion, numVersion, 10); // parse current number
    if (**numVersion == '.')
        (*numVersion)++;

    Version hijo = nodo->primerHijo;

    while (hijo != NULL)
    {
        int numeroHijo = atoi(convertirCadenaArregloChar(hijo->numero_version));

        if (numeroHijo == valor)
        {
            // exact match → descend
            return obtenerVersionPadre(hijo, numVersion);
        }

        hijo = hijo->siguienteHermano; // continue to next sibling
    }

    // no child matched this number → current node is the parent
    return nodo;
}


void crearSubVersion(Version padre, Version hijo, char* numeroVersion)
{
    hijo->numero_version = crearCadenaVacia();
    agregarCaracteresCadena(hijo->numero_version, numeroVersion);

    if (padre != NULL)
    {
        if (padre->primerHijo == NULL)
            padre->primerHijo = hijo;

        else
        {
            Version actual = padre->primerHijo;
            while (actual->siguienteHermano != NULL)
                actual = actual->siguienteHermano;

            int ultimoNumeroHijo = atoi(convertirCadenaArregloChar(hijo->numero_version));
            int ultimoNumeroActual = atoi(convertirCadenaArregloChar(actual->numero_version));
            if (ultimoNumeroActual==ultimoNumeroHijo)
            {
                hijo->siguienteHermano = actual->siguienteHermano;
                actual->siguienteHermano = hijo;
                while (actual!= NULL)
                {   ultimoNumeroActual = atoi(convertirCadenaArregloChar(actual->numero_version));
                    destruirCadena(actual->numero_version);
                    ultimoNumeroActual++;
                    actual->numero_version =  crearCadenaVacia();
                    int length = snprintf(NULL, 0, "%d", ultimoNumeroActual) + 1;
                    char* versionArray = (char*)malloc(length * sizeof(char));
                    snprintf(versionArray, length, "%d", ultimoNumeroActual);
                    agregarCaracteresCadena(actual->numero_version,versionArray);
                    actual = actual->siguienteHermano;
                }
            }
            else if (ultimoNumeroHijo - ultimoNumeroActual == 1)
            {
                if (actual->siguienteHermano != NULL)
                    hijo->siguienteHermano = actual->siguienteHermano;
                actual->siguienteHermano = hijo;
            }
        }
    }
}

void imprimirVersiones(NodoListaVersion nodoListaVersion)
{

    NodoListaVersion actual = nodoListaVersion;

    while (actual != NULL)
    {
        printf("hello");
        Version version = nodoListaVersion->raizVersion;
        char *numeroVersionRaiz = convertirCadenaArregloChar(version->numero_version);
        printf("%s", numeroVersionRaiz);
        Cadena versiones = crearCadenaVacia();
        agregarCaracteresCadena(versiones, convertirCadenaArregloChar(version->numero_version));
        imprimirSubversiones(version, versiones);
        destruirCadena(versiones);
        delete[] numeroVersionRaiz;
        actual = actual->siguienteNodo;
    }
}

void imprimirSubversiones(Version version, Cadena numeroVersion)
{

    if (version != NULL)
    {
        char *versiones = convertirCadenaArregloChar(numeroVersion);
        char numVersion = versiones[strlen(versiones) - 1];
        agregarCaracterFinalCadena(numeroVersion, '.');
        agregarCaracterFinalCadena(numeroVersion, numVersion);
        delete[] versiones;
        char *completo = convertirCadenaArregloChar(numeroVersion);
        printf("%s\n", completo);
        delete[] completo;
        if (version->primerHijo != NULL)
        {
            imprimirSubversiones(version->primerHijo, numeroVersion);
        }
        eliminarCaracterFinalCadena(numeroVersion);
        eliminarCaracterFinalCadena(numeroVersion);
        imprimirSubversiones(version->siguienteHermano, numeroVersion);
    }
}
