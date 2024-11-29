#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "headers/structs.h"
#include "headers/utils.h"

// incialização do estoque
Estoque *initialize_stock()
{
  Estoque *estoque = malloc(sizeof(Estoque));
  if (!estoque)
  {
    printf("Erro ao alocar memória para o estoque.\n");
    exit(EXIT_FAILURE);
  }

  estoque->num_elem = 0;
  estoque->capacidade = 5; // Defina uma capacidade inicial.
  estoque->produto = malloc(estoque->capacidade * sizeof(Produto));

  if (!estoque->produto)
  {
    printf("Erro ao alocar memória da lista de produtos.\n");
    exit(EXIT_FAILURE);
  }
  return estoque;
}

// função de escrita no arquivo
void write_data(int codigo, char *nome, float preco, int quantidade)
{
  FILE *arquivo;
  arquivo = fopen("produtos.csv", "a");


  fprintf(arquivo, "%d,%s,%f,%d\n", codigo, nome, preco, quantidade);

  fclose(arquivo);
}

// função de carregamento dos dados do arquivo
void load_data(Estoque *estoque) {
  FILE *arquivo = fopen("produtos.csv", "r");
  if (!arquivo) {
    printf("Nenhum arquivo de dados encontrado. Criando estoque vazio.\n");
    return;
  }

  char buffer[1000];
  while (fgets(buffer, sizeof(buffer), arquivo)) {
    Produto novo_produto;
    sscanf(buffer, "%d,%30[^,],%f,%d", &novo_produto.codigo, novo_produto.nome, &novo_produto.preco, &novo_produto.quantidade);

    if (estoque->num_elem >= estoque->capacidade) {
      printf("Memória realocada.\nCapacidade atual: %d\n", estoque->capacidade);
      estoque->capacidade *= 2;
      estoque->produto = realloc(estoque->produto, estoque->capacidade * sizeof(Produto));
      if (!estoque->produto) {
        fprintf(stderr, "Erro ao realocar memória.\n");
        exit(EXIT_FAILURE);
      }
    }
    estoque->produto[estoque->num_elem++] = novo_produto;
  }
  fclose(arquivo);
}

// cadastra produto
void insert_product(Estoque *estoque)
{
  int codigo_input;
  char *nome_input;
  float preco_input;
  int quant_input;

  // as seguintes funções vão ler e verificar as entradas do usuario
  bool error = false;
  bool *ptr_error = &error;

  codigo_input = read_code(estoque, ptr_error, true);
  if (error == true) return;
  nome_input = read_name(estoque, ptr_error);
  if (error == true) return;
  preco_input = read_price(ptr_error);
  if (error == true) return;
  quant_input = read_amount(ptr_error);
  if (error == true) return;

  if (estoque->num_elem >= estoque->capacidade) {
    estoque->capacidade *= 2;
    estoque->produto = realloc(estoque->produto, estoque->capacidade * sizeof(Produto));
    if (!estoque->produto) {
      fprintf(stderr, "Erro ao realocar memória da lista de produtos.\n");
      exit(EXIT_FAILURE);
    }
  }

  // atribuindo os dados do produto a lista estoque->produto
  estoque->produto[estoque->num_elem].codigo = codigo_input;
  strcpy(estoque->produto[estoque->num_elem].nome, nome_input);
  estoque->produto[estoque->num_elem].preco = preco_input;
  estoque->produto[estoque->num_elem].quantidade = quant_input;

  estoque->num_elem++;

  // armazena os dados do produto no arquivo produtos.csv
  write_data(codigo_input, nome_input, preco_input, quant_input);

  printf("new num_elem: %d\n\n", estoque->num_elem);
}

// remove o produto do lista sequencial e do arquivo
void remove_product(Estoque *estoque) {
  // primeira parte que removerá o produto na lista sequencial
  if(estoque->num_elem == 0){
    printf("Ainda não existem produtos no estoque, tente novamente.\n\n");
    return;
  }

  int codigo;
  printf("Digite o código do produto a ser removido: ");
  scanf("%d", &codigo);
  while (getchar() != '\n');

  int pos = -1;
  for(int i = 0; i < estoque->num_elem; i++){
    if(estoque->produto[i].codigo == codigo){
      pos = i;
      break;
    }
  }

  if(pos == -1){
    printf("Produto com o código '%d' não foi encontrado\n", codigo);
    return;
  }

  for(int i = pos; i < estoque->num_elem - 1; i++){
    estoque->produto[i] = estoque->produto[i + 1];
  }
  estoque->num_elem--;
  printf("new num_elem: %d\n", estoque->num_elem);
  printf("Produto com código '%d' removido com sucesso.\n\n", codigo);

  // segunda parte que removerá o produto do arquivo
  FILE *arquivo, *temp;

  char nome_arquivo[13] = "produtos.csv";
  char temp_nome_arquivo[18] = "temp_produtos.csv";

  char buffer[1000];

  // abertura dos arquivos
  arquivo = fopen(nome_arquivo, "r");
  temp = fopen(temp_nome_arquivo, "w");

  // checa se abriu corretamente
  if (arquivo == NULL || temp == NULL)
  {
    printf("Erro ao abrir o arquivo\n");
  }

  bool continuar_lendo = true;
  int linha_atual = 0;
  do
  {
    // salva uma linha inteira na variável buffer
    fgets(buffer, 1000, arquivo);

    // escrita das linhas no arquivo exceto pela que será excluida
    if (feof(arquivo)) continuar_lendo = false;
    else if (linha_atual != pos)
      fputs(buffer, temp);

    linha_atual++;

  } while (continuar_lendo);

  // fechamento dos arquivos
  fclose(arquivo);
  fclose(temp);

  // exclui o arquivo antigo e renomeia o temporario para ser o principal
  remove(nome_arquivo);
  rename(temp_nome_arquivo, nome_arquivo);
}

// função que procura o produto pelo codigo e retorna o indice dele na lista
int search_product(Estoque *estoque, int codigo, bool print)
{
  if (estoque-> num_elem == 0){
    printf("O estoque está vazio :D\n");
    return -1;
  }

  int i = 0;
  while (i < estoque->num_elem)
  {
    if (estoque->produto[i].codigo == codigo)
    {
      if (print == true)
        print_product(estoque, codigo);
      return i;
    }
    else if (i + 1 == estoque->num_elem)
    {
      if (print == true)
        printf("Não existe produto com esse código.\n\n");
      return -1;
    }
    i++;
  }
}

void list_products(Estoque *estoque)
{
  if (estoque->num_elem == 0)
  {
    printf("Nenhum produto no estoque.\n\n");
    return;
  }
  for (int i = 0; i < estoque->num_elem; i++)
  {
    print_product(estoque, estoque->produto[i].codigo);
  }
}

// atualiza o produto dado o codigo dele
void update_product(Estoque *estoque) {
  if (estoque->num_elem == 0) {
    printf("O estoque está vazio. Nada para atualizar.\n");
    return;
  }

  int codigo;
  printf("Digite o código do produto a ser atualizado: ");
  while (scanf("%d", &codigo) != 1)
  {
    printf("Insira um valor válido\n");
    printf("Digite o código do produto: ");
  }
  while (getchar() != '\n'); // Limpar o buffer

  int pos = search_product(estoque, codigo, true);
  if (pos == -1) {
    printf("Produto com o código '%d' não foi encontrado\n", codigo);
    return;
  }

  Produto *produto = &estoque->produto[pos];

  // Pedir os novos valores

  char *input;
  input = malloc(50 * sizeof(char));

  // atualiza o nome
  printf("\n");
  printf("Novo nome: ");
  fgets(input, sizeof(input), stdin);
  if (input[0] != '\n') {
    remove_newline(input, 50);
    strcpy(produto->nome, input);
  }
  while (getchar() != '\n');

  // atualizar o preço
  printf("\n");
  printf("Novo preço: ");
  fgets(input, sizeof(input), stdin);
  if (input[0] != '\n') {
    produto->preco = atof(input);
  }

  // atualiza a quantidade
  printf("\n");
  printf("Nova quantidade: ");
  fgets(input, sizeof(input), stdin);
  if (input[0] != '\n') {
    produto->quantidade = atoi(input);
  }

  free(input);

  // atualiza o arquivo CSV
  FILE *arquivo = fopen("produtos.csv", "w");
  if (!arquivo) {
    fprintf(stderr, "Erro ao abrir o arquivo para atualizar.\n");
  return;
  }

  for (int i = 0; i < estoque->num_elem; i++) {
    Produto p = estoque->produto[i];
    fprintf(arquivo, "%d,%s,%.2f,%d\n", p.codigo, p.nome, p.preco, p.quantidade);
  }

  fclose(arquivo);
}

