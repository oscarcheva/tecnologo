/*
  Módulo de definición de 'Linea'.

  Los elementos de tipo 'Linea' son punteros a una estructura (que debe
  definirse en linea.cpp).

  Laboratorio de EDA Turno Nocturno curso 2025.
  UTU-LATU
 */

#ifndef _LINEA_H
#define _LINEA_H


typedef struct _rep_linea *Linea;

//**************************** CONSTRUCTORAS ***************** */
//Crea una columna vacia
Linea crearLineaVacia();

//Pre-cond: existen por lo menos (num_fila - 1)
//Poa-Cond: inserta una nueva linea en la posicion "numLila"; 
//          Las Lineas debajo, si existen, se renumeran numLila=numLila+1
void insertarLinea(Linea &linea, char* texto, unsigned int numLinea);

//************************** SELECTORAS ********************** */

//Pre-Cond: esVaciaLinea(linea) retorna false; 
//Pos-Cond: Retorna un puntero de Linea a la siguiente linea de la
//          estructura "linea"
Linea siguienteLinea(Linea linea);

//Pre-Cond: esVaciaLinea(linea) retorna false; 
//Pos-Cond: Retorna un puntero de Linea a la anterior a linea de la
//          estructura "linea"
Linea anteriorLinea(Linea linea);

//Pos-Cond: Retorna la cantidad de lineas que tiene la estructura linea
unsigned int cantidadLineas(Linea linea);

//retorna el numero de la Linea linea
unsigned int getNumeroLinea(Linea linea);

//Pre-cond: La Linea numLila, existe en la estructura "linea"
//Pos-Cond: retorna un arreglo dinámico con todo el texto de la Linea "numLinea".
//          sin compartir memoria con "linea"
char* obtenerTextoLinea (Linea linea, unsigned int numLinea);

//*************************** PREDICADOS ********************** */

//Pos-Cond: retorna true si linea es vacía
bool esVaciaLinea(Linea linea);

//Pre-Cond: Retorna true si la Linea "numLinea" existe en la estructura "linea"
bool existeNumeroLinea(Linea linea, unsigned int numLinea);

//Pre-Cond: (esVaciaFila(fila1) && esVaciaFila(fila2)) retorna false
//Pos-Cond: retorna true si fila1 tiene los mismos caracteres 
//          y en el mismo orden que fila2
bool sonIgualesLineas(Linea linea1, Linea linea2);


//***************************** DESTRUCTORAS **************** */

//Pre-cond: la Linea "numLinea" existe en la Linea "linea"
//Pos-Cond: elimina la Linea de la estructura "linea" de la posicion "numLinea"
void eliminarLinea(Linea &linea, unsigned int numLinea);

//Pos-Cond: elimina toda la memoria de la estructura Linea "linea"
void destruirLinea(Linea &linea);

#endif
