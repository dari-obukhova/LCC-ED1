#include "TP.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>

SList slist_crear() {
  return NULL;
}

SList slist_agregar_inicio(SList lista, void* dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

char* buscar_posicion(SList lista, size_t posicion) {
  int i = 1;
  for(; i <= posicion; i++) lista = lista -> sig;
  return lista->dato;
}

int leer_archivo (char* archivo, SList* lista) {
  int contador = 0;
  int i;
  char c;
  char cadena[MAXCHAR];

  SList lista_aux = slist_crear();

  FILE* fnombres;
  char* nombre;

  fnombres = fopen(archivo, "r");
  if (fnombres == NULL) {
      return -1;
  }
  for(i = 0; (c = fgetc(fnombres)) != EOF; i = 0) {
    cadena[i] = c;
    i++;
    while((c = fgetc(fnombres)) != '\n') {
        cadena[i]=c;
        i++;
    }
    cadena[i-1] = 0;
    cadena[i] = '\0';
    nombre = malloc(sizeof(char)*i);
    strcpy(nombre, cadena);
    lista_aux = slist_agregar_inicio(lista_aux, nombre);
    contador ++;
  }
  fclose(fnombres);
  *lista = lista_aux;
  return contador;
}

char* dato_aleatorio(SList lista, int largoLista) {
  int posAleatoria = rand() % (largoLista);
  char* dato = buscar_posicion(lista, posAleatoria);
  return dato;
}

Persona* nueva_persona(SList listaNombres, int lenNombres, SList listaLugarNacimiento, int lenLugares) {
  Persona* nuevoNodo = malloc(sizeof(Persona));
  char* nombreAux = dato_aleatorio(listaNombres, lenNombres);
  nuevoNodo->nombre = malloc(sizeof(char)*((strlen(nombreAux))+1));
  strcpy(nuevoNodo->nombre, nombreAux);
  nuevoNodo->edad = (rand() % 100)+1;
  char* lugarAux = dato_aleatorio(listaLugarNacimiento, lenLugares);
  nuevoNodo->lugarDeNacimiento = malloc(sizeof(char)*((strlen(lugarAux))+1));
  strcpy(nuevoNodo->lugarDeNacimiento, lugarAux);
  return nuevoNodo;
}

SList crear_lista_personas(SList listaNombres, int lenNombres, SList listaLugarNacimiento, int lenLugares, int n) {
  SList listaPersonas = slist_crear();
  for(int i = 0; i < n; i++){
    Persona* personaNueva = nueva_persona(listaNombres,lenNombres, listaLugarNacimiento, lenLugares);
    listaPersonas = slist_agregar_inicio(listaPersonas, personaNueva);
  }
  return listaPersonas;
}

void devuelve_archivo(SList listaPersonas) {
  FILE *archivoFinal = fopen("personas.txt", "w");
  for (SNodo *nodo = listaPersonas; nodo != NULL; nodo = nodo->sig) {
    Persona* persona;
    persona = nodo->dato;
    fprintf(archivoFinal, "%s, %d, %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
  }
  fclose(archivoFinal);
}

void destruir_lista(SList lista, FuncionVisitante destruir) {
  assert(lista!=0);
  while (lista != NULL) {
      destruir(lista->dato);
      SNodo* sig = lista->sig;
      free(lista);
      lista=sig;
  }
}

void destruir_dato(void* dato) {
  assert(dato!=0);
  free((char *) dato);
}

void destruir_persona(void* dato) {
  assert(dato!=0);
  free(((Persona*) dato)->nombre);
  free(((Persona*) dato)->lugarDeNacimiento);
  free((Persona*) dato);
}
