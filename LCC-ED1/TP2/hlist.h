#ifndef __HLIST_H__
#define __HLIST_H__

#include <stddef.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _SNodo {
  wchar_t* dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo* SList;

typedef struct _HList {  //Header
  SList inicio;
  SList final;
} HList;

//Función que crea un header vacio.
HList* hlist_crear();

//Función que agrega un dato al último nodo de una lista.
void hlist_agregar_final(HList* header, wchar_t* dato);

//Función que destruye la header list.
void hlist_destruir(HList* header);

//Función que se fija si una palabra está en una lista.
int esta_palabra_hlist(HList* header, wchar_t* palabra);

//Función que elimina el primer nodo de una lista.
HList* hlist_eliminar_primer_nodo(HList* header);

#endif /* __HLIST_H__ */
