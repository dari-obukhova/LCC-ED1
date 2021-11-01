#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "dfs.h"
#include <locale.h>
#include "btree.h"



int main (int argc,  char **argv) {

  char *archivoEntrada = malloc(sizeof(char) * MAX_CHAR);
  char *archivoSalida = malloc(sizeof(char) * MAX_CHAR);

  strcpy(archivoEntrada, argv[1]);
  strcpy(archivoSalida, argv[2]);

  resolver_tsp(archivoEntrada, archivoSalida);

  free(archivoEntrada);
  free(archivoSalida);

  return 0;
 }
