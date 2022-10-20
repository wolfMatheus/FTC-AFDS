#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./cli.h"

CLI_Item *getItem(char *name, int position, int number_values)
{
  CLI_Item *item = malloc(sizeof(CLI_Item));
  item->name = name;
  item->position = position;
  item->number_values = number_values;
  return item;
}

CLI_Value *createCLIValue(char *value)
{
  CLI_Value *cli_value = malloc(sizeof(CLI_Value));
  cli_value->value = value;
  cli_value->next = NULL;
}

CLI_Item *searchItem(CLI_Parametros parametros, char *value)
{
  for (int i = 0; i < parametros.items_size; i++)
  {
    if (!strcmp(parametros.items[i]->name, value))
    {
      return parametros.items[i];
    }
  }
  return NULL;
}

void registerParam(CLI_Parametros *parametros, char *name, int number_values)
{
  if (parametros->items_size == parametros->size)
  {
    parametros->size += 1;
    parametros->items = realloc(parametros->items, sizeof(CLI_Item *) * parametros->size);
  }
  parametros->items[parametros->items_size] = getItem(name, parametros->items_size, number_values);
  parametros->items_size++;
}

CLI_Parametros *getParams(int initial_size)
{
  CLI_Parametros *parametros = malloc(sizeof(CLI_Parametros));
  parametros->size = initial_size;
  parametros->items_size = 0;
  parametros->items = malloc(sizeof(CLI_Item *) * initial_size);
}

CLI_Value *getValuesLinkedList(CLI_Item *item, char *argv[], int *current_index)
{

  CLI_Value *head = NULL;
  CLI_Value *prev = NULL;
  for (int j = 0; j < item->number_values; j++)
  {
    (*current_index)++;
    CLI_Value *value = createCLIValue(argv[*current_index]);
    if (prev)
    {
      prev->next = value;
    }
    else
    {
      head = value;
    }
    prev = value;
  }
  return head;
}

void populateValuesArray(CLI_Parametros *cli_parametros, CLI_Value **values, int size, int argc, char *argv[])
{
  int i = 0;
  while (i < argc - 1)
  {
    CLI_Item *item = searchItem(*cli_parametros, argv[i]);
    // If parameter is registered, store it on the array.
    if (item)
    {
      CLI_Value *head = getValuesLinkedList(item, argv, &i);
      values[item->position] = head;
    }
    i++;
  }
}

CLI_Result *readCLI(CLI_Parametros *cli_parametros, int argc, char *argv[])
{
  CLI_Result *result = malloc(sizeof(CLI_Result));

  result->parametros = cli_parametros;
  result->size = cli_parametros->items_size;

  CLI_Value **values = malloc(sizeof(CLI_Value *) * result->size);
  for (int i = 0; i < result->size; i++)
  {
    values[i] = NULL;
  }

  populateValuesArray(cli_parametros, values, result->size, argc, argv);
  result->values = values;
  return result;
}

CLI_Value *getCLIValue(CLI_Result result, char *parametros)
{
  CLI_Item *item = searchItem(*result.parametros, parametros);
  return result.values[item->position];
}

void freeCLI(CLI_Result *result)
{
  for (int i = 0; i < result->size; i++)
  {
    freeLinkedList(result->values[i]);
  }
  freeCLIParametros(result->parametros);
  free(result->values);
  free(result);
}

void freeLinkedList(CLI_Value *head)
{
  if (head == NULL || head->next == NULL)
  {
    free(head);
  }
  else
  {
    freeLinkedList(head->next);
    free(head);
  }
}

void freeCLIParametros(CLI_Parametros *parametros)
{
  for (int i = 0; i < parametros->items_size; i++)
  {
    free(parametros->items[i]);
  }
  free(parametros->items);
  free(parametros);
}
