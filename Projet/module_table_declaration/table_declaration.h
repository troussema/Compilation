/*-------------------------------------------------------------------------------
 *                                                                              *
 * Module contenant les fonctions pour gerer la table des declarations          *
 *                                                                              *
 * Auteur: SOLOFO RABONARIJAONA                                                 *
 *                                                                              *
 * Historique:                                                                  *
 *     - Creation le 03/11/17 par S.RABONARIJAONA                                                  *
 *                                                                              *
 *------------------------------------------------------------------------------*/


#ifndef TABLE_DECLARATION_H

#define TABLE_DECLARATION_H
#define TAILLE_TABLE_DECLARATION 200
#define OFFSET_DEBORDEMENT 100
#define LONGUEUR_LEXEME_MAX 100
#define FALSE 0
#define TRUE 1

enum Nature{
  TYPE_SIMPLE, 			/* les types simples : int bool float ... */
  TYPE_STRUCT,			
  TYPE_ARRAY,
  VAR,
  FUNC,
  PROC
};

typedef struct {/* structure de la table des déclarations */
  int index;
  char lexeme[100];
  int nature;
  int suivant;
  int region;
  int description;
  int execution;
  int a_ete_insere;
}declaration;


/* déclaration des fonctions  */


/* =========== Insere une ligne dans la table ========== */
void inserer(char *lexeme, int nature, int region, int description, int execution);
/* ============ modifier le champ suivant d'une declaration ============== */
void modifier_suivant(int index, int new_suivant);
/* ============= affiche la table à la sortie standard =============== */
void afficher_table();
/* =========== Initialise la table (insere les types simples) ======== */
void init_table();

#endif
