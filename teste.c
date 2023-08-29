#include "aloca.h"
#include "libs/j_linkedList.h"

int main(void) {
  // teoricamente se um utf8 consome mais de um byte
  // o único problema vai ser no printf que printa
  // byte a byte.

  list lista = list_new(); 
  list_addFirst(&lista, item_new(16, "NUM16"));
  list_addFirst(&lista, item_new(32, "NUM32"));
  list_addLast(&lista,  item_new(64, "NUM64"));
  list_addFirst(&lista, item_new(8, "NUM08"));

  // O método aplicável para remoção é:
  // ou item = list_findbyUTF8(char* in);
  // ou item = list_findbyNumber(int in);
  // ou item = list_Find(char *in1, int in2);
  //
  // list_itemRemove(item);

  // Porém não existe método de find por enquanto,
  // então não tem como remover por enquanto kkk,
  // não dá para fazer item1 = item_new();
  // e depois itemRemove(item1) pois a lista
  // copia o conteúdo e como temos um ponteiro
  // ele vai mudar na cópia da string (para alocar).

  char *aux = list_toString(lista);
  printf("%s", aux);
  libera(aux);
  list_Free(&lista);
}
