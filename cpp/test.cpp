#include <stdio.h>

int main (){

    float base = 0;
    int exponente = 0;

    printf("\n Por favor ingrese la base: ");
    scanf("%f",&base);

    printf("\n Por favor ingrese el exponente: ");
    scanf("%d",&exponente);

    if (exponente < 0)
    printf("El exponente no puede ser menor a 0");
    else{
        printf ("\n La potencia es %d a la %f",base,exponente);
        printf ("\n El resultado de la operacion es: ");
        if (exponente == 0)
        printf ("1");
        else if (exponente == 1 )
        printf ("%b",base);
        else {
            int resultado;
            for (int x = exponente; x<= exponente; x++)
            {
             resultado *= x;   
            }
            printf ("%b",resultado);

        }


    }

    return 0;
}