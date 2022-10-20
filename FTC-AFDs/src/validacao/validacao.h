#include <stdio.h>
#include "../cli/cli.h"
#include "../parametros/parametros.h"

/**
 * Estrutura que representa o Validacaoo de aplicacao, basicamente armazenando quais parametros foram informados e 
 * seus respectivos valores. A aplicacao so consegue receber no maximo dois arquivos de entrada e um de saida, e somente
 * uma operacao pode ocorrer por vez. 
*/
typedef struct application_ctx
{
  int dot;
  int complemento;
  int intersecao;
  int uniao;
  int minimizacao;
  int reconhecer;
  int outputProvided;

  int err;
  char message[100];

  char *input1;
  char *input2;
  char *output;
} ApplicationValidacao;

/**
 * Gera o Validacaoo de aplicacao a partir de um resultado de CLI.
 * @param result: o resultado de CLI.
 * @return o Validacaoo de aplicacao correspondente.
*/
ApplicationValidacao *getAppValidacao(CLI_Result result);

/**
 * Recebe e valida o Validacaoo recebido. Basicamente verifica se somente uma opcao foi selecionada, e tambem se a quantidade
 * correta de valores para cada opcao selecionada foi informado. Caso nao seja valido, preenche o campo err e message da
 * estrutura ApplicationValidacao, informando que ocorreu um erro.
 * @param appValidacao: Validacaoo da aplicacao.
*/
void validateAppValidacao(ApplicationValidacao *appValidacao);

/**
 * Libera a memoria alocada pelo Validacaoo de aplicacao.
 * @param Validacao: Validacaoo da aplicacao.
*/
void freeAppValidacao(ApplicationValidacao *Validacao);