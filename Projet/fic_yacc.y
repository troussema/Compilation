%token PROG BEGIN2 END EMPTY PVIRG VIRG VAR TYPE STRUCT ENDSTRUCT ARRAY OF PROCEDURE FUNCTION RETURN WRITE READ FOR WHILE DO IF THEN ELSE ELSEIF 
%token INT FLOAT CHAR STRING BOOL TRUE FALSE EQUAL NEQUAL LESS LESSEQ GREATER GREATEREQ OR AND 
%token PLUS MINUS MULT DIV MOD POW 
%token PO PF CO CF PP DP AFF
%token CSTINT CSTFLOAT CSTSTRING CSTCHAR FORMAT
%token JMP SPACE
%token IDF 
%token DEFINE 
%{
#include <stdio.h>
#include "tables/tables.c"
#include "arbres/arbres.c"

#define TAILLE_MAX 1000 

int main();
int yylex();
void yyerror(const char *s);
extern int num_ligne;
extern int num_colone;

/*Pour table de representation*/
 int num_lexeme=0;
 int champs_structure=0;
 int born=0;
 int champs_tableau=0;
 int nombre_parametres=0;

 arbre aa;
 
 arbre arbreidf;
 

%}

%%
programme            : liste_def PROG corps {aa=$3;} 
                     | PROG corps  {aa = $2;}
                     ;

liste_def	     : DEFINE  
                     | liste_def DEFINE  
		     ;
		     ;
corps                : liste_instructions {$$ = $1;} 
	             | liste_declarations liste_instructions   {$$ = $2;}
	             ;
liste_declarations   : declaration
		     | liste_declarations declaration
                     ;
liste_instructions   : BEGIN2 suite_liste_inst END { $$ =concat_pere_fils(creer_noeud(AA_LISTE,-1,-1,"AA_LISTE"),$2); }
		     ;
suite_liste_inst     : instruction 
		     | liste_declarations suite_liste_inst
                     | suite_liste_inst instruction { $$=concat_pere_frer(concat_pere_fils(creer_noeud(AA_LISTE,-1,-1,"AA_LISTE"),$1),$2);}
		     ;
declaration          : declaration_type 
	             | declaration_variable PVIRG
	             | declaration_procedure 
	             | declaration_fonction 
	             ;
declaration_type     : TYPE variable DP STRUCT { inserer_table_representation_aux("struct"); } liste_champs ENDSTRUCT  { printf("** %s", $2); inserer_aux($2, TYPE_STRUCT); inserer_table_taille(); inserer_table_representation_aux("fin_struct");}

| TYPE variable DP ARRAY { inserer_table_representation_aux("array"); } dimension  OF nom_type  PVIRG  {printf("** %s", $2); inserer_aux($2, TYPE_ARRAY); inserer_table_type($8); inserer_table_taille(); inserer_table_representation_aux("fin_array"); }
		     ;
dimension             : CO liste_dimensions CF
		      ;
liste_dimensions      : une_dimension
		      | liste_dimensions VIRG une_dimension
		      ;
une_dimension         : CSTINT PP CSTINT {my_itoa($1, inf); my_itoa($3, sup); inserer_table_representation_aux(inf); inserer_table_representation_aux(sup); taille++;}
		      ;
liste_champs          : un_champ  PVIRG {inserer_table_representation_aux("MV");}
                      | liste_champs un_champ PVIRG {inserer_table_representation_aux("MV");} 
		      ;
un_champ              : variable DP nom_type {inserer_table_representation_aux($1); inserer_table_representation_aux($3); taille++; }
		      ;
nom_type              : type_simple  {$$ = $1;}
		      | variable {$$ = $1;}
		      ;
type_simple           : INT   {$$ = "int";}
	              | FLOAT   {$$ = "float";}
	              | BOOL   {$$ = "boolean";}
		      | CHAR   {$$ = "char";}
		      | STRING CO CSTINT CF   {$$ = "string";}
		      ;
declaration_variable  : VAR variable DP nom_type   { printf("** %s",$2);inserer_aux($2, TYPE_VAR);}
                      | VAR variable DP nom_type AFF const {printf("** %s", $2);inserer_aux($2, TYPE_VAR);}
		      ;
declaration_procedure : PROCEDURE variable liste_parametres corps {printf("** %s", $2); inserer_aux($2, TYPE_PROC); inserer_table_representation_aux("proc");}
		      ;
declaration_fonction  : FUNCTION variable liste_parametres RETURN type_simple
corps {printf("** %s", $2); inserer_aux($2, TYPE_FUNC); inserer_table_representation_aux("func");}
		      ;
liste_parametres      : 
		      | PO liste_param PF
		      ;

liste_param           : un_param {nombre_parametres++;}
           	      | liste_param {nombre_parametres++;}  VIRG un_param
		      ;
un_param              : variable DP type_simple 
	 	      ;
instruction           : affectation PVIRG 
	              | condition
	              | tant_que
	              | appel PVIRG
                      | EMPTY PVIRG
                      | ecrire PVIRG
                      | lire PVIRG
	              | RETURN resultat_retourne PVIRG
		      ;
resultat_retourne     :
		      | expression
		      ;	
appel                 : variable liste_arguments {$$=creer_noeud(AA_CALL,-1,-1,-1);}
		      ;
ecrire                : WRITE PO CSTSTRING liste_args_ecrire PF {$$=creer_noeud(AA_WRITE,-1,-1,-1);}
                      ;
liste_args_ecrire     :
                      | VIRG un_arg
		      | liste_args_ecrire VIRG un_arg
		      ;
lire                  : READ PO CSTSTRING liste_variable PF
                      ;
liste_variable        : VIRG variable
                      | liste_variable VIRG variable
                      ;
liste_arguments       : PO liste_args PF
		      ;

liste_args            : un_arg
		      | liste_args VIRG un_arg
                      |
		      ;	
un_arg                : expression
                      ;
condition             : IF PO expression PF
                        THEN  liste_instructions
		      | IF PO expression PF
                        THEN  liste_instructions
                        ELSE  liste_instructions
                      ;
tant_que              : WHILE PO expression PF DO liste_instructions
                      ;
affectation           : variable egal expression { $$=concat_pere_fils(creer_noeud(AA_AFF,-1,-1,"AA_AFF"), concat_pere_frer(arbreidf,$3)); }
		      ;
egal                  : AFF
                      ;
variable              : IDF {tab_l[nb_tab]=effaceespace($1);nb_tab++; printf("( %s )", $1); $$ =effaceespace($1); num_lexeme=$1;} { arbreidf=creer_noeud(AA_IDF,$1,-1,$1);}
                      ;
concatenation         : CSTSTRING PLUS expression
                      | CSTSTRING PLUS CSTSTRING
                      ;
booleen               : TRUE
                      | FALSE
                      ;
expression            : e_test
                      | concatenation
                      ;
e_test                : e 
                      | e_test EQUAL e 
                      | e_test NEQUAL e
                      | e_test LESS e
                      | e_test LESSEQ e
                      | e_test GREATER e
                      | e_test GREATEREQ e
                      | e_test OR e
                      | e_test AND e
                      ; 
e                     : e1 
                      | e PLUS e1  {$$=concat_pere_fils(creer_noeud(AA_PLUS,-1,-1,"AA_PLUS"),concat_pere_frer($1,$3)); }
                      | e MINUS e1 { $$=concat_pere_fils(creer_noeud(AA_MINUS,-1,-1,"AA_MINUS"),concat_pere_frer($1,$3)); }
                      ;
e1                    : e2 {$$=$1;}
                      | e1 MULT e2 
                      | e1 DIV e2 
                      | e1 MOD e2
                      ;
e2                    : PO e PF 
                      | CSTINT { $$=creer_noeud(AA_INT,$1,-1,"int"); }
                      | variable {$$=arbreidf;}
		      | appel {$$=$1;}
		      | CSTFLOAT { $$=creer_noeud(AA_FLOAT,$1,-1,"float"); }
                      | booleen {$$=creer_noeud(AA_BOOL,$1,-1,"bool"); }
                      ;

const: 	            CSTINT { $$=creer_noeud(AA_INT,$1,-1,"int"); }
		    |CSTFLOAT {$$=creer_noeud(AA_FLOAT,$1,-1,"float"); }
		    |CSTCHAR { $$=creer_noeud(AA_CHAR,$1,-1,"char"); }
		    |CSTSTRING { $$=creer_noeud(AA_STRING,$1,-1,"string"); }
		    |booleen 	{ $$=creer_noeud(AA_BOOL,$1,-1,"bool"); }
		    ;
%%
int main(void){
	yyparse();

	init_tab_lex();
	//	initialisation_table_representation();
	
	for (int i=nb_lex;i<nb_tab;i++)
	{ 
	if ((existe_lex(tab_l[i])==-1) )
	remplissage_tab_lex(tab_l[i],i);
	}

	init_tab_hash();
	remplissage_tab_hash();

	init_table();		/* initialisation table declaration */
	/* remplissage table declaration */
	while (compteur_table_declaration_aux >= 0)
	  inserer(table_declaration_aux[compteur_table_declaration_aux].lexeme, table_declaration_aux[compteur_table_declaration_aux--].nature, 9, 9, 9);
	
	affichage_tab_lex();
	afficher_table();	/* afficher table declaration */

	init_table_representation();

	for (int i = 0; i < compteur_table_representation_aux; i++)
	  inserer_table_representation(table_representation_aux[i]);

	afficher_table_representation();

	
	//affichage arbre: 

	affichage(aa,1);

	return 0;
}

