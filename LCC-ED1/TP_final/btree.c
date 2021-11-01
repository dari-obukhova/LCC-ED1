#include "btree.h"

BTree btree_crear() {
  return NULL;
}

BTree btree_insertar(BTree raiz, char* dato, int id) {
    BTree nuevoNodo;
    nuevoNodo = malloc(sizeof(BTNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->id = id;
    nuevoNodo->left = NULL;
    nuevoNodo->right = NULL;
    nuevoNodo->parent = NULL;

    if (raiz == NULL) {
        raiz = nuevoNodo;
    }
    else {
        BTree anterior, reco;
        reco = raiz;

        while (reco != NULL) {
            anterior = reco;
            if (strcmp(dato, reco->dato) < 0) {  // dato < reco->dato
                reco = reco->left;
              }
            else if (strcmp(dato, anterior->dato) == 0) {
              return raiz;
            }
            else {
              reco = reco->right;
            }
        }
          if (strcmp(dato, anterior->dato) < 0) { //dato < anterior->dato
          anterior->left = nuevoNodo;
          nuevoNodo->parent = anterior;
          raiz = btree_check_balance(nuevoNodo);
          return raiz;
          }
          else {
            anterior->right = nuevoNodo;
            nuevoNodo->parent = anterior;
            raiz = btree_check_balance(nuevoNodo);
            return raiz;
          }
      }
  return raiz;
}

int btree_esta_vacio(BTree arbol) {
  if (arbol == NULL)
    return 1;
  else return 0;
}

int btree_buscar_id(BTree raiz, char* dato) {
   BTree actual = raiz;
   int encontrado = 0;
   int id;
   while(encontrado == 0 && !btree_esta_vacio(actual)) {
      if(strcmp(dato, actual->dato) == 0) {  //dato == actual->dato
        encontrado = 1;
        id = actual->id;
      }
      else if (strcmp(dato, actual->dato) < 0) { //dato < actual->dato
        actual = actual->left;
      }
      else if (strcmp(dato, actual->dato) > 0) { //dato > actual->dato
        actual = actual->right;
      }
   }
   return id;
}


int btree_altura(BTree arbol) {
  if (arbol == NULL) return 0;
  int altura1 = btree_altura(arbol->left)+1;
  int altura2 = btree_altura(arbol->right)+1;
  return altura1 < altura2 ? altura2 : altura1;
}

BTree btree_check_balance(BTree nodo) {
  if ((btree_altura(nodo->left) - btree_altura(nodo->right)) > 1 ||
      (btree_altura(nodo->left) - btree_altura(nodo->right) < -1)) {
        nodo = btree_rebalance(nodo);
  }
  if (nodo->parent == NULL) {
        return nodo;
  }
  return btree_check_balance(nodo->parent);
}

BTree btree_rebalance(BTree nodo) {
  if ((btree_altura(nodo->left) - btree_altura(nodo->right)) > 1) {
    if ((btree_altura((nodo->left)->left) > (btree_altura((nodo->left)->right)))) {
      nodo = right_rotation(nodo);
      return nodo;
    }
    else {
      nodo = left_right_rotation(nodo);
      return nodo;
    }
  }
  else {
    if ((btree_altura((nodo->right)->left) > (btree_altura((nodo->right)->right)))) {
    nodo = right_left_rotation(nodo);
    return nodo;
    }
  else {
    nodo = left_rotation(nodo);
    return nodo;
    }
  }
}

BTree left_rotation (BTree nodo) {
  BTree nodoTemp = nodo->right;
  BTree padreTemp = nodo->parent;
  if (padreTemp != NULL) {
    if ((strcmp(padreTemp->dato, nodoTemp->dato) < 0)) {
      padreTemp->right = nodoTemp;
    } else {
      padreTemp->left = nodoTemp;
    }
  }
  nodo->right = nodoTemp->left;
  nodo->parent = nodoTemp;
  nodoTemp->parent = padreTemp;
  nodoTemp->left = nodo;
  return nodoTemp;
}

BTree right_rotation (BTree nodo) {
  BTree nodoTemp = nodo->left;
  BTree padreTemp = nodo->parent;
  if (padreTemp != NULL) {
    if ((strcmp(padreTemp->dato, nodoTemp->dato) < 0)) {
      padreTemp->right = nodoTemp;
    } else {
      padreTemp->left = nodoTemp;
    }
  }
  nodo->left = nodoTemp->right;
  nodo->parent = nodoTemp;
  nodoTemp->parent = padreTemp;
  nodoTemp->right = nodo;
  return nodoTemp;
}

BTree right_left_rotation (BTree nodo) {
  nodo->right = right_rotation(nodo->right);
  return left_rotation (nodo);
}

BTree left_right_rotation (BTree nodo) {
  nodo->left = left_rotation(nodo->left);
  return right_rotation(nodo);
}

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    free(nodo->dato);
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

void btree_imprimir(BTree arbol) {
  if (arbol != NULL) {
    printf (" %s\n", arbol->dato);
    btree_imprimir(arbol->left);
    btree_imprimir(arbol->right);
  }
}
