#include <stdio.h>
#include <stdlib.h>
#include "./validacao.h"
#include "../parametros/parametros.h"

int updateForOneInput(CLI_Result resultado, char *name, char **receiver, ApplicationContext *appContext, int required)
{
  CLI_Value *value = getCLIValue(resultado, name);
  if (value)
  {
    *receiver = value->value;
  }
  else
  {
    if (required)
    {
      appContext->err = 1;
      sprintf(appContext->message, "Command %s: No input provided.", name);
    }
  }
  return !!value;
}

int updateForTwoInputs(CLI_Result resultado, char *name, ApplicationContext *appContext)
{
  CLI_Value *value = getCLIValue(resultado, name);
  if (value)
  {
    appContext->input1 = value->value;
    if (value->next)
    {
      appContext->input2 = value->next->value;
    }
    else
    {
      appContext->err = 1;
      sprintf(appContext->message, "Command %s: Two inputs are required.", name);
    }
  }
  return !!value;
}

ApplicationContext *getAppContext(CLI_Result resultado)
{
  ApplicationContext *appContext = malloc(sizeof(ApplicationContext));
  appContext->err = 0;

  appContext->outputProvided = updateForOneInput(resultado, OUTPUT, &appContext->output, appContext, 1);
  appContext->dot = updateForOneInput(resultado, DOT, &appContext->input1, appContext, 0);
  appContext->complemento = updateForOneInput(resultado, COMPLEMENTO, &appContext->input1, appContext, 0);
  appContext->minimizacao = updateForOneInput(resultado, MINIMIZACAO, &appContext->input1, appContext, 0);
  appContext->intersecao = updateForTwoInputs(resultado, INTERSECAO, appContext);
  appContext->uniao = updateForTwoInputs(resultado, UNIAO, appContext);
  appContext->reconhecer = updateForTwoInputs(resultado, RECONHECER, appContext);

  return appContext;
}

void validateAppContext(ApplicationContext *appContext)
{
  int operations[6] = {appContext->dot,
                       appContext->complemento,
                       appContext->minimizacao,
                       appContext->intersecao,
                       appContext->uniao,
                       appContext->reconhecer};
  int numberSelected = 0;
  for (int i = 0; i < 6; i++)
  {
    if (operations[i])
      numberSelected++;
  }
  if (numberSelected > 1)
  {
    appContext->err = 1;
    sprintf(appContext->message, "You cannot choose more than one operation per execution.");
  }
  if (!numberSelected)
  {
    appContext->err = 1;
    sprintf(appContext->message, "You must select one operation to do!");
  }
}

void freeAppContext(ApplicationContext *context)
{
  free(context);
}
