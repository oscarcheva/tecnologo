/*
  Módulo de definición de 'Version'.

  Los elementos de tipo 'Version' son punteros a una estructura (que debe
  definirse en version.cpp).

  Laboratorio de EDA Turno Nocturno curso 2025.
  UTU-LATU
 */

#ifndef _VERSION_H
#define _VERSION_H

typedef struct _rep_version *Version;

//***********************  CONSTRUCTORAS ***************** */

// Pos-Cond: Retorna una version vacia
Version crearVersionVacia();

// Pre-Cond: num_version tiene que estar en el rango de 1 o la ultima version + 1 de
//			la Version "version"
// Pos-Cond: Crea una nueva version con el numero de verion "num_version
//			Las versiones iguales y mayores a num_version se les suma 1 al numero de version.
void crearVersion(Version &version, char *num_version);

//************************ SELECTORAS ********************* */

// Pre-Cond: la Version "numVersion" existe en version
// Pos-Cond: Retorna un puntero a la version que tiene como numero "numVersion"
Version obtenerVersion(Version &version, char *numVersion);

// Pre-cond: La version "version" tiene por lo menos "numLinea" de Lineas
// Pos-Cond: Agrega el string texto como la fila num_fila de la Version "version"
//           Las filas debajo de num_filas se renumeran como numLinea=numLinea+1
void agregarFilaVersion(Version &version, char *numeroVersion, char *textoFila, unsigned int numLinea);

// Pre-Cond: existeVersion(version, numeroVersion) retorna true.
// Pos-Cond: Imprime la Version "nombreVersion"
void imprimirVersion(Version version, char *numeroVersion);

////////////////////////////////// AGREGADA 05/09/2025  ////////////
// Pre-Cond: version != NULL
// Pos-Cond: retorna un puntero a la siguiente Version de "version"
Version siguienteVersion(Version version);

////////////////////////////////// AGREGADA 05/09/2025  ////////////
// Pre-Cond: version !=NULL
// Pos-Cond: retorna un puntero a un arreglo dinamico con el numero de la Version "version"
char *nombreVersion(Version version);

////////////////////////////////// AGREGADA 16/09/2025  ////////////
// Pre-Cond: (!esVaciaVersion(version)) retorna true
// Pos-Cond: retorna un entero con el numero de la ultima verison que hay en la Version "version"

int numeroUltimaVersion(Version version);

////////////////////////////////// AGREGADA 16/09/2025  ////////////
// Pre-Cond: No tiene
// Pos-Cond: retorna un entero con el numero de la ultima linea de la Verison de "version"
int numeroUltimaLineaVersion(Version version);

//********************* PREDICADOS ************************* */

//********** MODIFICADO 15/09/2025******************************
// pre-cond:No tiene
// pos-cond:Retorna true si la Version "version" es vacia.
bool esVaciaVersion(Version version);

// Retorna true si la Version "numeroVersion" existe en "version"
bool existeVersion(Version version, char *numeroVersion);

//****************  DESTRUCTORAS ***********************

// Pre-Cond: la Linea "numLinea" existe en la version "version"
// Pos-Cond: se elimina la Linea de la posicion "numLinea"
//           el resto de las Lineas debajo se renumeran como numLinea=numLinea-1
void eliminarLineaVersion(Version &version, char *numeroVersion, unsigned int numLinea);

// Pre-Cond: la version "numeroVersion" existe en version
// Pos-Cond: elimina toda la mermoria reservada por "numeroVersion"
//           y sus sub-versiones.
void destruirVersion(Version &version, char *numeroVersion);

////////////////////////////////// AGREGADA 05/09/2025  ////////////
// Pre-Cond: No tiene
// Pos-Cond: Elimina toda la memoria reservada por "version"
void destruirTodasLasVersiones(Version &version);

#endif
