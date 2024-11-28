#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "headers/structs.h"
#include "headers/utils.h"

// incialização do estoque
void *initialize_stock()
{
  Estoque *estoque;
  return estoque = malloc(sizeof(Estoque));
};

void write_data(char *codigo, char *nome, float preco, int quantidade)
{
  FILE *arquivo;
  arquivo = fopen("produtos.csv", "a");

  fprintf(arquivo, "%s,%s,%f,%d\n", codigo, nome, preco, quantidade);

  fclose(arquivo);
}

void insert_product(Estoque *estoque)
{
  char *codigo_input;
  char *nome_input;
  float preco_input;
  int quant_input;

  // as seguintes funções vão ler e verificar as entradas do usuario
  bool error = false;
  bool *ptr_error = &error;

  codigo_input = read_code(estoque, ptr_error);
  if (error == true) return;
  nome_input = read_name(estoque, ptr_error);
  if (error == true) return;
  preco_input = read_price(ptr_error);
  if (error == true) return;
  quant_input = read_amount(ptr_error);
  if (error == true) return;

  // atribuindo os dados do produto a lista estoque->produto
  strcpy(estoque->produto[estoque->num_elem].codigo, codigo_input);
  strcpy(estoque->produto[estoque->num_elem].nome, nome_input);
  estoque->produto[estoque->num_elem].preco = preco_input;
  estoque->produto[estoque->num_elem].quantidade = quant_input;

  // mostra os dados do produto adicionado na tela e aumenta num_elem
  printf("Code: %s | ", estoque->produto[estoque->num_elem].codigo);
  printf("Name: %s | ", estoque->produto[estoque->num_elem].nome);
  printf("Price: %.2f | ", estoque->produto[estoque->num_elem].preco);
  printf("Amount: %d\n\n", estoque->produto[estoque->num_elem].quantidade);
  estoque->num_elem++;

  // armazena os dados do produto no arquivo produtos.csv
  write_data(codigo_input, nome_input, preco_input, quant_input);

  printf("new num_elem: %d\n\n", estoque->num_elem);
}

// cadastra produto

//void remove_product(Estoque *estoque) {
  //if(estoque->num_elem == 0){
    //printf("Ainda não existem produtos no estoque, tente novamente.\n");
    //return;
  //}
  
  //char codigo[10];
  //printf("Digite o código do produto a ser removido: ");
  //fgets(codigo, sizeof(codigo), stdin)
  //remove_newline(codigo, strlen(código))
  //}
  //int posi = -1;
  //for(int i = 0; i < estoque->num_elem; i++){
  //  if(strcmp(estoque->produto[i].codigo, codigo) == 0){    
  //    posição = i;
  //    break}
  //}
  //
  //  if(posicao == -1){
  //     printf("Produto com o código '%s' não encontrado, codigo)} 
  //     return;
  //
  //for(int i = posicao; i < estoque->num_elem - 1; i++){
  //  estoque->produto[i] = estoque->produto[i + 1];
  //}
  //estoque->num_elem--;   
  //printf("Produto com código '%s' removido com sucesso.\n", codigo);

void search_product(Estoque *estoque) {
  if (estoque-> num_elem == 0){
    printf("O estoque está vazio :D\n");
    return;
  }

  char codigo[10];
  printf("Código do produto: ");
  fgets(codigo, 10, stdin);
  remove_newline(codigo, 10);

  int i = 0;
  while (i < estoque->num_elem)
  {
    if (strcmp(estoque->produto[i].codigo, codigo) == false)
    {
      printf("achei o produto\n");
      estoque->produto[i].codigo;
      estoque->produto[i].nome;
      
      printf("Codigo: %s | ", estoque->produto[i].codigo);
      printf("%s | ", estoque->produto[i].nome);
      printf("%f | ", estoque->produto[i].quantidade);
      printf("%d\n", estoque->produto[i].preco);
      printf("\n");
    }
    else if (i + 1 == estoque->num_elem)
    {
      printf("Esse produto não existe.\n");
    }
    i++;
  } 
};

void update_product() {};
