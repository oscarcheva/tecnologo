/*
  Módulo de definición de 'CADENA'.

  Los elementos de tipo 'Cadena' son punteros a una estructura (que debe
  definirse en cadena.cpp).

  Laboratorio de EDA Turno Nocturno curso 2025.
  UTU-LATU
 */

#ifndef _CADENA_H
#define _CADENA_H

typedef struct _rep_cadena *Cadena;

/* Operaciones de Cadena */

//Pos-Cond: retorna una cadena de caracteres vacia
Cadena crearCadenaVacia();

//Pre-Cond: esVaciaCadenaCaracteres(cadena)retorna true.
//Pos-Cond: agrega los caracteres de cadena a la fila vaica "fila"
void agregarCaracteresCadena(Cadena &cadena, char* texto);

//retorna true si la cadena es vacia
bool esVaciaCadenaCaracteres (Cadena cadena);

//retorna true si la cadena1 es igual a la cadena2, false en caso contrario
bool sonIgualesCadenas(Cadena cadena1, Cadena cadena2);

//retorna el dato char* de la tupla tup
//pre-cond retorna un puntero a un arreglo dinamico 
char* convertirCadenaArregloChar(Cadena cadena);

//Pos-Cond: libera toda la memoria de cadena
void destruirCadena (Cadena &cadena);

#endif
