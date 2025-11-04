/* 6339682 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/version.h"
#include "../include/cadena.h"
#include "../include/linea.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _nodo_version
{
    Cadena numero_version;
    Linea inicioLineas;
    _nodo_version *siguienteHermano;
    _nodo_version *primerHijo;
    _nodo_version *padre;
} typedef *NodoVersion;

struct _rep_version
{
    NodoVersion raizVersion;
    Version siguienteNodo;
};

Version crearVersionVacia();

void crearVersion(NodoVersion &version, char *num_version);

NodoVersion obtenerRaiz(Version nodoVersion, char **numVersion);

void agregarFilaVersion(NodoVersion &version, char *numeroVersion, char *textoFila, unsigned int numLinea);

void imprimirVersion(NodoVersion version, char *numeroVersion);

NodoVersion siguienteVersion(NodoVersion version);

char *nombreVersion(NodoVersion version);

int numeroUltimaVersion(NodoVersion version);

int numeroUltimaLineaVersion(Version version, char *numeroVersion);

bool esVaciaVersion(NodoVersion version);

bool existeVersion(NodoVersion version, char *numeroVersion);

void eliminarLineaVersion(NodoVersion &version, char *numeroVersion, unsigned int numLinea);

void destruirVersion(NodoVersion &version);

void eliminarSubVersionesHijas(NodoVersion &version);

void destruirTodasLasVersiones(Version &version);

NodoVersion obtenerVersionPadre(NodoVersion nodo, char **numVersion);

void crearSubVersion(NodoVersion padre, NodoVersion hijo, char *numeroVersion);

void imprimirSubversiones(NodoVersion version, Cadena numeroVersion);

void borrarSubVersion(NodoVersion &padre, char *numeroVersion);

NodoVersion obtenerSubVersion(NodoVersion padre, char *numVersion);

NodoVersion crearNodoVersionVacio()
{
    NodoVersion nodo = new _nodo_version;
    nodo->numero_version = NULL;
    nodo->padre = NULL;
    nodo->primerHijo = NULL;
    nodo->siguienteHermano = NULL;
    return nodo;
}

Version crearVersionVacia()
{
    Version nuevo = new _rep_version;
    nuevo->raizVersion = NULL;
    nuevo->siguienteNodo = NULL;
    return nuevo;
}

void crearVersion(Version &version, char *num_version)
{
    if (num_version[1] != '\0')
    {
        NodoVersion padre = obtenerVersionPadre(obtenerRaiz(version, &num_version), &num_version);
        NodoVersion hijo = crearNodoVersionVacio();
        crearSubVersion(padre, hijo, num_version);
    }
    else
    {
        int numeroVersion = atoi(num_version);
        Version nodoActual = version;
        if (version->raizVersion == NULL)
        {
            NodoVersion nuevaVersion = crearNodoVersionVacio();
            nuevaVersion->numero_version = crearCadenaVacia();
            agregarCaracteresCadena(nuevaVersion->numero_version, num_version);
            version->raizVersion = nuevaVersion;
        }
        else if (nodoActual == NULL)
        {
            Version nuevoNodo = crearVersionVacia();
            NodoVersion nuevaVersion = crearNodoVersionVacio();
            nuevaVersion->numero_version = crearCadenaVacia();
            agregarCaracteresCadena(nuevaVersion->numero_version, num_version);
            nuevoNodo->raizVersion = nuevaVersion;
            version->siguienteNodo = nuevoNodo;
        }
        else
        {
            Version nuevoNodo = crearVersionVacia();
            NodoVersion nuevaVersion = crearNodoVersionVacio();
            nuevaVersion->numero_version = crearCadenaVacia();
            agregarCaracteresCadena(nuevaVersion->numero_version, num_version);
            nuevoNodo->raizVersion = nuevaVersion;

            int numVersionActual = 1;
            Version previo = NULL;

            if (numeroVersion == 1)
            {
                nuevoNodo->siguienteNodo = version;
                nuevoNodo->raizVersion = nuevaVersion;
                version = nuevoNodo;
            }
            else
            {
                while (nodoActual->siguienteNodo != NULL && numVersionActual != numeroVersion)
                {
                    previo = nodoActual;
                    nodoActual = nodoActual->siguienteNodo;
                    numVersionActual++;
                }
            }
            if (nodoActual->siguienteNodo == NULL && numeroVersion - numVersionActual == 1)
            {
                nodoActual->siguienteNodo = nuevoNodo;
            }
            else if (numeroVersion - numVersionActual <= 1)
            {
                nuevoNodo->siguienteNodo = nodoActual;
                if (previo != NULL)
                    previo->siguienteNodo = nuevoNodo;

                while (nodoActual != NULL)
                {
                    NodoVersion versionActual = nodoActual->raizVersion;

                    char *numeroVersionStr = convertirCadenaArregloChar(nodoActual->raizVersion->numero_version);
                    int numeroVersionActual = atoi(numeroVersionStr);
                    delete[] numeroVersionStr;
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

NodoVersion obtenerRaiz(Version nodoLista, char **numVersion)
{
    if (numVersion == NULL || **numVersion == '\0')
        return NULL;

    int valor = strtol(*numVersion, numVersion, 10);
    if (**numVersion == '.')
        (*numVersion)++;

    Version actual = nodoLista;
    while (actual != NULL)
    {
        char *numeroVersionStr = convertirCadenaArregloChar(actual->raizVersion->numero_version);
        int numeroRaiz = atoi(numeroVersionStr);
        delete[] numeroVersionStr;
        if (numeroRaiz == valor)
            return actual->raizVersion;
        actual = actual->siguienteNodo;
    }

    return NULL;
}

NodoVersion obtenerVersionPadre(NodoVersion nodo, char **numVersion)
{
    if (nodo == NULL || **numVersion == '\0')
        return nodo; // reached end of stringplam

    if (*(*numVersion + 1) == '\0')
        return nodo;

    int valor = strtol(*numVersion, numVersion, 10); // parse current number
    if (**numVersion == '.')
        (*numVersion)++;

    NodoVersion hijo = nodo->primerHijo;

    while (hijo != NULL)
    {
        char *numeroVersionStr = convertirCadenaArregloChar(hijo->numero_version);
        int numeroHijo = atoi(numeroVersionStr);
        delete[] numeroVersionStr;

        if (numeroHijo == valor)
        {
            // exact match → descend
            return obtenerVersionPadre(hijo, numVersion);
        }

        hijo = hijo->siguienteHermano; // continue to next sibling
    }

    // no child matched this number → current node is the parent
    if (*(*numVersion + 1) != '\0' || *(*numVersion) != '\0')
        return NULL;
    return nodo;
}

void crearSubVersion(NodoVersion padre, NodoVersion hijo, char *numeroVersion)
{
    hijo->numero_version = crearCadenaVacia();
    agregarCaracteresCadena(hijo->numero_version, numeroVersion);

    char *numeroVersionHijo = convertirCadenaArregloChar(hijo->numero_version);
    int ultimoNumeroHijo = atoi(numeroVersionHijo);
    delete[] numeroVersionHijo;

    if (padre != NULL)
    {
        if (padre->primerHijo == NULL && ultimoNumeroHijo == 1)
            padre->primerHijo = hijo;

        else if (padre->primerHijo != NULL)
        {
            NodoVersion actual = padre->primerHijo;
            char *numeroVersionActual = convertirCadenaArregloChar(actual->numero_version);
            int ultimoNumeroActual = atoi(numeroVersionActual);
            delete[] numeroVersionActual;

            if (ultimoNumeroActual == ultimoNumeroHijo)
            {
                hijo->siguienteHermano = actual;
                padre->primerHijo = hijo;
            }
            else
            {
                {
                    while (actual->siguienteHermano != NULL && ultimoNumeroActual + 1 != ultimoNumeroHijo)
                    {
                        actual = actual->siguienteHermano;
                        char *numeroVersionStr = convertirCadenaArregloChar(actual->numero_version);
                        ultimoNumeroActual = atoi(numeroVersionStr);
                        delete[] numeroVersionStr;
                    }
                }
            }

            if (ultimoNumeroHijo - ultimoNumeroActual <= 1)
            {
                if (ultimoNumeroHijo == 1)
                {
                    hijo->siguienteHermano = actual;
                    padre->primerHijo = hijo;
                }
                else
                {
                    hijo->siguienteHermano = actual->siguienteHermano;
                    actual->siguienteHermano = hijo;
                    actual = hijo->siguienteHermano;
                }

                while (actual != NULL)
                {
                    char *numeroVersionStr = convertirCadenaArregloChar(actual->numero_version);
                    int ultimoNumeroActual = atoi(numeroVersionStr);
                    delete[] numeroVersionStr;
                    destruirCadena(actual->numero_version);
                    ultimoNumeroActual++;
                    actual->numero_version = crearCadenaVacia();
                    int length = snprintf(NULL, 0, "%d", ultimoNumeroActual) + 1;
                    char *versionArray = (char *)malloc(length * sizeof(char));
                    snprintf(versionArray, length, "%d", ultimoNumeroActual);
                    agregarCaracteresCadena(actual->numero_version, versionArray);
                    actual = actual->siguienteHermano;
                }
            }
        }
    }
}

NodoVersion obtenerVersion(Version version, char *numVersion)
{
    NodoVersion nodo = NULL;
    if (numVersion[1] != '\0')
    {
        NodoVersion padre = obtenerVersionPadre(obtenerRaiz(version, &numVersion), &numVersion);
        nodo = obtenerSubVersion(padre, numVersion);
    }
    else
    {
        int numeroVersion = atoi(numVersion);
        Version nodoActual = version;
        char *numeroVersionStr = convertirCadenaArregloChar(nodoActual->raizVersion->numero_version);
        int numeroActual = atoi(numeroVersionStr);
        delete[] numeroVersionStr;
        while (nodoActual != NULL && numeroActual != numeroVersion)
        {
            nodoActual = nodoActual->siguienteNodo;
            if (nodoActual != NULL)
            {
                numeroVersionStr = convertirCadenaArregloChar(nodoActual->raizVersion->numero_version);
                numeroActual = atoi(numeroVersionStr);
                delete[] numeroVersionStr;
            }
        }
        if (nodoActual != NULL)
            nodo = nodoActual->raizVersion;
    }
    return nodo;
}

NodoVersion obtenerSubVersion(NodoVersion padre, char *numVersion)
{
    if (padre != NULL)
    {
        NodoVersion actual = padre->primerHijo;
        char *numeroVersionActual = convertirCadenaArregloChar(actual->numero_version);
        int ultimoNumeroActual = atoi(numeroVersionActual);
        int ultimoNumeroBuscado = atoi(numVersion);
        delete[] numeroVersionActual;

        while (actual != NULL && ultimoNumeroActual != ultimoNumeroBuscado)
        {
            actual = actual->siguienteHermano;
            if (actual != NULL)
            {
                numeroVersionActual = convertirCadenaArregloChar(actual->numero_version);
                ultimoNumeroActual = atoi(numeroVersionActual);
                delete[] numeroVersionActual;
            }
        }
        if (actual != NULL)
            return actual;
    }
    return NULL;
}

void agregarFilaVersion(Version &version, char *numeroVersion, char *textoFila, unsigned int numLinea)
{
    NodoVersion actual = obtenerVersion(version, numeroVersion);

    if (actual->inicioLineas == NULL)
    {
        Linea linea = crearLineaVacia();
        actual->inicioLineas = linea;
    }
    insertarLinea(actual->inicioLineas, textoFila, numLinea);
}

void imprimirVersion(Version version)
{
    Version actual = version;

    while (actual != NULL)
    {
        NodoVersion version = actual->raizVersion;
        char *numeroVersionStr = convertirCadenaArregloChar(version->numero_version);
        int numeroVersionRaiz = atoi(numeroVersionStr);
        delete[] numeroVersionStr;
        printf("%d\n", numeroVersionRaiz);
        Cadena versiones = crearCadenaVacia();
        agregarCaracteresCadena(versiones, convertirCadenaArregloChar(version->numero_version));
        imprimirSubversiones(version->primerHijo, versiones);
        destruirCadena(versiones);
        actual = actual->siguienteNodo;
    }
}

void imprimirLineasVersion(Version version, char *numeroVersion)
{
    NodoVersion actual = obtenerVersion(version, numeroVersion);
    if (actual != NULL)
    {
        Linea lineaActual = actual->inicioLineas;
        if (lineaActual == NULL)
            printf("No hay lineas en la version\n");
        else
        {
            unsigned int contador = 1;

            while (lineaActual != NULL)
            {
                char *textoLinea = obtenerTextoLinea(lineaActual, contador);
                printf("%s\n", textoLinea);
                delete[] textoLinea;
                contador++;
                lineaActual = siguienteLinea(lineaActual);
            }
        }
    }
}

int numeroUltimaLineaVersion(Version version, char *numeroVersion)
{
    NodoVersion actual = obtenerVersion(version, numeroVersion);
    unsigned int contador = 0;

    if (actual != NULL)
    {
        Linea lineaActual = actual->inicioLineas;
        if (lineaActual != NULL)

            while (lineaActual != NULL)
            {
                contador++;
                lineaActual = siguienteLinea(lineaActual);
            }
    }
    return contador;
}

Version siguienteVersion(Version version)
{
    return version->siguienteNodo;
}

bool existeVersion(Version version, char *numeroVersion)
{
    NodoVersion nodo = obtenerVersion(version, numeroVersion);
    return nodo != NULL;
}

void eliminarLineaVersion(Version &version, char *numeroVersion, unsigned int numLinea)
{
    NodoVersion actual = obtenerVersion(version, numeroVersion);
    if (actual != NULL)
        eliminarLinea(actual->inicioLineas, numLinea);
}

void destruirVersion(NodoVersion &version)
{
    version->siguienteHermano = NULL;
    version->primerHijo = NULL;
    destruirCadena(version->numero_version);
    version->numero_version = NULL;
    version->padre = NULL;
    delete version;
}

void borrarVersion(Version &version, char *numVersion)
{
    if (numVersion[1] != '\0')
    {
        NodoVersion padre = obtenerVersionPadre(obtenerRaiz(version, &numVersion), &numVersion);
        borrarSubVersion(padre, numVersion);
    }
    else
    {
        int numeroVersion = atoi(numVersion);
        Version nodoActual = version;
        char *numeroVersionStr = convertirCadenaArregloChar(nodoActual->raizVersion->numero_version);
        int numeroActual = atoi(numeroVersionStr);
        delete[] numeroVersionStr;
        Version previa = NULL;
        while (nodoActual != NULL && numeroActual != numeroVersion)
        {
            previa = nodoActual;
            nodoActual = nodoActual->siguienteNodo;
            if (nodoActual != NULL)
            {
                numeroVersionStr = convertirCadenaArregloChar(nodoActual->raizVersion->numero_version);
                numeroActual = atoi(numeroVersionStr);
                delete[] numeroVersionStr;
            }
        }
        if (nodoActual != NULL)
        {
            if (previa == NULL)
                version = nodoActual->siguienteNodo;

            else
                previa->siguienteNodo = nodoActual->siguienteNodo;

            Version aBorrar = nodoActual;
            nodoActual = nodoActual->siguienteNodo;
            while (nodoActual != NULL)
            {
                NodoVersion versionActual = nodoActual->raizVersion;
                char *numeroVersionStr = convertirCadenaArregloChar(versionActual->numero_version);
                int numeroVersionActual = atoi(numeroVersionStr);
                delete[] numeroVersionStr;
                numeroVersionActual--;
                int length = snprintf(NULL, 0, "%d", numeroVersionActual) + 1;
                char *versionArray = (char *)malloc(length * sizeof(char));
                snprintf(versionArray, length, "%d", numeroVersionActual);
                destruirCadena(versionActual->numero_version);
                versionActual->numero_version = crearCadenaVacia();
                agregarCaracteresCadena(versionActual->numero_version, versionArray);
                nodoActual = nodoActual->siguienteNodo;
                free(versionArray);
            }
            eliminarSubVersionesHijas(aBorrar->raizVersion);
            delete aBorrar;
        }
    }
}

void borrarSubVersion(NodoVersion &padre, char *numeroVersion)
{
    if (padre != NULL && padre->primerHijo != NULL)
    {
        int numVersion = atoi(numeroVersion);

        NodoVersion actual = padre->primerHijo;

        char *numeroVersionStr = convertirCadenaArregloChar(actual->numero_version);
        int numActual = atoi(numeroVersionStr);
        delete[] numeroVersionStr;

        NodoVersion previo = NULL;

        if (numVersion == numActual)
        {
            padre->primerHijo = actual->siguienteHermano;
        }
        else
        {
            while (actual != NULL && numVersion != numActual)
            {
                previo = actual;
                actual = actual->siguienteHermano;
                if (actual != NULL)
                {
                    char *numeroVersionStr = convertirCadenaArregloChar(actual->numero_version);
                    numActual = atoi(numeroVersionStr);
                    delete[] numeroVersionStr;
                }
            }
        }
        if (actual != NULL)
        {
            NodoVersion aBorrar = actual;
            actual = actual->siguienteHermano;
            if (previo != NULL)
                previo->siguienteHermano = actual;
            while (actual != NULL)
            {
                char *numeroVersionStr = convertirCadenaArregloChar(actual->numero_version);
                int ultimoNumeroActual = atoi(numeroVersionStr);
                delete[] numeroVersionStr;
                destruirCadena(actual->numero_version);
                ultimoNumeroActual--;
                actual->numero_version = crearCadenaVacia();
                int length = snprintf(NULL, 0, "%d", ultimoNumeroActual) + 1;
                char *versionArray = (char *)malloc(length * sizeof(char));
                snprintf(versionArray, length, "%d", ultimoNumeroActual);
                agregarCaracteresCadena(actual->numero_version, versionArray);
                actual = actual->siguienteHermano;
                free(versionArray);
            }
            eliminarSubVersionesHijas(aBorrar->primerHijo);
        }
    }
}

void eliminarSubVersionesHijas(NodoVersion &version)
{
    if (version != NULL)
    {
        eliminarSubVersionesHijas(version->primerHijo);
        eliminarSubVersionesHijas(version->siguienteHermano);
        destruirVersion(version);
    }
}

void destruirTodasLasVersiones(Version &version)
{
    Version actual = version;
    while (actual != NULL)
    {
        Version aBorrar = actual;
        eliminarSubVersionesHijas(aBorrar->raizVersion);
        destruirVersion(aBorrar->raizVersion);
        delete aBorrar;
    }
}

void imprimirVersiones(Version nodoListaVersion)
{
    Version actual = nodoListaVersion;
    while (actual != NULL)
    {
        NodoVersion version = actual->raizVersion;
        char *numeroVersionRaiz = convertirCadenaArregloChar(version->numero_version);
        printf("%s\n", numeroVersionRaiz);
        Cadena versiones = crearCadenaVacia();
        agregarCaracteresCadena(versiones, convertirCadenaArregloChar(version->numero_version));
        imprimirSubversiones(version->primerHijo, versiones);
        destruirCadena(versiones);
        delete[] numeroVersionRaiz;
        actual = actual->siguienteNodo;
    }
}

void imprimirVersionArchivo(Version version, char *numeroVersion)
{
    NodoVersion actual = obtenerVersion(version, numeroVersion);
    if (actual != NULL)
    {
        char *numeroVersionRaiz = convertirCadenaArregloChar(actual->numero_version);
        printf("%s\n", numeroVersionRaiz);
        Cadena versiones = crearCadenaVacia();
        agregarCaracteresCadena(versiones, convertirCadenaArregloChar(actual->numero_version));
        imprimirSubversiones(actual->primerHijo, versiones);
        destruirCadena(versiones);
        delete[] numeroVersionRaiz;
    }
}

void imprimirSubversiones(NodoVersion version, Cadena numeroVersion)
{
    if (version != NULL)
    {
        printf(" ");
        char *versiones = convertirCadenaArregloChar(version->numero_version);
        char numVersion = versiones[strlen(versiones) - 1];
        agregarCaracterFinalCadena(numeroVersion, '.');
        agregarCaracterFinalCadena(numeroVersion, numVersion);
        delete[] versiones;
        char *completo = convertirCadenaArregloChar(numeroVersion);
        printf("%s\n", completo);
        delete[] completo;
        if (version->primerHijo != NULL)
        {
            printf(" ");
            imprimirSubversiones(version->primerHijo, numeroVersion);
        }
        eliminarCaracterFinalCadena(numeroVersion);
        eliminarCaracterFinalCadena(numeroVersion);
        imprimirSubversiones(version->siguienteHermano, numeroVersion);
    }
}
