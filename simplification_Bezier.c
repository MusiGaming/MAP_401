#include<stdio.h>               /* utilisation des entrees-sorties standard de C */
#include<stdlib.h>              /* utilisation des fonctions malloc et free */
#include <stdbool.h>            /* utilisation du type bool */
#include <string.h>             /* utilisation de manipulation des chaines de caractères*/

#include "contour.h"            //Inclusion de notre fichier header


Bezier2 approx_bezier2(Liste_Point L, int j1, int j2) {
    // int j1 = 0; int j2 = L.taille -1;
    int n = j2 - j1;
    Tableau_Point TL = sequence_points_liste_vers_tableau(L);
    Bezier2 B;
    B.C0 = TL.tab[j1];
    B.C2 = TL.tab[j2];

    if (n==1) {
        B.C1.x = (1./2.)*(TL.tab[j1].x + TL.tab[j2].x);
        B.C1.x = (1./2.)*(TL.tab[j1].y + TL.tab[j2].y);
    }
    else if (n >= 2) {
        double nR = (double)n;
        double alpha = (3*nR)/((nR*nR)-1);
        double beta = (1-2*nR)/(2*(nR+1));
        double x, y;
        for(int i = 1; i <= (n-1); i++) {
            x = x + TL.tab[i+j1].x;
            y = y + TL.tab[i+j1].y;
        }
        B.C1.x = alpha * x + beta * (TL.tab[j1].x + TL.tab[j2].x); 
        B.C1.y = alpha * y + beta * (TL.tab[j1].y + TL.tab[j2].y);
    }
    else {
        printf("ERREUR : indices dans approx_bezier2\n");
    }
    
    return B;
}

Point Point_sur_bezier2 (Bezier2 B, double t) {
    Point Ct;
    Ct.x = ((1-t)*(1-t))*B.C0.x + 2*t*(1-t)*B.C1.x + (t*t)*B.C2.x;
    Ct.y = ((1-t)*(1-t))*B.C0.y + 2*t*(1-t)*B.C1.y + (t*t)*B.C2.y;
    printf("Ct = (%lf, %lf)\n", Ct.x, Ct.y);
    return Ct;
}

double dist_point_Bezier2 (Point P, Bezier2 B, double t) {
    Point Ct = Point_sur_bezier2(B,t);
	Vecteur V = vect_bipoint (P, Ct);
	double d = norme_euclidienne(V);
    printf ("d : %lf\n", d);
	return d;
}

Liste_Bezier2 simplification_douglas_peucker_bezier2 (Liste_Point L, int j1, int j2, double d) {
    int dmax, k = j1, n = j2 - j1;
    Liste_Bezier2 LB = creer_liste_bezier2_vide();

    Tableau_Point TL = sequence_points_liste_vers_tableau(L);
    Bezier2 B = approx_bezier2(L, j1, j2);

    for (int j = j1+1; j <= j2; j++) {                              //Pour chaque points entre les point j1 et j2
        int i = j-j1;
        double ti = (double)i / (double)n;
        double dj = dist_point_Bezier2(TL.tab[j], B, ti);
        if (dmax < dj){                                             //On trouve le point qui est le plus éloigné du segment
            dmax = dj;
            k = j;          //indice du point le plus éloigné
        }
    }

    if (dmax <= d) {
        LB = ajouter_element_liste_Bezier2(LB, B);
    } else {
        Liste_Bezier2 LB1 = simplification_douglas_peucker_bezier2(L, j1, k, d);
        Liste_Bezier2 LB2 = simplification_douglas_peucker_bezier2(L, k, j2, d);
        LB = concatener_liste_Bezier2(LB1, LB2);
    }

    return LB;
}

Bezier3 convertion_Bezier2_Bezier3(Bezier2 B2) {
    Bezier3 B3;
    B3.C0 = B2.C0;
    B3.C3 = B2.C2;

    B3.C1.x = (2*B2.C1.x + B2.C0.x)/3;
    B3.C1.x = (2*B2.C1.y + B2.C0.y)/3;
    B3.C2.x = (2*B2.C1.x + B2.C2.x)/3;
    B3.C2.x = (2*B2.C1.y + B2.C2.y)/3;
}

//Permet d'écrire l'ensemble des contours dans un fichier eps pouvant être lu comme une image affichable
void esp_fichier_Bezier2(char nom[], Liste_Bezier2 LB, UINT h, UINT l) {
    int size = strlen(nom);                                 //On récupère la taille du nom du fichier image donné en argument de la commande dans le terminal
    for(int i = size; i > (size - 4); i--) {                //On lui retire son extention '.pbm'
        nom[i-1] = '\0';
    }
    nom = strcat(nom, ".eps");                              //Puis on rajoute '.eps' pour faire le nom de notre fichier image affichable

    double n = 100;
    FILE *file;                                             //On créer un fichier
    file = fopen(nom, "w");                                 //Avec le nom qu'on viens de créer, puis on dit qu'on veut écrire dedans
    fprintf(file, "%%!PS-Adobe-3.0 EPSF-3.0\n");                //On écrit les deux premières lignes obligatoires du format .eps
    fprintf(file , "%%%%BoundingBox: 0 0 %f %f\n\n", l*n, h*n);     //Avec la taille de l'image à créer (donc les mêmes que l'image donné)

    Tableau_Bezier2 TLB = sequence_Bezier2_liste_vers_tableau(LB);      //On transforme notre liste de contour en tableau pour une manipulation plus simple
    for (int i = 0; i < TLB.taille; i++) {                               //Puis, pour chaque contour,  
        Bezier3 B3 = convertion_Bezier2_Bezier3(TLB.tab[i]);
        fprintf(file, "%u %u moveto\n", B3.C0.x, B3.C0.y);        //Dit au stylo de se déplacer au 1er point
        fprintf(file, "%f %f %f %f %f %f curveto\n", B3.C1.x*n, B3.C1.y*n, B3.C2.x*n, B3.C2.y*n, B3.C3.x*n, B3.C3.y*n);
    }    

    printf("Quel mode pour le remplissage ? (0 = vide, 1 = fill)\n");   //On demande à l'utilisateur si il désire que l'image soit rempli ou vide
    int mode = 0;
    scanf("%d", &mode);                                                 //On vérifie et récupère la réponse de l'utilisateur
    
    if (mode == 1) {
        fprintf(file, "\n0 setlinewidth fill\n\nshowpage");             //On ajoute une ligne pour mettre l'image rempli si le choix est le même
    }
    else {
        fprintf(file, "\n0 setlinewidth stroke\n\nshowpage");           //On ajoute une ligne pour mettre l'image vide si le choix est le même
    }

    fclose(file);                                                       //On ferme le fichier qui est près à l'emplois
}

Liste_Bezier2 TT_contour_en_Bezier2(Liste_Contour LC) {
    Tableau_Contour TLC = sequence_Contours_liste_vers_tableau(LC);
    Liste_Bezier2 LB = creer_liste_bezier2_vide();
    for (int i = 0; i <= LC.taille; i++) {
        Bezier2 B = approx_bezier2(TLC.tab[i], 0, TLC.tab[i].taille-1);
        LB = ajouter_element_liste_Bezier2(LB, B);
    }
    return LB;
}


int main(int argc, char *argv[]){

    // if (argc>2) {
    //     printf("Erreur nombre d'arguments");
    //     exit(999);
    // }

    // Image I = lire_fichier_image(argv[1]);
    // Liste_Contour LC,LC2;
    // LC = TT_Les_Contours(I);
    // LC2 = TT_Contours_Simplifier_Douglas(LC);
    // esp_fichier_tt_contours(argv[1], LC2, hauteur_image(I), largeur_image(I));

    // Liste_Bezier2 LB = TT_contour_en_Bezier2(LC2);
    // Liste_Bezier2 LB2 = simplification_douglas_peucker_bezier2 (LC2, atol(argv[1]), atol(argv[2]), atol(argv[3]));

    Point P0; P0.x = 0; P0.y = 0;
    Point P1; P1.x = 1; P1.y = 0;
    Point P2; P2.x = 1; P2.y = 1;
    Point P3; P3.x = 1; P3.y = 2;
    Point P4; P4.x = 2; P4.y = 2;
    Point P5; P5.x = 3; P5.y = 2;
    Point P6; P6.x = 3; P6.y = 3;
    Point P7; P7.x = 4; P7.y = 3;
    Point P8; P8.x = 5; P8.y = 3;
    Liste_Point L = creer_liste_Point_vide();
    L = ajouter_element_liste_Point(L, P0);
    L = ajouter_element_liste_Point(L, P1);
    L = ajouter_element_liste_Point(L, P2);
    L = ajouter_element_liste_Point(L, P3);
    L = ajouter_element_liste_Point(L, P4);
    L = ajouter_element_liste_Point(L, P5);
    L = ajouter_element_liste_Point(L, P6);
    L = ajouter_element_liste_Point(L, P7);
    L = ajouter_element_liste_Point(L, P8);

    // double i = atol(argv[3]);
    // double t = i / (L.taille-1);
    // printf("i : %lf  ; taille : %d  ;  t : %lf\n", i, L.taille-2, t);
    Bezier2 B = approx_bezier2(L,atol(argv[1]),atol(argv[2]));
    printf("B : (%lf, %lf), (%lf, %lf), (%lf, %lf)\n", B.C0.x, B.C0.y, B.C1.x, B.C1.y, B.C2.x, B.C2.y);
    // Point Ct = Point_sur_bezier2(B, t);
    // printf("Ct = (%lf, %lf)\n", Ct.x, Ct.y);

    // double d = dist_point_Bezier2(L.first->suiv->suiv->data, B, t);
    // printf("dist : %lf\n", d);

    Liste_Bezier2 LB = simplification_douglas_peucker_bezier2 (L, atol(argv[1]), atol(argv[2]), atol(argv[3]));
    ecrire_Liste_Bezier(LB);
    char txt[] = "test2.txt";
    esp_fichier_Bezier2(txt, LB, 3, 5);
}