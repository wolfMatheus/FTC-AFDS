#include <stdio.h>
#include <stdlib.h>
#include "./validacao.h"
#include "../parametros/parametros.h"

int updateForOneInput(CLI_Result result, char *name, char **receiver, ApplicationValidacao *appValidacao, int required)
{
  CLI_Value *value = getCLIValue(result, name);
  if (value)
  {
    *receiver = value->value;
  }
  else
  {
    if (required)
    {
      appValidacao->err = 1;
      sprintf(appValidacao->message, "Command %s: No input provided.", name);
    }
  }
  return !!value;
}

int updateForTwoInputs(CLI_Result result, char *name, ApplicationValidacao *appValidacao)
{
  CLI_Value *value = getCLIValue(result, name);
  if (value)
  {
    appValidacao->input1 = value->value;
    if (value->next)
    {
      appValidacao->input2 = value->next->value;
    }
    else
    {
      appValidacao->err = 1;
      sprintf(appValidacao->message, "Command %s: Two inputs are required.", name);
    }
  }
  return !!value;
}

ApplicationValidacao *getAppValidacao(CLI_Result result)
{
  ApplicationValidacao *appValidacao = malloc(sizeof(ApplicationValidacao));
  appValidacao->err = 0;

  appValidacao->outputProvided = updateForOneInput(result, OUTPUT, &appValidacao->output, appValidacao, 1);
  appValidacao->dot = updateForOneInput(result, DOT, &appValidacao->input1, appValidacao, 0);
  appValidacao->complemento = updateForOneInput(result, COMPLEMENTO, &appValidacao->input1, appValidacao, 0);
  appValidacao->minimizacao = updateForOneInput(result, MINIMIZACAO, &appValidacao->input1, appValidacao, 0);
  appValidacao->intersecao = updateForTwoInputs(result, INTERSECAO, appValidacao);
  appValidacao->uniao = updateForTwoInputs(result, UNIAO, appValidacao);
  appValidacao->reconhecer = updateForTwoInputs(result, RECONHECER, appValidacao);

  return appValidacao;
}

void validateAppValidacao(ApplicationValidacao *appValidacao)
{
  int operations[6] = {appValidacao->dot,
                       appValidacao->complemento,
                       appValidacao->minimizacao,
                       appValidacao->intersecao,
                       appValidacao->uniao,
                       appValidacao->reconhecer};
  int numberSelected = 0;
  for (int i = 0; i < 6; i++)
  {
    if (operations[i])
      numberSelected++;
  }
  if (numberSelected > 1)
  {
    appValidacao->err = 1;
    sprintf(appValidacao->message, "You cannot choose more than one operation per execution.");
  }
  if (!numberSelected)
  {
    appValidacao->err = 1;
    sprintf(appValidacao->message, "You must select one operation to do!");
  }
}

void freeAppValidacao(ApplicationValidacao *validacao)
{
  free(validacao);
}
