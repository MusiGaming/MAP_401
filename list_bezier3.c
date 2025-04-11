#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include "list_bezier3.h"

Cellule_Liste_Bezier3* creer_element_liste_Bezier3(Bezier3 B)
{
	Cellule_Liste_Bezier3 *el;
	el = (Cellule_Liste_Bezier3 *)malloc(sizeof(Cellule_Liste_Bezier3));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Courbe : allocation impossible\n");
		exit(-1);
	}
	el->data = B;
	el->suiv = NULL;
	return el;
}

Liste_Bezier3 creer_liste_Bezier3_vide()
{
	Liste_Bezier3 L = {0, NULL, NULL};
	return L;
}

Liste_Bezier3 ajouter_element_liste_Bezier3(Liste_Bezier3 L,Bezier3 S)
{
	Cellule_Liste_Bezier3 *el;
	
	el = creer_element_liste_Bezier3(S);
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

Liste_Bezier3 supprimer_liste_Bezier3(Liste_Bezier3 L)
{
	Cellule_Liste_Bezier3 *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Bezier3 *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 L1, Liste_Bezier3 L2)
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

Liste_Bezier3 supprimer_premier_element_liste_Bezier3(Liste_Bezier3 L)
{
	/* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_Bezier3 *e1=L.first;  /* Pointeur vers le premier element  */ 
	Cellule_Liste_Bezier3 *e2=e1->suiv; /* Pointeur vers le deuxieme element */ 
	
	/* supprimer l'element pointe par e1 */
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
Tableau_Bezier3 sequence_Bezier3_liste_vers_tableau(Liste_Bezier3 L)
{
	Tableau_Bezier3 T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Contour */
	T.tab = malloc(sizeof(Bezier3) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_Contours_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de Contours T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_Bezier3 *el = L.first; /* Contoureur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}




Liste_Liste_Bezier3 creer_liste_liste_bezier3_vide()
{
	Liste_Liste_Bezier3 L = {0, NULL, NULL};
	return L;
}

Cellule_Liste_Liste_Bezier3 *creer_element_liste_liste_Bezier3(Liste_Bezier3 v)
{
	Cellule_Liste_Liste_Bezier3 *el;
	el = (Cellule_Liste_Liste_Bezier3 *)malloc(sizeof(Cellule_Liste_Liste_Bezier3));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Bezier3 : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

Liste_Liste_Bezier3 ajouter_element_liste_liste_Bezier3(Liste_Liste_Bezier3 L, Liste_Bezier3 e)
{
	Cellule_Liste_Liste_Bezier3 *el;
	
	el = creer_element_liste_liste_Bezier3(e);
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

Tableau_Liste_Bezier3 sequence_Bezier3_liste_liste_vers_tableau(Liste_Liste_Bezier3 L)
{
	Tableau_Liste_Bezier3 T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Bezier3 */
	T.tab = malloc(sizeof(Liste_Bezier3) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_Bezier3s_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de Bezier3s T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_Liste_Bezier3 *el = L.first; /* Bezier3eur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}