%{
#include "y.tab.h"
#include <stdio.h>

int num_ligne = 1;
int num_colone = 0;
%}
X [^"]
Y [^"*]
Z [^"*/]
number [0-9]
integer -?{number}+
integer_pos {number}+
float {integer}\.{integer_pos}
%%
[ \n]*\/\*({Y}|\*\**{Z}|\*\**\"{X}*\"|\"{X}*\")*\*\**\/[ \n]* {printf("COMMENTS\n");}
[ \n]*\/\/.*[ \n]* {printf("COMMENTS\n");}
prog[ \n\t]* {printf("PROG "); return (PROG);}
[ \n\t]*begin[ \n\t]* {printf(" BEGIN2 ");return (BEGIN2);}
[ \n\t]*end[ \n\t]* {printf(" END \n");return(END);}
[ \t\n]*empty[ ]* {printf(" EMPTY ");return (EMPTY);}
[ ]*;[ \t\n]* {printf(" PVIRG ");return (PVIRG);}
[ ]*,[ ]* {printf(" VIRG ");return (VIRG);}
[ \n\t]*var[ ]* {printf(" VAR ");return (VAR);}
[ \t\n]*type[ ]* {printf(" TYPE ");return (TYPE);}
[ ]*struct[ \t\n]* {printf(" STRUCT ");return (STRUCT);}
endstruct {printf(" ENDSTRUCT ");return (ENDSTRUCT);}
[ ]*array[ ]* {printf(" ARRAY ");return (ARRAY);}
[ ]*of[ ]* {printf(" OF ");return (OF);}
[ \t\n]*proc[ ]* {printf(" PROC ");return (PROCEDURE);}
[ \t\n]*func[ ]* {printf(" FUNC ");return (FUNCTION);}
[ \t\n]*return[ ]* {printf(" RETURN ");return (RETURN);}
[ \t\n]*write[ ]* {printf(" WRITE ");return (WRITE);}            
[ \t\n]*read[ ]* {printf(" READ ");return (READ);} 
[ \n\t]*for[ \n\t]* {printf(" FOR ");return (FOR);}
[ \n\t]*while[ \n\t]* {printf(" WHILE ");return (WHILE);}
[ \n\t]*do[ \n\t]* {printf(" DO ");return (DO);}
[ \n\t]*if[ \n\t]* {printf(" IF ");return (IF);}
[ \n\t]*then[ \n\t]* {printf(" THEN ");return (THEN);}
[ \n\t]*else[ \n\t]* {printf(" ELSE ");return (ELSE);} 
[ \n\t]*elseif[ \n\t]* {printf(" ELSEIF "); return (ELSEIF);}
[ ]*int[ ]* {printf(" INT ");return (INT);}
[ ]*float[ ]* {printf(" FLOAT ");return (FLOAT);}
[ ]*char[ ]* {printf(" CHAR ");return (CHAR);}
[ ]*string[ ]* {printf(" STRING ");return (STRING);}
[ ]*bool[ ]* {printf(" BOOL ");return (BOOL);}
[ ]*true[ ]* {printf(" TRUE ");return (TRUE);}
[ ]*false[ ]* {printf(" FALSE ");return (FALSE);}
[ ]*==[ ]* {printf(" EQUAL ");return (EQUAL);}
[ ]*\!=[ ]* {printf(" NEQUAL ");return (NEQUAL);}               
[ ]*\<[ ]* {printf(" LESS ");return (LESS);}                   
[ ]*\<=[ ]* {printf(" LESSEQ ");return (LESSEQ);}                 
[ ]*\>[ ]* {printf(" GREATER ");return (GREATER);}                 
[ ]*\>=[ ]* {printf(" GREATEREQ ");return (GREATEREQ);}              
[ ]*\|\|[ ]* {printf(" OR ");return (OR);}                      
[ ]*\&\&[ ]* {printf(" AND ");return (AND);}                    
[ ]*\+[ ]* {printf(" PLUS ");return (PLUS);}                   
[ ]*-[ ]* {printf(" MINUS ");return (MINUS);}                      
[ ]*\*[ ]* {printf(" MULT ");return (MULT);}                      
[ ]*\/[ ]* {printf(" DIV ");return (DIV);}                        
[ ]*\%[ ]* {printf(" MOD ");return (MOD);}                         
[ ]*\^[ ]* {printf(" POW ");return (POW);}                         
[ ]*\([ ]* {printf(" PO ");return (PO);}
[ ]*\)[ ]* {printf(" PF ");return (PF);}
[ ]*\[[ ]* {printf(" CO ");return (CO);}
[ ]*\][ ]* {printf(" CF ");return (CF);}
[ ]*\.\.[ ]* {printf(" PP ");return (PP);}
[ ]*\:[ ]* {printf(" DP ");return (DP);}
[ ]*=[ ]* {printf(" AFF ");return (AFF);}
[ \t]* {printf(" SPACE ");return SPACE;}
[ ]*\'[^\']\'[ ]* {printf(" CSTCHAR ");return (CSTCHAR);}
[ ]*\"[^\"]*\"[ ]* {printf(" CSTSTRING ");return (CSTSTRING);}
[ \t\n]*[A-Za-z](_|[A-Za-z]|[0-9])*[ ]* { printf(" IDF ");yylval = strdup(yytext); return (IDF);}
[ \t]*\n+[ \t]* {printf(" JMP\n");num_ligne++; num_colone = 0; return (JMP);}
[ ]*0|-?[1-9][0-9]*[ ]* {printf(" CSTINT ");yylval = atoi(yytext); return (CSTINT);}
[ ]*{float}[ ]* {printf(" CSTFLOAT "); return (CSTFLOAT);}
[ \t\n]*#define[ ]+[A-Z]+[0-9]*[A-Z]*[ ]+({integer}|{float})[ \t\n]* {printf(" #DEFINE ");return (DEFINE);}
%%
