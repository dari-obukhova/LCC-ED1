#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__
#include "btree.h"
#include <wchar.h>
#include <wctype.h>
#include <wctype.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash.
 */
typedef unsigned long long int (*FuncionHash)(void* clave);


/**
 * Estructura principal que representa la tabla hash.
 */
typedef struct {
  BTree* tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
} TablaHash;

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash fun);

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
TablaHash* tablahash_insertar(TablaHash* tabla, wchar_t* dato);

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
int tablahash_buscar(TablaHash* tabla, wchar_t* dato);

/**
 * Elimina un elemento de la tabla.
 */
void tablahash_eliminar(TablaHash* tabla, void* clave);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla);

/**
  * Crea una tabla hash con las palabras de un archivo y una función dada.
  */
TablaHash* devuelve_tabla(char* archivo, FuncionHash hash);

/*
  * Devuelve 1 si la palabra se encuentra en la tabla hash y 0 en caso contrario.
  */
int esta_palabra_tabla(wchar_t* palabra, TablaHash* tabla);



#endif /* __TABLAHASH_H__ */
