#include <stdio.h>

 
typedef struct cli_item
{
  char *name;
  int number_values;
  int position;
} CLI_Item;

typedef struct cli_structure
{
  CLI_Item **items;
  int tamanho;
  int items_size;
} CLI_Params;


typedef struct cli_value
{
  char *value;
  struct cli_value *next;
} CLI_Value;


typedef struct cli_result
{
  CLI_Params *params;
  CLI_Value **values;
  int tamanho;
} CLI_Result;


CLI_Value *createCLIValue(char *value);


CLI_Item *getItem(char *name, int position, int number_values);


CLI_Params *getParams(int initial_size);


CLI_Result *readCLI(CLI_Params *params, int argc, char *argv[]);

/**
 * Procura o item com o dado nome nos parametros informados.
 * @param params: parametros que podem conter o item.
 * @param value: nome do item a ser procurado
 * @return item procurado caso seja encontrado, NULL caso contrario.
*/
CLI_Item *searchItem(CLI_Params params, char *value);


CLI_Value *getCLIValue(CLI_Result result, char *param);


void freeLinkedList(CLI_Value *head);


void registraParametros(CLI_Params *params, char *name, int number_values);


void freeCLI(CLI_Result *result);


void freeCLIParams(CLI_Params *params);