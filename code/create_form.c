#include "projet_svg.h"

// Définition de la scène globale
Scene ma_scene = { .count = 0 };

//fonction pour vider le tampon clavier
void clear_stdin(void) {
    int c;
    while ((c = getc(stdin)) != '\n' && c != EOF);
}

// Fonction pour demander et valider une couleur hexadécimale (format RRGGBB)
char* add_color(void) {
    char buffer[20];
    bool valide = false;
    while (!valide) {
        printf("Entrez une couleur au format hexadécimal (ex: FF0000) : \n");
        if (scanf("%19s", buffer) != 1) {
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
    char *color = malloc(6 * sizeof(char));
    if (color != NULL) {
        strcpy(color, buffer);
    }
    return color;
}

//fonction pour créé les points
int add_new_point(point *p){
    int verif;
    do{
        printf("Entrer l'abscisse du point (entier compris entre -250 et 250)\n");
        verif=scanf("%d",&p->x);
        //vide le buffer d entrer
        clear_stdin();
    }while(verif !=1 || p->x<-250 || p->x>250);
    do{
        printf("Entrer l'ordonnée du point (entier compris entre -250 et 250)\n");
        verif=scanf("%d",&p->y);
        //vide le buffer d entrer
        clear_stdin();
    }while(verif !=1 || p->y<-250 || p->y>250);
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

// Fonction pour créer les cercles et les ajouter à la liste chaînée
int add_new_circle(void){
    circle_s *c = malloc(sizeof(circle_s));
    c->center = malloc(sizeof(point));
    add_new_point(c->center);
    c->radius = add_radius();
    c->color_border = add_color();
    c->color = add_color();

    node_t *new_node = malloc(sizeof(node_t));
    new_node->fig.circle = c;
    new_node->type = CIRCLE;
    new_node->next = NULL;

    // Ajout en fin de liste
    if (ma_scene.head == NULL) {
        ma_scene.head = new_node;
    } else {
        node_t *current = ma_scene.head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    ma_scene.count++;
    return 0;
}

// Fonction pour créer les lignes et les ajouter à la liste chaînée
int add_new_line(void){
    line_s *l = malloc(sizeof(line_s));
    l->a = malloc(sizeof(point));
    printf("Point A :\n");
    add_new_point(l->a);
    l->b = malloc(sizeof(point));
    printf("Point B :\n");
    add_new_point(l->b);
    l->color = add_color();

    node_t *new_node = malloc(sizeof(node_t));
    new_node->fig.line = l;
    new_node->type = LINE;
    new_node->next = NULL;

    // Ajout en fin de liste
    if (ma_scene.head == NULL) {
        ma_scene.head = new_node;
    } else {
        node_t *current = ma_scene.head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    ma_scene.count++;
    return 0;
}

//fonction principal
int add_new_form(void){
    unsigned char choice;
    bool boucle = true;
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
            clear_stdin();
            add_new_line();
            break;
        case '2':
            clear_stdin();
            add_new_circle();
            break;
        default:
            clear_stdin();
            printf("Option invalide\n");
            break;
        }
    }
    return 0;
}