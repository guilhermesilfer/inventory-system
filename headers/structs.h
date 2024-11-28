#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX 100

// estrutura do produto
struct produto
{
  char nome[30], codigo[10];
  float preco;
  int quantidade;
};
typedef struct produto Produto;

// estrutura da lista sequencial que preferi chamar de estoque
typedef struct estoque
{
  Produto produto[MAX];
  int num_elem;
} Estoque;

#endif
