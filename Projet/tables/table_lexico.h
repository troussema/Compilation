#ifndef TABLE_DECLARATION_H

#define TAILLE_MAX 1000 

typedef struct structlex 
{
	int numlex;
	int longeur;
	char *contenue;
	int suiv;
} structlex;

/* déclaration des fonctions  */
void init_tab_hash();
int calcul_hash();
void remplissage_tab_hash();

void init_tab_lex();
void affichage_tab_lex();
void remplissage_tab_lex(char* ch,int n);

int existe_lex(char* ch);
char* effaceespace(char* ch);


#endif
