#include<stdio.h>
#include"pila.h"
struct nodoPila{
    int elem;
    nodoPila * sig;
}typedef *Nodo;

struct _pila{
    int cota;
    int cantidad;
    nodoPila * pila;
};

//****************Contructoras*************/

//Pre_Condicion:No tiene
//Pos_Condicion: Retorna una pila sin elementos.
Pila crearPilaVacia(int cota){
    Pila p = new _pila();
    p->cota = cota;
    p->cantidad = 0;
    p->pila = NULL;
    return p;

}

//Pre_Condicion:esLLenaPila(p) retorna false
//Pos_Condicion: inserta el elemento elem en el tope de p
void insertarElementoPila(Pila &p, int elem){
    Nodo nuevoNodo = new nodoPila();
    nuevoNodo -> elem = elem;
    nuevoNodo -> sig = p->pila;
    p -> pila = nuevoNodo;
    p -> cantidad++;
}

//****************Selectora*************/

//Pre_Condicion:Que no este vacia
//Pos_Condicion: Retorna el elemento que esta en el tope de p
int obtenerTopePila(Pila p){
    return p -> pila -> elem;
}

//Pre_Condicion:esVaciaPila(p) retorna false
//Pos_Condicion: elimina el elem que esta en el tope de p
void eliminarTopePila(Pila &p){
    nodoPila * borrar = p -> pila;
    p -> pila = borrar -> sig;
    delete borrar;
    p->cantidad--;

}

//****************Predicado*************/

//Pre_Condicion:No tiene
//Pos_Condicion:retorna true si la pila no tiene elementos, false en lo contrario
bool esVaciaPila(Pila p){
    return p->pila == nullptr;
};

//Pre_Condicion:No tiene
//Pos_Condicion:retorna true si la pila  tiene elementos, false en lo contrario
bool esLLenaPila(Pila p){
    return p->cantidad == p->cota;
};

//****************Destructoras*************/

//Pre_Condicion:No tiene
//Pos_Condicion:Libera toda la memoria de p
void destruirPila(Pila &p){

}//
// Created by oeche on 18/08/2025.
//
