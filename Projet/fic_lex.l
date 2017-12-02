%{
#include "y.tab.h"
#include <stdio.h>

int num_ligne = 1;
int num_colone = 0;
int ind=0;
%}
X [^"]
Y [^"*]
Z [^"*/]
number [0-9]
integer -?{number}+
integer_pos {number}+
float {integer}\.{integer_pos}
%%
\/\*({Y}|\*\**{Z}|\*\**\"{X}*\"|\"{X}*\")*\*\**\/ ;
\/\/.* ;
prog { return (PROG);}
begin {return (BEGIN2);}
end  {return(END);}
empty {return (EMPTY);}
\; {return (PVIRG);}
, {return (VIRG);}
var {return (VAR);}
type {return (TYPE);}
struct {return (STRUCT);}
endstruct {return (ENDSTRUCT);}
array {return (ARRAY);}
of {return (OF);}
proc {return (PROCEDURE);}
func {return (FUNCTION);}
return {return (RETURN);}
write {return (WRITE);}            
read {return (READ);} 
for {return (FOR);}
while {return (WHILE);}
do {return (DO);}
if {return (IF);}
then {return (THEN);}
else {return (ELSE);} 
elseif { return (ELSEIF);}
int {return (INT);}
float {return (FLOAT);}
char {return (CHAR);}
string {return (STRING);}
bool {return (BOOL);}
true {return (TRUE);}
false {return (FALSE);}
== {return (EQUAL);}
\!= {return (NEQUAL);}               
\< {return (LESS);}                   
\<= {return (LESSEQ);}                 
\> {return (GREATER);}                 
\>= {return (GREATEREQ);}              
\|\| {return (OR);}                      
\&\& {return (AND);}                    
\+ {return (PLUS);}                   
- {return (MINUS);}                      
\* {return (MULT);}                      
\/ {return (DIV);}                        
\% {return (MOD);}                         
\^ {return (POW);}                         
\( {return (PO);}
\) {return (PF);}
\[ {return (CO);}
\] {return (CF);}
\.\. {return (PP);}
\: {return (DP);}
= {return (AFF);}
[ \t]* ;
\'[^\']\' {return (CSTCHAR);}
\"[^\"]*\" {return (CSTSTRING);}
[A-Za-z](_|[A-Za-z]|[0-9])* { 
 remplissage_tab_lex(strdup(yytext));yylval.val1=strdup(yytext) ; return (IDF);}
\n {num_ligne++; }
0|-?[1-9][0-9]* {/*yylval = atoi(yytext);*/ return (CSTINT);}
{float} { return (CSTFLOAT);}
#define[ ]+[A-Z]+[0-9]*[A-Z]*[ ]+({integer}|{float}) {return (DEFINE);}


%%

int yyerror(const char *s)
{
  fprintf(stderr, "Ligne : %d  : Erreur : %s\n", num_ligne, s);
  exit (-1);
}
