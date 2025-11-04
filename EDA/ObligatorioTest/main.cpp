#include <iostream>
#include <string.h>

#include "version.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    char *numeroVersion = "1";
    NodoListaVersion version  = crearNodoListaVersion();
    crearVersion(version,numeroVersion);
    char *numeroVersion2 = "2";
    crearVersion(version,numeroVersion2);
    char *numeroVersion3 = "3";
    crearVersion(version,numeroVersion3);
    char *numeroVersion4 = "2";
    crearVersion(version,numeroVersion4);
    char *numeroVersion5 = "9";
    crearVersion(version,numeroVersion5);

    char *numeroVersion6 = "2.1";
    crearVersion(version,numeroVersion6);
    char *numeroVersion7 = "2.2";
    crearVersion(version,numeroVersion7);
    char *numeroVersion8 = "2.5";
    crearVersion(version,numeroVersion8);

    crearVersion(version,numeroVersion7);

    imprimirVersiones(version);

    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}