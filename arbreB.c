#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "arbreB.h"

#define T_MAX 2


typedef struct noeudB {
	int nbCles;
	char tabCles[2 * T_MAX - 1];
	struct noeudB *tabFils[2 * T_MAX];
	bool feuille;
} NoeudB;





struct arbreB {
	struct noeudB *racine;
};





ArbreB arbreB_creer() {
	ArbreB arbre = malloc(sizeof(struct arbreB));
	
	if (arbre == NULL)
	{
		fprintf(stderr,"Allocation impossible");
		exit(EXIT_FAILURE);
	}
	
	arbre->racine = malloc(sizeof(struct noeudB));
	
	
	if (arbre->racine == NULL)
	{
		fprintf(stderr,"Allocation impossible");
		exit(EXIT_FAILURE);
	}
	
	arbre->racine->nbCles = 0;
	
	for (int i = 0; i < (2 * T_MAX + 1); i++)
		arbre->racine->tabFils[i] = NULL;
	
	arbre->racine->feuille = true;
	
	return arbre;
}




/**
 * Determine si un caractere est present dans l'arborescence d'un arbre ayant pour racine le noeud en parametre
 * @pre: le noeud parcouru existe
 */
static bool noeudB_rechercher(NoeudB *noeud, char value) {
	assert(noeud != NULL);
	
	int i;
	
	for (i = 0; i < noeud->nbCles && value > noeud->tabCles[i]; i++) {
	}
	
	if (i < noeud->nbCles && value == noeud->tabCles[i])
		return true;
	
	if (noeud->feuille)
		return false;
	else
		return noeudB_rechercher(noeud->tabFils[i],value);
}







bool arbreB_rechercher(ArbreB arbre, char value) {
	assert(arbre != NULL);
	
	return noeudB_rechercher(arbre->racine,value);
}






/**
 * Determine si un noeud est plein
 */
static bool noeud_plein(NoeudB *noeud) {
	assert(noeud != NULL);
	
	return noeud->nbCles == 2 * T_MAX - 1;
}






/**
 * Partage un noeud enfant du noeud passe en parametre
 * @param x: le noeud pere du noeud a partager
 * @param i: indice du pointeur contenu dans la liste des pointeurs de x, qui reference le noeud a partager
 * @pre: le noeud x est non plein
 * @pre: le noeud fils a partager est plein
 */
static void noeudB_enfant_partager(NoeudB *x, int i) {
	assert(x != NULL);
	assert(!noeud_plein(x) && noeud_plein(x->tabFils[i]));
	
	struct noeudB *z = malloc(sizeof(struct noeudB));
	
	if (z == NULL)
	{
		fprintf(stderr,"Allocation Impossible");
		exit(EXIT_FAILURE);
	}
	
	struct noeudB *y = x->tabFils[i];
	z->feuille = y->feuille;
	z->nbCles = T_MAX - 1;
	int j;
	
	for (j = 0; j < T_MAX - 1; j++)
		z->tabCles[j] = y->tabCles[j + T_MAX];
	
	if (!y->feuille)
	{
		for (j = 0; j < T_MAX; j++)
			z->tabFils[j] = y->tabFils[j + T_MAX];
	}
	
	y->nbCles = T_MAX - 1;
	
	for (j = x->nbCles + 1; j >= i + 1; j--)
		x->tabFils[j + 1] = x->tabFils[j];
	
	x->tabFils[i + 1] = z;
	
	for (j = x->nbCles; j >= i; j--)
		x->tabCles[j + 1] = x->tabCles[j];
	
	x->tabCles[i] = y->tabCles[T_MAX];
	x->nbCles += 1;
}




/**
 * Ajoute ......................................................
 */
static void arbreB_incomplet_ajouter(NoeudB *x, char value) {
	assert(x != NULL);
	
	int i = x->nbCles - 1;
	
	if (x->feuille)
	{
		while (i >= 0 && value < x->tabCles[i]) {
			x->tabCles[i + 1] = x->tabCles[i];
			i -= 1;
		}
		
		x->tabCles[i + 1] = value;
		x->nbCles += 1;
	}
	else
	{
		while (i >= 0 && value < x->tabCles[i])
			i -= 1;
		
		i += 1;
		
		if (noeud_plein(x->tabFils[i]))
		{
			noeudB_enfant_partager(x,i);
			
			if (value > x->tabCles[i])
				i += 1;
		}
		
		arbreB_incomplet_ajouter(x->tabFils[i],value);
	}
}





void arbreB_ajouter(ArbreB arbre, char value) {
	assert(arbre != NULL);
	
	if (arbreB_rechercher(arbre,value))
		return;
	
	struct noeudB *r = arbre->racine;
	
	if (noeud_plein(r))
	{
		struct noeudB *s = malloc(sizeof(struct noeudB));
		
		if (s == NULL)
		{
			fprintf(stderr,"Allocation Impossible");
			exit(EXIT_FAILURE);
		}
		
		s->feuille = false;
		s->nbCles = 0;
		s->tabFils[0] = r;
		arbre->racine = s;
		
		noeudB_enfant_partager(s,0);
		arbreB_incomplet_ajouter(s,value);
	}
	else
		arbreB_incomplet_ajouter(r,value);
}





/**
 * Parcourt, de manière récursive, la sous-arborescence d'un B-arbre a partir d'un de ses noeuds
 * @param fct: pointeur de fonction appliquant un traitement a chaque cle d'un noeud
 * @param user_data: donnees complementaires pour le traitement de l'arborescence
 */
void noeudB_parcours(NoeudB *noeud, void (*fct)(char,void*), void *user_data)
{
	if (noeud == NULL)
		return;
	
	int i;
	
	for (i = 0; i < noeud->nbCles; i++) {
		noeudB_parcours(noeud->tabFils[i],fct,user_data);
		(*fct)(noeud->tabCles[i],user_data);
	}
}






void arbreB_parcours(ArbreB arbre, void (*fct)(char,void*), void *user_data) {
	assert(arbre != NULL);
	
	noeudB_parcours(arbre->racine,fct,user_data);
}