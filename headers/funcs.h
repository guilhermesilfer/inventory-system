#ifndef FUNCS_H
#define FUNCS_H

#include "structs.h"

// incialização do estoque
Estoque *initialize_stock();

// inserir produto no estoque
void insert_product();

// remover produto do estoque
void remove_product();

// procuror produto no estoque
void search_product();

// atualizar produto no estoque
void update_product();

// listar produtos do estoque
void list_products(Estoque *);

// liberação da memória do estoque
void free_stock(Estoque *estoque);

#endif
