#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include <stdbool.h>
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

void memoire_sous_fichier(Image I, Point P, Point pos, Orientation O){
    double x0 = P.x - 1, y0 = P.y - 1;
    int i = 0;

    pos = set_point(x0,y0);

    FILE *file;
    file = fopen("contour_ecriture.txt","w");
    fprintf(file, "\n   ");

    while (true){
        i++;
        fprintf(file," %.2lf  %.2lf\n",pos.x,pos.y);
        pos = avancer(pos,O,1);
        O = nouvelle_orientation(I,pos,O);

        if(pos.x == x0 && pos.y == y0 && O == Est){
            break;
        }
    }
    fprintf(file," %.2lf  %.2lf\n",pos.x,pos.y);
    rewind(file);
    fprintf(file,"%d\n\n",i+1);

    fclose(file);
}

void memoire_tableau(){
    unsigned int DIM_MAX = 10000;
    typedef Point TabPoints[DIM_MAX];
    typedef struct Contour_{
        unsigned int np;
        TabPoints tab;
    }Contour;
    
}

void memoriser_position(FILE *file, Point pos){
    fprintf(file," %.2lf  %.2lf\n",pos.x,pos.y);
}

int main(int argc, char *argv[]){

    if (argc>2) {
        printf("Erreur nombre d'arguments");
        exit(999);
    }

    Point P,pos;
    Image I = lire_fichier_image(argv[1]);
    Orientation O = Est ; 
    double x0 = P.x - 1, y0 = P.y - 1;

    pos = set_point(x0,y0);
    P = trouver_pixel_depart(I);

    tests(P);

    printf("contour de l'image: \n");

    memoire_sous_fichier(I, P, pos, O); 
}

