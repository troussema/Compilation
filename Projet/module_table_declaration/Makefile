CC = gcc
OPTIONS = -Wall

Test : test_table_declaration.o table_declaration.o
	$(CC) test_table_declaration.o table_declaration.o -o test

test_table_declaration.o : test_table_declaration.c table_declaration.h
	$(CC) $(OPTIONS)  -c test_table_declaration.c 


table_declaration.o : table_declaration.c table_declaration.h
	$(CC) $(OPTIONS) -c table_declaration.c 

clean :
	rm -f *~ *.o
