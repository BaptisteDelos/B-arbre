#ifndef ARBRE_B_H
#define ARBRE_B_H
#include <stdio.h>
#include <stdbool.h>

/* -------------------- *
 *   Types definition   *
 * -------------------- */

typedef struct arbreB *ArbreB;



/* -------------------- *
 *    Constructeurs     *
 * -------------------- */

/**
 * Alloue la memoire pour un B-arbre et l'initialise
 */
ArbreB arbreB_creer();



/**
 * Ajoute un caractère dans un B-arbre
 */
void arbreB_ajouter(ArbreB arbre, char value);




/* -------------------- *
 *      Accesseurs      *
 * -------------------- */


/**
 * Determine si un caractere est present dans un B-arbre
 */
bool arbreB_rechercher(ArbreB arbre, char value);



/**
 * Affiche le contenu d'un B-arbre
 * @param fct: pointeur de fonction appliquant un traitement a chaque cle d'un noeud du B-arbre
 * @param user_data: donnees complementaires pour le traitement de l'arbre
 */
void arbreB_parcours(ArbreB arbre, void (*fct)(char,void*), void *user_data);






/* -------------------- *
 *     Destructeur      *
 * -------------------- */

/**
 * Libere la memoire allouee a un B-arbre
 */
void arbreB_liberer(ArbreB arbre);






#endif //ARBRE_B_H