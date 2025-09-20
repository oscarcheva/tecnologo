/* 1111111 */
/*
  Módulo de implementación de 'utils'.

  UTU-Latu-Turno-Nocturno
 */

#include "../include/utils.h"

#include "stdio.h"

nat leerNat() {
  nat res;
  scanf("%u", &res);
  return res;
}

char leerChar() {
  char res;
  scanf(" %c", &res);
  return res;
}

double leerDouble() {
  double res;
  scanf("%lf", &res);
  return res;
}

void leerChars(ArregloChars cs) { scanf("%s", cs); }

void leerRestoLinea(ArregloChars cs) { scanf("%[^\n]", cs); }
