#ifndef STRUCTS_H
#define STRUCTS_H

// estrutura do produto
struct produto
{
  char nome[30];
  float preco;
  int quantidade, codigo;
};
typedef struct produto Produto;

// estrutura da lista sequencial que preferi chamar de estoque
typedef struct estoque
{
  Produto *produto;
  int num_elem;
  int capacidade;
} Estoque;

#endif
