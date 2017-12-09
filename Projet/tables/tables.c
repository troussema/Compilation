/*-------------------------------------------------------------------------------
 *                                                                              *
 * Module contenant les fonctions pour gerer la table des declarations          *
 *                                                                              *
 * Auteur: SOLOFO RABONARIJAONA                                                 *
 *         HABIB MOHAMED                                                                 *
 * Historique:                                                                  *
 *     - Creation le 03/11/17  par S.RABONARIJAONA                              *      - Modification le 05/11/17 par S.RABONARIJAONA
 *                                                                              *
 *------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables.h"

int NB_ELEM=0;


/* int compteur_table_debordement = OFFSET_DEBORDEMENT; */
/* declaration table_declaration[TAILLE_TABLE_DECLARATION]; */
/* int compteur_description_type_entete = 0; */
/* int compteur_table_declaration_aux = 0; */
/* declaration_aux table_declaration_aux[TAILLE_TABLE_DECLARATION]; */


/* =========== Insere un lexeme dans la table declaration auxiliaire ====== */
void inserer_aux(char lexeme[LONGUEUR_LEXEME_MAX], int nature)
{
  strcpy(table_declaration_aux[compteur_table_declaration_aux].lexeme, lexeme);
  table_declaration_aux[compteur_table_declaration_aux++].nature = nature;
}

/* =========== Insere une ligne dans la table ========== */

void inserer(char lexeme[LONGUEUR_LEXEME_MAX], int nature, int region, int description, int execution)
{
  int i; 			/* courant sur table */
  int index = existe_lex(lexeme); /* ### DONNER PAR OUSSEMA TRABELSI ### */ /* recuperer l'indice du lexeme dans la table lexicographique */
  if (index == -1)
  {
    fprintf(stderr, "le lexeme n'existe pas dans la table lexicographique");
    //exit(EXIT_FAILURE);
  }

  /* verifier si le lexeme existe deja dans la zone normale */
  if(table_declaration[index].a_ete_insere == VRAI)
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
  table_declaration[index].a_ete_insere = VRAI; /* mise à jour indicateur a_ete_insere */
  
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
    table_declaration[i].a_ete_insere = FAUX;
  }
  inserer("int", TYPE_SIMPLE, 0, 0, 1);
  inserer("float", TYPE_SIMPLE, 0, 1, 1);
  inserer("bool", TYPE_SIMPLE, 0, 2, 1);
  inserer("char", TYPE_SIMPLE, 0, 3, 1);
  inserer("string", TYPE_SIMPLE, 0, 4, 1);
}


/* ============= affiche la table à la sortie standard =============== */
void afficher_table()
{
  int i;
  fprintf(stdout, "TABLE DES DECLARATIONS - ZONE NORMALE\n");
  fprintf(stdout, "--------------------------------------\n");
  fprintf(stdout, "\n| Index | Nature | Suivant | Region | Description | Execution | Lexeme |\n");
  fprintf(stdout, "\n|----------------------------------------------------------------------|\n");
  for (i = 0; i < OFFSET_DEBORDEMENT; i++)
  {
    fprintf(stdout, "| %d    | %d     | %d      | %d     | %d          | %d        | %s     |\n", table_declaration[i].index, table_declaration[i].nature, table_declaration[i].suivant, table_declaration[i].region, table_declaration[i].description, table_declaration[i].execution, table_declaration[i].lexeme);
    fprintf(stdout, "|----------------------------------------------------------------------|\n");
  }

  fprintf(stdout, "\n\nTABLE DES DECLARATIONS - ZONE DE DEBORDEMENT\n");
  fprintf(stdout, "--------------------------------------\n");
  fprintf(stdout, "\n| Index | Nature | Suivant | Region | Description | Execution | Lexeme |\n");
  fprintf(stdout, "\n|----------------------------------------------------------------------|\n");
  for (; i < TAILLE_TABLE_DECLARATION; i++)
  {
    fprintf(stdout, "| %d    | %d     | %d      | %d     | %d          | %d        | %s     |\n", table_declaration[i].index, table_declaration[i].nature, table_declaration[i].suivant, table_declaration[i].region, table_declaration[i].description, table_declaration[i].execution, table_declaration[i].lexeme);
    fprintf(stdout, "|----------------------------------------------------------------------|\n");
  }
}

/* ============ table description =============== */

/* void inserer_table_declaration (int type, char lex[LONGUEUR_LEXEME_MAX]) */
/* { */
/*   switch (type) */
/*     { */
/*     case TYPE_STRUCT: */
/*       table_description[compteur_table_description].lexeme = NULL; */
/*       table_description[compteur_table_description++].valeur = description; */
/*       description += taille * 3 + 1; */
/*       break; */
/*     case TYPE_ARRAY: */
/*       table_description[compteur_table_description].lexeme = NULL; */
/*       table_description[compteur_table_description++].valeur = description; */
/*       description += taille * 2 + 2; */
/*       break; */
/*     case TYPE_VAR: */
/*       table_description[compteur_table_description].valeur = NULL */
/*       strcpy(table_description[compteur_table_description++].lexeme, lex); */
/*       break; */
/*     case TYPE_PROC: */
/*       table_description[compteur_table_description].lexeme = NULL; */
/*       table_description[compteur_table_description++].valeur = description++; */
/*       break; */
/*     case TYPE_FUNC: */
/*       table_description[compteur_table_description].lexeme = NULL; */
/*       table_description[compteur_table_description++].valeur = description++; */
/*       break; */
/*     default: */
/*       break; */
/*     } */
/* } */




/* ----------------------------- TABLE LEXICOGRAPHIQUE&HASH ----------------- 
*                                                                              *
*			 Auteur: TRABELSI Oussema                              *
*                                                                              */


structlex table_lex[TAILLE_MAX];


//tableau de has 
int tab_hash[31];

void init_tab_hash(){
	for ( int i = 0; i <=31; i++)
	tab_hash[i]=-1;

remplissage_tab_hash();

}

int calcul_hash(char *ch)
{
	int j,res=0;
	for (j=0 ;j<=strlen(ch);j++)
	{
	res+=ch[j];
	}	
	res=res%32;
	return res;
}

void remplissage_tab_hash(){
int i,j,k,trouve=0,res,res2;

for ( i = 0; i < NB_ELEM; i++)
		{ 	
	res=0; res2=0;
	if (table_lex[i].numlex!=-1)
	{ 

//on calcule le hash code
	res=calcul_hash(table_lex[i].contenue);
	

	if (tab_hash[res]==-1)
	{
	tab_hash[res]=table_lex[i].numlex;
	
	}	
	else
	{
	k=i;
	res2=0; trouve=0;
	
	do
	{
	k--;
	res2=calcul_hash(table_lex[k].contenue);
	if (res==res2)
	{  trouve=1;
	table_lex[k].suiv=i;		
	}
	
	}while (trouve==0 && k>0);	

	}


	
	}

		}
}


void init_tab_lex(){

  remplissage_tab_lex("int");
   remplissage_tab_lex ("float");
   remplissage_tab_lex("bool");
   remplissage_tab_lex("char");
	}



void affichage_tab_lex(){
	int i;

	printf("\nTable de Lexemes:\n\n");

	printf("num:	|long:	|lexeme:			|suiv:	\n");
	for ( i = 0 ;(i<NB_ELEM ) ;i++)
		{	 if (table_lex[i].numlex!=-1)
			{
			
	
			printf("%d:    ",table_lex[i].numlex);
			printf("%3d	|%10s			|%3d	\n",
			table_lex[i].longeur,table_lex[i].contenue,table_lex[i].suiv );	
			}

		}
}	


int remplissage_tab_lex(char* ch){
int i;

if (existe_lex(ch)==-1)
{ 
	

	table_lex[NB_ELEM].numlex=NB_ELEM;
	table_lex[NB_ELEM].longeur=strlen(ch);
	table_lex[NB_ELEM].contenue=ch;	
	table_lex[NB_ELEM].suiv=-1;
NB_ELEM++;
}

return NB_ELEM;
}

int existe_lex(char* ch){
int i,ret;
for ( i = 0 ;(i<NB_ELEM ) ;i++)
		{
	ret=strcmp(ch,table_lex[i].contenue);
	if(ret==0)
	return table_lex[i].numlex;
		}
return -1;
}




/************** TABLE DE REPRESENTATION DES TYPES ET DES ENTETE DE SOUS PROGRAMMES ************************/
/*
void init_table_representation()
{
  int i;
  for (i = 0; i < TAILLE_TABLE_REPRESENTATION; i++)
    table_representation[i] = 0;
}

void afficher_table_representation()
{
  int i;
  printf("\n\nTABLE DE REPRESENTATION DES TYPES ET ENTETE DE SOUS PROGRAMMES\n");
  printf("--------------------------------------------------------------\n");
  for (i = 0; i < compteur_table_representation; i++)
    {
      printf("+ --- +\n");
      printf("| %d  |\n", table_representation[i]);
      printf("+ --- +\n");
    }
}

void inserer_table_representation_aux (char valeur[LONGUEUR_LEXEME_MAX])
{
  strcpy(table_representation_aux[compteur_table_representation_aux++], valeur);
}

void inserer_table_representation (char valeur[LONGUEUR_LEXEME_MAX])
{
  int num_lex;
  if (strcmp(valeur, "struct") == 0)
    index_taille = compteur_table_representation++;
  
  else if (strcmp(valeur, "proc") == 0)
    table_representation[compteur_table_representation++] = 0;

  else if (strcmp(valeur, "array") == 0)
    {
      index_taille = compteur_table_representation++;
      index_type = compteur_table_representation++;
    }

  else if (strcmp(valeur, "func") == 0)
    table_representation[compteur_table_representation++] = 0;

  else if (strcmp(valeur, "fin_struct") == 0)
    {
      table_representation[index_taille] = table_taille[compteur_table_taille++];
    }
  else if (strcmp(valeur, "fin_array") == 0)
    {
      table_representation[index_taille] = table_taille[compteur_table_taille++];
      table_representation[index_type] = existe_lex(table_type[compteur_table_type++]);
    }
  else if (strcmp(valeur, "MV") == 0)
    table_representation[compteur_table_representation++] = -2;
  
  else if ((num_lex = existe_lex(valeur)) >= 0)
    table_representation[compteur_table_representation++] = num_lex;

  else
    table_representation[compteur_table_representation++] = atoi(valeur);
}

void inserer_table_taille()
{
  table_taille[compteur_table_taille_aux++] = taille;
  taille = 0;
}

void inserer_table_type(char *type)
{
  strcpy(table_type[compteur_table_type_aux++], type);
}

void my_itoa(int value, char *arg)
{
  sprintf(arg,"%d", value);
}

*/

/*table de representation*/

int inserer_table_representation(int typ)
{
	table_representation[indice] = typ;
	indice++;
	/*return indice;*/	
	return indice-1;
}

void type_tableau()
{
	case1 = inserer_table_representation(-1);

}
/* pour les borne du tableaux */
int borne_tableau(int typ)
{
  table_representation[case1] = typ;
  return case1;
}

/*
int borne_tableau(int typ)
{representation[case1] = typ;
  return case1;
}
*/

/*
int champs(int typ)
{
 representation[case2] = valeur;
  return case2;
}
*/

//l'affichage
void afficher_table_representation()
{


    int i;
	printf("\ntable de representation des types\n\n");
	for ( i = 0 
		 ;(i < TAILLE_MAXI) && (table_representation[i]!=-1)
		 ;i++)
		{
			printf("|");
			
			printf("%d \t",i);
			printf("|");
			/*les condition juste pour un affichage non decaler*/
			
			if(table_representation[i]<0)
				printf(" %d     |\n",table_representation[i] );	
			
			else
				printf(" %d      |\n",table_representation[i] );

		}
       printf("\n");

}



void nbr_champs()
{
	case2 = inserer_table_representation(-1);
	/*case2 = inserer_table_representation(0);*/
}
/*
void nbr_champs()
{
	case2 = inserer_table_representation(0);
}
*/
/*
void nbr_champs()
{
	case1 = inserer_table_representation(0);
}
*/

int champs(int typ)
{
  table_representation[case2] = typ;
  return case2;
}



