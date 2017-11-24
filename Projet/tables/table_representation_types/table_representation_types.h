#ifndef TABLE_REPRESENTATION_TYPES_H
#define TABLE_REPRESENTATION_TYPES_H_

    int indice_ajout = 0;
int case1 = 0,case2 = 0;
    #define TAILLE_MAX 20
int table_representation[TAILLE_MAX] = {-1};	
void afficher_table_representation();
int inserer_table_representation(int valeur);
void nbr_champs();
int champs(int valeur);
void type_tableau();
int borne_tableau(int valeur);

#endif /* TABLE_REPRESENTATION_TYPES_H_ */
