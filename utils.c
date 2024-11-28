#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "headers/structs.h"

void print_menu()
{
  printf("#####################################\n");
  printf("#####     PAINEL DO ESTOQUE     #####\n");
  printf("#####################################\n\n");
  printf("(Digite o número da opção que deseja)\n\n");
  printf("[0] Sair (implemented)\n");
  printf("[1] Novo produto (implemented)\n");
  printf("[2] Procurar produto (implemented)\n");
  printf("\n");
  printf("=====================================\n\n");
}

// percorre todos os produtos e checa se já existe algum com o mesmo nome
bool product_exists(Estoque *estoque, char nome[])
{
  int n = estoque->num_elem;
  for (int i = 0; i < n; i++)
  {
    if (strcmp(estoque->produto[i].nome, nome) == false)
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
bool is_int(char *string) {
  char *ptr_end;

  if (string == NULL || *string == '\0') {
    return false;
  }

  long value = strtol(string, &ptr_end, 10);

  if (*ptr_end != '\0') {
    return false;
  }

  return true;
}

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

char *read_code(Estoque *estoque, bool *ptr_error)
{
  char *codigo_input;
  codigo_input = malloc(12 * sizeof(char));

  bool voltar = false;
  while (voltar == false) // while para repetir caso o produto digitado ja exista
  {
    // coleta o codigo do produto
    while (true)
    {
      printf("Necessário ser um inteiro\n");
      printf("Código: ");
      fgets(codigo_input, 12, stdin);
      int tamanho = strlen(codigo_input);
      remove_newline(codigo_input, tamanho);
      printf("\n");

      if (is_int(codigo_input)) break;
      else
      {
        printf("Código inválido.\n");
        continue;
      }
    }

    // confere se a string passou de 10 de tamanho
    if(strlen(codigo_input) > 10)
    {
      printf("Só pode ter no máximo 10 caracteres\n");
      while (getchar() != '\n');
      continue;
    }

    // checa se já existe algum produto com esse nome
    bool existe;
    existe = product_exists(estoque, codigo_input);
    if (existe == true)
    {
      printf("Esse código de produto já existe.\n");

      // continua até o usuario digitar uma entrada válida
      bool voltar = true;
      while (true)
      {
        voltar = goto_menu();

        if (voltar == true)
        {
          *ptr_error = true;
          return "ERROR 1";
        }
        else if (voltar == false) break;
      }
    }
    else // caso não exista um produto com esse nome, o nome é retornado
      return codigo_input;
  }
  return "ERROR 2";
};

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

    // checa se já existe algum produto com esse nome
    bool existe;
    existe = product_exists(estoque, nome_input);
    if (existe == true)
    {
      printf("Esse nome de produto já existe.\n");

      // continua até o usuario digitar uma entrada válida
      bool voltar = true;
      while (true)
      {
        voltar = goto_menu();

        if (voltar == true)
        {
          *ptr_error = true;
          return "ERROR 1";
        }
        else if (voltar == false) break;
      }
    }
    else // caso não exista um produto com esse nome, o nome é retornado
      return nome_input;
  }
  return "ERROR 2";
};

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
};

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
};