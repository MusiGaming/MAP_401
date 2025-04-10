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

/*---- le type liste de Bezier2 ----*/
// typedef struct Cellule_L_Liste_Bezier2_
// {
// 	Liste_Bezier2 data;    /* donnee de l'element de L_Liste */
// 	struct Cellule_L_Liste_Bezier2_* suiv; /* Bezier2eur sur l'element suivant */
// } Cellule_L_Liste_Bezier2;

// typedef struct L_Liste_Bezier2_
// {
// 	unsigned int taille;        /* nombre d'elements dans la L_Liste */
// 	Cellule_L_Liste_Bezier2 *first; /* Bezier2eur sur le premier element de la L_Liste */
// 	Cellule_L_Liste_Bezier2 *last;  /* Bezier2eur sur le dernier element de la L_Liste */
// 	                       /* first = last = NULL et taille = 0 <=> L_Liste vide */
// } L_Liste_Bezier2;

// typedef struct Tableau_Bezier2_
// {
// 	unsigned int taille; /* nombre d'elements dans le tableau */
// 	Bezier2 *tab;          /* (pointeur vers) le tableau des elements */
// } Tableau_Bezier2;

Liste_Bezier2 creer_liste_bezier2_vide();
Cellule_Liste_Bezier2 *creer_element_liste_Bezier2(Bezier2 v);
Liste_Bezier2 ajouter_element_liste_Bezier2(Liste_Bezier2 L, Bezier2 e);
Tableau_Bezier2 sequence_Bezier2_liste_vers_tableau(Liste_Bezier2 L);
Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 L1, Liste_Bezier2 L2);
void ecrire_Liste_Bezier(Liste_Bezier2 L);

#endif 