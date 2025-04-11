#ifndef _LIST_BEZIER3_H_
#define _LIST_BEZIER3_H_

#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include "conventions.h"
#include "list_bezier2.h"


typedef struct Cellule_Liste_Bezier3_
{
	Bezier3 data;   /* Courbe */ 
	struct Cellule_Liste_Bezier3_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Bezier3;

/*---- le type liste de point ----*/
typedef struct Liste_Bezier3_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Bezier3 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Bezier3 *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Bezier3;

typedef struct Tableau_Bezier3_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Bezier3 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Bezier3;

Cellule_Liste_Bezier3* creer_element_liste_Bezier3(Bezier3 B);
Liste_Bezier3 creer_liste_Bezier3_vide();
Liste_Bezier3 ajouter_element_liste_Bezier3(Liste_Bezier3 L, Bezier3 S);
Liste_Bezier3 supprimer_liste_Bezier3(Liste_Bezier3 L);
Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 L1, Liste_Bezier3 L2);
Liste_Bezier3 supprimer_premier_element_liste_Bezier3(Liste_Bezier3 L);
Tableau_Bezier3 sequence_Bezier3_liste_vers_tableau(Liste_Bezier3 L);

/* TYPE LIST LIST BEZIER3*/

typedef struct Cellule_Liste_Liste_Bezier3_
{
	Liste_Bezier3 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Liste_Bezier3_* suiv; /* Bezier3eur sur l'element suivant */
} Cellule_Liste_Liste_Bezier3;

typedef struct Liste_Liste_Bezier3_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Liste_Bezier3 *first; /* Bezier3eur sur le premier element de la liste */
	Cellule_Liste_Liste_Bezier3 *last;  /* Bezier3eur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Liste_Bezier3;

typedef struct Tableau_Liste_Bezier3_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Liste_Bezier3 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Liste_Bezier3;

Liste_Liste_Bezier3 creer_liste_liste_bezier3_vide();
Cellule_Liste_Liste_Bezier3 *creer_element_liste_liste_Bezier3(Liste_Bezier3 v);
Liste_Liste_Bezier3 ajouter_element_liste_liste_Bezier3(Liste_Liste_Bezier3 L, Liste_Bezier3 e);
Tableau_Liste_Bezier3 sequence_Bezier3_liste_liste_vers_tableau(Liste_Liste_Bezier3 L);

#endif 