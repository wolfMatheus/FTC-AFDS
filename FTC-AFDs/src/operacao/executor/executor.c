#include <stdlib.h>
#include "../reconhecimento/reconhecimento.h"

void executeOperation(ApplicationValidacao validacao)
{
  AFD *afd = readAFD(validacao.input1);
  AFD *result = NULL;
  if (validacao.dot)
  {
    DOTFormat *dotFormat = visualizacao(afd);
    writeDot(dotFormat, validacao.output);
    freeDot(dotFormat);
  }
  if (validacao.complemento)
  {
    result = complemento(afd);
  }
  if (validacao.intersecao)
  {
    AFD *afd2 = readAFD(validacao.input2);
    result = intersecao(afd, afd2);
    freeAFD(afd2);
  }
  if (validacao.uniao)
  {
    AFD *afd2 = readAFD(validacao.input2);
    result = uniao(afd, afd2);
    freeAFD(afd2);
  }
  if (validacao.minimizacao)
  {
    result = minimizacao(afd);
  }
  if (validacao.reconhecer)
  {
    int size;
    char **words = readWords(validacao.input2, &size);
    if (!words)
    {
      return;
    }
    int *results = reconhecer(afd, words, size);
    writeReconhecerResult(results, validacao.output, size);
    free(results);
    freeWords(words, size);
  }
  if (result)
  {
    writeAFD(*result, validacao.output);
    freeAFD(result);
  }
  freeAFD(afd);
}