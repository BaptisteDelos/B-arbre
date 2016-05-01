#include <stdlib.h>
#include <assert.h>
#include "arbreB.h"

#define K 2
#define KEY_MAX 2*K-1


typedef struct s_node {
	int n;
	int cle[KEY_MAX];
	bool leaf;
	struct s_node * c[KEY_MAX + 1];
}s_Node;


struct s_tree {
	int size;
	struct s_node * root;
};


/**
 * Determine si un caractere est present dans l'arborescence d'un arbre ayant pour racine le noeud en parametre
 * @pre: le noeud parcouru existe
 */
static int node_search(s_Node * x, int e) {
	assert(x != NULL);
	int i;
	
	for (i = 0; i < x->n && e > x->cle[i]; i++) {}
	
	if (i < x->n && e == x->cle[i])
		return i;
	if (x->leaf)
		return -1;
	else
		return node_search(x->c[i],e);
}


bool tree_search(Tree tree, int value) {
	assert(tree != NULL);
	
	return node_search(tree->root,value) > -1;
}


Tree tree_create() {
	Tree tree = malloc(sizeof(struct s_tree));
	
	if (tree == NULL)
	{
		fprintf(stderr,"malloc in tree_create");
		exit(EXIT_FAILURE);
	}
	
	tree->root = (struct s_node *) malloc(sizeof(struct s_node));
	if (tree->root == NULL)
	{
		fprintf(stderr,"malloc in tree_create");
		free(tree);
		exit(EXIT_FAILURE);
	}
	
	tree->root->leaf = true;
	
	return tree;
}


/**
 * Libere l'espace memoire alloue a un noeud
 */
static void node_free(s_Node * x)
{
	int i;
	
	if (x == NULL)
		return;
	
	for (i = 0; i < x->n + 1; i++) {
		node_free(x->c[i]);
	}
	
	free(x);
}


void tree_free(Tree tree) {
	assert(tree != NULL);
	
	node_free(tree->root);
	free(tree);
}


/**
 * Partage un noeud enfant du noeud passe en parametre
 * @param x: le noeud pere du noeud a partager
 * @param i: indice du pointeur contenu dans la liste des pointeurs de x, qui reference le noeud a partager
 * @pre: le noeud x est non plein
 * @pre: le noeud fils a partager est plein
 */
static void node_child_divide(s_Node * x, int i, s_Node * y) {
	assert(x != NULL && y != NULL);
	assert(x->c[i] == y);
	
	struct s_node * z = (struct s_node *) malloc(sizeof(struct s_node));
	if (z == NULL)
	{
		fprintf(stderr,"malloc in node_child_divide");
		exit(EXIT_FAILURE);
	}
	
	z->leaf = y->leaf;
	z->n = K - 1;
	
	for (int j = 0; j < K - 1; j++)
		z->cle[j] = y->cle[j + K];
	
	if (!y->leaf)
	{
		for (int j = 0; j < K; j++)
			z->c[j] = y->c[j + K];
	}
	
	y->n = K - 1;
	
	for (int j = x->n; j >= i; j--)
		x->c[j + 1] = x->c[j];
	x->c[i + 1] = z;
	
	for (int j = x->n - 1; j >= i - 1; j--)
		x->cle[j + 1] = x->cle[j];
	x->cle[i] = y->cle[K - 1];
	x->n += 1;
}


static void tree_add_incomplete(s_Node * x, int e) {
	assert(x != NULL);
	
	int i = x->n - 1;
	
	if (x->leaf)
	{
		for (; i >= 0 && e < x->cle[i]; i--)
			x->cle[i + 1] = x->cle[i];
		
		x->cle[i + 1] = e;
		x->n += 1;
	}
	else
	{
		for(; i >= 0 && e < x->cle[i]; i--) {}
		i++;
		
		if (x->c[i]->n == KEY_MAX)
		{
			node_child_divide(x,i,x->c[i]);
			
			if (e > x->cle[i])
				i++;
		}
		tree_add_incomplete(x->c[i],e);
	}
}


void tree_add(Tree tree, int value) {
	assert(tree != NULL);
	
	struct s_node * r = tree->root;
	
	if (r->n == KEY_MAX)
	{
		struct s_node * s = (struct s_node *) malloc(sizeof(struct s_node));
		if (s == NULL)
		{
			fprintf(stderr,"malloc in tree_add");
			exit(EXIT_FAILURE);
		}
		
		s->leaf = false;
		s->n = 0;
		s->c[0] = r;
		tree->root = s;
		node_child_divide(tree->root,0,r);
		tree_add_incomplete(tree->root,value);
	}
	else
		tree_add_incomplete(r,value);
	
	tree->size += 1;
}


/**
 * Parcourt, de manière récursive, la sous-arborescence d'un B-arbre a partir d'un de ses noeuds
 * @param fct: pointeur de fonction appliquant un traitement a chaque cle d'un noeud
 * @param user_data: donnees complementaires pour le traitement de l'arborescence
 */
static void node_browse(s_Node * x, void (*fct)(int,void*), void *user_data)
{
	if (x == NULL)
		return;
	
	int i;
	
	for (i = 0; i < x->n; i++) {
		node_browse(x->c[i],fct,user_data);
		(*fct)(x->cle[i],user_data);
	}
	
	node_browse(x->c[i],fct,user_data);
}


void tree_browse(Tree tree, void (*fct)(int,void*), void *user_data) {
	assert(tree != NULL);
	
	node_browse(tree->root,fct,user_data);
}