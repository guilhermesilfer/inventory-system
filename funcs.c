#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/structs.h"

// incialização do estoque
void *initialize_stock() {
  Estoque *estoque;
  return estoque = malloc(sizeof(Estoque));
};

void insert_product(Estoque *estoque) {
  char nome[30];

  printf("Digite o nome do produto:\n");
  fgets(nome, 30, stdin);

  if (product_exists(estoque, nome) == true) {
    printf("O produto já existe.\n")
  };
  strcpy(estoque->produto[estoque->num_elem].nome, nome);
  estoque->num_elem++;
};

void remove_product() {};

void search_product() {};

void update_product() {};

// liberação da memória do estoque
void free_stock(Estoque *estoque) {
  free(estoque);
};
