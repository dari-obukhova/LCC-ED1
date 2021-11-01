#ifndef __BTREE_H__
#define __BTREE_H__
#define MAX_CHAR 30
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct _BTNodo {
  wchar_t* dato; //cambiar wchar_t*
  struct _BTNodo *left;
  struct _BTNodo *right;
  struct _BTNodo *parent;
} BTNodo;

typedef BTNodo* BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 *
 */
BTree btree_insertar(BTree raiz, wchar_t* dato); //int btree_insertar

/**
 * Devuelve 1 si e
 */
int btree_esta_vacio(BTree arbol);

/**
 * Busca un dato en un árbol. Devuelve 1 si está y 0 en caso contrario.
 */
int btree_buscar(BTree raiz, wchar_t* dato);

/**
 * Devuelve altura de un arbol.
 */
int btree_altura(BTree arbol);


/**
 * Chequea que el árbol esté balanceado.
 */
BTree btree_check_balance(BTree nodo);

/**
 * Aplica rotaciones para un Nodo desbalanceado.
 */
BTree btree_rebalance(BTree nodo);

/**
 * Aplica rotación a la izquierda para un nodo.
 */
BTree left_rotation (BTree nodo);

/**
 * Aplica rotación a la derecha para un nodo.
 */
BTree right_rotation (BTree nodo);

/**
 * Aplica rotación a la derecha y a la izquerda para un nodo.
 */
BTree right_left_rotation (BTree nodo);

/**
 * Aplica rotación a la izquierda y a la derecha para un nodo.
 */
BTree left_right_rotation (BTree nodo);

/**
 * Destruye el árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Imprime un arbol en un archivo.
 */
void btree_imprimir_archivo(BTree arbol, FILE* farchivo, int* bandera);


#endif /* __BTREE_H__ */
