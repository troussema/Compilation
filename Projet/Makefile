CC = gcc
Y = yacc
L = lex

OPTIONS = -v

compiler :fic_yacc fic_lex c1 c2 clean

fic_yacc : fic_yacc.y
	$(Y) -v -d fic_yacc.y
fic_lex : fic_lex.l
	$(L) fic_lex.l
c1 : lex.yy.c
	$(CC) -c lex.yy.c
c2 : y.tab.c lex.yy.o 
	$(CC) -v -o analyseur y.tab.c lex.yy.o -ly -ll

clean :
	rm -f *.o  *.c *.h *.output *~
