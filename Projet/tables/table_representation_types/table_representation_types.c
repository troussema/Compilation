#include <stdlib.h>
#include <stdio.h>
#include "table_representation_types.h"





int inserer_table_representation(int typ)
{
	table_representation[indice_ajout] = typ;
	indice_ajout++;
	return indice_ajout-1;
}

void type_tableau()
{
	case1 = inserer_table_representation(-1);

}

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
void afficher_table_representation()
{


    int i;
	printf("\ntable de representation des types\n\n");
	for ( i = 0 
		 ;(i < TAILLE_MAX) && (table_representation[i]!=-1)
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
}

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






