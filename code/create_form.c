#include "projet_svg.h"

//fonction pour vider le tampon clavier
void clear_stdin(void) {
    int c;
    while ((c = getc(stdin)) != '\n' && c != EOF);
}

// Fonction pour demander et valider une couleur hexadécimale (format RRGGBB)
char* add_color(void) {
    char buffer[100];
    bool valide = false;
    while (!valide) {
        printf("Entrez une couleur au format hexadécimal (ex: FF0000) : \n");
        if (scanf("%99s", buffer) != 1) {
            // Vider le buffer en cas d'erreur de lecture
            while (getchar() != '\n');
            continue;
        }
        // Vide le reste du tampon clavier
        clear_stdin();
        // Vérification de la longueur
        if (strlen(buffer) != 6) {
            printf("Erreur : La couleur doit contenir exactement 6 caractères (ex: FFFFFF).\n");
            continue;
        }
        // Vérification que les 6 caractères suivants sont bien hexadécimaux
        valide = true;
        for (int i = 0; i < 6; i++) {
            if (!isxdigit((unsigned char)buffer[i])) {
                valide = false;
                break;
            }
        }
        if (!valide) {
            printf("Erreur : Caractères hexadécimaux invalides (utilisez 0-9 et A-F).\n");
        }
    }
    // Allocation dynamique de la couleur validée
    char *color = malloc(8 * sizeof(char));
    if (color != NULL) {
        strcpy(color, buffer);
    }
    return color;
}

//fonction pour créé les points
int add_new_point(point *p){
    int verif;
    do{
        printf("Entrer l'abscisse du point (entier positif inferieur a 500)\n");
        verif=scanf("%d",&p->x);
        //vide le buffer d entrer
        clear_stdin();
    }while(verif !=1 || p->x<0 || p->x>500);
    do{
        printf("Entrer l'ordonnée du point (entier positif inferieur a 500)\n");
        verif=scanf("%d",&p->y);
        //vide le buffer d entrer
        clear_stdin();
    }while(verif !=1 || p->y<0 || p->y>500);
    return 0;
}

//fonction pour créé le rayon
int add_radius(void){
    int r;
    int verif;
    do{
        printf("Entrer le rayon (entier positif)\n");
        verif=scanf("%d",&r);
        //vide le buffer d entrer
        clear_stdin();
    }while(verif !=1 || r<=0);
    return r;
}

//fonction pour créé les cercles
int add_new_circle(FILE *file){
    figure *c=malloc(sizeof(circle_s));
    c->circle=malloc(sizeof(circle_s));
    //centre
    c->circle->center=malloc(sizeof(point));
    add_new_point(c->circle->center);
    //rayon
    c->circle->radius=add_radius();
    //couleur
    c->circle->color_border=add_color();
    c->circle->color=add_color();
    //ajout de la ligne
    fprintf(file,"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"#%s\" fill=\"#%s\"/>\n", c->circle->center->x, c->circle->center->y, c->circle->radius, c->circle->color_border, c->circle->color);
    //liberation de la memoire allouer
    free(c->circle->center);
    free(c->circle->color);
    free(c->circle->color_border);
    free(c->circle);
    free(c);
    return 0;
}

//fonction pour créé les lignes
int add_new_line(FILE *file){
    figure *l=malloc(sizeof(line_s));
    l->line=malloc(sizeof(line_s));
    //point a
    l->line->a=malloc(sizeof(point));
    add_new_point(l->line->a);
    //point b
    l->line->b=malloc(sizeof(point));
    add_new_point(l->line->b);
    //couleur
    l->line->color=add_color();
    //ajoute de la ligne
    fprintf(file,"<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"#%s\" />\n", l->line->a->x, l->line->a->y, l->line->b->x, l->line->b->y, l->line->color);
    //liberation de la memoire allouer
    free(l->line->color);
    free(l->line->a);
    free(l->line->b);
    free(l->line);
    free(l);
    return 0;
}

//fonction principal
int add_new_form(void){
    unsigned char choice;
    bool boucle = true;
    //ouvre le fichier htlm, le créer si il n'existe pas
    FILE *file = fopen("index/index.html", "w");//chemin absolu : /mnt/c/Users/lixis/Desktop/devellopement/coda/projet/projet/index/index.html
    if(file==NULL){
        printf("Une erreur est survenu lors du chargement du fichier");
        return 0;
    }
    fprintf(file, "<svg viewBox=\"0 0 500 500\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    //creation des forme dans le fichier
    while(boucle){
        printf("\nChoix des formes :\n");
        printf("=> 0 - Quittez\n");
        printf("=> 1 - Ligne\n");
        printf("=> 2 - Cercle\n");
        scanf(" %c",&choice);
        switch (choice){
        case '0':
            boucle=false;
            break;
        case '1':
            add_new_line(file);
            break;
        case '2':
            add_new_circle(file);
            break;
        default:
            printf("Option invalide\n");
            break;
        }
        //vide l entrer clavier avant de demander l option
        clear_stdin();
    }
    //fermeture du fichier
    fprintf(file, "</svg>");
    fclose(file);
    return 0;
}