CC = gcc
OPTIONS = -Wall

main : main_table_representation_types.o table_representation_types.o
	$(CC) main_table_representation_types.o table_representation_types.o -o main

main_table_representation_types.o : main_table_representation_types.c table_representation_types.h
	$(CC) $(OPTIONS)  -c main_table_representation_types.c 


table_declaration.o : table_representation_types.c table_representation_types.h
	$(CC) $(OPTIONS) -c table_representation_types.c 

clean :
	rm -f *~ *.o
