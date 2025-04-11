#include<stdio.h>               /* utilisation des entrees-sorties standard de C */
#include<stdlib.h>              /* utilisation des fonctions malloc et free */
#include <stdbool.h>            /* utilisation du type bool */
#include <string.h>             /* utilisation de manipulation des chaines de caractères*/

#include "simplification_Bezier3.h"            //Inclusion de notre fichier header

Point Point_sur_bezier3 (Bezier3 B, double t){
	Point P;
	P.x = B.C0.x * ((1-t)*(1-t)*(1-t)) + B.C1.x * 3*t*((1-t)*(1-t))+B.C2.x*3*t*t*(1-t)+B.C3.x*t*t*t;
	P.y = B.C0.y * ((1-t)*(1-t)*(1-t)) + B.C1.y * 3*t*((1-t)*(1-t))+B.C2.y*3*t*t*(1-t)+B.C3.y*t*t*t;
	//Point P = set_point (Cx, Cy);
	return P;
}

double fonction_delta (double k, double n){
	double res = (6*k*k*k*k)-(8*n*k*k*k)+(6*k*k)-(4*n*k)+(n*n*n*n)-(n*n);
	return res;
}

Bezier3 approx_bezier3(Liste_Point L, int j1, int j2) {
    Bezier3 B;
    Tableau_Point TL = sequence_points_liste_vers_tableau(L);

    B.C0 = TL.tab[j1]; B.C3 = TL.tab[j2];
    double n = j2 - j1;
    if (n == 1 || n == 2){
        Bezier2 B2 = approx_bezier2(L,j1,j2);
        B = convertion_Bezier2_Bezier3(B2);
        return B;
    } else {
        double alpha = (-15.*n*n*n + 5.*n*n + 2.*n + 4.)/(3.*(n + 2.)* (3.*n*n + 1.));
        double beta = (10.*n*n*n - 15.*n*n + n + 2.) / (3.*(n + 2.)*(3.*n*n + 1.));
        double gamma = (70.*n) / (3.*(n*n - 1)*(n*n - 4.)*(3*n*n + 1.));
        Point Pj1 , Pj2;
		Pj1.x = 0;
		Pj2.x = 0;
		Pj1.y = 0;
		Pj2.y = 0;

        for (int i=1; i<=n-1;i++){
			Pj1.x = Pj1.x + fonction_delta(i,n)*(TL.tab[j1 + i]).x;
			Pj1.y = Pj1.y + fonction_delta(i,n)*(TL.tab[j1 + i]).y;
			Pj2.x = Pj2.x + fonction_delta(n-i,n)*(TL.tab[j1 + i]).x;
			Pj2.y = Pj2.y + fonction_delta(n-i,n)*(TL.tab[j1 + i]).y;
		}
        B.C1.x = alpha*TL.tab[j1].x + gamma*Pj1.x + beta*TL.tab[j2].x;
		B.C1.y = alpha*TL.tab[j1].y + gamma*Pj1.y+beta*TL.tab[j2].y;
		B.C2.x = beta*TL.tab[j1].x + gamma*Pj2.x+alpha*TL.tab[j2].x;
		B.C2.y = beta*TL.tab[j1].y + gamma*Pj2.y+alpha*TL.tab[j2].y;
    }
    return B;
}

double distance_point_bezier3 (Point P, Bezier3 B, double t){
	Point C = Point_sur_bezier3(B,t);
	Vecteur V = vect_bipoint (P, C);
	double N = norme_euclidienne(V);
	return N;
}

Liste_Bezier3 simplification_douglas_peucker_Bezier3 (Liste_Point LP,int j1, int j2, double d){
    Tableau_Point TP = sequence_points_liste_vers_tableau(LP);
    double dmax = 0, n = j2-j1;
    int k = j1;

    Liste_Bezier3 L  = creer_liste_Bezier3_vide();
	Liste_Bezier3 L1 = creer_liste_Bezier3_vide();
	Liste_Bezier3 L2 = creer_liste_Bezier3_vide();
	Bezier3 C = approx_bezier3 (LP,j1,j2);
    
    for (int j=j1+1; j<=j2 ; j++){
		double i=j-j1;
		double ti = i/n;
        double dj = distance_point_bezier3(TP.tab[j], C, ti);
        if (dmax<dj) {
            dmax = dj;
            k=j;
        }
    }
    
    if (dmax <= d){
        L = ajouter_element_liste_Bezier3(L,C);
    } else {
        L1 = simplification_douglas_peucker_Bezier3(LP,j1,k,d);
		L2 = simplification_douglas_peucker_Bezier3(LP,k,j2,d);
		L = concatener_liste_Bezier3(L1,L2);
    }
    return L;
}

Liste_Liste_Bezier3 TT_contour_en_Bezier3(Liste_Contour LC) {
    Tableau_Contour TLC = sequence_Contours_liste_vers_tableau(LC);
    Liste_Liste_Bezier3 LB = creer_liste_liste_bezier3_vide();
    
    printf("Quel degré de simplification voulez-vous ? \n");      //On demande à l'utilisateur si il désire que l'image soit rempli ou vide
    double d = 0;
    scanf("%lf", &d);

    for (int i = 0; i <= LC.taille-1; i++) {
        Liste_Bezier3 LB2 = simplification_douglas_peucker_Bezier3(TLC.tab[i],0, TLC.tab[i].taille -1, d);
        LB = ajouter_element_liste_liste_Bezier3(LB, LB2);
    }
    // ecrire_Liste_Bezier(LB);
    return LB;
}

void esp_fichier_Bezier3(char nom[], Liste_Liste_Bezier3 LLB, UINT h, UINT l) {
    Tableau_Liste_Bezier3 TLLB = sequence_Bezier3_liste_liste_vers_tableau(LLB);
    Tableau_Bezier3 TLB;
    Bezier3 B3;

    int size = strlen(nom);                                 //On récupère la taille du nom du fichier image donné en argument de la commande dans le terminal
    for(int i = size; i > (size - 4); i--) {                //On lui retire son extention '.pbm'
        nom[i-1] = '\0';
    }
    nom = strcat(nom, ".eps");                              //Puis on rajoute '.eps' pour faire le nom de notre fichier image affichable

    FILE *file;                                             //On créer un fichier
    file = fopen(nom, "w");                                 //Avec le nom qu'on viens de créer, puis on dit qu'on veut écrire dedans
    fprintf(file, "%%!PS-Adobe-3.0 EPSF-3.0\n");                //On écrit les deux premières lignes obligatoires du format .eps
    fprintf(file , "%%%%BoundingBox: 0 0 %d %d\n\n", l, h);     //Avec la taille de l'image à créer (donc les mêmes que l'image donné)
    printf("taille LLB : %d\n",LLB.taille);

    for (int k = 0; k<LLB.taille;k++) {
        TLB = sequence_Bezier3_liste_vers_tableau(TLLB.tab[k]);      //On transforme notre liste de contour en tableau pour une manipulation plus simple
        B3 = TLB.tab[0];
        fprintf(file, "%f %f moveto\n", B3.C0.x, h-B3.C0.y);        //Dit au stylo de se déplacer au 1er point
        for (int i = 0; i < TLB.taille; i++) {                               //Puis, pour chaque contour,  
            B3 = TLB.tab[i];
            fprintf(file, "%f %f %f %f %f %f curveto\n", B3.C1.x, h-B3.C1.y, B3.C2.x, h-B3.C2.y, B3.C3.x, h-B3.C3.y);
        }
    }
        
    printf("Quel mode pour le remplissage ? (0 = vide, 1 = fill)\n");   //On demande à l'utilisateur si il désire que l'image soit rempli ou vide
    int mode = 0;
    scanf("%d", &mode);                                                 //On vérifie et récupère la réponse de l'utilisateur
    
    if (mode == 1) {
        fprintf(file, "\nfill\n\nshowpage");             //On ajoute une ligne pour mettre l'image rempli si le choix est le même
    }
    else {
        fprintf(file, "\n0.1 setlinewidth stroke\n\nshowpage");           //On ajoute une ligne pour mettre l'image vide si le choix est le même
    }

    fclose(file);                                                       //On ferme le fichier qui est près à l'emplois
}