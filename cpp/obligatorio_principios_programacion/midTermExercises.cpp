#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "matrizPerfecta.h"

struct materia
{
    int codigo;
    char nombre[30];
    int idDocente;
    int cargaHoraria;
    int creditos;
};

struct materias
{
    materia catedras[40];
    int tope = 0;
};

void cargarMateria()
{
    materia materia;

    printf("Por favor ingrese el codigo de la materia");
    scanf("%d", &materia.codigo);

    printf("Por favor ingrese el nombre de la materia");
    scanf("%s", &materia.nombre);

    printf("Por favor ingrese el identificador de la materia");
    scanf("%d", &materia.idDocente);

    printf("Por favor ingrese la carga horaria de la materia");
    scanf("%s", &materia.cargaHoraria);

    printf("Por favor ingrese los creditos de la materia");
    scanf("%s", &materia.creditos);
}

void ordenarMaterias()
{
    materias materias = materias;
    for (int p = 1; p < materias.tope; p++)
    {
        materia verificador = materias.catedras[p];
        int puntero = p;
        while (puntero != 0)
        {
            materia verificado = materias.catedras[p - 1];
            if (verificador.codigo < verificado.codigo)
            {
                materias.catedras[p - 1] = verificador;
                materias.catedras[p] = verificado;
                p--;
            }
            else
                p = 0;
        }
    }
}

void perfectMatrix()
{
    const int rows = 3;
    const int columns = 5;

    int matriz[rows][columns] = {
        {2, 3, 1, 4, 2},
        {3, 2, 4, 3, 4},
        {4, 4, 4, 2, 3}};
    bool perfect = true;

    for (int x = 0; x <= columns - 1; x++)
    {
        int suma = 0;
        for (int y = 0; y <= rows - 1; y++)
        {
            suma += matriz[y][x];
        }
        if (suma != 9)
            perfect = false;
    }

    printf("The matrix %s perfect", perfect ? "is" : "is not");
}

void reverseArray()
{

    const int length = 10;
    int array[length] =
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int x = 0; x <= length - 1; x++)
    {
        printf("%d", array[x]);
    }

    printf("%s", "\n");

    for (int x = 0; x <= (length - 1) / 2; x++)
    {
        int temp = array[x];
        array[x] = array[length - 1 - x];
        array[length - 1 - x] = temp;
    }

    for (int x = 0; x <= length - 1; x++)
    {
        printf("%d", array[x]);
    }
    printf("%s", "\n");
}

void lowestRow()
{

    const int rows = 3;
    const int columns = 5;

    int row = 0;
    int sum = 0;

    int matriz[rows][columns] = {
        {2, 3, 1, 4, 2},
        {3, 2, 4, 3, 4},
        {1, 0, 1, 2, 3}};

    for (int x = 0; x <= rows - 1; x++)
    {
        int currentSum = 0;

        for (int y = 0; y <= columns - 1; y++)
        {
            currentSum += matriz[x][y];
        }
        if (x == 0)
            sum = currentSum;
        if (currentSum < sum)
            row = x;
        sum = currentSum;
    }

    printf("The lowest row is: %d", (row + 1));
}

int factorialWithRecursion(int n)
{
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorialWithRecursion(n - 1);
}

void ascendingRecursiveNumber(int n)
{

    if (n == 0)
        printf("0 ");
    else
        ascendingRecursiveNumber(n - 1);
    printf("%d ", n);
}

int recursivePower(int n, int x)
{
    if (x == 0 || n == 1)
        return 1;
    else if (x == 1)
        return n;
    else
        return n* recursivePower(n,x-1);
}

int main()
{

    // perfectMatrix();
    // reverseArray();
    // lowestRow();

    // printf("%d",factorialWithRecursion(5));
    // ascendingRecursiveNumber(5);

    printf("%d",recursivePower(2,5));


    return 0;
}