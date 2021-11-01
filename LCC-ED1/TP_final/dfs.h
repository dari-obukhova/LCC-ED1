#ifndef _DFS_H_
#define __DFS_H__
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "btree.h"
#define MAX_CHAR 50
#define MAX_CIUDADES 50
#define MAX_TO_READ 250 //el máximo de caracteres para leer

/**
 * Búsqueda en profundidad (Depth First Search)
 */
void dfs(int i, int n, int* matrix[n], int visited[], int itr, int camino_actual[],
  int camino_optimo[], int costo_actual, int* costo_optimo);

/**
  * Crea una matriz de tamaño n.
  */
int** matriz_crear(int n);

/**
  * Lee archivo y devuelve matriz con costos entre ciudades.
  */
int** leer_archivo(char* entrada, int* cantidad_ciudades, char** arreglo_ciudades, BTree btree_ciudades);

/**
  * Devuelve archivo con la solución del problema.
  */
void devolver_archivo(char* salida, int camino_optimo[], int cantidad_ciudades, char** arreglo_ciudades, int* matriz[cantidad_ciudades], int costo_optimo);

/**
  * Llama las funciónes auxiliares para leer archivo, encontrar el caminó más corto y devolver la solución como archivo del texto.
  */
void resolver_tsp(char* entrada, char* salida);


#endif /* __DFS_HH__ */
