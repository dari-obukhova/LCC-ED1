#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

#define MAXCHAR 100

typedef void (*FuncionVisitante) (void *dato);

typedef struct _SNodo {
  void* dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo* SList;

typedef struct _HL {  //Header
  SList inicio;
  SList final;
} HL;

typedef HL* HLptr;

typedef struct {
  char* nombre;
  int edad;
  char* lugarDeNacimiento; // pais o capital
} Persona;

typedef int (*Predicado) ( void* dato) ;

typedef void* (*Copia) (void* dato) ;

typedef void* (*Funcion) (void* dato);

//Función que crea un header vacio.
HLptr h_crear();

//Función que agrega un dato al último nodo de una lista.
HLptr hl_agregar_final(HLptr header, void* dato);

//Función que lee el archivo de las personas y devuelve la lista de palabras.
HLptr leer_archivo (char* archivo, HLptr header);

//Función que copia los datos de Persona a una nueva dirección de memoria.
void* copiar_persona(void* dato);

//Función que abre un archivo de texto, guarda los datos de cada linea en estructura Persona,
//agrega estructura Persona a la lista
void crear_archivo(SList lista, char* archivo);

//la función filter toma una lista de elementos y un predicado, una función que
//retorna true/false, como argumentos y retorna una nueva lista formada por los elementos
//de la lista original que cumplen con el predicado.
HLptr filter (HLptr header, Predicado p, Copia c);

//la función map, toma como argumentos una lista y una función y retorna una
//nueva lista formada por las im´agenes de cada elemento de la lista original luego de aplicarle
//la función.
HLptr map(HLptr header, Funcion f, Copia c);

// Función predicado, si la edad supera los 60 años entonces es verdadero.
//En caso contrario devuelve falso.
int viejos(void* dato);

// Función predicado, si el nombre empieza con D es verdadero, en caso contrario
//devuelve falso.
int empieza_d(void*dato);

//Función que cambia el lugar de nacimiento de las persona por una X.
void* lugar_no_disponible(void * dato);

//Función que cambia la edad a 21.
void* juventud(void* dato);

// Función que libera la memoria utilizada.
void destruir_hlista(HLptr header);

#endif /* __SLIST_H__ */
