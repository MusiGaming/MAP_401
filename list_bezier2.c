#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include "list_bezier2.h"

Liste_Bezier2 creer_liste_bezier2_vide()
{
	Liste_Bezier2 L = {0, NULL, NULL};
	return L;
}

Cellule_Liste_Bezier2 *creer_element_liste_Bezier2(Bezier2 v)
{
	Cellule_Liste_Bezier2 *el;
	el = (Cellule_Liste_Bezier2 *)malloc(sizeof(Cellule_Liste_Bezier2));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Bezier2 : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

Liste_Bezier2 ajouter_element_liste_Bezier2(Liste_Bezier2 L, Bezier2 e)
{
	Cellule_Liste_Bezier2 *el;
	
	el = creer_element_liste_Bezier2(e);
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

Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 L1, Liste_Bezier2 L2)
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

Tableau_Bezier2 sequence_Bezier2_liste_vers_tableau(Liste_Bezier2 L)
{
	Tableau_Bezier2 T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Bezier2 */
	T.tab = malloc(sizeof(Bezier2) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_Bezier2s_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de Bezier2s T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_Bezier2 *el = L.first; /* Bezier2eur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}

void ecrire_Liste_Bezier(Liste_Bezier2 L)
{
	Tableau_Bezier2 TP = sequence_Bezier2_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	
	printf("Bezier avec %d Bezier2s\n[", nP);
	for (k = 0; k < nP; k++)
	{	
		Bezier2 P = TP.tab[k]; /* recuperer le point d'indice k */
		printf(" ((%5.1f,%5.1f), (%5.1f,%5.1f), (%5.1f,%5.1f))", P.C0.x, P.C0.y, P.C1.x, P.C1.y, P.C2.x, P.C2.y);
	} 
	printf("]\n");
	
	free(TP.tab); /* supprimer le tableau de point TP */
}
