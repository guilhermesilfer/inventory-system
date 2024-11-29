#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "headers/structs.h"
#include "headers/funcs.h"

void print_menu()
{
  printf("#####################################\n");
  printf("#####     PAINEL DO ESTOQUE     #####\n");
  printf("#####################################\n\n");
  printf("(Digite o número da opção que deseja)\n\n");
  printf("[0] Sair (implemented)\n");
  printf("[1] Novo produto (implemented)\n");
  printf("[2] Remover produto (implemented)\n");
  printf("[3] Mostrar produtos (implemented)\n");
  printf("[4] Procurar produto (implemented)\n");
  printf("[5] Atualizar produto (implemented\n");
  printf("\n");
  printf("=====================================\n\n");
}

// percorre todos os produtos e checa se já existe algum com o mesmo codigo
bool product_exists(Estoque *estoque, int codigo)
{
  int n = estoque->num_elem;
  for (int i = 0; i < n; i++)
  {
    if (estoque->produto[i].codigo == codigo)
    {
      return true;
    }
  }
  return false;
}

// remove o caractere '\n' de uma string
void remove_newline(char *string, int tamanho)
{
  int i = 0;
  while (i < tamanho) {
    if (string[i] == '\n')
    {
      string[i] = '\0';
    }
    else if (string[i] == '\0') return;
    i++;
  }
}

// checa se uma string é um inteiro valido
//bool is_int(char *string) {
//  char *ptr_end;
//
//  if (string == NULL || *string == '\0') {
//    return false;
//  }
//
//  long value = strtol(string, &ptr_end, 10);
//
//  if (*ptr_end != '\0') {
//    return false;
//  }
//
//  return true;
//}

// menu que aparece caso o produto já exista
bool goto_menu()
{
  while (true)
  {
    printf("1 - Voltar ao menu\n");
    printf("2 - Tentar novamente\n");

    int input = 0;
    printf(": ");
    scanf("%d", &input);
    while(getchar() != '\n');

    if (input == 1)
    {
      return true;
    }
    else if (input == 2)
    {
      return false;
    }
    else
    {
      printf("Insira uma opção válida\n\n");
      continue;
    }
  }
}

int read_code(Estoque *estoque, bool *ptr_error, bool check_existence)
{
  int codigo_input;

  bool voltar = false;
  while (voltar == false) // while para repetir caso o produto digitado ja exista
  {
    printf("Necessário ser um inteiro\n");
    printf("Código: ");
    // coleta o codigo do produto
    while (scanf("%d", &codigo_input) != 1)
    {
      while (getchar() != '\n');
      printf("Código inválido.\n");
      printf("Código: ");
      continue;
    }
    while (getchar() != '\n');
    printf("\n");

    if (check_existence == true)
    {
      // checa se já existe algum produto com esse nome
      bool existe;
      existe = product_exists(estoque, codigo_input);
      if (existe == true)
      {
        printf("Esse código de produto já existe.\n");

        // continua até o usuario digitar uma entrada válida
        // voltar = true;
        while (true)
        {
          voltar = goto_menu();

          if (voltar == true)
          {
            return *ptr_error = true;
          }
          else if (voltar == false) break;
        }
      }
      else // caso não exista um produto com esse nome, o nome é retornado
        return codigo_input;
    }
    else
      return codigo_input;
  }
}

char *read_name(Estoque *estoque, bool *ptr_error)
{
  char *nome_input;
  nome_input = malloc(32 * sizeof(char));

  bool voltar = false;
  while (voltar == false) // while para repetir caso o produto digitado ja exista
  {
    // coleta o nome do produto
    printf("Nome: ");
    fgets(nome_input, 32, stdin);
    int tamanho = strlen(nome_input);
    remove_newline(nome_input, tamanho);
    printf("\n");

    // confere se a string passou de 30 de tamanho
    if(strlen(nome_input) > 30)
    {
      printf("Só pode ter no máximo 30 caracteres\n");
      while (getchar() != '\n');
      continue;
    }
    return nome_input;
  }
  return NULL;
}

float read_price(bool *ptr_error)
{
  float preco_input = 0.0;

  bool voltar = false;
  while (voltar == false) // while para repetir caso o produto digitado ja exista
  {
    printf("Caso hajam casas decimais, separe-as por ponto.\n");
    printf("Preço: ");
    // lê e checa se é um float
    if (scanf("%f", &preco_input) != 1)
    {
      printf("Digite um preço válido.\n\n");
      while (getchar() != '\n');

      voltar = goto_menu();
      if (voltar == true)
      {
        *ptr_error = true;
        return 0.0;
      }
      else continue;
    }

    while (getchar() != '\n');
    printf("\n");

    return preco_input;
  }
  return -1.0;
}

int read_amount(bool *ptr_error)
{
  int quant_input = 0;

  bool voltar = false;
  while (voltar == false)
  {
    printf("Necessário ser inteiro.\n");
    printf("Quantidade: ");
    // lê e checa se é um inteiro
    if (scanf("%d", &quant_input) != 1)
    {
      printf("Digite uma quantidade válida.\n\n");
      while (getchar() != '\n');

      voltar = goto_menu();
      if (voltar == true)
      {
        *ptr_error = true;
        return 0;
      }
      else continue;
    }

    while (getchar() != '\n');
    printf("\n");

    return quant_input;
  }
  return -1;
}

void print_product(Estoque *estoque, int codigo_input)
{
  // procura pelo produto e retorna a posição
  int pos = search_product(estoque, codigo_input, false);

  if (pos == -1)
  {
    printf("Não existe produto com o código: %d\n", codigo_input);
    return;
  }

  // armazenando os dados em strings
  char codigo[100];
  char nome[100];
  char preco[100];
  char quantidade[100];
  sprintf(codigo, "%d", estoque->produto[pos].codigo);
  strcpy(nome, estoque->produto[pos].nome);
  sprintf(preco, "%f", estoque->produto[pos].preco);
  sprintf(quantidade, "%d", estoque->produto[pos].quantidade);

  // imprime os dados
  printf("Código: %s | ", codigo);
  printf("Nome: %s | ", nome);
  printf("Preço: %.2f | ", estoque->produto[pos].preco);
  printf("Quantidade: %s | \n", quantidade);
  for (int i = 0; i < strlen(codigo); i++) printf("_");
  printf("_________|");
  for (int i = 0; i < strlen(nome); i++) printf("_");
  printf("________|");
  for (int i = 0; i < strlen(preco) - 4; i++) printf("_");
  printf("_________|");
  for (int i = 0; i < strlen(quantidade); i++) printf("_");
  printf("______________|\n\n");
}
