%token PROG BEGIN2 END EMPTY PVIRG VIRG VAR TYPE STRUCT ENDSTRUCT ARRAY OF PROCEDURE FUNCTION RETURN WRITE READ FOR WHILE DO IF THEN ELSE ELSEIF 
%token INT FLOAT CHAR STRING BOOL TRUE FALSE EQUAL NEQUAL LESS LESSEQ GREATER GREATEREQ OR AND 
%token PLUS MINUS MULT DIV MOD POW 
%token PO PF CO CF PP DP AFF
%token CSTINT CSTFLOAT CSTSTRING 
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
liste_declarations   : declaration
		     | liste_declarations PVIRG declaration
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
	              | RETURN resultat_retourne PVIRG
		      ;
resultat_retourne     :
		      | expression
		      ;	
appel                 : IDF liste_arguments
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
                        ELSE  liste_instructions
                      ;
tant_que              : WHILE expression DO liste_instructions
                      ;
affectation           : variable egal expression
		      ;
egal                  : AFF
                      ;
variable              : IDF
                      ;
concatenation         : CSTSTRING PLUS expression
                      | expression PLUS CSTSTRING
                      | CSTSTRING PLUS CSTSTRING
                      ;
expression            : e_test {printf("\n");}
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
                      | e PLUS e1 {printf("+");}
                      | e MINUS e1 {printf("-");}
                      ;
e1                    : e2
                      | e1 MULT e2 {printf("*");}
                      | e1 DIV e2 {printf("/");}
                      | e1 MOD e2
                      ;
e2                    : PO e PF 
                      | CSTINT {printf("(%d) ",$1);}
                      | variable
		      | appel
		      | CSTFLOAT
                      ;
%%
