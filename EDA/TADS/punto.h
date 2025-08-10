#ifndef PUNTO_H
#define PUNTO_H

typedef struct _punto *Punto;


// **** Constructores ****

Punto construirPunto1();
Punto construirPunto2(int x, int y);


// **** Selectores ****
int coordenadaXPunto(Punto p);
int coordenadaYPunto(Punto p);

// **** Predicado ****

int sonIgualesPuntos(Punto p1, Punto p2);

// **** Destructor ****

void destruirPunto(Punto p);
#endif