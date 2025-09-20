//
// Created by oeche on 14/08/2025.
//

// ------------- TAD Lista --------------------
#ifndef LISTA_H
#define LISTA_H

typedef struct _nodoLista *Lista ;

// ------------- TAD Constructoras -------------------

//pre-cond: No tiene
//post-cond: Retorna una lista vacia
Lista crearListaVacia();


// ------------- TAD Selectoras  ---------------------

//pre-cond: No tiene
//post-cond: Agrega el elemento al final de la lista
void insertarElemento(Lista &lista, int elemento);

//pre-cond: !esVaciaLista()
//post-cond: Retorna el primer elemento de la lista y lo elimina
int eliminarPrimerElemento(Lista &lista);

// ------------- TAD Predicados ----------------------

//pre-cond: No tiene
//post-cond: Retorna 1 por true (lista vacia) y 0 por false
bool esListaVacia(Lista &lista);

// ------------- TAD Destructoras --------------------

//pre-cond: No tiene
//post-cond: Libera la memoria de L
void destruirLista(Lista &lista);


#endif //LISTA_H
