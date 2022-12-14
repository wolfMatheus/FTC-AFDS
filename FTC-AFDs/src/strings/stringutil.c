#include <stdlib.h>
#include <string.h>
#include "./stringutil.h"

char *copyString(char *src)
{
  char *newString = malloc(sizeof(char) * strlen(src) + 1);
  strcpy(newString, src);
  return newString;
}

char *concatWithComma(char *str1, char *str2)
{
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  char *newStr = malloc(sizeof(char) * (len1 + len2 + 2));
  int indiceAtual = 0;
  for (int i = 0; i < len1; i++)
  {
    newStr[indiceAtual] = str1[i];
    indiceAtual++;
  }
  newStr[indiceAtual] = '_';
  indiceAtual++;
  for (int i = 0; i < len2; i++)
  {
    newStr[indiceAtual] = str2[i];
    indiceAtual++;
  }
  newStr[indiceAtual] = '\0';
  return newStr;
}

char **splitByComma(char *str)
{
  int tamanho = strlen(str);
  int wordLength = 0;
  char **words = malloc(sizeof(char *) * 2);
  for (int i = 0; i < tamanho; i++)
  {
    wordLength++;
    int secondSize = tamanho - wordLength + 1;
    if (str[i] == '_')
    {
      words[0] = malloc(sizeof(char) * wordLength);
      words[1] = malloc(sizeof(char) * secondSize);
      str[i] = '\0';
      strcpy(words[0], str);
      str[i] = '_';
      for (int j = 0; j < secondSize; j++)
      {
        words[1][j] = str[i + 1 + j];
      }
      words[1][secondSize - 1] = '\0';
      break;
    }
  }
  return words;
}

void freeSplit(char **split)
{
  free(split[0]);
  free(split[1]);
  free(split);
}