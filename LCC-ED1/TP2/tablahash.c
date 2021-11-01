#include "tablahash.h"
#include "corrector.h"


TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash) {
  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->hash = hash;
  tabla->capacidad = capacidad;
  tabla->tabla = malloc(sizeof(BTree) * capacidad); //
  tabla->numElems = 0;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->tabla[idx] = NULL;
  }
  return tabla;
}

TablaHash* tablahash_insertar(TablaHash* tabla, wchar_t* dato) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned long long int idx = tabla->hash(dato);
  idx = idx % tabla->capacidad;



  tabla->tabla[idx] = btree_insertar(tabla->tabla[idx], dato);

  return tabla;
}

int tablahash_buscar(TablaHash* tabla, wchar_t* dato) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned long long int idx = tabla->hash(dato);
  idx = idx % tabla->capacidad;

  BTree arbol = tabla->tabla[idx];

  int encontrado = btree_buscar(arbol, dato); //Buscamos en el árbol de su posición.

  return encontrado;
}

TablaHash* devuelve_tabla(char* archivo, FuncionHash hash) {
  int cantidad = cantidad_palabras(archivo);
  int capacidad = cantidad * 0.1; //El 10% de la cantidad de palabras.

  TablaHash* tablahash = tablahash_crear(capacidad, hash);
  int contador = 0;
  wchar_t buffer[MAX_CHAR];

  int i;
  wchar_t c;

  FILE* farchivo;
  wchar_t* palabra;

  farchivo = fopen(archivo, "r");
  assert(farchivo != NULL && "No se puede abrir el archivo del diccionario");

  for(i = 0; (c = fgetwc(farchivo)) != WEOF; i = 0) {
    buffer[i] = c;
    i++;
    while((c = fgetwc(farchivo)) != L'\n') {
        buffer[i] = towlower(c);
        i++;
    }
    //buffer[i-1] = 0;
    buffer[i] = '\0';
    palabra = malloc(sizeof(wchar_t)*(i+1));
    wcscpy(palabra, buffer);
    //printf("palabra: %ls\n", palabra); //BORRAR

    //unsigned long long int clave = hash(palabra);  //ESTO ES POR LO DE ABAJO SI NO FUNCIONA EL CASTEO. //BORRAR
    //wprintf(L"La clave de palabra %ls es %llu \n", palabra, ((unsigned long long int*)hash(palabra)));  //BORRAR
    tablahash_insertar(tablahash, palabra);

    contador ++;
  }

  fclose(farchivo);
  printf("La tablahash fue creada con éxito.\n");
  return tablahash;
}

int esta_palabra_tabla(wchar_t* palabra, TablaHash* tabla) {
  unsigned long long int idx = tabla->hash(palabra);
  idx = idx % tabla->capacidad;
  return btree_buscar(tabla->tabla[idx], palabra);
}

void tablahash_destruir(TablaHash* tabla) {
  for (int i = 0; i < tabla->capacidad; i++) {
    btree_destruir(tabla->tabla[i]);
    tabla->tabla[i] = NULL;
  }
  free(tabla->tabla);
  free(tabla);
}
