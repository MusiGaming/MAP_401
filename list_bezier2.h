#ifndef _LIST_BEZIER2_H_
#define _LIST_BEZIER2_H_

#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include "conventions.h"


typedef struct Bezier2_ {
	Point C0;
	Point C1;
	Point C2;
} Bezier2;

typedef struct Bezier3_ {
	Point C0;
	Point C1;
	Point C2;
	Point C3;
} Bezier3;

typedef struct Cellule_Liste_Bezier2_
{
	Bezier2 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Bezier2_* suiv; /* Bezier2eur sur l'element suivant */
} Cellule_Liste_Bezier2;

typedef struct Liste_Bezier2_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Bezier2 *first; /* Bezier2eur sur le premier element de la liste */
	Cellule_Liste_Bezier2 *last;  /* Bezier2eur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Bezier2;

typedef struct Tableau_Bezier2_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Bezier2 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Bezier2;

Liste_Bezier2 creer_liste_bezier2_vide();
Cellule_Liste_Bezier2 *creer_element_liste_Bezier2(Bezier2 v);
Liste_Bezier2 ajouter_element_liste_Bezier2(Liste_Bezier2 L, Bezier2 e);
Tableau_Bezier2 sequence_Bezier2_liste_vers_tableau(Liste_Bezier2 L);
Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 L1, Liste_Bezier2 L2);
void ecrire_Liste_Bezier(Liste_Bezier2 L);

/* TYPE LIST LIST BEZIER2*/

typedef struct Cellule_Liste_Liste_Bezier2_
{
	Liste_Bezier2 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Liste_Bezier2_* suiv; /* Bezier2eur sur l'element suivant */
} Cellule_Liste_Liste_Bezier2;

typedef struct Liste_Liste_Bezier2_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Liste_Bezier2 *first; /* Bezier2eur sur le premier element de la liste */
	Cellule_Liste_Liste_Bezier2 *last;  /* Bezier2eur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Liste_Bezier2;

typedef struct Tableau_Liste_Bezier2_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Liste_Bezier2 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Liste_Bezier2;

Liste_Liste_Bezier2 creer_liste_liste_bezier2_vide();
Cellule_Liste_Liste_Bezier2 *creer_element_liste_liste_Bezier2(Liste_Bezier2 v);
Liste_Liste_Bezier2 ajouter_element_liste_liste_Bezier2(Liste_Liste_Bezier2 L, Liste_Bezier2 e);
Tableau_Liste_Bezier2 sequence_Bezier2_liste_liste_vers_tableau(Liste_Liste_Bezier2 L);


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
#endif 