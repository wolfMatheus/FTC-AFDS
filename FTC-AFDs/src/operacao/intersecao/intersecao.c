#include "../produto/produto.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

AFD *intersecao(AFD *afd1, AFD *afd2)
{
  AFD *produto = afdProduto(afd1, afd2);
  int numberFinalStates = (*afd1->number_final_states) * (*afd2->number_final_states);
  produto->final_states = malloc(sizeof(int) * numberFinalStates);
  *produto->number_final_states = numberFinalStates;
  int currentIndex = 0;
  int n2 = *afd2->number_final_states;
  for (int i = 0; i < *afd1->number_final_states; i++)
  {
    int index1 = afd1->final_states[i];
    for (int j = 0; j < *afd2->number_final_states; j++)
    {
      int index2 = afd2->final_states[j];
      int productIndex = (index1 * n2) + index2;
      produto->final_states[currentIndex] = productIndex;
      currentIndex++;
    }
  }

  return produto;
}