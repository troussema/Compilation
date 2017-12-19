%union {
    struct arb *type1;
    int val1;
 }
%type <val1> un_champ type_simple un_param nom_type variable IDF CSTCHAR CSTSTRING CSTINT CSTFLOAT
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

 
 
 
 

%}

%%
programme            : liste_def PROG corps
                     | PROG corps 
                     ;

liste_def	     : DEFINE 
                     | liste_def DEFINE 
		     ;
		     ;
corps                : liste_instructions 
	             | liste_declarations liste_instructions  
	             ;
liste_declarations   : declaration
		     | liste_declarations declaration
                     ;
liste_instructions   : BEGIN2 suite_liste_inst END 
		     ;
suite_liste_inst     : instruction 
		     | liste_declarations suite_liste_inst
                     | suite_liste_inst instruction 
		     ;
declaration          : declaration_type 
	             | declaration_variable PVIRG
	             | declaration_procedure 
	             | declaration_fonction 
	             ;
declaration_type     : TYPE variable DP STRUCT {
                      champs_structure = 0;
                           nbr_champs();
		     } liste_champs {
                         champs(champs_structure);
		       } ENDSTRUCT  

		       | TYPE variable DP ARRAY {
                              champs_tableau = 0;
	                      type_tableau();
                              nbr_champs();
			 }  dimension {
                                  champs(champs_tableau);
			    }  OF nom_type {
                                borne_tableau($9);
		     }  PVIRG  
dimension             : CO liste_dimensions CF
		      ;
liste_dimensions      : une_dimension {champs_tableau++;}
		      | liste_dimensions VIRG une_dimension {champs_tableau++;}
 		      ;
		      ;
une_dimension         : CSTINT PP CSTINT {
                         
                           inserer_table_representation($1);//CSTINT 
                           inserer_table_representation($3);//CSTINT 
                       } 
		      ;
liste_champs          : un_champ  PVIRG {champs_structure++;} 
                      | liste_champs un_champ PVIRG {champs_structure++;} 
		      ;
un_champ              : IDF DP nom_type {
                            
                          inserer_table_representation($1);//variable
                        inserer_table_representation($3);//nom_type
//Machine virtuel                            
inserer_table_representation(-2);//Machine virtuel
                           
                          }
		      ;
nom_type              : type_simple  
		      | variable 
		      ;
/*les $$ comme l'exemple du td int 0 et float 1 ...*/
type_simple           : INT {$$=0;}    
	              | FLOAT {$$=1;}  
	              | BOOL {$$=2;}   
		      | CHAR {$$=3;}   
		      | STRING CO CSTINT CF {$$=4;}   
		      ;
declaration_variable  : VAR variable DP nom_type   
                      | VAR variable DP nom_type AFF const 
		      ; 
declaration_procedure : PROCEDURE {
                       nombre_parametres=0; /*initialiser le nbr de parametre*/
                           nbr_champs();
		      } variable liste_parametres {
champs(nombre_parametres);
              } corps 
		      ;
declaration_fonction  : FUNCTION {
                           nombre_parametres=0; /*initialiser le nbr de parametre*/
                           nbr_champs();
                           type_tableau();
                       } variable liste_parametres RETURN type_simple {
                           borne_tableau($6);
                           champs(nombre_parametres);
                       }
corps 
		      ;
liste_parametres      : 
		      | PO liste_param PF
		      ;

liste_param           : un_param {nombre_parametres++;}
           	      | liste_param {nombre_parametres++;}   VIRG un_param 
		      ;
un_param              : variable DP type_simple {
	                    inserer_table_representation($1);//variable
                        inserer_table_representation($3);//nom_type
}
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
appel                 : variable liste_arguments
		      ;
ecrire                : WRITE PO CSTSTRING liste_args_ecrire PF
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
affectation           : variable egal expression 
		      ;
egal                  : AFF
                      ;
variable              : IDF  
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
                      | e PLUS e1  {/* $$=concat_pere_fils(creer_noeud(AA_PLUS,-1,-1),concat_pere_frer($1,$3)); */}
                      | e MINUS e1 {/* $$=concat_pere_fils(creer_noeud(AA_MINUS,-1,-1),concat_pere_frer($1,$3)); */}
                      ;
e1                    : e2 
                      | e1 MULT e2 
                      | e1 DIV e2 
                      | e1 MOD e2
                      ;
e2                    : PO e PF 
                      | CSTINT {/* $$=creer_noeud(AA_INT,$1,-1); */}
                      | variable 
		      | appel
		      | CSTFLOAT {/* $$=creer_noeud(AA_FLOAT,$1,-1); */}
                      | booleen {/* $$=creer_noeud(AA_BOOL,$1,-1); */}
                      ;

const: 	            CSTINT {/* $$=creer_noeud(AA_INT,$1,-1); */}
		    |CSTFLOAT {/*$$=creer_noeud(AA_FLOAT,$1,-1); */}
		    |CSTCHAR {/* $$=creer_noeud(AA_CHAR,$1,-1); */}
		    |CSTSTRING {/* $$=creer_noeud(AA_STRING,$1,-1); */}
		    |booleen 	{/* $$=creer_noeud(AA_BOOL,$1,-1); */}
		    ;
%%
int main(void){
	
	init_tab_lex();
	yyparse();
	init_tab_hash();
	
	affichage_tab_lex();

	afficher_table_representation();
	


	return 0;
}

