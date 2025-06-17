#include <stdio.h>

int main()
{
    printf("Hello World from c++ \n");

    int a = 80;

    switch (a / 10)
    {
    case 3:
        printf("Treinta");
        break;
    case 4:
        printf("Cuarenta");
        break;
    case 5:
        printf("Cincuenta");
        break;
    case 6:
        printf("Sesenta");
        break;
    case 7:
        printf("Setenta");
        break;
    case 8:
        printf("Ochenta");
        break;
    case 9:
        printf("Noventa");
        break;
    default:
        break;
    }

    switch (a % 10)
    {
    case 1:
        printf(" y uno");
        break;
        case 2:
        printf(" y dos");
        break;
        case 3:
        printf(" y tres");
        break;
        case 4:
        printf(" y cuatro");
        break;
        case 5:
        printf(" y cinco");
        break;
        case 6:
        printf(" y seis");
        break;
        case 7:
        printf(" y siete");
        break;
        case 8:
        printf(" y ocho");
        break;
        case 9:
        printf(" y nueve");
        break;
    default:
        break;
    }

    printf("\n");


    int b = 945;


    printf("El numero es %d \n",b);
    printf("Dividiendo entre 100 queda %d \n",b/100);
    printf("Dividiendo mod 100 y entre 10 queda %d \n",(b%100)/10);
    printf("Dividiendo mod 10 queda %d \n",b%10);



}