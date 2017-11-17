/*-------------------------------------------------------------------------------
 *                                                                              *
 * Module contenant les fonctions pour gerer la table des declarations          *
 *                                                                              *
 * Auteur: SOLOFO RABONARIJAONA                                                 *
 *                                                                              *
 * Historique:                                                                  *
 *     - Creation le 03/11/17  par S.RABONARIJAONA                              *      - Modification le 05/11/17 par S.RABONARIJAONA
 *                                                                              *
 *------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_declaration.h"


int compteur_table_debordement = OFFSET_DEBORDEMENT;
declaration table_declaration[TAILLE_TABLE_DECLARATION];
int compteur_description_type_entete = 0;
int compteur_table_declaration_aux = 0;
declaration_aux table_declaration_aux[TAILLE_TABLE_DECLARATION];


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


/* ----------------------------- TABLE LEXICOGRAPHIQUE ----------------- */


structlex table_lex[TAILLE_MAX];


//tableau de has 
int tab_hash[31];

void init_tab_hash(){
	for ( int i = 0; i <=31; i++)
	tab_hash[i]=-1;
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

for ( i = 0; i < TAILLE_MAX; i++)
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
int i;
	for ( i = 0; i < TAILLE_MAX; i++)
	{
	table_lex[i].numlex=-1;
	table_lex[i].longeur=-1;
	table_lex[i].contenue="vide";
	table_lex[i].suiv=-1;
	}
	//init des types binaires
	//int
	table_lex[0].numlex=0;
	table_lex[0].longeur=strlen("int");
	table_lex[0].contenue="int";
	table_lex[0].suiv=-1;
	//float
	table_lex[1].numlex=1;
	table_lex[1].longeur=strlen("float");
	table_lex[1].contenue="float";
	table_lex[1].suiv=-1;
	//bool
	table_lex[2].numlex=2;
	table_lex[2].longeur=strlen("bool");
	table_lex[2].contenue="bool";
	table_lex[2].suiv=-1;
	//char
	table_lex[3].numlex=3;
	table_lex[3].longeur=strlen("char");
	table_lex[3].contenue="char";
	table_lex[3].suiv=-1;
	//string
	table_lex[4].numlex=4;
	table_lex[4].longeur=strlen("string");
	table_lex[4].contenue="string";
	table_lex[4].suiv=-1;
}



void affichage_tab_lex(){
	int i;

	printf("\nTable de Lexemes:\n\n");

	printf("num:	|long:	|lexeme:			|suiv:	\n");
	for ( i = 0 ;(i<TAILLE_MAX ) ;i++)
		{	 if (table_lex[i].numlex!=-1)
			{
			
	
			printf("%d:    ",table_lex[i].numlex);
			printf("%3d	|%10s			|%3d	\n",
			table_lex[i].longeur,table_lex[i].contenue,table_lex[i].suiv );	
			}

		}
}	


void remplissage_tab_lex(char* ch,int n){
int i;
	//printf("ici:%s %d\n",ch,n);
	table_lex[n].numlex=n;
	table_lex[n].longeur=strlen(ch);
	table_lex[n].contenue=ch;	
	table_lex[n].suiv=-1;


}

int existe_lex(char* ch){
int i,ret;
for ( i = 0 ;(i<TAILLE_MAX ) ;i++)
		{
	ret=strcmp(ch,table_lex[i].contenue);
	if(ret==0)
	return table_lex[i].numlex;
		}
return -1;
}

char* effaceespace(char* ch)
{
 
  int i;
  int j = -1;
  for (i = 0; ch[i]; i++)
    if (ch[i] != ' ')
        ch[++j] = ch[i];
  ch[++j] = '\0';
 
  return ch;
}
