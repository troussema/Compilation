#ifndef TABLE_DECLARATION_H

#define TABLE_DECLARATION_H
#define TAILLE_TABLE_DECLARATION 40
#define OFFSET_DEBORDEMENT 20
#define LONGUEUR_LEXEME_MAX 100
#define FAUX 0
#define VRAI 1


enum Nature{
  TYPE_SIMPLE, 			/* les types simples : int bool float ... */
  TYPE_STRUCT,			
  TYPE_ARRAY,
  TYPE_VAR,
  TYPE_FUNC,
  TYPE_PROC
};

    int indice = 0;
int case1 = 0,case2 = 0;
    #define TAILLE_MAXI 30
typedef struct {/* structure de la table des déclarations */
  int index;
  char lexeme[LONGUEUR_LEXEME_MAX];
  int nature;
  int suivant;
  int region;
  int description;
  int execution;
  int a_ete_insere;
}declaration;
typedef struct {
  char lexeme[LONGUEUR_LEXEME_MAX];
  int nature;
}declaration_aux;

/* typedef struct{ */
/*   int valeur; */
/*   char lexeme[LONGUEUR_LEXEME_MAX]; */
/* }description; */


int compteur_table_debordement = OFFSET_DEBORDEMENT;
declaration table_declaration[TAILLE_TABLE_DECLARATION];
int compteur_description_type_entete = 0;
int compteur_table_declaration_aux = 0;
declaration_aux table_declaration_aux[TAILLE_TABLE_DECLARATION];
/* description table_description[TAILLE_TABLE_DECLARATION]; */
/* int compteur_table_description = 0; */
/* int description = 0; */


/* déclaration des fonctions  */

/* =========== Insere un lexeme dans la table declaration auxiliaire ====== */
void inserer_aux(char lexeme[LONGUEUR_LEXEME_MAX], int nature);
/* =========== Insere une ligne dans la table ========== */
void inserer(char lexeme[LONGUEUR_LEXEME_MAX], int nature, int region, int description, int execution);
/* ============ modifier le champ suivant d'une declaration ============== */
void modifier_suivant(int index, int new_suivant);
/* ============= affiche la table à la sortie standard =============== */
void afficher_table();
/* =========== Initialise la table (insere les types simples) ======== */
void init_table();


/* --------------------  TABLE LEXICOGRAPHIQUE----------------------------- */

#define TAILLE_MAX 1000 

typedef struct
{
	int numlex;
	int longeur;
	char *contenue;
	int suiv;
} structlex;

int nb_lex=5; //car il y'a avant des types binaires (int,float,bool,char,string)
int nb_tab=5;
char *tab_l[TAILLE_MAX]={"vide"};

/* déclaration des fonctions  */
void init_tab_hash();
int calcul_hash();
void remplissage_tab_hash();

void init_tab_lex();
void affichage_tab_lex();
int remplissage_tab_lex(char* ch);

int existe_lex(char* ch);
char* effaceespace(char* ch);


/**** TABLE DES REPRESENTATION DES TYPES ET ENTETE DE SOUS PROGRAMME ****/

#define TAILLE_TABLE_REPRESENTATION 100
//int table_representation[TAILLE_TABLE_REPRESENTATION];
//char table_representation_aux[TAILLE_TABLE_REPRESENTATION][100];
int compteur_table_representation_aux = 0;
int compteur_table_representation = 0;
int index_taille = 0;
int table_taille[50];
int compteur_table_taille = 0;
int compteur_table_taille_aux = 0;
int taille = 0;
int index_type = 0;
char table_type[50][100];
int compteur_table_type = 0;
int compteur_table_type_aux = 0;
char sup[100];
char inf[100];
int table_representation[TAILLE_MAX] = {-1};	
void afficher_table_representation();
int inserer_table_representation(int valeur);
void nbr_champs();
int champs(int valeur);
void type_tableau();
int borne_tableau(int valeur);
/*
void inserer_table_representation_aux (char valeur[LONGUEUR_LEXEME_MAX]);
void inserer_table_representation (char valeur[LONGUEUR_LEXEME_MAX]);
void afficher_table_representation();
void init_table_representation();
void inserer_table_taille();
void inserer_table_type(char *type);
void my_itoa(int value, char *arg);
void inserer_table_declaration (int type, char lex[LONGUEUR_LEXEME_MAX]);
*/

#endif
