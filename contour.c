#include<stdio.h>               /* utilisation des entrees-sorties standard de C */
#include<stdlib.h>              /* utilisation des fonctions malloc et free */
#include <stdbool.h>            /* utilisation du type bool */
#include <string.h>             /* utilisation de manipulation des chaines de caractères*/

#include "contour.h"            //Inclusion de notre fichier header

//Ecriture visuel de la couleur du pixel
void ecrire_pixel(Pixel p){
    if (p==0){              //Si le pixel est blanc on le représente par '_'
        printf("_");
    }else if (p==1){        //Si le pixel est noir on le représente par 'N'
        printf("N");
    }
}

//print l'orientation dans le terminal (uniquement)
void ecrire_orientation(Orientation o){
    switch (o){             //On observe le type de 'o' pour determiner l'orientation
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

//Honnetement le titre explique pas mal l'utilitée de la fonction sauf qu'on renvoi les coordonnés d'un pixel et non pas d'un point comme le nom du type
Point trouver_pixel_depart(Image I){
    UINT H = hauteur_image(I);          //On défini les dimentions de l'image 'I'
	UINT L = largeur_image(I);
    
    //permet de trouver le premier pixel noir de l'image 'I'
	for (UINT i = 1; i <= H; i++){              //On vérifie pour chaque pixel qu'il est noir ou blanc (de droite à gauche puis de haut en bas)
        for (UINT j = 1; j <= L; j++){
			Pixel pix = get_pixel_image(I, j, i); 
            if (pix == NOIR) {
                return set_point(j,i);          //On renvoie le premier point noir trouvé
            }
        }
    }
    return set_point(-1,-1);        //En cas d'erreur, le point (-1,-1) est renvoyé car il ne peut pas exister peut importe l'image
}

//permet de trouver vers quel point nous devons avancer en fct de l'orientation dans la quelle nous regardons actuellement
Point avancer(Point p, Orientation o, int k){
    switch (o){         //vérifie l'orientation dans laquelle on regarde 
        case Nord : 
            return set_point(p.x,p.y - k);      //retourne le point sur lequel on doit aller 
            break;                              //('k' étant le nombre de déplacement à faire (que 1 dans notre code))
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

//permet de nous faire regarder à droite ou à gauche
Orientation tourner_robot(Orientation o, int deg) {
    int x = 0;
    if (deg == 90) {        //Si on veut regarder à gauche
        x= -1;
    }
    else if (deg == 270) {  //Si on veut regarder à droite
        x = 1;  
    }

    //comme l'orientation est un type énuméré, chaque orientation à un numéro attitré (0 à 3 pour N,E,S,O)
    switch (o+x) {      //les orientations ont été codé dans le sens horaires, donc ajouter 1 nous fais regarder à droite et -1 à gauche. 
        case 4:         //Si on dépasse 3, on retourne à 0
            return 0;
            break;
        case -1:        //Si on va en dessous de 0, on retourne à 3
            return 3;
            break;
        default:
            return (o+x);  //Sinon, on renvoie juste la nouvelle orientation
            break;
    }
}

//Trouve automatiquement et renvoie la prochaine direction en observant la couleur des cases en fonction de l'orientation 
//Lire la partie entre les deux algos page 11 du polycopié étudiant est plus que vivement recommandé
Orientation nouvelle_orientation(Image I, Point p, Orientation o){
    Pixel pG , pD ;     //On défini les points pG (point gauche) et pD, lire la partie entre les deux algos page 11 du polycopié étudiant

    switch (o) {    //Selon l'orientation actuelle 
        case Nord:
            pD = get_pixel_image(I, p.x+1, p.y);    //On définie les points pD et pG de manière purement calculatoire
            pG = get_pixel_image(I, p.x, p.y);      //lire la partie entre les deux algos page 11 du polycopié étudiant pour comprend les calculs
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
        default:                                    //En cas d'erreur d'orientation
            printf("Mauvaise orientation dans 'nouvelle Orientation'");
            exit(0);
            break;
        }

    if (pG == NOIR){                        //Si le point gauche est noir, on renvoie l'orientation en regardant à gauche
        return tourner_robot(o, 90);        
    }else if ( pD == BLANC){                //Si le point gauche ET le point droit est blanc, on renvoie l'orientation en regardant à droite
        return tourner_robot(o, 270);       
    }else{                                  //Sinon (point gauche blanc et point droit noir), on renvoie la même orientation et on continu tout droit
        return o;
    }
}

//Calcul et renvoi 1 contour et l'enregistre et dans une liste et dans un fichier (en plus de l'écrire dans le terminal)
//Cette fonction était utilisé pour la tache 3 mais est désormais parfaitement inutile
Contour memoire_sous_fichier(Image I, Point P, Point pos, Orientation O){
    //Le point P est le pixel de départ donné par 'trouver_pixel_depart'
    //L'orientation de départ est 'est' (pourquoi n'est-elle pas défini ici alors ? bah je sais pas)
    double x0 = P.x - 1, y0 = P.y - 1;  //permet de définir le point de départ 4 ligne après
    int i = 0;                          //int pour itération
    Contour C;                          //On défini C comme une liste de points vide

    C = creer_liste_Point_vide();       
    pos = set_point(x0,y0);             //Là on définit le point de départ

    FILE *file;                                     //on creer un ficher avec un nom de variable 'file'
    file = fopen("contour_ecriture.txt","w");       //On appelle le fichier 'contour_ecriture.txt' qu'on ouvre pour écrire dedans
    fprintf(file, "Taille du contour :                           points\n  ");

    while (true){                                               //Tant que nous ne sommes pas de retour à la case initiale et à la bonne orientation
        i++;                                                    //Compteur de points dans le contour
        fprintf(file," %.2lf  %.2lf\n",pos.x,pos.y);            //Ajoute le point au fichier
        // printf(" %.2lf  %.2lf\n",pos.x,pos.y);
        C = ajouter_element_liste_Point(C, pos);                //Ajoute le point à la liste contour
        pos = avancer(pos,O,1);                                 //Avance
        O = nouvelle_orientation(I,pos,O);                      //et on vérifie si on doit changer notre orientation

        if(pos.x == x0 && pos.y == y0 && O == Est){             //Condition qui vérifie le retour à la case initiale et à la bonne orientation
            break;
        }
    }
    fprintf(file," %.2lf  %.2lf\n",pos.x,pos.y);                //On refait une dernière itération pour remettre le 1er élément à la fin du contour,
    C = ajouter_element_liste_Point(C, pos);                    //pour boucler le tour du contour
    printf("C :");                           //On ecrit dans le terminal notre contour
    // printf(" %.2lf  %.2lf\n",pos.x,pos.y);
    rewind(file);                                               //retour au début de fichier
    fprintf(file,"Taille du contour : %d points\n\n",i+1);      //on écrit dans le fichier le nombre de points dans le contour

    fclose(file);                                               //On ferme le fichier
    return C;                                                   //Et on renvoi notre liste contour
}

//Ecrit dans un fichier l'ensemble des points de 1 contour de manière à pouvoir être ouvert par un fichier image eps
void eps_fichier(FILE *file, Contour C, UINT h, UINT l){
    fprintf(file, "%f %f moveto\n", C.first->data.x, h-C.first->data.y);        //Dit au stylo de se déplacer au 1er point
        C.first = C.first->suiv;
    while (C.first != C.last) {
        fprintf(file, "%f %f lineto\n", C.first->data.x, h-C.first->data.y);    //Puis on relis tous les points les uns entre les autres
        C.first = C.first->suiv;
    }
    fprintf(file, "%f %f lineto\n", C.last->data.x, h-C.last->data.y);          //Jusqu'au dernier
}

//Permet d'écrire l'ensemble des contours dans un fichier eps pouvant être lu comme une image affichable
void esp_fichier_tt_contours(char nom[], Liste_Contour LC, UINT h, UINT l) {
    int size = strlen(nom);                                 //On récupère la taille du nom du fichier image donné en argument de la commande dans le terminal
    for(int i = size; i > (size - 4); i--) {                //On lui retire son extention '.pbm'
        nom[i-1] = '\0';
    }
    nom = strcat(nom, ".eps");                              //Puis on rajoute '.eps' pour faire le nom de notre fichier image affichable
    
    FILE *file;                                             //On créer un fichier
    file = fopen(nom, "w");                                 //Avec le nom qu'on viens de créer, puis on dit qu'on veut écrire dedans
    fprintf(file, "%%!PS-Adobe-3.0 EPSF-3.0\n");                //On écrit les deux premières lignes obligatoires du format .eps
    fprintf(file , "%%%%BoundingBox: 0 0 %u %u\n\n", l, h);     //Avec la taille de l'image à créer (donc les mêmes que l'image donné)

    Tableau_Contour TLC = sequence_Contours_liste_vers_tableau(LC);      //On transforme notre liste de contour en tableau pour une manipulation plus simple
    for (int i = 0; i < TLC.taille; i++) {                               //Puis, pour chaque contour,  
        eps_fichier(file, TLC.tab[i], h, l);                             //on les écrit dans le fichier 
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

//Renvoie si l'image en argument est vide (true) ou avec au moins une case rempli de noir (false)
bool image_vide(Image I) {
    for (int h = 0; h<=hauteur_image(I); h++){              //on regarde chaque pixel de l'image en argument de gauche à droite puis de haut en bas
        for (int l = 0; l<=largeur_image(I); l++){
            if (get_pixel_image(I,l,h) == NOIR ) {          //Si un des pixels est noir
                return false;                               //on retourne 'false'
                break;
            }
        }
    }
    return true;                                            //Sinon on retourne 'true'
}

//On créer et renvoie une image calque, identique à celle d'origine mais où on mis les pixels en noir que ceux qui était noir dans l'original et avec le voisin du dessus blanc
//Voir l'étape 1 de la page 22 du polycopié étudiant 
Image Image_calque(Image I){
    Image Calque = creer_image(largeur_image(I), hauteur_image(I));                     //On créer une image vide avec les mêmes dimensions que l'originale
    for (int h = 0; h<=hauteur_image(I); h++){                                          //Pour chaque pixel de l'image de gauche à droite puis de haut en bas
        for (int l = 0; l<=largeur_image(I); l++){
            if (get_pixel_image(I,l,h) == NOIR && get_pixel_image(I,l,h-1)==BLANC) {    //Si dans l'image originale, le pixel était noir et son voisin du dessus blanc
                set_pixel_image(Calque, l, h, NOIR);                                    //On met ce pixel en noir
            }
        }
    }
    // ecrire_image(Calque);                                                               //écrit notre nouvelle image calque
    return(Calque);                                                                     //On renvoie notre nouvelle image calque
}

//Calcule et retourne une liste de tous les contours de l'image en argument dans la commande du terminal
Liste_Contour TT_Les_Contours(Image I) {
    Orientation O = Est;                                                    //Définie l'orientation O initiale à Est
    Liste_Contour LC = creer_liste_Contour_vide();                          //Créer une liste de contour vide
    Image Calque = Image_calque(I);                                         //Créer notre image calque 
    int nb_contours = 0, nb_point_total = 0, nb_segment = 0;                //initialisation des compteurs pour les stats (pas aussi importante que celle d'un match de tennis)

    while (!image_vide(Calque)){                                            //Tant que l'image calque n'est pas vide
        Point P = trouver_pixel_depart(Calque);                             //On trouve notre pixel de départ depuis l'image calque
        Contour C = creer_liste_Point_vide();                               //On créer un contour vide (liste de point)
        
        double x0 = P.x - 1, y0 = P.y - 1;                                  //"calcul" de notre point initial
        int i = 0;

        Point pos = set_point(x0,y0);                                       //On pose notre point inital

        // printf("P : x=%f, y=%f\n", P.x, P.y);                              //prints de débuggage (ne pas garder si possible) #47
        // printf("pos : x=%f, y=%f\n", pos.x, pos.y);

        while (true){                                                       //tant que nous ne somme pas retourner au point inital de notre contour et à la bonne orientation
            i++;
            // printf(" %.2lf  %.2lf\n",pos.x,pos.y);                         //prints de débuggage (ne pas garder si possible) #47
            C = ajouter_element_liste_Point(C, pos);                        //On ajoute le point à notre contour
            pos = avancer(pos,O,1);                                         //Puis on avance
            O = nouvelle_orientation(I,pos,O);                              //Et on change d'orientation si nécéssaire pour la prochaine avancé

            if (O==Est) {                                                   //Si on regarde (l'orientation est) à l'Est 
                set_pixel_image(Calque, pos.x+1, pos.y+1, BLANC);           //On remplace le pixel correspondant au point à Blanc sur le calque
            }                                                               //voir l'étape 2 de la page 22 du polycopié étudiant

            if(pos.x == x0 && pos.y == y0 && O == Est){                     //Permet de vérifier que nous somme retourner au point inital de notre contour 
                break;                                                      //et avec l'orientation à l'est
            }
        }
        C = ajouter_element_liste_Point(C, pos);                            //Puis on remet le point inial dans le contour pour "boucler" celui-ci
        set_pixel_image(Calque, pos.x+1, pos.y+1, BLANC);                   //Le point inital devient blanc sur le calque 
        // printf("C :"); ecrire_contour(C);                                  //prints de débuggage (ne pas garder si possible) #47
        // ecrire_image(Calque);                                              //prints de débuggage (ne pas garder si possible) #47
        i++;

        nb_contours++;                                                      //On compte un contour de plus
        nb_point_total = nb_point_total +i;                                 //On augmente le nombre total de point par le nombre de point dans le contour actuel
        nb_segment = nb_segment +i -1;                                      //On augmente le nombre total de segment par le nombre de segment dans le contour actuel
        //                                                                  //(-1 pour retirer le segment qui fait le liens entre le dernier point et le premier)
        LC = ajouter_element_liste_Contour(LC, C);                          //Puis on ajoute le contour actuel à notre liste de contour
    }

    // ecrire_list_contour(LC);                                                            //écriture de la liste de contours dans le terminal #47
    printf("On a trouvé %d contours \n", nb_contours);                                  //Affichage des stats #47
    printf("Avec un total de %d points et %d segments\n", nb_point_total, nb_segment);

    return LC;                                                                          //Retourne la liste de contours
}

//Calcule et renvoie la distance entre un point P et un segment [A,B]
//Voir la page 26 du polycopié étudiant 
double dist_seg(Point A, Point B, Point P){
    if (A.x == B.x && A.y == B.y){              //cas si A=B
        return distance(A,P);                   //Bah on retourne la distance entre P et A
    }
    else {                                      //cas si A différent de B
        //Calcul de lambda, une variable permettant de savoir la position de P par rapport au segment [A,B]
        double lambda = produit_scalaire(vect_bipoint(A,P),vect_bipoint(A,B))/produit_scalaire(vect_bipoint(A,B),vect_bipoint(A,B));
        // printf("Lambda : %f\n", lambda);
        if (lambda<0) {                         //Si le Q, projeté de P par rapport à [A,B], est avant A
            // printf("1\n");                        //prints de débuggage (ne pas garder si possible) #47
            return distance(A, P);              //On retourne la distance entre A et P
        }
        else if (lambda <= 1) {                 //Si le Q, projeté de P par rapport à [A,B], est entre A et B inclus
            Point Q;                            //On défini et calcul la position de Q (voir calcul en bas de la p26 du polycopié étudiant)
            Q.x = A.x + lambda*(B.x-A.x);
            Q.y = A.y + lambda*(B.y-A.y);
            // printf("2\n");                        //prints de débuggage (ne pas garder si possible) #47
            return distance(Q, P);              //On retourne la distance entre Q et P
        }
        else {                                  //Si le Q, projeté de P par rapport à [A,B], est après B
            // printf("3\n");                        //prints de débuggage (ne pas garder si possible) #47
            return distance(B, P);              //On retourne la distance entre B et P
        }
    }
}

//Fonction récurente qui renvoie un contour simplifié 
//Lire page 27 à 29 du polycopié de livret étudiant (de TD)
Liste_Point simplification_douglas_peucker(Contour C, int j1, int j2, double d) {
    Tableau_Point TC = sequence_points_liste_vers_tableau(C);       //On transforme notre contour en tableau de point pour une manipulation plus facile 
    Liste_Point L = creer_liste_Point_vide();                       //On créer la liste simplifier vide
    double dmax = 0, dj = 0;
    int k = j1;

    for (int j = j1+1; j <= j2; j++) {                              //Pour chaque points entre les point j1 et j2
        dj = dist_seg(TC.tab[j1], TC.tab[j2], TC.tab[j]);           //On regarde la distance du point par rapport au segment des points j1-j2
        if (dmax < dj){                                             //On trouve le point qui est le plus éloigné du segment
            dmax = dj;
            k = j;          //indice du point le plus éloigné
        }
    }

    if (dmax <= d) {                                                         //Si la distance du point le plus éloigné est plus grand que la précision
        L = ajouter_element_liste_Point(L, TC.tab[j1]);                         //On rajoute les points du segments dans la liste simplifiée
        L = ajouter_element_liste_Point(L, TC.tab[j2]);
    } else {                                                                //Sinon, on divise le segment au point le plus éloigné et on recommence
        Liste_Point L1 = simplification_douglas_peucker(C, j1, k, d);       // #divide&conquer
        Liste_Point L2 = simplification_douglas_peucker(C, k, j2, d);
        L2 = supprimer_premier_element_liste_Point(L2);
        L = concatener_liste_Point(L1, L2);
    }
    // ecrire_contour(L);
    return L;   //On renvoi notre liste simplifié
}

Liste_Contour TT_Contours_Simplifier_Douglas(Liste_Contour LC){
    Tableau_Contour TLC = sequence_Contours_liste_vers_tableau(LC);      //On transforme notre liste de contour en tableau pour une manipulation plus simple
    Liste_Contour TTL = creer_liste_Contour_vide();                       //TT les contours simplifier
    
    printf("Quel degré de simplification voulez-vous ? (entre 0 et 1)\n");      //On demande à l'utilisateur si il désire que l'image soit rempli ou vide
    double d = 0;
    scanf("%lf", &d);                                                            //On vérifie et récupère la réponse de l'utilisateur
    
    
    for (int i = 0; i < TLC.taille; i++) {                               //Puis, pour chaque contour,  
        printf("%d\n", i);
        Liste_Point L1 = creer_liste_Point_vide();
        Liste_Point L, L2;
        L1 = ajouter_element_liste_Point(L1, TLC.tab[i].first->data);

        L2 = simplification_douglas_peucker(TLC.tab[i], 0, TLC.tab[i].taille -1, d);
        L2 = supprimer_premier_element_liste_Point(L2);                                 //LIGNE EXTREMEMENT IMPORTANTE
        L = concatener_liste_Point(L1, L2);
        // ecrire_contour(L);
        TTL = ajouter_element_liste_Contour(TTL, L);
    }  
    ecrire_list_contour(TTL);
    return TTL;
}

int nb_points(Liste_Contour LC){
    int s = 0;
    Cellule_Liste_Contour* cel = LC.first;
    while(cel != NULL){
        s = s + (cel->data.taille);
        cel = cel->suiv;
    }
    return s;
}

int main(int argc, char *argv[]){

    if (argc>2) {
        printf("Erreur nombre d'arguments");
        exit(999);
    }

    Image I = lire_fichier_image(argv[1]);
    Liste_Contour LC,LC2;
    LC = TT_Les_Contours(I);
    LC2 = TT_Contours_Simplifier_Douglas(LC);
    int p = nb_points(LC2);
    printf("AAAAAAAAAAAAAH %d\n", (p-LC2.taille));
    //esp_fichier_tt_contours(argv[1], LC2, hauteur_image(I), largeur_image(I));
    
}