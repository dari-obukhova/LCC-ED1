#include "hlist.h"


HList* hlist_crear() {
  HList* header;
  header = malloc(sizeof(HList));
  header->inicio = NULL;
  header->final = NULL;
  return header;
}

void hlist_agregar_final(HList* header, wchar_t* dato) {

  SList nuevoNodo = malloc(sizeof(SNodo));

  if (header->inicio == NULL) { //Si la lista está vacía.
    header->inicio = nuevoNodo;
  } else
    (header->final)->sig = nuevoNodo;

  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  header->final = nuevoNodo;
}

void hlist_destruir(HList* header) {
  SList lista = header->inicio;
  SList listaSig;
  while (lista != NULL) {
    free(lista->dato);
    listaSig = lista->sig;
    free(lista);
    lista = listaSig;
  }
  free(header);
}

void hlist_imprimir(SList lista) {
  while(lista != NULL) {
    printf("%ls\n", lista->dato);
    lista = lista->sig;
  }
}
HList* hlist_eliminar_primer_nodo(HList* header) {
  SList listaAux = header->inicio;
  header->inicio = header->inicio->sig;
  free(listaAux->dato);
  free(listaAux);
  return header;
}
int esta_palabra_hlist(HList* header, wchar_t* palabra) {
  int bandera = 0;
  SList lista = header->inicio;
  while(lista != NULL && !bandera) {
    if (wcscmp(lista->dato, palabra) == 0) bandera = 1;
    lista = lista->sig;
  }
  return bandera;
}
