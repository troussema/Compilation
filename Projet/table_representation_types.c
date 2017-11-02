#include <stdlib.h>
#include <stdio.h>

#define TAILLE_MAX 1000 /* c'est gratuit */
#define MV -2  /* Solo ;) */ 

int table_representation_types[TAILLE_MAX];
/*Variables a donner*/
int code_type;/* le code du type A donner par le Chef Ouss */
int contenue_type; /*A donner par le chef Solo*/
int pointeur; /*Statique donc a nous de faire un pointeur */

/*commencant par le plus simple 
	l'initialisation de la table
		comme ça je commite ce soir
*/

void initialisation_table(){
	int i;
	for ( i = 0; i < TAILLE_MAX; i++)
	{
		table_representation_types[i]=-1;/*les autre numeron
										   on a besoin sauf les moins*/
	}
}

void affichage_table(){
	int i;
	for ( i = 0 
		 ;(i < TAILLE_MAX) && (table_representation_types[i]!=-1)
		 ;i++)
		{
			printf("%d ----\t",i);
			printf("--");
			printf(" %d\n",table_representation_types[i] );	
			

		}
}	

/*Remplissage de la table de representation type par les donner*/

void remplissage_table(int contenue_type, int code_type){
      table_representation_types[pointeur]=contenue_type;
      pointeur++;
      table_representation_types[pointeur]= code_type;
      pointeur++;
      table_representation_types[pointeur]= code_type;
      pointeur++;
      table_representation_types[pointeur]= MV;
      pointeur++;
}

/*Juste pour le test*/

int main(int argc, char const *argv[])
{
	/* code */
	printf("\nTable de representation des types\n\n");
	printf("Il manque les donnees lexem a definire plus tard\n\n");
	initialisation_table();
	remplissage_table(contenue_type, code_type);
	affichage_table();
	printf("\n\n");
	return 0;
}
