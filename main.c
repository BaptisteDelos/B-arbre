#include <stdlib.h>
#include <time.h>

#include "arbreB.h"

void tree_print(int value, void *data) {
	printf("%d\n", value);
}


int main (void) {
	int val;
	char line[5];
	FILE * DICTIONNAIRE = fopen("dictionnaire.txt","a+");
	
	int nb_ligne;
	int index;
	
	srand(time(NULL));
	
	for (nb_ligne = 0; nb_ligne < 1000; ++nb_ligne) {
		for (index = 0; index < nb_ligne; ++index) {
			fprintf(DICTIONNAIRE, "%d\n", ((rand() % 110105) + 15));
		}
	}
	
	Tree tree = tree_create();
	fseek(DICTIONNAIRE,0,SEEK_SET);
	
	while (fgets(line,5,DICTIONNAIRE) != NULL) {
		val = atoi(line);
		tree_add(tree,val);
	}
	
	tree_browse(tree,&tree_print,NULL);
	
	tree_free(tree);
	fclose(DICTIONNAIRE);
	
	return 0;
}