#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include "structs.h"

void print_menu();

bool product_exists(Estoque *estoque, int codigo);

void remove_newline(char *string, int tamanho);

bool goto_menu(bool voltar);

char *read_name(Estoque *estoque, bool *ptr_error);

int read_code(Estoque *estoque, bool *ptr_error, bool check_existence);

float read_price(bool *ptr_error);

int read_amount(bool *ptr_error);

void print_product(Estoque *estoque, int codigo);

#endif
