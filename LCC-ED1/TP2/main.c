#include "tablahash.h"
#include "corrector.h"
#include <string.h>
#include <locale.h>

unsigned long long int hash(void* clave) {
  int c = 21;
  int hash = 0;
  wchar_t* palabra = clave;
  for (int i = 0; i <  wcslen(palabra); i++) {
    hash = (c*hash) + palabra[i];
  }
  return hash;
}

int main(int argc,  char **argv) {
  setlocale(LC_CTYPE,"");

  char *archivoEntrada = malloc(sizeof(char) * MAX_CHAR);
  char *archivoSalida = malloc(sizeof(char) * MAX_CHAR);

  strcpy(archivoEntrada, argv[1]);
  strcpy(archivoSalida, argv[2]);

  TablaHash* tablahash = devuelve_tabla("listado-general.txt", hash);

  //printf("%d\n",tablahash_buscar(tablahash, L"a")); //BORRAR ESTO ES PARA VER SI ENCUENTRA LA LETRA a
  corrector(archivoEntrada, archivoSalida, tablahash);

  tablahash_destruir(tablahash);
  return 0;

}
