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
    NodoListaVersion inicioVersion;
};

Archivo crearArchivoVacio(char *nomArchivo);

void crearVersionArchivo(Archivo &archivo, char *numVersion);

// void versionIndependienteArchivo(Archivo &archivo, char *numVersion);

char *obtenerNombreArchivo(Archivo archivo);

void mostrarVersionesArchivo(Archivo archivo);

void insertarLineaVersionDeArchivo(Archivo &archivo, char *numeroVersion, char *textoFila, unsigned int numFila);

void imprimirVersionArchivo(Archivo archivo, char *numeroVersion);

void mostrarCambiosArchivo(Archivo archivo, char *numeroVersion);

void mostrarTextoArchivoVersion(Archivo archivo, char *numeroVersion);

unsigned int numeroUltimaVersionArchivo(Archivo archivo);

unsigned int numeroUltimaLinea(Archivo archivo, char *nombreVersion);

bool igualesVersionesArchivo(Archivo archivo, char *numeroVersion1, char *numeroVersion2);

bool existeVersionEnArchivo(Archivo archivo, char *numeroVersion);

void borrarArchivoCompleto(Archivo &archivo);

void borrarVersionDeArchivo(Archivo &archivo, char *numeroVersion);

void borrarLineaVersionArchivo(Archivo &archivo, char *numeroVersion, unsigned int numFila);

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

    if (archivo->inicioVersion == NULL)
    {
        archivo->inicioVersion = crearNodoListaVersion();
    }
}