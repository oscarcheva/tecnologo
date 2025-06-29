
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>

const int LIMITE_EN_ARRAYS = 20;

struct fecha
{
    int dia;
    int mes;
    int anio;
};

struct jugador
{
    long cedula;
    char nombre[LIMITE_EN_ARRAYS];
    char apellido[LIMITE_EN_ARRAYS];
    char alias[LIMITE_EN_ARRAYS];
    int saldo;
    bool activo;
    struct fecha fechaNacimiento;
};

struct jugadores
{
    struct jugador participantes[50];
    int tope = 0;
};

struct apuesta
{
    int valorApuesta;
    bool resultado;
    char alias[LIMITE_EN_ARRAYS];
    int saldoResultante;
};

struct apuestas
{
    struct apuesta jugadas[10];
    int tope;
};

void generarCopas(char &copa1, char &copa2, char &copa3, int valor)
{
    if (valor == 1)
    {
        copa1 = '.';
        copa2 = '0';
        copa3 = '0';
    }
    else if (valor == 2)
    {
        copa1 = '0';
        copa2 = '.';
        copa3 = '0';
    }
    else
    {
        copa1 = '0';
        copa2 = '0';
        copa3 = '.';
    }
}

void jugar(char &copa1, char &copa2, char &copa3, int valor)
{

    generarCopas(copa1, copa2, copa3, valor);
}

void estafar(char &copa1, char &copa2, char &copa3, int seleccion, int valor)
{

    if (seleccion == 3)
        valor = 1;
    else
        valor += 1;
    generarCopas(copa1, copa2, copa3, valor);
}

void modificarSaldo(int &saldo, int &apuesta, bool gano)
{
    if (gano)
        saldo += apuesta;
    else
        saldo -= apuesta;

    printf("Saldo: %d", saldo);
}

bool verificarResultado(char copa)
{
    if (copa == '.')
        return true;

    return false;
}

/// Copia el alias del alias del jugador al alias de la apuesta
void copiarNombre(char entrada[], char salida[])
{
    for (int i = 0; i < LIMITE_EN_ARRAYS; ++i)
    {
        salida[i] = entrada[i];
        if (entrada[i] == '\0')
            break;
    }
}

bool validarCI(long ci)
{
    return (ci >= 1000000 && ci <= 99999999);
}

bool esBisiesto(int anio)
{
    return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}

// Devuelve la cantidad de dias segun el mes
int diasDelMes(int mes, int anio)
{
    switch (mes)
    {
    case 2:
        return esBisiesto(anio) ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 31;
    }
}

bool validarFecha(int dia, int mes, int anio)
{
    if (anio < 1900 || anio > 2025)
        return false;
    if (mes < 1 || mes > 12)
        return false;
    int maxDias = diasDelMes(mes, anio);
    return (dia >= 1 && dia <= maxDias);
}

bool sonIguales(char aliasJugador[], char aliasJugadores[])
{
    int i = 0;
    while (aliasJugador[i] != '\0' && aliasJugadores[i] != '\0')
    {
        if (aliasJugador[i] != aliasJugadores[i])
            return false;
        i++;
    }
    return aliasJugador[i] == '\0' && aliasJugadores[i] == '\0';
}

bool esMayor(char jugadorAdelante[], char jugadorAtras[])
{
    int i = 0;
    while (jugadorAdelante[i] != '\0' && jugadorAtras[i] != '\0')
    {
            if (jugadorAdelante[i] > jugadorAtras[i])
                return true;
            else if (jugadorAdelante[i] == jugadorAtras[i])
                i++;
            else
                return false;
    }
    return true;
}

// Se revisa el alias de cada jugador en el struct de jugadores con el alias ingresado por texto
bool aliasExiste(struct jugadores lista, char alias[])
{
    for (int i = 0; i < lista.tope; i++)
    {
        if (sonIguales(lista.participantes[i].alias, alias))
        {
            return true;
        }
    }
    return false;
}

// Se revisa el alias de cada jugador en el struct de jugadores con el alias ingresado por texto y devuelve el indice del
int buscarAlias(struct jugadores lista, char alias[])
{
    for (int i = 0; i < lista.tope; i++)
    {
        if (sonIguales(lista.participantes[i].alias, alias))
        {
            return i;
        }
    }
    return -1;
}

void altaJugador(struct jugadores &todosJugadores)
{

    struct jugador nuevo;
    printf("Ingrese CI: ");
    scanf("%ld", &nuevo.cedula);
    if (!validarCI(nuevo.cedula))
    {
        printf("CI inválida.\n");
        return;
    }

    printf("Ingrese alias: ");
    scanf("%s", nuevo.alias);

    for (int i = 0; i < todosJugadores.tope; i++)
    {
        if (sonIguales(todosJugadores.participantes[i].alias, nuevo.alias))
        {
            if (!todosJugadores.participantes[i].activo)
            {
                todosJugadores.participantes[i].activo = true;
                printf("Jugador reactivado con éxito.\n");
                return;
            }
            else
            {
                printf("El alias ya existe y está activo.\n");
                return;
            }
        }
    }

    printf("Ingrese nombre: ");
    scanf("%s", nuevo.nombre);

    printf("Ingrese apellido: ");
    scanf("%s", nuevo.apellido);

    printf("Ingrese fecha de nacimiento (DD MM AAAA): ");
    scanf("%d %d %d", &nuevo.fechaNacimiento.dia, &nuevo.fechaNacimiento.mes, &nuevo.fechaNacimiento.anio);
    if (!validarFecha(nuevo.fechaNacimiento.dia, nuevo.fechaNacimiento.mes, nuevo.fechaNacimiento.anio))
    {
        printf("Fecha inválida.\n");
        return;
    }

    nuevo.saldo = 1000;
    nuevo.activo = true;
    todosJugadores.participantes[todosJugadores.tope] = nuevo;
    todosJugadores.tope++;

    printf("Jugador dado de alta exitosamente.\n");
}

void bajaJugador(struct jugadores &todosJugadores)
{
    char alias[LIMITE_EN_ARRAYS];
    printf("Ingrese alias del jugador a dar de baja: ");
    scanf("%s", alias);

    for (int i = 0; i < todosJugadores.tope; i++)
    {
        if (sonIguales(todosJugadores.participantes[i].alias, alias))
        {
            if (!todosJugadores.participantes[i].activo)
            {
                printf("El jugador ya está inactivo.\n");
                return;
            }
            todosJugadores.participantes[i].activo = false;
            printf("Jugador dado de baja correctamente.\n");
            return;
        }
    }
    printf("Alias no encontrado.\n");
}

void modificarJugador(struct jugadores &todosJugadores)
{
    char alias[LIMITE_EN_ARRAYS];
    printf("Ingrese alias del jugador a modificar: ");
    scanf("%s", alias);

    for (int i = 0; i < todosJugadores.tope; i++)
    {
        if (sonIguales(todosJugadores.participantes[i].alias, alias) && todosJugadores.participantes[i].activo)
        {
            printf("Nombre actual: %s\n", todosJugadores.participantes[i].nombre);
            printf("Ingrese nuevo nombre: ");
            scanf("%s", todosJugadores.participantes[i].nombre);

            printf("Apellido actual: %s\n", todosJugadores.participantes[i].apellido);
            printf("Ingrese nuevo apellido: ");
            scanf("%s", todosJugadores.participantes[i].apellido);

            printf("CI actual: %ld\n", todosJugadores.participantes[i].cedula);
            printf("Ingrese nueva CI: ");
            scanf("%ld", &todosJugadores.participantes[i].cedula);
            if (!validarCI(todosJugadores.participantes[i].cedula))
            {
                printf("CI inválida. Cancelando.\n");
                return;
            }

            printf("Fecha nacimiento actual: %d/%d/%d\n", todosJugadores.participantes[i].fechaNacimiento.dia,
                   todosJugadores.participantes[i].fechaNacimiento.mes,
                   todosJugadores.participantes[i].fechaNacimiento.anio);
            printf("Ingrese nueva fecha de nacimiento (DD MM AAAA): ");
            scanf("%d %d %d", &todosJugadores.participantes[i].fechaNacimiento.dia,
                  &todosJugadores.participantes[i].fechaNacimiento.mes,
                  &todosJugadores.participantes[i].fechaNacimiento.anio);
            if (!validarFecha(todosJugadores.participantes[i].fechaNacimiento.dia,
                              todosJugadores.participantes[i].fechaNacimiento.mes,
                              todosJugadores.participantes[i].fechaNacimiento.anio))
            {
                printf("Fecha inválida. Cancelando.\n");
                return;
            }

            printf("Datos modificados exitosamente.\n");
            return;
        }
    }
    printf("Alias no encontrado o jugador inactivo.\n");
}

void menuGestionDeUsuarios(struct jugadores &todosJugadores)
{
    int opcion;
    do
    {
        printf("Gestión de Usuario \n");
        printf("1. Alta de jugador\n");
        printf("2. Baja de jugador\n");
        printf("3. Modificar jugador\n");
        printf("4. Volver al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            altaJugador(todosJugadores);
            break;
        case 2:
            bajaJugador(todosJugadores);
            break;
        case 3:
            modificarJugador(todosJugadores);
            break;
        case 4:
            printf("Volviendo al menú principal.\n");
            break;
        default:
            printf("Opción inválida.\n");
        }
    } while (opcion != 4);
}

void ordenarJugadores(struct jugadores &jugadores)
{
    struct jugador verificador, verificado;
    int puntero;
    for (int p = 1; p < jugadores.tope; p++)
    {
        puntero = p;
        verificador = jugadores.participantes[p];

        while (puntero > 0)
        {
            verificado = jugadores.participantes[puntero - 1];
            if (!esMayor(verificador.alias, verificado.alias))
            {
                jugadores.participantes[puntero] = verificado;
                jugadores.participantes[puntero - 1] = verificador;
                puntero--;
            }
            else{
                puntero = 0;
            }
        }
    }
}

void listadoJugadores(struct jugadores jugadores)
{
    if (jugadores.tope != 0)
    {
        ordenarJugadores(jugadores);
        printf("%-12s %-10s %-12s %-10s %-6s\n", "Cedula", "Nombre", "Apellido", "Alias", "Saldo");

        for (int i = 0; i <= jugadores.tope - 1; i++)
        {

            struct jugador participante = jugadores.participantes[i];

            if (participante.activo)
                printf("%-12ld %-10s %-12s %-10s %-6d\n",
                       participante.cedula,
                       participante.nombre,
                       participante.apellido,
                       participante.alias,
                       participante.saldo);
        }
        printf("\n");
    }
    else
        printf("No existen jugadores registrados");

}
void listadoTodasLasApuestas(struct apuestas apuestas)
{

    if (apuestas.tope != 0)
    {

        printf("%-12s %-10s %-20s\n", "Alias", " Gano?", "   Apostado");

        for (int i = 0; i <= apuestas.tope - 1; i++)
        {

            struct apuesta jugada = apuestas.jugadas[i];

            printf("%-10s",
                   jugada.alias);

            if (jugada.resultado)
                printf("%-10s", "Si Ha acertado");
            else
                printf("%-10s", "No ha acertado");

            printf("     %d\n",
                   jugada.valorApuesta);
        }
        printf("\n");
    }
    else{
        printf("No existen apuestas registradas");
    }
}
void listadoDeApuestasPorJugador(jugadores jugadores, char alias[LIMITE_EN_ARRAYS], struct apuestas jugadas)
{
    int indiceJugador = buscarAlias(jugadores, alias);
    if (indiceJugador == -1)
        printf("El alias no existe\n");
    else
    {
        struct jugador participante = jugadores.participantes[indiceJugador];

        if (jugadas.tope != 0)
        {

            printf("Las apuestas de %s que tiene un saldo actual de %d son: \n", alias, participante.saldo);
            printf("\n");
            printf("%-12s %-10s %-20s\n", "Gano?", "   Apostado", "      Saldo Resultante");

            for (int i = 0; i <= jugadas.tope - 1; i++)
            {
                if (sonIguales(alias, jugadas.jugadas[i].alias))
                {
                    struct apuesta jugada = jugadas.jugadas[i];
                    if (sonIguales(jugada.alias, alias))
                    {

                        if (jugada.resultado)
                            printf("%-10s", "Si Ha acertado");
                        else
                            printf("%-10s", "No ha acertado");

                        printf("    %d",
                               jugada.valorApuesta);

                        printf("             %d\n",
                               jugada.saldoResultante);
                    }
                }
            }
        }
        else{
            printf("El participante no tiene apuestas");
        }
        printf("\n");
    }
}

void menuConsultas(struct jugadores participantes, struct apuestas jugadas)
{
    int seleccion = 0;
    do
    {
        printf("*** Menu de consulta, ingrese la opcion que desee.***\n");
        printf("********** 1 - Listado de jugadores. ****************\n");
        printf("********** 2 - Listado de todas las apuestas.********\n");
        printf("********** 3 - Listado de apuestas por jugador.******\n");
        printf("********** 4 - Salir. *******************************\n");
        scanf("%d", &seleccion);
        switch (seleccion)
        {
        case 1:
            listadoJugadores(participantes);
            break;
        case 2:
            listadoTodasLasApuestas(jugadas);
            break;
        case 3:
            char alias[LIMITE_EN_ARRAYS];
            printf("Por favor ingrese el alias del jugador: ");
            scanf("%s", &alias);
            listadoDeApuestasPorJugador(participantes, alias, jugadas);
            break;
        case 4:
            printf("Volviendo al menú principal.\n");
            break;
        default:
            printf("por favor ingrese datos validos");
            break;
        }

    } while (seleccion != 4);
}

void juego(struct jugadores &jugadores, char alias[LIMITE_EN_ARRAYS], struct apuestas &jugadas)
{
    int indiceJugador = buscarAlias(jugadores, alias);
    if (indiceJugador == -1)
        printf("El alias no existe\n");
    else
    {
        struct jugador participante = jugadores.participantes[indiceJugador];
        if (!participante.activo)
        printf("El jugador no esta activo para jugar \n2");
        else{
        const int MAX_MONTO = 1000;
        const int MIN_APUESTA = 50;

        int saldo = participante.saldo;
        int apuesta;
        int seleccion;
        char copa1;
        char copa2;
        char copa3;
        bool acierto = false;
        int ganadas = 0;
        int valorAleatorio;
        int ultimaJugada = 0;

        printf("Bienvenido/a, a continuación comenzaremos a jugar.\nPara cada jugada debes indicar con un '1', '2', o '3', en qué copa se encuentra la bola.\nRecuerda que también puedes optar por retirarte indicándolo con un '4'. \nAhora dime, cuanto dinero tienes disponible? \n");

        if (saldo < MIN_APUESTA || MAX_MONTO > 1000)
            printf("El saldo inicial debe ser igual o mayor a 50 y menor o igual a 1000");
        if (saldo < MIN_APUESTA || saldo > 1000)
            printf("El saldo inicial debe ser igual o mayor a 50 y menor o igual a 1000\n");
        else
        {
            printf("\nO O O");
            printf("\n1 2 3 \n");
            printf("\nCopa?: ");

            scanf("%d", &seleccion);

            while (seleccion != 4 && saldo > MIN_APUESTA)
                while (seleccion != 4 && saldo >= MIN_APUESTA)
                {
                    valorAleatorio = rand() % 3 + 1;

                    apuesta = 0;
                    while (apuesta < MIN_APUESTA || apuesta > saldo)
                    {
                        printf("Apuesta?: ");
                        scanf("%d", &apuesta);
                        if (apuesta < MIN_APUESTA)
                            printf("Para jugar hay que pagar amigo \n");

                        else if (apuesta > saldo)
                            printf("No puedes apostar mas de tu saldo \n");
                    }

                    if (ganadas == 2)
                    {
                        acierto = false;
                        estafar(copa1, copa2, copa3, seleccion, valorAleatorio);
                    }
                    else
                    {

                        jugar(copa1, copa2, copa3, valorAleatorio);

                        switch (seleccion)
                        {
                        case 1:
                            acierto = verificarResultado(copa1);
                            break;
                        case 2:
                            acierto = verificarResultado(copa2);
                            break;
                        case 3:
                            acierto = verificarResultado(copa3);
                            break;
                        }
                    }

                    printf("\n %c %c %c \n", copa1, copa2, copa3);

                    if (acierto)
                    {
                        printf("\nHa acertado ");
                        ganadas++;
                    }
                    else
                    {
                        printf("\nNo ha acertado ");
                        ganadas = 0;
                    }

                    modificarSaldo(participante.saldo, apuesta, acierto);
                    ultimaJugada = apuesta;

                    printf("\n");

                    struct apuesta jugada;

                    copiarNombre(alias, jugada.alias);
                    jugada.resultado = acierto;
                    jugada.valorApuesta = apuesta;
                    jugada.saldoResultante = participante.saldo;
                    
                    jugadores.participantes[indiceJugador] = participante;

                    jugadas.jugadas[jugadas.tope] = jugada;
                    jugadas.tope++;

                    if (saldo < MIN_APUESTA)
                        printf("Para jugar hay que pagar amigo \n");
                    else
                    {

                        printf("\nO O O");
                        printf("\n1 2 3 \n");
                        printf("\nCopa?: ");

                        scanf("%d", &seleccion);
                        if (ultimaJugada > 200 && acierto == false && seleccion == 4)
                            while (seleccion == 4)
                            {
                                printf("Debido a tu orgullo debes jugar esta partida, aun no puedes salir");
                                printf("\nO O O");
                                printf("\n1 2 3 \n");
                                printf("\nCopa?: ");
                                scanf("%d", &seleccion);
                            }
                    }
                }

            printf("Nos vemos a la proxima");
        }
    }
    }
}

int main()
{

    struct jugadores jugadores;
    struct apuestas apuestas;

    int seleccion;

    do
    {
        printf("Menu de jugador, ingrese la opcion que desee.\n");
        printf("************** 1 - Gestion de jugadores. ****\n");
        printf("************** 2 - Consultas. ***************\n");
        printf("************** 3 - Apostar. *****************\n");
        printf("************** 4 - Salir. *******************\n");
        scanf("%d", &seleccion);
        switch (seleccion)
        {
        case 1:
            menuGestionDeUsuarios(jugadores);
            break;
        case 2:
            menuConsultas(jugadores, apuestas);
            break;
        case 3:
            char alias[LIMITE_EN_ARRAYS];
            printf("Por favor ingrese el alias del jugador: ");
            scanf("%s", &alias);
            juego(jugadores, alias, apuestas);
            break;
        case 4:
            printf("Nos vemos a la proxima amigo");
            break;
        default:
            printf("Por favor ingrese datos validos");
            break;
        }

    } while (seleccion != 4);
    return 0;
}
