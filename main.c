#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "headers/utils.h"
#include "headers/funcs.h"
#include "headers/structs.h"

int main()
{
  // criação do estoque e inicialização
  Estoque *estoque = NULL;
  estoque = initialize_stock(estoque);

  // criação do arquivo
  FILE *arquivo;
  arquivo = fopen("produtos.csv", "a");
  fclose(arquivo);

  // checa se houve erro ao inicializar o estoque
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }

  // while para execução contínua do programa
  while (true)
  {
    print_menu();

    char input;
    while (true)
    {
      printf("input: ");
      scanf("%c", &input);
      printf("\n");
      // captura o '\n' do input
      while (getchar() != '\n');

      if (isdigit(input)) break;
      else
      {
        printf("Digite uma entrada válida\n");
        continue;
      }
    }

    // converte char em inteiro
    int num = input - '0';

    // switch case para seleção no menu
    switch (num)
    {
      case 0:
        // libera a memória do estoque
        free(estoque);
        return 0;
      case 1:
        // cadastra novo produto
        insert_product(estoque);
        break;
      case 2:
        // procuro produto pelo codigo
        search_product(estoque);
        break;
    }
  }

  return 0;
}
