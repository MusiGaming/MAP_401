#include<stdio.h>               /* utilisation des entrees-sorties standard de C */
#include<stdlib.h>              /* utilisation des fonctions malloc et free */
#include <stdbool.h>            /* utilisation du type bool */
#include <string.h>             /* utilisation de manipulation des chaines de caractères*/

#include "simplification_Bezier.h"            //Inclusion de notre fichier header


Bezier2 approx_bezier2(Liste_Point L, int j1, int j2) {
    Tableau_Point C = sequence_points_liste_vers_tableau(L);
    Bezier2 B;
    Point P1 = C.tab[j1];
    Point P2 = C.tab[j2];
    double n = j2 - j1;
    B.C0 =  P1;
    B.C2 = P2 ;
    double Cx,Cy;
    

    if (n == 1 ){
        Cx = (P1.x + P2.x)/2.;
        Cy = (P1.y + P2.y)/2.;
        B.C1 = set_point(Cx,Cy);
    }
    else {
        
        double a = 3 * n / (pow(n,2)-1);
        double b = (1 - 2* n )/ (2*(n+1));
        Point P;
        P.x = 0;
        P.y = 0;
        for (int i = 1 ; i <= n-1; i++){

            P = add_point(P, C.tab[i + j1]);
        }
        Cx = P.x * a + b * (P1.x + P2.x);
        Cy = P.y * a + b * (P1.y + P2.y);
        B.C1 = set_point(Cx, Cy);
        
    }
    return B;
}

Point Point_sur_bezier2 (Bezier2 B, double t) {
    Point Ct;
    Ct.x = ((1-t)*(1-t))*B.C0.x + 2*t*(1-t)*B.C1.x + (t*t)*B.C2.x;
    Ct.y = ((1-t)*(1-t))*B.C0.y + 2*t*(1-t)*B.C1.y + (t*t)*B.C2.y;
    // printf("Ct = (%lf, %lf)\n", Ct.x, Ct.y);
    return Ct;
}

double dist_point_Bezier2 (Point P, Bezier2 B, double t) {
    Point Ct = Point_sur_bezier2(B,t);
	Vecteur V = vect_bipoint (P, Ct);
	double d = norme_euclidienne(V);
    // printf ("d : %lf\n", d);
	return d;
}

Liste_Bezier2 simplification_douglas_peucker_bezier2 (Liste_Point LP, int j1, int j2, double d) {
    Tableau_Point CONT = sequence_points_liste_vers_tableau(LP);
    double n = j2-j1;
    
    Liste_Bezier2 L,L1,L2;

	Bezier2 C = approx_bezier2 (LP,j1,j2);
    
    double dmax = 0;
    int k = j1;
    for (int j=j1+1; j<=j2 ; j++){
		double i=j-j1;
		double ti = i/n;
        Point P = CONT.tab[j];
        double dj = dist_point_Bezier2(P, C, ti);
        if ( dmax<dj) {
            dmax = dj;
            k=j;
        }
    }
    
    L  = creer_liste_bezier2_vide();
	L1 = creer_liste_bezier2_vide();
	L2 = creer_liste_bezier2_vide();
    
    if (dmax <= d){
        L = ajouter_element_liste_Bezier2(L,C);
    } else {
        L1 = simplification_douglas_peucker_bezier2(LP,j1,k,d);
		L2 = simplification_douglas_peucker_bezier2(LP,k,j2,d);
		L = concatener_liste_Bezier2(L1,L2);
    }
    return L;
}

Bezier3 convertion_Bezier2_Bezier3(Bezier2 B2) {
    Bezier3 b3;
    b3.C0=B2.C0;
    b3.C1.x=(2*(B2.C1.x)+B2.C0.x)/3;
    b3.C1.y=(2*(B2.C1.y)+B2.C0.y)/3;
    b3.C2.x=(2*(B2.C1.x)+B2.C2.x)/3;
    b3.C2.y=(2*(B2.C1.y)+B2.C2.y)/3;
    b3.C3=B2.C2;
    return  b3;
}

//Permet d'écrire l'ensemble des contours dans un fichier eps pouvant être lu comme une image affichable
void esp_fichier_Bezier2(char nom[], Liste_Liste_Bezier2 LLB, UINT h, UINT l) {
    Tableau_Liste_Bezier2 TLLB = sequence_Bezier2_liste_liste_vers_tableau(LLB);
    Tableau_Bezier2 TLB;
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
        printf("k:%d\n",k);
        TLB = sequence_Bezier2_liste_vers_tableau(TLLB.tab[k]);      //On transforme notre liste de contour en tableau pour une manipulation plus simple

        B3 = convertion_Bezier2_Bezier3(TLB.tab[0]);
        fprintf(file, "%f %f moveto\n", B3.C0.x, h-B3.C0.y);        //Dit au stylo de se déplacer au 1er point
        for (int i = 0; i < TLB.taille; i++) {                               //Puis, pour chaque contour,  
            B3 = convertion_Bezier2_Bezier3(TLB.tab[i]);
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

Liste_Liste_Bezier2 TT_contour_en_Bezier2(Liste_Contour LC) {
    Tableau_Contour TLC = sequence_Contours_liste_vers_tableau(LC);
    Liste_Liste_Bezier2 LB = creer_liste_liste_bezier2_vide();
    
    printf("Quel degré de simplification voulez-vous ? \n");      //On demande à l'utilisateur si il désire que l'image soit rempli ou vide
    double d = 0;
    scanf("%lf", &d);

    for (int i = 0; i <= LC.taille-1; i++) {

        Liste_Bezier2 LB2 = simplification_douglas_peucker_bezier2(TLC.tab[i],0, TLC.tab[i].taille -1, d);
        LB = ajouter_element_liste_liste_Bezier2(LB, LB2);
    }
    // ecrire_Liste_Bezier(LB);
    return LB;
}
