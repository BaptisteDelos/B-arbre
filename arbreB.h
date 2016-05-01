#ifndef ARBRE_B_H
#define ARBRE_B_H
#include <stdio.h>
#include <stdbool.h>

/* -------------------- *
 *   Types definition   *
 * -------------------- */

typedef struct s_tree * Tree;



/* -------------------- *
 *    Constructeurs     *
 * -------------------- */

/**
 * Alloue la memoire pour un B-arbre et l'initialise
 */
Tree tree_create();



/**
 * Ajoute un caractère dans un B-arbre
 */
void tree_add(Tree tree, int value);




/* -------------------- *
 *      Accesseurs      *
 * -------------------- */


/**
 * Determine si un caractere est present dans un B-arbre
 */
bool tree_search(Tree tree, int value);



/**
 * Affiche le contenu d'un B-arbre
 * @param fct: pointeur de fonction appliquant un traitement a chaque cle d'un noeud du B-arbre
 * @param user_data: donnees complementaires pour le traitement de l'arbre
 */
void tree_browse(Tree tree, void (*fct)(int,void*), void *user_data);






/* -------------------- *
 *     Destructeur      *
 * -------------------- */

/**
 * Libere la memoire allouee a un B-arbre
 */
void tree_free(Tree tree);






#endif //ARBRE_B_H