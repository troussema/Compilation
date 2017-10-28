%token PROG BEGIN2 END EMPTY PVIRG VIRG VAR TYPE STRUCT ENDSTRUCT ARRAY OF PROCEDURE FUNCTION RETURN WRITE READ FOR WHILE DO IF THEN ELSE ELSEIF 
%token INT FLOAT CHAR STRING BOOL TRUE FALSE EQUAL NEQUAL LESS LESSEQ GREATER GREATEREQ OR AND 
%token PLUS MINUS MULT DIV MOD POW 
%token PO PF CO CF PP DP AFF
%token CSTINT CSTFLOAT CSTSTRING CSTCHAR FORMAT
%token JMP SPACE
%token IDF
%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);  
extern int num_ligne;
extern int num_colone;
%}
%%
programme            : PROG corps 
                     ;
corps                : liste_instructions
	             | liste_declarations liste_instructions 
	             ;
liste_declarations   : declaration PVIRG
		     | liste_declarations declaration PVIRG
                     ;
liste_instructions   : BEGIN2 suite_liste_inst END
		     ;
suite_liste_inst     : instruction
                     | suite_liste_inst instruction 
		     ;
declaration          : declaration_type 
	             | declaration_variable
	             | declaration_procedure 
	             | declaration_fonction 
	             ;
declaration_type       : TYPE IDF DP suite_declaration_type
		       ;
suite_declaration_type : STRUCT liste_champs ENDSTRUCT
		       | ARRAY dimension OF nom_type
		       ;
dimension             : CO liste_dimensions CF
		      ;
liste_dimensions      : une_dimension
		      | liste_dimensions VIRG une_dimension
		      ;
une_dimension         : expression PP expression 
		      ;
liste_champs          : un_champ
		      | liste_champs PVIRG un_champ
		      ;
un_champ              : IDF DP nom_type
		      ;
nom_type              : type_simple
		      | IDF
		      ;
type_simple           : INT
	              | FLOAT
	              | BOOL
		      | CHAR
		      | STRING CO CSTINT CF
		      ;
declaration_variable  : VAR IDF DP nom_type
		      |VAR IDF DP nom_type AFF const
		      ;
declaration_procedure : PROCEDURE IDF liste_parametres corps
		      ;
declaration_fonction  : FUNCTION IDF liste_parametres RETURN type_simple corps
		      ;
liste_parametres      : 
		      | PO liste_param PF
		      ;

liste_param           : un_param
           	      | liste_param PVIRG un_param
		      ;
un_param              : IDF DP type_simple
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
appel                 : IDF liste_arguments
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
