/*-------------------------------------------------------------------------------
 *                                                                              *
 * Module contenant les fonctions pour gerer la table des declarations          *
 *                                                                              *
 * Auteur: SOLOFO RABONARIJAONA                                                 *
 *                                                                              *
 * Historique:                                                                  *
 *     - Creation le 03/11/17  par S.RABONARIJAONA                              *
 *                                                                              *
 *------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_declaration.h"


int compteur_table_debordement = OFFSET_DEBORDEMENT;
declaration table_declaration[TAILLE_TABLE_DECLARATION];
int compteur_description_type_entete = 0;

/* =========== Insere une ligne dans la table ========== */

void inserer(char lexeme[100], int nature, int region, int description, int execution)
{
  int i; 			/* courant sur table */
  int index /* = renvoyer_index(lexeme) ### DONNER PAR OUSSEMA TRABELSI ### */; /* recuperer l'indice du lexeme dans la table lexicographique */
  if (strcmp(lexeme, "int") == 0)
    index = 0;
  if (strcmp(lexeme, "char") == 0)
    index = 1;

  /* verifier si le lexeme existe deja dans la zone normale */
  if(table_declaration[index].a_ete_insere == TRUE)
  {  
    /* parcourir la zones debordement de la table pour verifier si le lexeme existe dejà */
    for(i = compteur_table_debordement - 1; i >= OFFSET_DEBORDEMENT; i--)
    {
      if (strcmp(table_declaration[i].lexeme, lexeme) == 0) /* si lexeme existe deja */
      {
	index = compteur_table_debordement++; /* insere dans zone de debordement */
	modifier_suivant(i, index);	  /* modifier suivant du lexeme qui existe deja */
	i = 0;				  /* sortir de la boucle */
      }
    }
    if (i > 0)			/* s'il n'existe pas encore dans la zone de debordement*/
    {
      modifier_suivant(index, compteur_table_debordement);
      index = compteur_table_debordement++;
    }
  }


  
  strcpy(table_declaration[index].lexeme, lexeme); /* copie le lexème en parametre dans la colonne lexeme */
  table_declaration[index].nature = nature;
  table_declaration[index].region = region;
  table_declaration[index].description = description;
  table_declaration[index].execution = execution;
  table_declaration[index].a_ete_insere = TRUE; /* mise à jour indicateur a_ete_insere */
  
}



/* ============ modifier le champ suivant d'une declaration ============== */

void modifier_suivant(int index, int new_suivant)
{
  table_declaration[index].suivant = new_suivant;
}

/* =========== Initialise la table (insere les types simples) ======== */
void init_table()
{
  int i;
  for (i = 0; i < TAILLE_TABLE_DECLARATION; i++)
  {
    table_declaration[i].index = i;
    table_declaration[i].nature = -1;
    table_declaration[i].suivant = -1;
    table_declaration[i].region = -1;
    table_declaration[i].description = -1;
    table_declaration[i].execution = -1;
    table_declaration[i].a_ete_insere = FALSE;
  }
  inserer("int", TYPE_SIMPLE, 0, 0, 1);
  //inserer("int", TYPE_SIMPLE, 0, 0, 1);
  /* inserer("float", TYPE_SIMPLE, 0, 1, 1); */
  /* inserer("bool", TYPE_SIMPLE, 0, 2, 1); */
  inserer("char", TYPE_SIMPLE, 0, 3, 1);
  /* inserer("string", TYPE_SIMPLE, 0, 4, 1); */
}


/* ============= affiche la table à la sortie standard =============== */
void afficher_table()
{
  int i;
  fprintf(stdout, "TABLE DES DECLARATIONS - ZONE NORMALE\n");
  fprintf(stdout, "--------------------------------------\n");
  fprintf(stdout, "\n| Index | Nature | Suivant | Region | Description | Execution |\n");
  fprintf(stdout, "\n|-------------------------------------------------------------|\n");
  for (i = 0; i < OFFSET_DEBORDEMENT; i++)
  {
    fprintf(stdout, "| %d    | %d     | %d      | %d     | %d          | %d        |\n", table_declaration[i].index, table_declaration[i].nature, table_declaration[i].suivant, table_declaration[i].region, table_declaration[i].description, table_declaration[i].execution);
    fprintf(stdout, "|-------------------------------------------------------------|\n");
  }

  fprintf(stdout, "\n\nTABLE DES DECLARATIONS - ZONE DE DEBORDEMENT\n");
  fprintf(stdout, "--------------------------------------\n");
  fprintf(stdout, "\n| Index | Nature | Suivant | Region | Description | Execution |\n");
  fprintf(stdout, "\n|-------------------------------------------------------------|\n");
  for (; i < TAILLE_TABLE_DECLARATION; i++)
  {
    fprintf(stdout, "| %d    | %d     | %d      | %d     | %d          | %d        |\n", table_declaration[i].index, table_declaration[i].nature, table_declaration[i].suivant, table_declaration[i].region, table_declaration[i].description, table_declaration[i].execution);
    fprintf(stdout, "|-------------------------------------------------------------|\n");
  }
}
