#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include <stdbool.h>
#include <string.h>
#include "contour.h"


void ecrire_pixel(Pixel p){
    if (p==0){
        printf("_");
    }else if (p==1){
        printf("N");
    }
}

void ecrire_orientation(Orientation o){
    switch (o){
        case Nord :
            printf("Nord \n");
            break;
        case Est :
            printf("Est \n");
            break;
        case Sud :
            printf("Sud \n");
            break;
        case Ouest :
            printf("Ouest \n");
            break;
        default : 
            printf("Erreur, verifier orientation. \n");
            break;
    }
}

Point trouver_pixel_depart(Image I){
    UINT H = hauteur_image(I);
	UINT L = largeur_image(I);
    
	for (UINT i = 1; i <= H; i++){
        for (UINT j = 1; j <= L; j++){
			Pixel pix = get_pixel_image(I, j, i);
            if (pix == NOIR) {
                return set_point(j,i);
            }
        }
    }
    return set_point(-1,-1);
}

Point avancer(Point p, Orientation o, int k){
    switch (o){
        case Nord : 
            return set_point(p.x,p.y - k);
            break;
        case Est :
            return set_point(p.x + k,p.y);
            break;   
        case Sud : 
            return set_point(p.x,p.y + k);
            break;
        case Ouest : 
            return set_point(p.x - k, p.y);
            break;
    }
}

Orientation tourner_robot(Orientation o, int deg) {
    int x = 0;
    if (deg == 90) {
        x= -1;
    }
    else if (deg == 270) {
        x = 1;
    }

    switch (o+x) {
    case 4:
        return 0;
        break;
    case -1:
        return 3;
        break;
    default:
        return (o+x);
        break;
    }
}


Orientation nouvelle_orientation(Image I, Point p, Orientation o){
    Pixel pG , pD ; 

    switch (o) {
    case Nord:
        pD = get_pixel_image(I, p.x+1, p.y);
        pG = get_pixel_image(I, p.x, p.y);
        break;
    case Est:
        pD = get_pixel_image(I, p.x+1, p.y+1);
        pG = get_pixel_image(I, p.x+1, p.y);
        break;
    case Sud:  
        pD = get_pixel_image(I, p.x, p.y+1);
        pG = get_pixel_image(I, p.x+1, p.y+1);
        break;
    case Ouest:
        pD = get_pixel_image(I, p.x, p.y);
        pG = get_pixel_image(I, p.x, p.y+1);
        break;
    default:
        printf("Mauvaise orientation dans 'nouvelle Orientation'");
        exit(0);
        break;
    }

    if (pG == NOIR){
        return tourner_robot(o, 90);
    }else if ( pD == BLANC){
        return tourner_robot(o, 270);
    }else{
        return o;
    }
}

void tests(Point P) {
    printf("Case INITIIIIIIIIIIIAALE : (%.2lf , %.2lf) \n", P.x,P.y);
}

Contour memoire_sous_fichier(Image I, Point P, Point pos, Orientation O){
    double x0 = P.x - 1, y0 = P.y - 1;
    int i = 0;
    Contour C;

    C = creer_liste_Point_vide();
    pos = set_point(x0,y0);

    FILE *file;
    file = fopen("contour_ecriture.txt","w");
    fprintf(file, "Taille du contour :   points\n  ");

    while (true){
        i++;
        fprintf(file," %.2lf  %.2lf\n",pos.x,pos.y);
        // printf(" %.2lf  %.2lf\n",pos.x,pos.y);
        C = ajouter_element_liste_Point(C, pos);
        pos = avancer(pos,O,1);
        O = nouvelle_orientation(I,pos,O);

        if(pos.x == x0 && pos.y == y0 && O == Est){
            break;
        }
    }
    fprintf(file," %.2lf  %.2lf\n",pos.x,pos.y);
    C = ajouter_element_liste_Point(C, pos);
    printf("C :"); ecrire_contour(C);
    // printf(" %.2lf  %.2lf\n",pos.x,pos.y);
    rewind(file);
    fprintf(file,"Taille du contour : %d points\n\n",i+1);

    fclose(file);
    return C;
}

void memoriser_position(FILE *file, Point pos){
    fprintf(file," %.2lf  %.2lf\n",pos.x,pos.y);
}

void eps_fichier(FILE *file, Contour C, UINT h, UINT l){
    fprintf(file, "%f %f moveto\n", C.first->data.x, h-C.first->data.y);
        C.first = C.first->suiv;
    while (C.first->suiv != C.last) {
        fprintf(file, "%f %f lineto\n", C.first->data.x, h-C.first->data.y);
        C.first = C.first->suiv;
    }
    fprintf(file, "%f %f lineto\n", C.last->data.x, h-C.last->data.y);
}

void esp_fichier_tt_contours(char nom[], Liste_Contour LC, UINT h, UINT l) {
    int size = strlen(nom);
    for(int i = size; i > (size - 4); i--) {
        nom[i-1] = '\0';
    }
    nom = strcat(nom, ".eps");
    
    FILE *file;
    file = fopen(nom, "w");
    fprintf(file, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(file , "%%%%BoundingBox: 0 0 %u %u\n\n", l, h);

    Tableau_Contour TC = sequence_Contours_liste_vers_tableau(LC);
    for (int i = 0; i < TC.taille; i++) {
        eps_fichier(file, TC.tab[i], h, l);
    }    

    printf("Quel mode pour le remplissage ? (0 = vide, 1 = fill)\n");
    int mode = 0;
    scanf("%d", &mode);
    
    if (mode == 1) {
        fprintf(file, "\n0 setlinewidth fill\n\nshowpage");
    }
    else {
        fprintf(file, "\n0 setlinewidth stroke\n\nshowpage");
    }

    fclose(file);
}

bool image_vide(Image I) {
    for (int h = 0; h<=hauteur_image(I); h++){
        for (int l = 0; l<=largeur_image(I); l++){
            if (get_pixel_image(I,l,h) == NOIR ) {
                return false;
                break;
            }
        }
    }
    return true;
}

Image Image_calque(Image I){
    Image Calque = creer_image(largeur_image(I), hauteur_image(I));
    for (int h = 0; h<=hauteur_image(I); h++){
        for (int l = 0; l<=largeur_image(I); l++){
            if (get_pixel_image(I,l,h) == NOIR && get_pixel_image(I,l,h-1)==BLANC) {
                set_pixel_image(Calque, l, h, NOIR);
            }
        }
    }
    ecrire_image(Calque);
    return(Calque);
}

Liste_Contour TT_Les_Contours(Image I, Orientation O) {
    Liste_Contour LC = creer_liste_Contour_vide();
    Image Calque = Image_calque(I);
    int nb_contours = 0, nb_point_total = 0, nb_segment = 0;

    while (!image_vide(Calque)){
        Point P = trouver_pixel_depart(Calque);
        Contour C = creer_liste_Point_vide();
        
        double x0 = P.x - 1, y0 = P.y - 1;
        int i = 0;

        Point pos = set_point(x0,y0);

        // printf("P : x=%f, y=%f\n", P.x, P.y);
        // printf("pos : x=%f, y=%f\n", pos.x, pos.y);

        while (true){
            i++;
            // printf(" %.2lf  %.2lf\n",pos.x,pos.y);
            C = ajouter_element_liste_Point(C, pos);
            pos = avancer(pos,O,1);
            O = nouvelle_orientation(I,pos,O);
            
            if (O==Est) {
                set_pixel_image(Calque, pos.x+1, pos.y+1, BLANC);
            }

            if(pos.x == x0 && pos.y == y0 && O == Est){
                break;
            }
        }
        C = ajouter_element_liste_Point(C, pos);
        set_pixel_image(Calque, pos.x+1, pos.y+1, BLANC);
        printf("C :"); ecrire_contour(C);
        ecrire_image(Calque);
        i++;

        nb_contours++;
        nb_point_total = nb_point_total +i;
        nb_segment = nb_segment +i -1;

        LC = ajouter_element_liste_Contour(LC, C);
    }

    printf("On a trouvé %d contours \n", nb_contours);
    printf("Avec un total de %d points et %d segments\n", nb_point_total, nb_segment);

    // ecrire_list_contour(LC);
    return LC;
}


int main(int argc, char *argv[]){

    if (argc>2) {
        printf("Erreur nombre d'arguments");
        exit(999);
    }

    Point P,pos;
    Image I = lire_fichier_image(argv[1]);
    Orientation O = Est ;
    // Contour C;
    double x0 = P.x - 1, y0 = P.y - 1;

    pos = set_point(x0,y0);
    P = trouver_pixel_depart(I);

    Liste_Contour LC;
    LC = TT_Les_Contours(I, O);

    esp_fichier_tt_contours(argv[1], LC, hauteur_image(I), largeur_image(I));
}