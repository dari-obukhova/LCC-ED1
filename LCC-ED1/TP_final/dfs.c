#include "dfs.h"


void dfs(int i, int cantidad_ciudades, int* matrix[cantidad_ciudades], int visited[],
  int itr, int camino_actual[], int camino_optimo[], int costo_actual, int* costo_optimo) {

  int j,l;
  camino_actual[itr] = i;
  itr++; //iteración

  if (itr == cantidad_ciudades) {
      if (matrix[i][0] != -1) { //cheq si podemos volver a la ciudad del inicio
        costo_actual = costo_actual + matrix[i][0];

        if (*costo_optimo == -1 || (costo_actual < *costo_optimo)) {
          *costo_optimo = costo_actual;

          for (l=0; l<cantidad_ciudades; l++) {
            camino_optimo[l] = camino_actual[l];
          }
        }
      }
  }
    else {
      for (j=0; j<cantidad_ciudades; j++) {

        if (!visited[j] && matrix[i][j]!=-1) {
          costo_actual = costo_actual + matrix[i][j];

          if (*costo_optimo == -1 || (costo_actual < *costo_optimo)) {
            visited[j]=1;

            dfs(j, cantidad_ciudades, matrix, visited, itr, camino_actual, camino_optimo, costo_actual, costo_optimo);

            visited[j]=0;
          }
        costo_actual = costo_actual - matrix[i][j];
        }
      }
    }
  }

int** matriz_crear(int n) {
  int **matriz, i;
  matriz = (int **) malloc(n*sizeof(int *));
  for (i=0; i<n; i++) matriz[i] = (int *)malloc(n*sizeof(int));
  return matriz;
}

int** leer_archivo(char* entrada, int* cantidad_ciudades, char** arreglo_ciudades, BTree btree_ciudades) {

  int i, j, id1, id2, costo;
  int id = 0;

  char* ciudad, ciudad1[MAX_CHAR], ciudad2[MAX_CHAR];
  char linea[MAX_TO_READ];

  int** matriz;

  FILE* fentrada;

  fentrada = fopen(entrada, "r");
  assert(fentrada != NULL && "No se puede abrir el archivo de la entrada");

  fscanf(fentrada, "%*[^\n]\n");
  fgets(linea, MAX_TO_READ, fentrada);
  ciudad = strtok(linea, ", \n");

  while (ciudad != NULL && strcmp(ciudad, "\n")!=0) {
    char* buffer = malloc(sizeof(char) * strlen(ciudad) + 1);
    strcpy(buffer, ciudad);
    btree_ciudades = btree_insertar(btree_ciudades, buffer, id);
    arreglo_ciudades[id] = buffer;
    id ++;
    ciudad = strtok(NULL, ", \n");
  }

  *cantidad_ciudades = id;

  matriz = matriz_crear(id);

  for (i=0; i<id; i++) {
    for (j=0; j<id; j++) {
      matriz[i][j] = -1;
    }
  }

  fscanf(fentrada, "%*[^\n]\n");

  while (!feof(fentrada)) {
    fscanf(fentrada, "%[^, ], %[^, ], %d\n", ciudad1, ciudad2, &costo);
    id1 = btree_buscar_id(btree_ciudades, ciudad1);
    id2 = btree_buscar_id(btree_ciudades, ciudad2);
    matriz[id1][id2] = costo;
    matriz[id2][id1] = costo;
  }

  fclose(fentrada);

  return matriz;
}

  void devolver_archivo(char* salida, int camino_optimo[], int cantidad_ciudades, char** arreglo_ciudades, int* matriz[cantidad_ciudades], int costo_optimo) {

    int i, ciudad1, ciudad2;

    FILE* fsalida;

    fsalida = fopen(salida, "w");
    assert(fsalida != NULL && "No se puede abrir el archivo de salida");

    for (i=0; i<(cantidad_ciudades - 1); i++) {
      ciudad1 = camino_optimo[i];
      ciudad2 = camino_optimo[i+1];

      fprintf(fsalida, "%s,%s,%d \n", arreglo_ciudades[ciudad1], arreglo_ciudades[ciudad2], matriz[ciudad1][ciudad2]);
    }

    fprintf(fsalida, "%s,%s,%d\n", arreglo_ciudades[ciudad2], arreglo_ciudades[0], matriz[ciudad2][0]); //siempre empezamos el camino con la primer ciudad
    fprintf(fsalida, "Costo: %d", costo_optimo);

    fclose(fsalida);
  }

  void resolver_tsp(char* entrada, char* salida) {
    int cantidad_ciudades = 0;
    char *arreglo_ciudades[MAX_CIUDADES];

    BTree btree_ciudades = btree_crear();

    int** matriz = leer_archivo(entrada, &cantidad_ciudades, arreglo_ciudades, btree_ciudades);

    int visited[cantidad_ciudades];

    int camino_actual[cantidad_ciudades];
    int camino_optimo[cantidad_ciudades];

    int costo_actual = 0;
    int costo_optimo = -1;

    for(int i=0; i<cantidad_ciudades; i++) {
      visited[i]=0;
    }

    visited[0]=1;

    dfs(0, cantidad_ciudades, matriz, visited, 0, camino_actual, camino_optimo, costo_actual, &costo_optimo);

    devolver_archivo(salida, camino_optimo, cantidad_ciudades, arreglo_ciudades, matriz, costo_optimo);

    btree_destruir(btree_ciudades);

    for (int i=0; i<cantidad_ciudades; i++) {
    free(arreglo_ciudades[i]);
    }

    for(int i = 0; i < cantidad_ciudades; i++) free(matriz[i]);

    free(matriz);
  }
