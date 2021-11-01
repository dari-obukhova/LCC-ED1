#include "corrector.h"

int cantidad_palabras(char* nombreArchivo) {
  FILE* fdiccionario;
  fdiccionario = fopen(nombreArchivo, "r");
  wchar_t c;
  int contadorPalabras = 0;
  c = fgetc(fdiccionario);
  while (c != WEOF) {
    if (c == '\n')
      contadorPalabras ++;
    c = fgetc(fdiccionario);
  }
  fclose(fdiccionario);
  return contadorPalabras;
}

int caracter_valido(wchar_t c) {
  if    ((c > 96 && c < 123) //a-z
      || (c == 243) //ö
      || (c == 252) //ü
      || (c == 233) //é
      || (c == 225) //á
      || (c == 237) //í
      || (c == 243) //ó
      || (c == 250) //ú
      || (c == 241)) //ñ
      return 1;
  return 0;
}

void corrector(char* entrada, char* salida, TablaHash* tabla) {

  wchar_t palabra[MAX_CHAR]; //Palabra del texto.
  wchar_t c; //Caracter auxiliar para la lectura del archivo.

  int i; //índice que representa la letra
  int linea = 1; //Número de linea del texto
  int* bandera = malloc(sizeof(int));  //Sirve para saber si es la primer pasada.
  *bandera = 0; //Inicializamos en 0;

  FILE* fentrada; //Archivo del diccionario.
  FILE* fsalida;  //Archivo donde escribimos las sugerencias.

  fentrada = fopen(entrada, "r");
  fsalida = fopen(salida, "w");

  assert(fentrada != NULL && "No se puede abrir el archivo del diccionario");
  assert(fsalida != NULL && "No se puede abrir el archivo de salida");


  for(i = 0; (c = fgetwc(fentrada)) != WEOF; i = 0) {
    if (c == L'\n') //Si llegamos a un salto de linea, aumenta la linea.
      linea++;
    c = towlower(c); //Pasamos a minúsculas el caracter.
    if (caracter_valido(c)){
      palabra[i] = c;
      i++;
    }
    while((c = fgetwc(fentrada)) != L'\n' && c != L' ') {

      c = towlower(c); //Pasamos a minúsculas el caracter.
      if (caracter_valido(c)){
        palabra[i] = c;
        i++;
      }
    }
    palabra[i] = L'\0'; //Agregamos el terminador al final de la palabra.
    if (wcslen(palabra) > 0) {  //Para que ignore las palabras vacías.

      if (!esta_palabra_tabla(palabra, tabla)) {

        BTree arbolSugerencias = btree_crear();
        HList* listaPosibles = hlist_crear();
        arbolSugerencias = crear_sugerencias(palabra, arbolSugerencias,
                                              listaPosibles, tabla, bandera);

        hlist_destruir(listaPosibles); //Liberamos la memoria.

        fwprintf(fsalida, L"Linea:%d, '%ls' no está en el diccionario. Quizás quiso decir:\n", linea, palabra);

        //Imprimimos la lista de sugerencia en el archivo.
        btree_imprimir_archivo(arbolSugerencias, fsalida, bandera);

        fwprintf(fsalida,L"\n");
        btree_destruir(arbolSugerencias); //Liberamos la memoria.

      }
    }
    if (c == L'\n') //Si llegamos a un salto de linea, aumenta la linea.
      linea++;
  }
  fclose(fsalida);
  fclose(fentrada);
  free(bandera);

  printf("El archivo de sugerencias fue creado con éxito.\n");
}

BTree crear_sugerencias(wchar_t* palabra, BTree arbolSugerencias,
                        HList* listaPosibles, TablaHash* tabla, int* bandera) {

  int* cantSugerencias = malloc(sizeof(int)); //Cantidad de sugerencias que hay en el árbol.
  *cantSugerencias = 0;

  arbolSugerencias = aplico_tecnicas(palabra, arbolSugerencias, cantSugerencias,
                                      listaPosibles, tabla);
  (*bandera) = 0;
  for(SList lista = listaPosibles->inicio;  (*cantSugerencias) < 5; lista = lista->sig) {
    wchar_t* palabraAux = listaPosibles->inicio->dato;
    arbolSugerencias = aplico_tecnicas(palabraAux, arbolSugerencias, cantSugerencias,
                                        listaPosibles, tabla);
    listaPosibles = hlist_eliminar_primer_nodo(listaPosibles);

    (*bandera) = 1;

  }
  free(cantSugerencias);
  return arbolSugerencias;
}

BTree aplico_tecnicas(wchar_t* palabra, BTree arbolSugerencias,
                      int* cantSugerencias, HList* listaPosibles, TablaHash* tabla) {

    arbolSugerencias = eliminar(palabra, arbolSugerencias, cantSugerencias,
                                listaPosibles, tabla);
    arbolSugerencias = intercambiar(palabra, arbolSugerencias, cantSugerencias,
                                    listaPosibles, tabla);
    arbolSugerencias = reemplazar(palabra, arbolSugerencias, cantSugerencias,
                                  listaPosibles, tabla);
    arbolSugerencias = insertar(palabra, arbolSugerencias, cantSugerencias,
                                listaPosibles, tabla);
    arbolSugerencias = separar(palabra, arbolSugerencias, cantSugerencias,
                              listaPosibles, tabla);
    return arbolSugerencias;
}

BTree intercambiar(wchar_t* palabra, BTree arbolSugerencias, int* cantSugerencias,
                  HList* listaPosibles, TablaHash* tabla) {

  int largoPalabra = wcslen(palabra);
  int i; //Índice de la palabra donde vamos a intercambiar.
  wchar_t buffer[largoPalabra+1]; //Largo más uno para agregar el terminador.
  wchar_t* nuevaPalabra1; //Palabra que vamos a agregar a la lista de sugerencias.
  wchar_t* nuevaPalabra2; //Palabra que vamos a agregar a la lista de posibles.

  wcscpy(buffer, palabra);
    for (i = 0; i < largoPalabra-1; i++) {
      if (palabra[i] != palabra[i+1]) {

        buffer[i] = palabra[i+1];
        buffer[i+1] = palabra[i];


        if (esta_palabra_tabla(buffer, tabla)
        && !btree_buscar(arbolSugerencias, buffer)) {

          nuevaPalabra1 = malloc(sizeof(wchar_t)*(largoPalabra+1));
          wcscpy(nuevaPalabra1, buffer);

          arbolSugerencias = btree_insertar(arbolSugerencias, nuevaPalabra1);
          (*cantSugerencias) = (*cantSugerencias) + 1;
        }
        nuevaPalabra2 = malloc(sizeof(wchar_t)*(largoPalabra+1));
        wcscpy(nuevaPalabra2, buffer);

        hlist_agregar_final(listaPosibles, nuevaPalabra2);
      }
      wcscpy(buffer, palabra);
  }

  return arbolSugerencias;
}

BTree reemplazar(wchar_t* palabra, BTree arbolSugerencias, int* cantSugerencias,
                  HList* listaPosibles, TablaHash* tabla) {

  int i; //Índice de la palabra donde vamos a reemplazar por otra letra.
  int letra; //Índice del alfabeto.
  int largoPalabra = wcslen(palabra);
  wchar_t buffer[largoPalabra+1]; //Largo más uno para agregar el terminador.
  wchar_t* nuevaPalabra1; //Palabra que vamos a agregar a la lista de sugerencias.
  wchar_t* nuevaPalabra2; //Palabra que vamos a agregar a la lista de posibles.
  wchar_t* alfabeto = L"abcdefghijklmnñopqrstuvwxyzáéíóúöü";

  wcscpy(buffer, palabra); //Copiamos la palabra al buffer.

  for (i = 0 ; i < largoPalabra; i++ ) {
    for(letra = 0; letra < wcslen(alfabeto); letra++){
      buffer[i] = alfabeto[letra];

      if (esta_palabra_tabla(buffer, tabla)
      && !btree_buscar(arbolSugerencias, buffer)) {

        nuevaPalabra1 = malloc(sizeof(wchar_t)*(largoPalabra+1)); //Asignamos memoria.
        wcscpy(nuevaPalabra1, buffer); //Copiamos la palabra.

        arbolSugerencias = btree_insertar(arbolSugerencias, nuevaPalabra1);
        (*cantSugerencias) = (*cantSugerencias) + 1;
      }
      nuevaPalabra2 = malloc(sizeof(wchar_t)*(largoPalabra+1));//Asignamos memoria.
      wcscpy(nuevaPalabra2, buffer); //Copiamos la palabra.

      hlist_agregar_final(listaPosibles, nuevaPalabra2);
    }
    wcscpy(buffer, palabra); //Volvemos a dejar el buffer como la palabra inicial.
  }
  return arbolSugerencias;
}

BTree insertar(wchar_t* palabra, BTree arbolSugerencias, int* cantSugerencias,
                  HList* listaPosibles, TablaHash* tabla) {

  int largoPalabra = wcslen(palabra);
  int i; //Índice donde vamos a insertar la letra.
  int j; //Índice del buffer.
  int k; //Índice de la palabra.
  int letra; //Índice del alfabeto.
  int largoAlfabeto;
  wchar_t buffer[largoPalabra+2];
  wchar_t* nuevaPalabra1; //Palabra que usaremos para la lista de sugerencias.
  wchar_t* nuevaPalabra2; //Palabra que usaremos para la lista de posibles.
  wchar_t* alfabeto = L"abcdefghijklmnñopqrstuvwxyzáéíóúöü";

  largoAlfabeto = wcslen(alfabeto);

  for (i = 1; i < largoPalabra; i++) {
    for (letra = 0; letra < largoAlfabeto; letra++) {
      for (j = 0, k = 0; k < largoPalabra; j++, k++) {
        if (j == i) {
          buffer[j] = alfabeto[letra];
          j++;
        }
        buffer[j] = palabra[k];
      }
      buffer[j] = L'\0'; //Agregamos el terminador.

      if (esta_palabra_tabla(buffer, tabla)
      && !btree_buscar(arbolSugerencias, buffer)) {

        nuevaPalabra1 = malloc(sizeof(wchar_t)*(largoPalabra+2)); //Asignamos memoria.
        wcscpy(nuevaPalabra1, buffer); //Copiamos palabra.

        arbolSugerencias = btree_insertar(arbolSugerencias, nuevaPalabra1);
        (*cantSugerencias) = (*cantSugerencias) + 1;
      }

      nuevaPalabra2 = malloc(sizeof(wchar_t)*(largoPalabra+2)); //Asignamos memoria.
      wcscpy(nuevaPalabra2, buffer); //Copiamos la palabra.

      hlist_agregar_final(listaPosibles, nuevaPalabra2);
    }
  }

  return arbolSugerencias;
}

BTree eliminar(wchar_t* palabra, BTree arbolSugerencias, int* cantSugerencias,
                  HList* listaPosibles, TablaHash* tabla) {

  int largoPalabra = wcslen(palabra);
  int i; //Índice a eliminar.
  int k; //Índice del buffer.
  int j; //Índice de la palabra.
  wchar_t buffer[largoPalabra+1]; //Largo más 1 para agregar el terminador.
  wchar_t* nuevaPalabra1; //Palabra que usaremos para la lista de sugerencias.
  wchar_t* nuevaPalabra2; //Palabra que usaremos para la lista de posibles.

  if (largoPalabra > 1){
    for (i=0; i < largoPalabra; i++) {
      for (k = 0, j = 0; j < largoPalabra; k++, j++) {
        if (k == i) {
          if (i == largoPalabra) (i++);
          j++;
        }
        buffer[k] = palabra[j];
      }
      buffer[k] = L'\0'; //Agregamos el terminador.

      if (esta_palabra_tabla(buffer, tabla)
      && !btree_buscar(arbolSugerencias, buffer)) {
        nuevaPalabra1 = malloc(sizeof(wchar_t)*largoPalabra);
        wcscpy(nuevaPalabra1, buffer);
        arbolSugerencias = btree_insertar(arbolSugerencias, nuevaPalabra1);

        (*cantSugerencias) = (*cantSugerencias) + 1;
      }
      nuevaPalabra2 = malloc(sizeof(wchar_t)*largoPalabra); //Asignamos memoria.
      wcscpy(nuevaPalabra2, buffer); //Copiamos la palabra.
      hlist_agregar_final(listaPosibles, nuevaPalabra2);
    }
  }

  return arbolSugerencias;
}

BTree separar(wchar_t* palabra, BTree arbolSugerencias, int* cantSugerencias,
                  HList* listaPosibles, TablaHash* tabla) {

  int largoPalabra = wcslen(palabra);
  int i; //Índice de la palabra donde pondremos el espacio.
  int j; //índice del buffer.
  int k; //Índice de la palabra.
  wchar_t buffer[largoPalabra+1]; //Largo más uno para agregar el terminador.
  wchar_t bufferAux[largoPalabra+1]; //Buffer auxiliar para la segunda palabra.
  wchar_t* nuevaPalabra; //Palabra que guardaremos en lista de Sugerencias.

  for (i = 1; i < largoPalabra; i++) {
    for (j = 0, k = 0; k < largoPalabra; j++, k++) {
      if (j == i) {
        buffer[j] = L' ';
        j++;
      }
      buffer[j] = palabra[k];
    }
    buffer[j] = L'\0'; //Agregamos el terminador al final.

    wmemmove(bufferAux, buffer, i);
    bufferAux[i] = '\0';

    if (esta_palabra_tabla(bufferAux, tabla)
      && esta_palabra_tabla(buffer+i+1, tabla)
      && !btree_buscar(arbolSugerencias, buffer)) {

        nuevaPalabra = malloc(sizeof(wchar_t)*(largoPalabra+2)); //Asignamos memoria.
        wcscpy(nuevaPalabra, buffer); //Copiamos la palabra.

        arbolSugerencias = btree_insertar(arbolSugerencias, nuevaPalabra);
        (*cantSugerencias) = (*cantSugerencias) + 1;
    }
  }
  return arbolSugerencias;
}
