#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX 5

// estrutura do produto
struct produto {
  int codigo, quantidade, preço;
  char nome[];
};

typedef struct produto Produto;

// estrutura da lista sequencial que preferi chamar de estoque
typedef struct estoque {
  Produto produto[MAX];
  int num_elem;
} Estoque;

#endif
