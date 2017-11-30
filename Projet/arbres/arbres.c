/*-------------------------------------------------------------------------------
 *                                                                              *
 * Module 							                *
 *                                                                              *
 * Auteur: TRABELSI Oussema                                                	*
 *                                                                              *
 *                                                 			        *
 *                                                                              *
 *------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbres.h"

/*marche pas encore*/



arbre creer_noeud(int nat,int numl,int numd,char *lex)
{

arbre a=(arbre )malloc(sizeof(arb));
  a->nature=nat;
  a->numlex=numl;
  a->numdecl=numd;
  a->lexeme=lex;
  a->frer=NULL;
  a->fils=NULL;
 
  return a;

}


	
arbre concat_pere_frer(arbre a1, arbre a2)
{


a1->frer=a2;
//a1->fils=NULL;

//a2->frer=a1;
//a2->fils=NULL;
return a1;
} 

arbre concat_pere_fils(arbre a1, arbre a2)
{
//a1->frer=NULL;
a1->fils=a2;

//a2->frer=NULL;
//a2->fils=NULL;

return a1;

} 

arbre creer_node_cstint(int numl, int numd){
	arbre aa=creer_noeud(AA_CSTINT,numl,numd,"csti");
	  return aa;
	}

arbre creer_node_cstfloat(int numl, int numd){
	arbre aa=creer_noeud(AA_CSTFLOAT,numl,numd,"cstf");
	  return aa;
	}
arbre creer_node_cstbool(int numl, int numd){
	arbre aa=creer_noeud(AA_CSTBOOL,numl,numd,"cstb");
	  return aa;
	}
arbre creer_node_cstchar(int numl, int numd){
	arbre aa=creer_noeud(AA_CSTCHAR,numl,numd,"cstc");
	  return aa;
	}
arbre creer_node_cststring(int numl, int numd){
	arbre aa=creer_noeud(AA_CSTSTRING,numl,numd,"cstc");
	  return aa;
	}






/*AFFICHAGE*/



/* AFFICHAGE dans lordre 
void inorder(arbre a)
{
	if(a == NULL)
		return ;

	
	inorder(a->fils);
	printf(" --> %d\n",a->nature );
	inorder(a->frer);

}
*/

char *rech_nature(int i)
{ char * nat;
	nat="inconnu";

if (i==100){ nat="AA_PLUS";}
if (i==101){ nat="AA_MINUS";}
if (i==102){ nat="AA_MULT";}
if (i==103){ nat="AA_DIV";}
if (i==104){ nat="AA_MOD";}
if (i==105){ nat="AA_POW";}


if (i==0){ nat="AA_INT";}
if (i==1){ nat="AA_FLOAT";}
if (i==2){ nat="AA_BOOL";}
if (i==3){ nat="AA_CHAR";}
if (i==4){ nat="AA_STRING";}

if (i==5){ nat="AA_GREATER";}
if (i==6){ nat="AA_LESS ";}
if (i==7){ nat="AA_EQUAL";}
if (i==8){ nat="AA_NEQUAL";}
if (i==9){ nat="AA_GREATEREQ";}
if (i==10){ nat="AA_LESSQ";}
if (i==11){ nat="AA_AND";}
if (i==12){ nat="AA_OR";}

if (i==13){ nat="AA_IF";}
if (i==14){ nat="AA_THEN ";}
if (i==15){ nat="AA_ELSE";}
if (i==16){ nat="AA_ELSEIF";}
if (i==17){ nat="AA_WHILE";}
if (i==18){ nat="AA_DO";}
if (i==19){ nat="AA_FOR";}


if (i==20){ nat="AA_AFF";}

if (i==21){ nat="AA_CSTINT";}
if (i==22){ nat="AA_CSTFLOAT";}
if (i==23){ nat="AA_CSTBOOL";}
if (i==24){ nat="AA_CSTCHAR";}
if (i==25){ nat="AA_CSTSTRING";}

if (i==26){ nat="AA_FUNCTION";}
if (i==27){ nat="AA_PROCEDURE";}
if (i==28){ nat="AA_RETURN";}


if (i==29){ nat="AA_WRITE";}
if (i==30){ nat="AA_READ";}

if (i==31){ nat="AA_EMPTY";}

if (i==32){ nat="AA_IDF";}
if (i==33){ nat="AA_ARRAY";}
if (i==34){ nat="AA_LISTE";}
if (i==35){ nat="AA_DEFINE";}
if (i==36){ nat="AA_STRUCT";}
if (i==37){ nat="AA_CALL";}



return nat;

}

void padding ( char ch, int n ){
  int i;
  
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void affichage( arbre a, int niveau ){
 
  
  if ( a == NULL ) {
    padding ( '\t', niveau );
    padding ( '\t', niveau );
    puts ( "\t\t~" );
  } else {
    affichage ( a->frer, niveau + 1 );
    padding ( '\t', niveau );
    padding ( '\t', niveau );
//ici on va afficher la nature 

char *nat=rech_nature(a->nature);

//affichage avec numlex et numdeclaration
	if (strcmp(nat,"AA_IDF")==0)
{
   printf ( "(%s)|%d|%d|{%s}\n", nat,a->numlex,a->numdecl,a->lexeme );
}
else {
printf ( "(%s)|%d|%d\n", nat,a->numlex,a->numdecl );
}

	//printf ( "(%s)", nat);

    affichage ( a->fils, niveau + 1 );
  }

}


//----------

int mainarbres()
{
/*
arbre aa=creer_noeud(5,1,12);
arbre afils=creer_noeud(3,12,10);
arbre afrer=creer_noeud(101,40,16);
arbre afrer2=creer_noeud(25,25,25);
arbre afrer3=creer_noeud(2,2,2);

concat_pere_frer(aa,afrer);
concat_pere_fils(aa,afils);
concat_pere_frer(afrer,afrer2);
concat_pere_frer(afrer2,afrer3);


affichage(aa,1);
*/
}
