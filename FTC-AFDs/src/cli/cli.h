#include <stdio.h>

/**
 * Representa um campo que se quer registrar na CLI. O nome precisa ser unico, number_values representa 
 * o numero esperado de argumentos quando o comando for usado, e position eh um campo de controle interno.
*/
typedef struct cli_item
{
  char *name;
  int number_values;
  int position;
} CLI_Item;

/**
 * Conjunto de parametros registrados para o funcionamento da CLI. Possui um conjunto de itens, que sao registrados
 * pelo usuario da biblioteca, um tamanho (items_size), e o tamanho real do array, para fins de controle interno (size).
*/
typedef struct cli_structure
{
  CLI_Item **items;
  int size;
  int items_size;
} CLI_Parametros;

/**
 * Lista ligada que representa os valores encontrados pela CLI para algum CLI_Item. Ela possui um valor e um ponteiro para
 * o proximo valor, uma vez que um CLI_Item pode ter varios valores associados.
*/
typedef struct cli_value
{
  char *value;
  struct cli_value *next;
} CLI_Value;

/**
 * Resultado final da execucao da CLI. Contem os parametros utilizados, os valores obtidos a partir da leitura, e o tamanho
 * do array de valores encontrados.
*/
typedef struct cli_result
{
  CLI_Parametros
 *parametros;
  CLI_Value **values;
  int size;
} CLI_Result;

/**
 * Factory method que gera um CLI_Value a partir de uma string value.
 * @parametros value: string desejada.
 * @return o CLI_Value correspondente.
*/
CLI_Value *createCLIValue(char *value);

/**
 * Factory method que gera um CLI_Item a partir de uma string nome, sua posicao e seu numero de valores. Esta funcao
 * eh usada internamente, portanto nao se preocupe com a necessidade de informar a posicao do item.
 * @parametros name: nome do valor.
 * @parametros position: posicao do valor.
 * @parametros number_values: numero de valores aceitos.
*/
CLI_Item *getItem(char *name, int position, int number_values);

/**
 * Retorna uma instancia de CLI_Parametros
 * com o vetor de itens alocado com o tamanho inicial informado.
 * @parametros initial_size: tamanho inicial do vetor de itens.
 * @return a instancia de parametros desejada.**/
CLI_Parametros *getParams(int initial_size);

/**
 * Faz a leitura completa dos parametros informados pelo usuario e converte tudo para uma instancia de CLI_Parametros
 *.
 * Eh interessante notar que nao eh feita nenhuma validacao aqui nesse metodo, devido ao fato de que ele nao foi construido
 * com esse intuito. Esse modulo eh de baixo nivel somente para retornar os valores encontrados, e a validacao eh feita por 
 * um modulo de mais alto nivel (modulo de Validacao).
 * @parametros parametros: parametros registrados na CLI.
 * @parametros argc: tamanho do argv.
 * @parametros argv: array de parametros passado pelo usuario. 
 * @return o resultado processado.
*/
CLI_Result *readCLI(CLI_Parametros *parametros, int argc, char *argv[]);

/**
 * Procura o item com o dado nome nos parametros informados.
 * @parametros parametros: parametros que podem conter o item.
 * @parametros value: nome do item a ser procurado
 * @return item procurado caso seja encontrado, NULL caso contrario.
*/
CLI_Item *searchItem(CLI_Parametros parametros, char *value);

/**
 * Retorna o valor correspondente ao parametro informado, dentro dos resultados de CLI.
 * @parametros result: resultado alvo
 * @parametros parametros: nome do item a ser procurado
 * @return lista ligada com os valores encontrados para o parametro.
*/
CLI_Value *getCLIValue(CLI_Result result, char *parametros);

/**
 * Libera a memoria alocada para uma lista ligada.
 * @parametros head: cabeca da lista ligada.
*/
void freeLinkedList(CLI_Value *head);

/**
 * Registra um novo parametro na instancia de parametros informada.
 * @parametros parametros: instancia de parametros de CLI alvo.
 * @parametros name: nome do parametro a ser adicionado.
 * @parametros number_values: numero de valores esperados para o parametro.
*/
void registerParam(CLI_Parametros *parametros, char *name, int number_values);

/**
 * Libera a memoria alocada para um resultado de CLI.
 * @parametros result: resultado que tera a memoria liberada.
*/
void freeCLI(CLI_Result *result);

/**
 * Libera a memoria alocada para parametros de CLI.
 * @parametros parametros: parametros que terao sua memoria liberada.
*/
void freeCLIParams(CLI_Parametros *parametros);