//
// Created by oeche on 11/08/2025.
//

#ifndef RACIONAL_H
#define RACIONAL_H

typedef struct _racional *Racional;

// **** Constructores ****

Racional construirRacional1();

// Pre-Cond: El denominador no puede ser 0;
// Post-Cond: Crea un racional ingreado por el usuario;= en la forma m/n
Racional construirRacional2(int numerador, int denominador);

// **** Selectores ****

int retornarNumerador(int p);

int retornarDenominador(int q);

// Pre-Cond: Ninguno de los racionales puede tener un denominador igual a 0
// Post-Cond: Crea un racional ingreado por el usuario;= en la forma m/n
Racional sumarRacionales(Racional racional1, Racional racional2);

// Pre-Cond: Ninguno de los racionales puede tener un denominador igual a 0
Racional restarRacionales(Racional racional1, Racional racional2);

// Pre-Cond: Ninguno de los racionales puede tener un denominador igual a 0
Racional multiplicarRacionales(Racional racional1, Racional racional2);

// Pre-Cond: Ninguno de los racionales puede tener un denominador igual a 0
Racional dividirRacionales(Racional racional1, Racional racional2);

// Pre-Cond: Ninguno de los racionales puede tener un denominador igual a 0
Racional simplicarRacional(Racional racional);

void imprimirRacional(Racional racional);

// **** Predicados ****

// Pre-Cond: Ninguno de los racionales puede tener un denominador igual a 0
// Post-Cond: Devuelve 0 si racional 1 es menor que racional 2, 0 si es igual y 1 si es mayor;
int compararRacionales(Racional racional1, Racional racional2);


// **** Destructores

int destruirRacional(Racional racional);

#endif //RACIONAL_H
