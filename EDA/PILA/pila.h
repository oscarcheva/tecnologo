
#ifndef PILA_H
#define PILA_H

typedef struct _pila * Pila;

//****************Contructoras*************/

//Pre_Condicion:No tiene
//Pos_Condicion: Retorna una pila sin elementos.
Pila crearPilaVacia(int cota);

//Pre_Condicion:esLLenaPila(p) retorna false
//Pos_Condicion: inserta el elemento elem en el tope de p
void insertarElementoPila(Pila &p, int elem);

//****************Selectora*************/

//Pre_Condicion:Que no este vacia
//Pos_Condicion: Retorna el elemento que esta en el tope de p
int obtenerTopePila(Pila p);

//Pre_Condicion:esVaciaPila(p) retorna false
//Pos_Condicion: elimina el elem que esta en el tope de p
void eliminarTopePila(Pila &p);

//****************Predicado*************/

//Pre_Condicion:No tiene
//Pos_Condicion:retorna true si la pila no tiene elementos, false en lo contrario
bool esVaciaPila(Pila p);

//Pre_Condicion:No tiene
//Pos_Condicion:retorna true si la pila  tiene elementos, false en lo contrario
bool esLLenaPila(Pila p);

//****************Destructoras*************/

//Pre_Condicion:No tiene
//Pos_Condicion:Libera toda la memoria de p
void destruirPila(Pila &p);

#endif
