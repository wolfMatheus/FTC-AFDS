#include <stdio.h>
#include "../operacoes.h"

char **readWords(char *fileName, int *size_ptr);

void freeWords(char **words, int tamanho);


void writeReconhecerResult(int *resultado, char *fileName, int tamanho);


char *transitionFunction(AFD *afd, char *simbolo, char *current_state);