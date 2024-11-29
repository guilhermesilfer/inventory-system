#ifndef FUNCS_H
#define FUNCS_H

#include "structs.h"

// incialização do estoque
Estoque *initialize_stock(Estoque *estoque);

// escreve os dados no arquivo
void write_data(int codigo, char *nome, float preco, int quantidade);

// carrega os dados do arquivo ao iniciar o programa
void load_data(Estoque *estoque);

// inserir produto no estoque
void insert_product(Estoque *estoque);

// remover produto do estoque
void remove_product(Estoque *estoque);

// atualizar produto no estoque
void update_product();

// procura produto pelo codigo
int search_product(Estoque *estoque, int codigo, bool print);

// mostra todos os produtos na tela
void list_products(Estoque *estoque);

#endif
