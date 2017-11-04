#include <stdlib.h>
#include <stdio.h>



#define TAILLE_MAX 1000 /* c'est gratuit */
#define MV -2  /* Solo ;) */ 


int table_representation_types[TAILLE_MAX];
/*Variables a donner*/
int nombre_champ; /*les champs qui contient le types*/
int num_lexical; /*numero dans la table lexico*/
int num_declaration; /*numero de declaration de type dans 
						la table des declaration*/
int pointeur; /*Statique donc a nous de faire un pointeur */





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
			printf("|");
			
			printf("%d \t",i);
			printf("|");
			/*les condition juste pour un affichage non decaler*/
			
			if(table_representation_types[i]<0)
				printf(" %d     |\n",table_representation_types[i] );	
			
			else
				printf(" %d      |\n",table_representation_types[i] );

		}
}	

/*Remplissage de la table de representation type par les donner*/

void remplissage_table(int nombre_champ, int num_lexical, int num_declaration){

      table_representation_types[pointeur]=nombre_champ;
      pointeur++;

      table_representation_types[pointeur]= num_lexical;
      pointeur++;

      table_representation_types[pointeur]= num_declaration;
      pointeur++;

      table_representation_types[pointeur]= MV;
      pointeur++;
}


/*pour le teste*/

int main(int argc, char const *argv[])
{
	printf("\nTable de representation des types\n\n");

	printf("_________________\n");
	printf("|   i   | descrip|\n");
	printf("|_______|________|\n");

	initialisation_table();
	
	remplissage_table(3,5,0);
	remplissage_table(6,0,5);
	remplissage_table(5,5,3);
	

	affichage_table();

	printf("|_______|________|\n");
	return 0;
	
}
