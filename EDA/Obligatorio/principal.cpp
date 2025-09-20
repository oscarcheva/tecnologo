/* 1111111 */ // sustituir con los 7 dígitos de la cédula

/* Módulo principal de la tarea de EDA

Intérprete de comandos para probar los módulos.

Cada comando tiene un nombre el cual solicitara los distintos datos


El comando Fin termina el programa
Laboratorio de EDA 2025 UTU - LATU - Turno Nocturno 
Profesor Ing. Ferando Arrieta

*/
//*********************  DIRECTIVAS DE PRE-PROCESAMIENTO *************
#include "include/archivo.h"
#include "include/utils.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstddef>
#define MAX_PALABRA 64
#define MAX_LINEA 256
#define MAX_NOMBRE 25
#define MAX_PARAMETRO 25
#define MAX_NUMERO 4
enum _retorno {OK, ERROR, NO_IMPLEMENTADA};
typedef enum _retorno TipoRet;

//*********************** FIRMAS DE FUNCIONES ********************************

//PRE Y POS CONDICIONES SE ENCUENTRAN EN LA LETRA DEL OBLIGATORIO
Archivo crearArchivo(char * nombre); 													//Obligatorio 1 y 2
TipoRet borrarArchivo(Archivo &a);														//Obligatorio 1 y 2
TipoRet crearVersion(Archivo &a, char * version);										//Obligatorio 1 y 2
TipoRet borrarVersion(Archivo &a, char * version); 										//Obligatorio 1 y 2
TipoRet mostrarVersiones(Archivo a);													//Obligatorio 1 y 2
TipoRet insertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea); //Obligatorio 1 y 2
TipoRet borrarLinea(Archivo &a, char * version, unsigned int nroLinea);					//Obligatorio 2
TipoRet mostrarTexto(Archivo a, char * version);										//Obligatorio 1 y 2
TipoRet mostrarCambios(Archivo a, char * version); 										//Obligatorio 2
TipoRet iguales(Archivo a, char * version1, char * version2, bool &iguales);			//Obligatorio 2
TipoRet versionIndependiente(Archivo &a, char * version); 								//Obligatorio 2


//*******************  PROGRAMA PRINCIPAL ******************************
int main() {

  char restoLinea[MAX_LINEA + 1];
  char palabra[MAX_PALABRA];
  char sentencia[MAX_PALABRA];
  char sinParametro[MAX_PARAMETRO];
  char numeroLinea[MAX_NUMERO];
  char version[MAX_PARAMETRO];
  char version1[MAX_PARAMETRO];
  char version2[MAX_PARAMETRO];
  char nomArchivo [MAX_NOMBRE];
  unsigned int numeroLin=0;
  int cont_comandos = 0;
  bool salir = false;
  bool valoresIguales = false;
  
  printf("\n\n************ BIENVENIDOS AL MANEJADOR DE VERSIONES DE ARCHIVO *********\n\n");
  printf("Ingrese el nombre del archivo a crear: ");
  scanf("%s",nomArchivo);
  Archivo a = crearArchivo(nomArchivo);
  printf("\n");
  while (!salir) {
        // mostrar el prompt
        cont_comandos++;
        printf("%d>", cont_comandos);	
        // leer el comando
        leerChars(sentencia);
        int largo=strlen(sentencia);
        for (int i=1;i<largo;i++){
            if ((sentencia[i]=='(') || (sentencia [i]==')'))
                sentencia[i]=',';
        }
        char* token = strtok(sentencia,",");
        char nombre_comando[MAX_PALABRA];
        strcpy(nombre_comando,token);
        int cont=0;
        while (token != NULL){
            if ((0==strcmp(nombre_comando, "borrarArchivo") && (cont==0)))
                    strcpy(sinParametro,token); 
            else if (0==strcmp(nombre_comando, "crearVersion") && (cont==2))
                    strcpy(version,token);
            else if (0==strcmp(nombre_comando, "borrarVersion") && (cont==2))
                    strcpy(version,token);
            else if (0==strcmp(nombre_comando, "mostrarVersiones") && (cont==0))
                    strcpy(sinParametro,token);
            else if (0==strcmp(nombre_comando, "insertarLinea") && (cont==2))
                    strcpy(version,token);
			else if (0==strcmp(nombre_comando, "insertarLinea") && (cont==3))
                    strcpy(palabra,token);
			else if (0==strcmp(nombre_comando, "insertarLinea") && (cont==4)){
                    strcpy(numeroLinea,token);
					sscanf(numeroLinea,"%u",&numeroLin);
			}
            else if (0==strcmp(nombre_comando, "borrarLinea") && (cont==2))
                    strcpy(version,token);
			else if (0==strcmp(nombre_comando, "borrarLinea") && (cont==3)){
                    strcpy(numeroLinea,token);	
					sscanf(numeroLinea,"%u",&numeroLin);
			}
            else if (0==strcmp(nombre_comando, "mostrarTexto") && (cont==2))
                    strcpy(version,token);
            else if (0==strcmp(nombre_comando, "mostrarCambios") && (cont==2))
                    strcpy(version,token);
            else if (0==strcmp(nombre_comando, "iguales") && (cont==2))
                    strcpy(version1,token);
			else if (0==strcmp(nombre_comando, "iguales") && (cont==3))
                    strcpy(version2,token);
            else if (0==strcmp(nombre_comando, "versionIndependiente") && (cont==2))
                    strcpy(version,token);
            token = strtok(NULL, ",");
            cont++;
        }
        // procesar el comando
		if (0 == strcmp(nombre_comando, "Fin")) {
				salir = true;
				printf("Fin.\n");
				// comentario
		}else if (0 == strcmp(nombre_comando, "borrarArchivo")) {       
					TipoRet salida=borrarArchivo(a);
					if (salida == OK)
						printf("OK\n");
					else if (salida == NO_IMPLEMENTADA )
							printf("NO_IMPLEMENTADA\n");
					else if( salida == ERROR )
						printf("ERROR\n");
					
        }else if (0 == strcmp(nombre_comando, "crearVersion")) {
					TipoRet salida=crearVersion(a,version);
                    if (salida == OK)
                        printf("OK\n");
                    else if (salida == NO_IMPLEMENTADA )
                            printf("NO_IMPLEMENTADA\n");
					else if( salida == ERROR )
						printf("ERROR\n");
						
        } else if (0 == strcmp(nombre_comando, "borrarVersion")) {
                    TipoRet salida=borrarVersion(a,version);
                    if (salida == OK)
                        printf("OK\n");
                    else if (salida == NO_IMPLEMENTADA )
                            printf("NO_IMPLEMENTADA\n");
					else if( salida == ERROR )
						printf("ERROR\n");
						
        } else if (0 == strcmp(nombre_comando, "mostrarVersiones")) {
					TipoRet salida=mostrarVersiones(a);
                     if (salida == OK)
                        printf("OK\n");
                    else if (salida == NO_IMPLEMENTADA )
                            printf("NO_IMPLEMENTADA\n");
					else if( salida == ERROR )
						printf("ERROR\n");
						
        } else if (0 == strcmp(nombre_comando, "insertarLinea")) {
                    TipoRet salida=insertarLinea(a,version,palabra,numeroLin);
                    if (salida == OK)
                        printf("OK\n");
                    else if (salida == NO_IMPLEMENTADA )
                            printf("NO_IMPLEMENTADA\n");
					else if( salida == ERROR )
						printf("ERROR\n");
						
        } else if (0 == strcmp(nombre_comando, "borrarLinea")) {
    
                    TipoRet salida=borrarLinea(a,version,numeroLin);
                    if (salida == OK)
                        printf("OK\n");
                    else if (salida == NO_IMPLEMENTADA )
                            printf("NO_IMPLEMENTADA\n");
					else if( salida == ERROR )
						printf("ERROR\n");
						
        } else if (0 == strcmp(nombre_comando, "mostrarTexto")) {
                    TipoRet salida=mostrarTexto(a,version);
                    if (salida == OK)
                        printf("OK\n");
                    else if (salida == NO_IMPLEMENTADA )
                            printf("NO_IMPLEMENTADA\n");
					else if( salida == ERROR )
						printf("ERROR\n");
						
        } else if (0 == strcmp(nombre_comando, "mostrarCambios")) {
                    TipoRet salida=mostrarCambios(a,version);
                    if (salida == OK)
                        printf("OK\n");
                    else if (salida == NO_IMPLEMENTADA )
                            printf("NO_IMPLEMENTADA\n");
					else if( salida == ERROR )
						printf("ERROR\n");
						
        } else if (0 == strcmp(nombre_comando, "iguales")) {
                    
                    TipoRet salida=iguales(a,version1,version2,valoresIguales);
                    if (salida == OK)
                        printf("OK\n");
                    else if (salida == NO_IMPLEMENTADA )
                            printf("NO_IMPLEMENTADA\n");
					else if( salida == ERROR )
						printf("ERROR\n");
				
        } else if (0 == strcmp(nombre_comando, "versionIndependiente")) {
                    TipoRet salida=versionIndependiente(a,version);
                    if (salida == OK)
                        printf("OK\n");
                    else if (salida == NO_IMPLEMENTADA )
                            printf("NO_IMPLEMENTADA\n");
					else if( salida == ERROR )
						printf("ERROR\n");
        } 
		else 
			printf("Comando no reconocido.\n");
       
        // if
        fgets(restoLinea, MAX_LINEA + 1, stdin);
  } // while
  return 0;
} // main



 //************* FUNCIONES A IMPLEMENTAR POR LOS ESTUDIANTES ***********
   
Archivo crearArchivo(char * nombre){
		
		return NULL;
}

TipoRet borrarArchivo(Archivo &a){
		return NO_IMPLEMENTADA;
}

TipoRet crearVersion(Archivo &a, char * version){
		return NO_IMPLEMENTADA;
}

TipoRet borrarVersion(Archivo &a, char * version){
		return NO_IMPLEMENTADA;
}

TipoRet mostrarVersiones(Archivo a){
		return NO_IMPLEMENTADA;
}

TipoRet insertarLinea(Archivo &a, char * version, char * linea, unsigned int nroLinea){ 
		return NO_IMPLEMENTADA;
}

TipoRet borrarLinea(Archivo &a, char * version, unsigned int nroLinea){
		return NO_IMPLEMENTADA;
}

TipoRet mostrarTexto(Archivo a, char * version){
		return NO_IMPLEMENTADA;
}

TipoRet mostrarCambios(Archivo a, char * version){
		return NO_IMPLEMENTADA;
}

TipoRet iguales(Archivo a, char * version1, char * version2, bool &iguales){
		return NO_IMPLEMENTADA;
}

TipoRet versionIndependiente(Archivo &a, char * version){
	   return NO_IMPLEMENTADA;
}
