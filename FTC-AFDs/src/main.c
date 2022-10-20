#include <stdio.h>
#include <string.h>
#include "./operacao/operacao.h"

/**
 * Registra os parametros necessarios para o funcionamento da CLI da aplicacao.
 */
CLI_Parametros *createCLIParametros()
{
  CLI_Parametros *parametros = getParams(10);

  registerParam(parametros, DOT, 1);
  registerParam(parametros, OUTPUT, 1);
  registerParam(parametros, COMPLEMENTO, 1);
  registerParam(parametros, INTERSECAO, 2);
  registerParam(parametros, UNIAO, 2);
  registerParam(parametros, MINIMIZACAO, 1);
  registerParam(parametros, RECONHECER, 2);

  return parametros;
}

/**
 * Programa principal, executa o modulo de CLI, depois aplica o modulo de Validacao,
 * e ao final aplica o modulo de operacoes, para retornar o resultado esperado.
 */
int main(int argc, char *argv[])
{
  CLI_Parametros *parametros = createCLIParametros();
  CLI_Result *result = readCLI(parametros, argc, argv);

  ApplicationValidacao *appValidacao = getAppValidacao(*result);
  if (appValidacao->err)
  {
    printf("Invalid input provided. Error log: %s\n", appValidacao->message);
    return 1;
  }

  validateAppValidacao(appValidacao);
  if (appValidacao->err)
  {
    printf("Invalid input provided. Error log: %s\n", appValidacao->message);
    return 1;
  }

  executeOperation(*appValidacao);

  freeAppValidacao(appValidacao);
  freeCLI(result);
  return 0;
}