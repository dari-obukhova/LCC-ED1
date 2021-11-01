#ifndef __CORRECTOR_H_
#define __CORRECTOR_H__
#include <wchar.h>
#include <wctype.h>
#include <assert.h>
#include "tablahash.h"
#include "btree.h"
#include "hlist.h"
#define MAXCHAR 30

/**
 * Función que dado un archivo de palabras devuelve la cantidad de palabras que tiene.
 */
int cantidad_palabras(char* nombreArchivo);

/**
 * Devuelve 1 si el caracter está dentro del alfabeto establecido. 0 en
 * caso contrario.
 */
int caracter_valido(wchar_t c);

/**
 * Función que se fija si una palabra está en el diccionario o no.
 */
void corrector(char* entrada, char* salida, TablaHash* tabla);

/**
 * Función que aplica las técnicas para encontrar palabras del Universo.
 * Devuelve un árbol de sugerencias.
 */
BTree aplico_tecnicas(wchar_t* palabra, BTree arbolSugerencias,
                    int* cantSugerencias, HList* listaPosibles, TablaHash* tabla);

/**
 * Función que crea sugerencias para la palabra que no están en el Universo.
 * Aplica las técnicas hasta encontrar al menos 5 sugerencias.
 * Devuelve un árbol de sugerencias.
 */
BTree crear_sugerencias(wchar_t* palabra, BTree arbolSugerencias,
                      HList* listaPosibles, TablaHash* tabla, int* bandera);

/**
 * Función que intercambia los caracteres de una palabra, agregandolos a un
 * árbol de sugerencias si se encontrase la palabra en el Universo y a una lista
 * de posibles palabras.
 * Devuelve un árbol de sugerencias.
 */
BTree intercambiar(wchar_t* palabra, BTree arbolSugerencias, int* cantSugerencias,
                  HList* listaPosibles, TablaHash* tabla);

/**
 * Función que reemplaza los caracteres de una palabra por letras del alfabeto,
 * agregandolos a un árbol sugerencias si se encontrase la palabra en el
 * Universo y la agrega a una lista de posibles palabras.
 * Devuelve un árbol de sugerencias.
 */
BTree reemplazar(wchar_t* palabra, BTree arbolSugerencias, int* cantSugerencias,
                HList* listaPosibles, TablaHash* tabla);

/**
 * Función que inserta caracteres del alfabeto entre cada par de letras de una
 * palabra. Agregándolos a un árbol de sugerencias si se encontrase la palabra
 * en el Universo y la agrega a una lista de posibles palabras.
 * Devuelve un árbol de sugerencias.
 */
BTree insertar(wchar_t* palabra, BTree arbolSugerencias, int* cantSugerencias,
                HList* listaPosibles, TablaHash* tabla);

/**
 * Función que elimina los caracteres de una palabra siempre y cuando el largo de
 * esta sea mayor a 1. Agrega cada palabra nueva a un árbol de sugerencias si se
 * encuentra en el Universo y la agrega a una lista de posibles palabras.
 * Devuelve un árbol de sugerencias.
 */
BTree eliminar(wchar_t* palabra, BTree arbolSugerencias, int* cantSugerencias,
                  HList* listaPosibles, TablaHash* tabla);

/**
 * Función que separa la palabra en dos palabras, si ambas se encuentran en el
 * Universo la agrega a un árbol de sugerencias. Devuelve el árbol de sugerencias.
 */
BTree separar(wchar_t* palabra, BTree arbolSugerencias, int* cantSugerencias,
                  HList* listaPosibles, TablaHash* tabla);

#endif /* __CORRECTOR_H__ */
