#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "TP.h"

int main () {
    srand(time(NULL));
    SList listaNombres = slist_crear();
    SList listaLugarNacimiento = slist_crear();
    char* fileNombres = "nombres.txt";
    char* fileLugarNac = "paises.txt";

    int lenNombres = leer_archivo(fileNombres, &listaNombres);

    assert(lenNombres != -1 && "No se puede abrir el archivo nombres.txt");

    int lenLugares = leer_archivo(fileLugarNac, &listaLugarNacimiento);

    assert(lenLugares != -1 && "No se puede abrir el archivo paises.txt");

    int n = 0;  //Cantidad de personas que se quieren poner en la lista.
    while(n <= 2000) {
      printf("Ingrese el número de personas que quiere en la lista, deben ser al menos 2000:\n");
      scanf("%d", &n);
    }

    SList listaPersonas = crear_lista_personas(listaNombres, lenNombres, listaLugarNacimiento, lenLugares, n);

    devuelve_archivo(listaPersonas);

    destruir_lista(listaPersonas, destruir_persona);

    destruir_lista(listaNombres, destruir_dato);

    destruir_lista(listaLugarNacimiento, destruir_dato);

    return 0;
}
