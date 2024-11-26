#include <stdio.h>
#include <stdlib.h>
#include "headers/utils.h"
#include "headers/funcs.h"
#include "headers/structs.h"

int main() {

  print_menu();

  // criação do estoque e inicialização
  Estoque *estoque = NULL;
  estoque = initialize_stock(estoque);

  // checa se houve erro ao inicializar o estoque
  if (estoque == NULL) {
    printf("Erro ao inicializar o estoque\n");
    return 1;
  } else {
    printf("Estoque inicializado\n");
  }

  printf("%d\n", estoque->num_elem);
  insert_product(estoque);
  printf("%d\n", estoque->num_elem);
  printf("%s\n", estoque->produto[0].nome);

  // liberação da memória do estoque
  free_stock(estoque);

  return 0;
}
