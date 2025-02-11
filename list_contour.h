#ifndef _LIST_CONTOUR_H_
#define _LIST_CONTOUR_H_

#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include "conventions.h"

typedef struct Cellule_Liste_Contour_
{
	Contour data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Contour_* suiv; /* Contoureur sur l'element suivant */
} Cellule_Liste_Contour;

/*---- le type liste de Contour ----*/
typedef struct Liste_Contour_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Contour *first; /* Contoureur sur le premier element de la liste */
	Cellule_Liste_Contour *last;  /* Contoureur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Contour;

typedef struct Tableau_Contour_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Contour *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Contour;

Cellule_Liste_Contour *creer_element_liste_Contour(Contour v);
/* creer une liste vide */
Liste_Contour creer_liste_Contour_vide();

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Contour ajouter_element_liste_Contour(Liste_Contour L, Contour e);

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Contour supprimer_liste_Contour(Liste_Contour L);

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Contour concatener_liste_Contour(Liste_Contour L1, Liste_Contour L2);

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Contour supprimer_premier_element_liste_Contour(Liste_Contour L);


/* creer une sequence de Contours sous forme d'un tableau de Contours 
   a partir de la liste de Contours L */
Tableau_Contour sequence_Contours_liste_vers_tableau(Liste_Contour L);
/* ecrire le contour L a l'ecran 
   cette fonction montre un exemple de conversion d'une liste de Contours en
   tableau de Contours afin de pouvoir par la suite acceder aux elements d'une
   sequence de Contours par indice */
void ecrire_list_contour(Liste_Contour L);



#endif 