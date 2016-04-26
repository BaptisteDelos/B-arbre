#include <stdlib.h>
#include "arbreB.h"
#include "test.h"

#define SIZE_MAX 1024





struct test_arbreB {
	int cur;//position courante dans le tableau
	int size;
	int tab[SIZE_MAX];
	bool result;//Le test est passé ou non
};



void verif_arbreB(char val, void* arg)
{
	struct test_arbreB *data = arg;
	if (!data->result)
		return;
	data->result = (data->cur < data->size && data->tab[data->cur++] == val);
}





void affichage_cle(char key, void *data) {
	(void)data;
	printf(" %c |",key);
}






bool test_arbreB_parcours (void) {
	ArbreB arbre = arbreB_creer();
	struct test_arbreB ar = {
		.cur = 0,
		.size = 5,
		.tab = {'a', 'e', 'p', 'x', 'z'},
		.result = true,
	};
	
	arbreB_ajouter(arbre,'e');
	arbreB_ajouter(arbre,'z');
	arbreB_ajouter(arbre,'x');
	arbreB_ajouter(arbre,'a');
	arbreB_ajouter(arbre,'p');
	
	printf("Contenu de l'arbre : |");
	arbreB_parcours(arbre,&affichage_cle,&ar);
	printf("\n");
	arbreB_parcours(arbre,&verif_arbreB,&ar);
	
	return (ar.result && ar.cur == ar.size);
}






int main (void) {
	TestSuite tst = tst_create();
	
	printf("\n\n-------------------------------- Test de parcours ---------------------------------\n\n"
	"On a introduit dans le B-arbre les caracteres suivants : e, z, x, a, p\n\n");
	test(tst,"Affichage du contenu du B-arbre dans l'ordre croissant des valeurs en parcours recursif ", test_arbreB_parcours());
	
	tst_results(tst);
	tst_free(tst);
	
	return 0;
}