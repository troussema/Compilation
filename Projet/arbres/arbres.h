#ifndef ARBREH
#define ARBREH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arb
{
int nature;
int numlex;
int numdecl;
struct arb * frer;
struct arb * fils;

}arb;

typedef struct arb  * arbre;

#define AA_PLUS 100
#define AA_MINUS 101
#define AA_MULT 102
#define AA_DIV 103
#define AA_MOD 104
#define AA_POW 105


#define AA_INT 0
#define AA_FLOAT 1
#define AA_BOOL 2
#define AA_CHAR 3
#define AA_STRING 4

 
#define AA_GREATER 5
#define AA_LESS 6
#define AA_EQUAL 7
#define AA_NEQUAL 8
#define AA_GREATEREQ 9
#define AA_LESSEQ 10
#define AA_AND 11
#define AA_OR 12

#define AA_IF 13
#define AA_THEN 14
#define AA_ELSE 15
#define AA_ELSEIF 16
#define AA_WHILE 16
#define AA_DO 17
#define AA_FOR 18

#define AA_AFF 19


#define AA_CSTINT 20
#define AA_CSTFLOAT 21
#define AA_CSTBOOL 22
#define AA_CSTCHAR 23
#define AA_CSTSTRING 24

#define AA_FUNCTION 25
#define AA_PROCEDURE 26
#define AA_RETURN 27



#define AA_WRITE 28
#define AA_READ 29

#define AA_EMPTY 30

#define AA_IDF 31

#define AA_ARRAY 32

#define AA_LISTE 33

#define AA_DEFINE 34

#define AA_STRUCT 35





arbre creer_noeud(int nat,int numl,int numd);
void concat_pere_frer(arbre a1, arbre a2);
void concat_pere_fils(arbre a1, arbre a2);
void affichage_test(arbre a);
arbre creer_node_cstint(int numl, int numd);
arbre creer_node_cstfloat(int numl, int numd);
arbre creer_node_cstbool(int numl, int numd);
arbre creer_node_cstchar(int numl, int numd);
arbre creer_node_cststring(int numl, int numd);

#endif
