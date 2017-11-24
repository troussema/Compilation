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



arbre creer_noeud(int nat,int numl,int numd)
{

arbre a=(arbre )malloc(sizeof(arb));
  a->nature=nat;
  a->numlex=numl;
  a->numdecl=numd;
  a->frer=NULL;
  a->fils=NULL;
 
  return a;

}



void concat_pere_frer(arbre a1, arbre a2)
{


a1->frer=a2;
a1->fils=NULL;

a2->frer=a1;
a2->fils=NULL;

} 

void concat_pere_fils(arbre a1, arbre a2)
{
a1->frer=NULL;
a1->fils=a2;

a2->frer=NULL;
a2->fils=NULL;



} 

void affichage_test(arbre a)
{

if (a!=NULL)
{

 
affichage_test(a->fils);
printf("nature: %d \n",a->nature);
printf("valeur: %d \n",a->numlex);
printf("valeur: %d \n",a->numdecl);

affichage_test(a->frer);
}

}


arbre creer_node_cstint(int numl, int numd){
	arbre aa=creer_noeud(AA_CSTINT,numl,numd);
	  return aa;
	}

arbre creer_node_cstfloat(int numl, int numd){
	arbre aa=creer_noeud(AA_CSTFLOAT,numl,numd);
	  return aa;
	}
arbre creer_node_cstbool(int numl, int numd){
	arbre aa=creer_noeud(AA_CSTBOOL,numl,numd);
	  return aa;
	}
arbre creer_node_cstchar(int numl, int numd){
	arbre aa=creer_noeud(AA_CSTCHAR,numl,numd);
	  return aa;
	}
arbre creer_node_cststring(int numl, int numd){
	arbre aa=creer_noeud(AA_CSTSTRING,numl,numd);
	  return aa;
	}


int main()
{

arbre aa=creer_noeud(5,1,12);
arbre afils=creer_noeud(3,12,10);
arbre afrer=creer_noeud(4,40,16);

concat_pere_fils(aa,afils);
//concat_pere_frer(afils,afrer);


affichage_test(aa);

}
