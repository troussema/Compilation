#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAILLE_MAX 1000 


int table_lex[TAILLE_MAX][3];
char* table_contenue_lex[TAILLE_MAX];



/*Variables a donner*/
//int longeur ;
//int lexeme; 




void init_table(){
	int i;
	for ( i = 0; i < TAILLE_MAX; i++)
	{ 	
		table_lex[i][0]=-1;
		table_lex[i][1]=-1;
		table_lex[i][2]=-1;
		//init de table contenue lex
		table_contenue_lex[i]="vide";

	}
}




void affichage_table(){
	int i,j;

	printf("\nTable de Lexemes:\n\n");

	printf("ind:	|long:	|lexeme:	|suiv:	\n");
	for ( i = 0 ;(i<TAILLE_MAX ) ;i++)
		{	 if (table_lex[i][1]!=-1)
			{
			j=table_lex[i][1];
	
			printf("%d:    ",i);
			printf("%3d	|%5s			|%3d	\n",
			table_lex[i][0],table_contenue_lex[j],table_lex[i][2] );	
			}

		}
}	


void remplissage_table_lexeme(char* ch,int n){
int i,j;
	
	

		table_lex[n][0]=strlen(ch);
		table_lex[n][1]=n;
		table_lex[n][2]=-99;
		//init de table contenue lex
		table_contenue_lex[n]=ch;

      
}



int main_tab_lexeme()
{

}
