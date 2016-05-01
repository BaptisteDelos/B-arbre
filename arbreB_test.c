#include <stdlib.h>
#include "arbreB.h"
#include "test.h"

#define SIZE_MAX 1024





struct test_tree {
	int cur;//position courante dans le tableau
	int size;
	int tab[SIZE_MAX];
	bool result;//Le test est passé ou non
};



void verif_tree(int val, void* arg)
{
	struct test_tree *data = arg;
	if (!data->result)
		return;
	data->result = (data->cur < data->size && data->tab[data->cur++] == val);
}





void print_key(int key, void *data) {
	(void)data;
	printf(" %d |",key);
}






bool test_tree_browse (void) {
	Tree tree = tree_create();
	struct test_tree ar = {
		.cur = 0,
		.size = 5,
		.tab = {1, 2, 3, 4, 5},
		.result = true,
	};
	
	tree_add(tree,2);
	tree_add(tree,5);
	tree_add(tree,1);
	tree_add(tree,3);
	tree_add(tree,4);
	
	printf("Contenu de l'arbre : |");
	tree_browse(tree,&print_key,NULL);
	printf("\n");
	tree_browse(tree,&verif_tree,&ar);
	tree_free(tree);
	
	return (ar.result && ar.cur == ar.size);
}






int main (void) {
	TestSuite tst = tst_create();
	
	printf("\n\n------------------------------------- Test de parcours --------------------------------------\n\n"
	"On a introduit dans le B-arbre les valeurs suivantes : 2, 5, 1, 3, 4\n\n");
	test(tst,"Affichage du contenu du B-arbre dans l'ordre croissant des valeurs en parcours recursif ", test_tree_browse());
	
	tst_results(tst);
	tst_free(tst);
	
	return 0;
}