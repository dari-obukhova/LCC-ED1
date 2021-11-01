#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "parte2.h"


HLptr h_crear() {
  HLptr header;
  header = malloc(sizeof(HL));
  header->inicio = NULL;
  header->final = NULL;
  return header;
}

HLptr hl_agregar_final(HLptr header, void* dato) {
  SList nuevoNodo = malloc(sizeof(SNodo));
  assert(header != NULL);
  if (header->inicio == NULL) { //Si la lista está vacía.
    header->inicio = nuevoNodo;
  } else {
    (header->final)->sig = nuevoNodo;
  }
  nuevoNodo->dato = (Persona*)dato;
  nuevoNodo->sig = NULL;
  header->final = nuevoNodo;
  return header;
}

HLptr leer_archivo(char* archivo, HLptr header) {
  int i;
  char c;
  char cadenaAux[MAXCHAR];
  FILE* fpersonas;
  fpersonas = fopen(archivo, "r");

  assert(fpersonas != NULL && "No se puede abrir el archivo");

  for(i = 0; (c = fgetc(fpersonas)) != EOF; i = 0) {
    cadenaAux[i] = c;
    Persona* nuevoNodo = malloc(sizeof(Persona));
    i++;

    //Dependiendo de la cantidad de comas, asignamos cada palabra de la linea a
    //nombre, edad o lugar de nacimiento.

    //Palabra del nombre.
    for (; (c = fgetc(fpersonas)) != ',' ; i++) {
      cadenaAux[i] = c;
    }
    cadenaAux[i] = '\0'; //Agregamos terminador.
    char* nombre = malloc(sizeof(char)*(i+1));
    strcpy(nombre, cadenaAux);
    nuevoNodo->nombre = nombre;
    fgetc(fpersonas); //Salteamos el espacio entre la coma y la palabra.

    //La edad.
    for (i=0;(c = fgetc(fpersonas)) != ','; i++) {
        cadenaAux[i] = c;
    }
    cadenaAux[i] = '\0'; //Agregamos terminador.
    nuevoNodo->edad = atoi(cadenaAux);   //Convertimos la edad en int.
    fgetc(fpersonas); //Salteamos el espacio entre la coma y la palabra.

    //Palabra del lugar de nacimiento.
    for (i=0; (c = fgetc(fpersonas)) != '\n'; i++) {
      cadenaAux[i] = c;
    }
    cadenaAux[i] = '\0';  //Agregamos terminador.
    char* lugarDeNacimiento = malloc(sizeof(char)*(i+1));
    strcpy(lugarDeNacimiento, cadenaAux);
    nuevoNodo->lugarDeNacimiento = lugarDeNacimiento;
    header = hl_agregar_final(header, (Persona*)nuevoNodo);
  }
  fclose(fpersonas);
  return header;
}

void* copiar_persona(void* dato) {
  Persona* p = malloc(sizeof(Persona));

  p->nombre = malloc(sizeof(char)*(strlen(((Persona*) dato)->nombre)+1));
  strcpy(p->nombre, ((Persona*)dato) -> nombre);

  p->edad = ((Persona*)dato) -> edad;

  p->lugarDeNacimiento = malloc((sizeof(char))*(strlen(((Persona*)dato)->lugarDeNacimiento)+1));
  strcpy(p->lugarDeNacimiento, ((Persona*)dato)->lugarDeNacimiento);

  return (void*)p;
}

void crear_archivo(SList lista, char* archivo) {
  FILE *farchivo;
  farchivo = fopen(archivo, "w");

  if(lista == NULL){
    printf("La lista está vacía.");
  }
  while (lista != NULL) {
    Persona* persona;
    persona = lista->dato; //tenemos que castear
    fprintf(farchivo, "%s, %d, %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
    lista = lista->sig;
  }
  fclose(farchivo);
}

HLptr filter (HLptr header, Predicado p, Copia c) {
  HLptr headerCopia = h_crear();
  SList lista = header->inicio;

  while (lista != NULL){
    if (p(lista->dato)) { //Si el predicado es verdadero la agrega a la lista.
      headerCopia = hl_agregar_final(headerCopia, c(lista->dato));
    }
    lista = lista->sig;
  }
  return headerCopia;
}

HLptr map(HLptr header, Funcion f, Copia c) {
  HLptr headerCopia = h_crear();
  SList lista = header->inicio;
  while(lista != NULL){
    hl_agregar_final(headerCopia, f(c((lista->dato))));
    lista = lista->sig;
  }
  return headerCopia;
}

int viejos(void* dato) {
  if ((((Persona*)dato)->edad) > 60){
     return 1;
  }
  return 0;
}

int empieza_d(void*dato) {
  char* nombre = ((Persona*)dato)->nombre;
  char primeraLetra = nombre[0];
  if(primeraLetra == 'D'){
    return 1;
  }
  return 0;
}

void* lugar_no_disponible(void * dato) {
  strcpy(((Persona*)dato)->lugarDeNacimiento, "X");
  return dato;
}

void* juventud(void* dato) {
  Persona* persona = dato;
  persona->edad = 21;
  return dato;
}

void destruir_hlista(HLptr header) {
  SList lista = header->inicio;
  while (lista != NULL) {
    free(((Persona*) (lista->dato))->nombre);
    free(((Persona*) (lista->dato))->lugarDeNacimiento);
    free(((Persona*) (lista->dato)));
    SList listaSig = lista->sig;
    free(lista);
    lista = listaSig;
  }
  free(header);
}
