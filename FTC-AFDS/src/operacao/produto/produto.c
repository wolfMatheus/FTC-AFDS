#include "./produto.h"
#include "../../strings/stringutil.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int doubleTransitionFunction(AFD *produtoAfd, AFD *afd1, AFD *afd2, char *state1, char *state2, char *simbolo)
{
  char *value1 = transitionFunction(afd1, simbolo, state1);
  char *value2 = transitionFunction(afd2, simbolo, state2);
  char *concattedValue = concatWithComma(value1, value2);

  int foundIndex = -1;
  for (int i = 0; i < *produtoAfd->estados_numericos; i++)
  {
    if (!strcmp(concattedValue, produtoAfd->estados[i]))
    {
      foundIndex = i;
      break;
    }
  }
  free(concattedValue);
  return foundIndex;
}

AFD *afdProduct(AFD *afd1, AFD *afd2)
{
  AFD *produtoAfd = getEmptyAFD();
  *produtoAfd->numero_simbolos = *afd1->numero_simbolos;
  produtoAfd->alphabet = malloc((*afd1->numero_simbolos) * sizeof(char *));
  for (int i = 0; i < *afd1->numero_simbolos; i++)
  {
    char *simbolo = afd1->alphabet[i];
    char *newSymbol = copyString(simbolo);
    produtoAfd->alphabet[i] = newSymbol;
  }

  int numberOfStates = (*afd1->estados_numericos) * (*afd2->estados_numericos);
  *produtoAfd->estados_numericos = numberOfStates;
  produtoAfd->estados = malloc(sizeof(char *) * numberOfStates);
  int currentStateIndex = 0;
  for (int i = 0; i < *afd1->estados_numericos; i++)
  {
    char *state1 = afd1->estados[i];
    for (int j = 0; j < *afd2->estados_numericos; j++)
    {
      char *state2 = afd2->estados[j];
      char *productState = concatWithComma(state1, state2);
      produtoAfd->estados[currentStateIndex] = productState;
      if (i == *afd1->estado_inicial && j == *afd2->estado_inicial)
      {
        *produtoAfd->estado_inicial = currentStateIndex;
      }
      currentStateIndex++;
    }
  }

  *produtoAfd->transicoes_numerica = numberOfStates * (*produtoAfd->numero_simbolos);
  produtoAfd->transicoes = malloc(sizeof(Transition *) * (*produtoAfd->transicoes_numerica));
  int indiceTransicaoAtual = 0;
  for (int i = 0; i < *produtoAfd->estados_numericos; i++)
  {
    char *estado= produtoAfd->estados[i];
    char **splitted = splitByComma(estado);
    for (int j = 0; j < *produtoAfd->numero_simbolos; j++)
    {
      char *simbolo = produtoAfd->alphabet[j];
      int resultado = doubleTransitionFunction(produtoAfd, afd1, afd2, splitted[0], splitted[1], simbolo);
      Transition *transicao = getEmptyTransition();
      *transicao->from = i;
      *transicao->to = resultado;
      *transicao->read = j;
      produtoAfd->transicoes[indiceTransicaoAtual] = transicao;
      indiceTransicaoAtual++;
    }
    freeSplit(splitted);
  }

  return produtoAfd;
}