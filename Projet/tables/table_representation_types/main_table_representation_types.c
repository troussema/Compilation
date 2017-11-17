#include <stdlib.h>
#include <stdio.h>
#include "table_representation_types.h"

int main(int argc, char const *argv[])
{
	printf("\nTable de representation des types\n\n");

	printf("_________________\n");
	printf("|   i   | descrip|\n");
	printf("|_______|________|\n");

	initialisation_table();
	
	remplissage_table(3,5,0);
	
	remplissage_table(6,0,5);

	remplissage_table(5,5,3);
	

	affichage_table();

	printf("|_______|________|\n");
	return 0;
	
}
