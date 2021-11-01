#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "parte2.h"

int main () {
  HLptr listaPersonas = h_crear();
  char* filePersonas = "personas.txt";

  listaPersonas = leer_archivo(filePersonas, listaPersonas);

  HLptr listaMapeada1 = h_crear();
  listaMapeada1 = map(listaPersonas, lugar_no_disponible, copiar_persona);
  crear_archivo(listaMapeada1->inicio, "maplugarNoDisponible.txt");

  HLptr listaMapeada2 = h_crear();
  listaMapeada2 = map(listaPersonas, juventud, copiar_persona);
  crear_archivo(listaMapeada2->inicio, "mapJuventud.txt");

  HLptr listaFiltrada1 = h_crear();
  listaFiltrada1 = filter(listaPersonas, viejos, copiar_persona);
  crear_archivo(listaFiltrada1->inicio, "filterViejos.txt");


  HLptr listaFiltrada2 = h_crear();
  listaFiltrada2 = filter(listaPersonas, empieza_d, copiar_persona);
  crear_archivo(listaFiltrada2->inicio, "filterDs.txt");


  destruir_hlista(listaFiltrada2);
  destruir_hlista(listaFiltrada1);
  destruir_hlista(listaMapeada2);
  destruir_hlista(listaMapeada1);

  destruir_hlista(listaPersonas);

  return 0;
}
