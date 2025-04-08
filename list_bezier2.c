#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include "list_bezier2.h"

Liste_Bezier2 creer_liste_bezier2_vide()
{
	Liste_Bezier2 L = {0, NULL, NULL};
	return L;
}