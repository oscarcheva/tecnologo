/* 6339682 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/archivo.h"
#include "../include/version.h"
#include "../include/cadena.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _rep_archivo
{
    Cadena nombreArchivo;
    Version inicioVersion;
};

Archivo crearArchivoVacio(char *nomArchivo)
{
    Archivo nuevo = new _rep_archivo;
    nuevo->inicioVersion = NULL;
    Cadena nombreCadena = crearCadenaVacia();
    agregarCaracteresCadena(nombreCadena, nomArchivo);
    nuevo->nombreArchivo = nombreCadena;
    return nuevo;
}

void crearVersionArchivo(Archivo &archivo, char *numVersion)
{
    if (archivo->inicioVersion == NULL && strcmp(numVersion, "1") == 0)
    {
        archivo->inicioVersion = crearVersionVacia();
    }

    crearVersion(archivo->inicioVersion, numVersion);
}

// void versionIndependienteArchivo(Archivo &archivo, char *numVersion){

// }

char *obtenerNombreArchivo(Archivo archivo)
{
    if (archivo == NULL)
        return NULL;
    char *nombreArchivo = convertirCadenaArregloChar(archivo->nombreArchivo);
    return nombreArchivo;
}

void mostrarVersionesArchivo(Archivo archivo)
{
    char *version = convertirCadenaArregloChar(archivo->nombreArchivo);
    printf("%s\n", version);
    delete[] version;

    if (archivo != NULL)
    {
        if (archivo->inicioVersion == NULL)
            printf("No hay versiones creadas\n");
        else
        {
            Version actual = archivo->inicioVersion;
            if (actual != NULL)
            {
                imprimirVersion(archivo->inicioVersion);
            }
        }
    }
}

void insertarLineaVersionDeArchivo(Archivo &archivo, char *numeroVersion, char *textoFila, unsigned int numFila)
{
    if (archivo != NULL && existeVersionEnArchivo(archivo, numeroVersion))
        agregarFilaVersion(archivo->inicioVersion, numeroVersion, textoFila, numFila);
}

void mostrarCambiosArchivo(Archivo archivo, char *numeroVersion)
{
    mostrarCambiosVersiones(archivo->inicioVersion, numeroVersion);
}

void mostrarTextoArchivoVersion(Archivo archivo, char *numeroVersion)
{
    imprimirLineasVersion(archivo->inicioVersion, numeroVersion);
}

bool existeVersionEnArchivo(Archivo archivo, char *numeroVersion)
{
    return existeVersion(archivo->inicioVersion, numeroVersion);
}

bool tienePrimerHijoVersion(Archivo a, char *version)
{
    return tienePrimerHijo(a->inicioVersion, version);
}

void borrarArchivoCompleto(Archivo &archivo)
{
    if (archivo != NULL)
    {
        if (archivo->inicioVersion != NULL)
            destruirTodasLasVersiones(archivo->inicioVersion);
        destruirCadena(archivo->nombreArchivo);
        delete archivo;
        archivo = NULL;
    }
}

void borrarVersionDeArchivo(Archivo &archivo, char *numeroVersion)
{
    if (archivo != NULL || existeVersionEnArchivo(archivo, numeroVersion))
        borrarVersion(archivo->inicioVersion, numeroVersion);
}

void borrarLineaVersionArchivo(Archivo &archivo, char *numeroVersion, unsigned int numFila)
{
    if (archivo != NULL || existeVersionEnArchivo(archivo, numeroVersion))
        eliminarLineaVersion(archivo->inicioVersion, numeroVersion, numFila);
}

unsigned int numeroUltimaLinea(Archivo archivo, char *nombreVersion)
{
    return numeroUltimaLineaVersion(archivo->inicioVersion, nombreVersion);
}

bool igualesVersionesArchivo(Archivo a, char *version1, char *version2)
{
    return versionesIguales(a->inicioVersion, version1, version2);
}
