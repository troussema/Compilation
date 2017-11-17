#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*marche pas encore*/

typedef struct arb
{
int nature;
int valeur;
struct arb * frer;
struct arb * fils;

}arbre;

arbre *creer_noeud(int nat,int val)
{

arbre *a=(arbre *)malloc(sizeof(arbre));
 
  a->nature=nat;
  a->valeur=val;
  a->frer=NULL;
  a->fils=NULL;
 
  return a;

}



void concat_pere_frer(arbre *a1, arbre *a2)
{
a1->frer=a2;
a1->fils=NULL;

a2->frer=a1;
a2->fils=NULL;

} 

void concat_pere_fils(arbre *a1, arbre *a2)
{
a1->frer=NULL;
a1->fils=a2;

a2->frer=NULL;
a2->fils=NULL;


} 

void affichage_test(arbre *a)
{

if (a!=NULL)
{

 
affichage_test(a->fils);
printf("nature: %d \n",a->nature);
printf("valeur: %d \n",a->valeur);
affichage_test(a->frer);
}



}


int main()
{

arbre *aa=creer_noeud(5,-999);
arbre *afils=creer_noeud(3,12);
arbre *afrer=creer_noeud(4,40);

concat_pere_fils(aa,afils);
//concat_pere_frer(afils,afrer);


affichage_test(aa);

}
