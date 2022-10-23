#include <stdio.h>
#define DOT_H


typedef struct dotformat_transition_est
{
  char *from;
  char *to;
  char *label;
} DOTTransition;


typedef struct dotformat_est
{
  char **double_circles;
  int numero_circulos_duplos;
  int transicoes_numerica;
  char *estado_inicial;
  DOTTransition **transicoes;
} DOTFormat;


DOTTransition *getDOTTransition(char *from, char *to, char *label);


DOTFormat *getDOTFormat(char **double_circles, int numero_circulos_duplos, DOTTransition **transicoes, int transicoes_numerica, char *estado_inicial);


void freeDotTransition(DOTTransition *transition);


void freeDot(DOTFormat *DOTFormat);


void writeDot(DOTFormat *DOTFormat, char *fileName);