#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include "list_contour.h"

Cellule_Liste_Contour *creer_element_liste_Contour(Contour v)
{
	Cellule_Liste_Contour *el;
	el = (Cellule_Liste_Contour *)malloc(sizeof(Cellule_Liste_Contour));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Contour : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}
/* creer une liste vide */
Liste_Contour creer_liste_Contour_vide()
{
	Liste_Contour L = {0, NULL, NULL};
	return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Contour ajouter_element_liste_Contour(Liste_Contour L, Contour e)
{
	Cellule_Liste_Contour *el;
	
	el = creer_element_liste_Contour(e);
	if (L.taille == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Contour supprimer_liste_Contour(Liste_Contour L)
{
	Cellule_Liste_Contour *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Contour *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Contour concatener_liste_Contour(Liste_Contour L1, Liste_Contour L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Contour supprimer_premier_element_liste_Contour(Liste_Contour L)
{
	/* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_Contour *e1=L.first;  /* Contoureur vers le premier element  */ 
	Cellule_Liste_Contour *e2=e1->suiv; /* Contoureur vers le deuxieme element */ 
	
	/* supprimer l'element Contoure par e1 */
	free(e1);
	
	/* mettre a jour la structure L */
	L.first = e2;
	if (e2 == NULL)    /* cas d'une liste L avec un seul element */
		L.last = NULL; /* --> la liste L devient une liste vide  */
	L.taille--;
	return L;
}


/* creer une sequence de Contours sous forme d'un tableau de Contours 
   a partir de la liste de Contours L */
Tableau_Contour sequence_Contours_liste_vers_tableau(Liste_Contour L)
{
	Tableau_Contour T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Contour */
	T.tab = malloc(sizeof(Contour) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_Contours_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de Contours T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_Contour *el = L.first; /* Contoureur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}

/* ecrire le contour L a l'ecran 
   cette fonction montre un exemple de conversion d'une liste de Contours en
   tableau de Contours afin de pouvoir par la suite acceder aux elements d'une
   sequence de Contours par indice */
void ecrire_list_contour(Liste_Contour L)
{
	Tableau_Contour TC = sequence_Contours_liste_vers_tableau(L);
	int k;
	int nP = TC.taille;
	
	printf("Liste contour avec %d éléments\n[", nP);
	for (k = 0; k < nP; k++)
	{	
		Contour P = TC.tab[k]; /* recuperer le Contour d'indice k */
		ecrire_contour(P);
	} 
	printf("]\n");
	
	free(TC.tab); /* supprimer le tableau de Contour TC */
}