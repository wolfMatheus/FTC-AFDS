#include <stdio.h>
#include "../afd/afd.h"
#include "../validacao/validacao.h"
#include "./visualizacao/filter/filter.h"

#define OPERATIONS_H

DOTFormat *visualizacao(AFD *afd);


AFD *complemento(AFD *afd);


AFD *intersecao(AFD *afd1, AFD *afd2);


AFD *uniao(AFD *afd1, AFD *afd2);

AFD *minimizacao(AFD *afd);


int *reconhecer(AFD *afd, char **words, int tamanho);


void executeOperation(ApplicationContext context);
