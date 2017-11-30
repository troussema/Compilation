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
arbre atest;
 arbre arbreidf;
 arbre tab_a[50];
int ind;

%}

%%
programme            : liste_def PROG corps {printf("1)----nombre de LISTE:%d\n",ind); 
aa=(concat_pere_fils($1,$3));  } 
                     | PROG corps  {$$=$2; aa = $2; }
                     ;
liste_def	     : DEFINE  {$$=creer_noeud(AA_DEFINE,-1,-1,"AA_DEFINE");}
                     | liste_def DEFINE  { $$=concat_pere_frer(creer_noeud(AA_DEFINE,-1,-1,"AA_DEFINE"),$1);}
		     ;
		     ;
corps                : liste_instructions {$$ = $1;} 
	             | liste_declarations liste_instructions   {$$=$2;}
	             ;
liste_declarations   : declaration {$$=$1;}
		     | liste_declarations declaration { /*marche pas encore $$=concat_pere_frer(creer_noeud(AA_LISTE,-1,-1,"AA_LISTD"),$1);*/} 
                     ;
liste_instructions   : BEGIN2 suite_liste_inst END { $$ =concat_pere_fils(creer_noeud(AA_LISTE,-1,-1,"AA_LISTE"),$2);tab_a[ind]=aa;ind++; }
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
                      | EMPTY PVIRG {$$ =creer_noeud(AA_EMPTY,-1,-1,"AA_EMPTY");}
                      | ecrire PVIRG
                      | lire PVIRG
	              | RETURN resultat_retourne PVIRG {$$=$2;}
		      ;
resultat_retourne     :
		      | expression
		      ;	
appel                 : variable liste_arguments  {$$=concat_pere_fils(creer_noeud(AA_CALL,-1,-1,"AA_CALL"),$2);}
		      ;
ecrire                : WRITE PO CSTSTRING liste_args_ecrire PF {$$ = concat_pere_fils(creer_noeud(AA_WRITE, -1, -1,"AA_WRITE"), concat_pere_fils(creer_noeud(AA_LISTE,-1,-1,"AA_LISTE"),concat_pere_frer(creer_noeud(AA_CSTSTRING,-1,-1,$3),$4)));}
                      ;
liste_args_ecrire     :
                      | VIRG un_arg {$$=$2;}
		      | liste_args_ecrire VIRG un_arg {$$=concat_pere_frer($3,concat_pere_fils(creer_noeud(AA_LISTE,-1,-1,"AA_LISTE"),$1));}
		      ;
lire                  : READ PO CSTSTRING liste_variable PF {$$ = concat_pere_fils(creer_noeud(AA_READ, -1, -1,"AA_READ"), concat_pere_fils(creer_noeud(AA_LISTE,-1,-1,"AA_LISTE"),concat_pere_frer(creer_noeud(AA_CSTSTRING,-1,-1,$3),$4)));}
                      ;
liste_variable        : VIRG variable {$$=arbreidf;} 
                      | liste_variable VIRG variable {$$=concat_pere_frer(arbreidf	,concat_pere_fils(creer_noeud(AA_LISTE,-1,-1,"AA_LISTE"),$1));}
                      ;
liste_arguments       :PO PF {$$=creer_noeud(-111,-1,-1,"()");}
		      | PO liste_args PF {$$=$2;}
		      ;

liste_args            : un_arg{$$=$1;}
		      | liste_args VIRG un_arg {$$=concat_pere_frer($3,concat_pere_fils(creer_noeud(AA_LISTE,-1,-1,"AA_LISTE"),$1));}
                      |
		      ;	
un_arg                : expression
                      ;
condition             : IF PO expression PF
                        THEN  liste_instructions {$$=concat_pere_fils(creer_noeud(AA_IF,-1,-1,"AA_IF"),concat_pere_frer($3,$6));}
		      | IF PO expression PF
                        THEN  liste_instructions 
                        ELSE  liste_instructions {$$=concat_pere_fils(creer_noeud(AA_IF,-1,-1,"AA_IF"),concat_pere_frer($3,concat_pere_frer($6,$8)));}
                      ;
tant_que              : WHILE PO expression PF DO liste_instructions {$$=concat_pere_fils(creer_noeud(AA_IF,-1,-1,"AA_WHILE"),concat_pere_frer($3,$6));}
                      ;
affectation           : variable egal expression { $$=concat_pere_fils(creer_noeud(AA_AFF,-1,-1,"AA_AFF"), concat_pere_frer(arbreidf,$3)); }
		      ;
egal                  : AFF
                      ;
variable              : IDF { tab_l[nb_tab]=effaceespace($1);nb_tab++; printf("( %s )", $1); $$ =effaceespace($1); num_lexeme=$1;} { arbreidf=creer_noeud(AA_IDF,$1,-1,$1);}
                      ;
concatenation         : CSTSTRING PLUS expression {$$=concat_pere_fils(creer_noeud(AA_CONCAT,-1,-1,"AA_CONCAT"),concat_pere_frer(creer_noeud(AA_CSTSTRING,-1,-1,$1),$3)); }
                      | CSTSTRING PLUS CSTSTRING {$$=concat_pere_fils(creer_noeud(AA_CONCAT,-1,-1,"AA_CONCAT"),concat_pere_frer(creer_noeud(AA_CSTSTRING,-1,-1,$1),creer_noeud(AA_CSTSTRING,-1,-1,$3))); }
                      ;
booleen               : TRUE { $$=creer_noeud(AA_TRUE,$1,-1,"AA_TRUE"); }
                      | FALSE { $$=creer_noeud(AA_FALSE,$1,-1,"AA_FALSE"); }
                      ;
expression            : e_test {$$=$1;}
                      | concatenation {$$=$1;}
                      ;
e_test                : e {$$=$1;}
                      | e_test EQUAL e {$$=concat_pere_fils(creer_noeud(AA_EQUAL,-1,-1,"AA_EQUAL"),concat_pere_frer($1,$3)); }
                      | e_test NEQUAL e{$$=concat_pere_fils(creer_noeud(AA_NEQUAL,-1,-1,"AA_NEQUAL"),concat_pere_frer($1,$3)); }
                      | e_test LESS e{$$=concat_pere_fils(creer_noeud(AA_LESS,-1,-1,"AA_LESS"),concat_pere_frer($1,$3)); }
                      | e_test LESSEQ e{$$=concat_pere_fils(creer_noeud(AA_LESSEQ,-1,-1,"AA_LESSEQ"),concat_pere_frer($1,$3)); }
                      | e_test GREATER e{$$=concat_pere_fils(creer_noeud(AA_GREATER,-1,-1,"AA_GREATEREQ"),concat_pere_frer($1,$3)); }
                      | e_test GREATEREQ e{$$=concat_pere_fils(creer_noeud(AA_GREATER,-1,-1,"AA_GREATEREQ"),concat_pere_frer($1,$3)); }
                      | e_test OR e {$$=concat_pere_fils(creer_noeud(AA_OR,-1,-1,"AA_OR"),concat_pere_frer($1,$3)); }
                      | e_test AND e{$$=concat_pere_fils(creer_noeud(AA_AND,-1,-1,"AA_AND"),concat_pere_frer($1,$3)); }
                      ; 
e                     : e1 {$$=$1;}
                      | e PLUS e1  {$$=concat_pere_fils(creer_noeud(AA_PLUS,-1,-1,"AA_PLUS"),concat_pere_frer($1,$3)); }
                      | e MINUS e1 { $$=concat_pere_fils(creer_noeud(AA_MINUS,-1,-1,"AA_MINUS"),concat_pere_frer($1,$3)); }
                      ;
e1                    : e2 {$$=$1;}
                      | e1 MULT e2 {$$=concat_pere_fils(creer_noeud(AA_MULT,-1,-1,"AA_MULT"),concat_pere_frer($1,$3)); }
                      | e1 DIV e2 {$$=concat_pere_fils(creer_noeud(AA_DIV,-1,-1,"AA_DIV"),concat_pere_frer($1,$3)); }
                      | e1 MOD e2 {$$=concat_pere_fils(creer_noeud(AA_MOD,-1,-1,"AA_MOD"),concat_pere_frer($1,$3)); }
		      | e1 POW e2 {$$=concat_pere_fils(creer_noeud(AA_POW,-1,-1,"AA_POW"),concat_pere_frer($1,$3)); }
                      ;
e2                    : PO e PF {$$=$2;}
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
		    |booleen 	
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
	//chaque begin et end ind++
	printf("2)----nombre de LISTE:%d\n",ind);
	
	

	return 0;
}

