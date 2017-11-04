#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAILLE_MAX 1000 

typedef struct structlex 
{
	int numlex;
	int longeur;
	char *contenue;
	int suiv;
} structlex;

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
	
	}while (trouve=0 && k>0);	

	}


	
	}

		}
}

/*
void remplissage_tab_hash(){
int i,j,k,trouve=0,res,res2;
	for ( i = 0; i < TAILLE_MAX; i++)
	{ 	
	res=0; res2=0; k=0;

	if (table_lex[i].numlex!=-1)
	{ 
//on calcule le hash code
	res=calcul_hash(table_lex[i].contenue);
	printf("ici:%d\n",res);
	
	if (tab_hash[res]==-1)
	{
	tab_hash[res]=table_lex[i].numlex;
	}	
	else
		{
	k=i;
	
	
		}	
	

	}	



	
}
*/
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
	return 1;
		}
return 0;
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


int main_tab_lex()
{

}
