#include <stdlib.h>
#include <stdio.h>
#include "table_declaration.h"

int main(int argc, char *argv[])
{
  init_table();
  inserer("int", TYPE_SIMPLE, 1, 1, 1);
  inserer("int", TYPE_SIMPLE, 3, 3, 3);
  inserer("char", TYPE_SIMPLE, 4, 4, 4);
  inserer("char", TYPE_SIMPLE, 6, 6, 6);
  inserer("int", TYPE_SIMPLE, 3, 3, 3);
  inserer("int", TYPE_SIMPLE, 3, 3, 3);
  inserer("int", TYPE_SIMPLE, 3, 3, 3);
  inserer("char", TYPE_SIMPLE, 6, 6, 6);
  inserer("char", TYPE_SIMPLE, 6, 6, 6);
  inserer("char", TYPE_SIMPLE, 6, 6, 6);
  afficher_table();
}
