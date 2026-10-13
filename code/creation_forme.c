#include "projet_svg.h"

// Fonction pour demander et valider une couleur hexadécimale (format RRGGBB)
char* add_color(void) {
    char buffer[100];
    bool valide = false;
    while (!valide) {
        printf("Entrez une couleur au format hexadécimal (ex: FF0000) : ");
        if (scanf("%99s", buffer) != 1) {
            // Vider le buffer en cas d'erreur de lecture
            while (getchar() != '\n');
            continue;
        }
        // Vide le reste du tampon clavier
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
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
    char *color_ptr = malloc(8 * sizeof(char));
    if (color_ptr != NULL) {
        strcpy(color_ptr, buffer);
    }
    return color_ptr;
}

int add_new_point(point *p){
    do{
        printf("Entrer l'abscisse du point (entier positif inferieur a 500)");
        scanf("%d",&p->x);
    }while(p->x<0 || p->x>500);
    do{
        printf("Entrer l'ordonnée du point (entier positif inferieur a 500)");
        scanf("%d",&p->y);
    }while(p->y<0 || p->y>500);
    return 0;
}

int add_new_line(FILE *file){
    line *l=malloc(sizeof(line));
    //point a
    l->a = malloc(sizeof(point));
    add_new_point(l->a);
    //point b
    l->b = malloc(sizeof(point));
    add_new_point(l->b);
    //couleur
    l->color=add_color();
    //ajoute de la ligne (a modifier plus tard pour les sauvegarde)
    fprintf(file,"<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"#%s\" />\n", l->a->x, l->a->y, l->b->x, l->b->y, l->color);
    //liberation de la memoire allouer
    free(l->color);
    free(l->a);
    free(l->b);
    free(l);
    return 0;
}

int add_new_form(void){
    unsigned char choice;
    bool boucle = true;

    //ouvre le fichier htlm, le créer si il n'existe pas
    FILE *file = fopen("../index/index.html", "w");
    fprintf(file, "<svg viewBox=\"0 0 500 500\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    if(file==NULL){
        printf("Une erreur est survenu lors du chargement du fichier");
        return 0;
    }
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
            //code de creation des forme
            break;
        default:
            printf("Option invalide\n");
            break;
        }
    }
    //fermeture du fichier
    fprintf(file, "</svg>");
    fclose(file);
    return 0;
}