#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

#define MAXCHAR 100

typedef void (*FuncionVisitante) (void *dato);

typedef struct _SNodo {
  void* dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

typedef struct {
  char* nombre;
  int edad;
  char* lugarDeNacimiento; // pais o capital
} Persona;

//Función que devuelve una lista vacia.
SList slist_crear();

//Función que agrega un dato al inicio de la lista.
SList slist_agregar_inicio(SList lista, void* dato);

//Función que dado una lista y una posición, devuelve el dato en esa posición.
char* buscar_posicion(SList lista, size_t posicion);

//Función que lee el archivo y agrega los datos a la lista.
int leer_archivo (char* archivo, SList* lista);

//Función que devuelve un dato aleatorio de la lista.
char* dato_aleatorio(SList lista, int largoLista);

//Función que agrega una nueva persona a la lista.
Persona* nueva_persona(SList listaNombres, int lenNombres, SList listaLugarNacimiento, int lenLugares);

//Función que crea la lista con los datos tipo estructura Persona.
SList crear_lista_personas(SList listaNombres, int lenNombres, SList listaLugarNacimiento, int lenLugares, int n);

//Función que crea un archivo de texto con los datos de la listaPersonas.
void devuelve_archivo(SList listaPersonas);

// Función que libera la memoria utilizada en la lista.
//Para espicificar que tipo de datos hay que destruir, pasamos la función destruir.
void destruir_lista(SList lista, FuncionVisitante destruir);

//Función que libera memoria de un puntero dato.
void destruir_dato(void* dato);

//Función que libera memoria de una estructura Persona.
void destruir_persona(void* dato);


#endif /* __SLIST_H__ */
