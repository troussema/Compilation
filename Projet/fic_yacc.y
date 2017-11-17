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
#include "tables/table_declaration.h"
#include "tables/table_declaration.c"
#include "tables/table_representation_types/table_representation_types.c"  
  /*icluuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuur

fffffffffffffffffffff


*/
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
			                      
                            
                            
                          }  ENDSTRUCT  {printf("** %s", $2); inserer_aux($2, TYPE_STRUCT);
}
                     | TYPE variable DP ARRAY {		
                            champs_tableau = 0;
			                      type_tableau();
                            nbr_champs();

                          }  dimension {
                            champs(champs_tableau);
			      
                          }  OF nom_type {
			                   
                          borne_tableau(champs_tableau);
                          
                         
                          
                        }  PVIRG  {printf("** %s", $2); inserer_aux($2, TYPE_ARRAY);}
		     ;
dimension             : CO liste_dimensions CF
		      ;
liste_dimensions      : une_dimension {champs_tableau++;}
		      | liste_dimensions VIRG une_dimension {champs_tableau++;}
		      ;
une_dimension         : CSTINT PP CSTINT {
                         
                            inserer_table_representation($1); //CSTINT
                            inserer_table_representation($3); //CSTINT
                          }
		      ;
liste_champs          : un_champ  PVIRG {champs_structure++;}
| liste_champs un_champ PVIRG {champs_structure++;}
		      ;
un_champ              : variable DP nom_type {
                            
                            inserer_table_representation($1);//variable
                            inserer_table_representation($3);//nom_type
//Machine virtuel                            
inserer_table_representation(-2);//Machine virtuel
                           
                          }
		      ;
nom_type              : type_simple
		      | variable
		      ;
type_simple           : INT  {$$=0;}  
	              | FLOAT  {$$=1;}
	              | BOOL  {$$=2;}
		      | CHAR  {$$=3;}
		      | STRING CO CSTINT CF  {$$=4;}
		      ;
declaration_variable  : VAR variable DP nom_type   { printf("** %s",$2);inserer_aux($2, TYPE_VAR);

		     }
                      | VAR variable DP nom_type AFF const {printf("** %s", $2);inserer_aux($2, TYPE_VAR);}
		      ;
declaration_procedure : PROCEDURE variable liste_parametres corps {printf("** %s", $2); inserer_aux($2, TYPE_PROC);}
		      ;
declaration_fonction  : FUNCTION variable liste_parametres RETURN type_simple
                            corps {printf("** %s", $2); inserer_aux($2, TYPE_FUNC);}
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
variable              : IDF {tab_l[nb_tab]=effaceespace($1);nb_tab++; printf("( %s )", $1); $$ =effaceespace($1); num_lexeme=$1;} 
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
                      | e PLUS e1 
                      | e MINUS e1 
                      ;
e1                    : e2
                      | e1 MULT e2 
                      | e1 DIV e2 
                      | e1 MOD e2
                      ;
e2                    : PO e PF 
                      | CSTINT 
                      | variable
		      | appel
		      | CSTFLOAT
                      | booleen
                      ;

const: 	            CSTINT
		    |CSTFLOAT
		    |CSTCHAR
		    |CSTSTRING
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
	
	//exemple pour solo
		
	/* int tst=existe_lex("char"); printf("existe: %d\n",tst); */
	/* int tst2=existe_lex("blabla");printf("existe pas: %d\n",tst2); */

      afficher_table_representation();


	return 0;
}

