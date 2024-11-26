#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include "headers/structs.h"

void print_menu();

bool product_exists(Estoque *estoque, char nome[]);

#endif
