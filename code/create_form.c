#include "projet_svg.h"

// Définition de la scène globale
Scene ma_scene = { .count = 0 };

//fonction pour vider le buffer d'entrer
void clear_stdin(void) {
    int c;
    while ((c = getc(stdin)) != '\n' && c != EOF);
}

//ajout en fin de liste
void add_to_scene(node_t *node){
    if (ma_scene.head == NULL) {
        ma_scene.head = node;
    } else {
        node_t *current = ma_scene.head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
    ma_scene.count++;
}

//fonction pour demander et valider une couleur hexadécimale (format RRGGBB)
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
int add_int(void){
    int r;
    int verif;
    do{
        printf("Entrer un entier positif\n");
        verif=scanf("%d",&r);
        //vide le buffer d entrer
        clear_stdin();
    }while(verif !=1 || r<=0);
    return r;
}

// Fonction pour créer les rectangle
int add_new_rectangle(void){
    rectangle_s *r = malloc(sizeof(rectangle_s));
    r->origin = malloc(sizeof(point));
    add_new_point(r->origin);
    printf("Couleur de la bordure :\n");
    r->color_border = add_color();
    printf("Couleur du fond :\n");
    r->color = add_color();
    r->translate_x = 0;
    r->translate_y = 0;
    r->rotate = 0;
    printf("Largeur : ");
    r->widht=add_int();
    printf("Hauteur / Longueur : ");
    r->height=add_int();

    node_t *new_node = malloc(sizeof(node_t));
    new_node->fig.rectangle = r;
    new_node->type = RECTANGLE;
    new_node->next = NULL;

    add_to_scene(new_node);
    return 0;
}

// Fonction pour créer les carré
int add_new_square(void){
    square_s *s = malloc(sizeof(square_s));
    s->origin = malloc(sizeof(point));
    add_new_point(s->origin);
    printf("Couleur de la bordure :\n");
    s->color_border = add_color();
    printf("Couleur du fond :\n");
    s->color = add_color();
    s->translate_x = 0;
    s->translate_y = 0;
    s->rotate = 0;
    printf("Largeur : ");
    s->widht=add_int();

    node_t *new_node = malloc(sizeof(node_t));
    new_node->fig.square = s;
    new_node->type = SQUARE;
    new_node->next = NULL;

    add_to_scene(new_node);
    return 0;
}

// Fonction pour créer les ellipse
int add_new_ellipse(void){
    ellipse_s *e = malloc(sizeof(ellipse_s));
    e->center = malloc(sizeof(point));
    add_new_point(e->center);
    printf("Rayon x : ");
    e->radius_x = add_int();
    printf("Rayon y: ");
    e->radius_y = add_int();
    printf("Couleur de la bordure :\n");
    e->color_border = add_color();
    printf("Couleur du fond :\n");
    e->color = add_color();
    e->translate_x = 0;
    e->translate_y = 0;
    e->rotate = 0;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->fig.ellipse = e;
    new_node->type = ELLIPSE;
    new_node->next = NULL;

    add_to_scene(new_node);
    return 0;
}

// Fonction pour créer les cercles
int add_new_circle(void){
    circle_s *c = malloc(sizeof(circle_s));
    c->center = malloc(sizeof(point));
    add_new_point(c->center);
    printf("Rayon : ");
    c->radius = add_int();
    printf("Couleur de la bordure :\n");
    c->color_border = add_color();
    printf("Couleur du fond :\n");
    c->color = add_color();
    c->translate_x = 0;
    c->translate_y = 0;
    c->rotate = 0;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->fig.circle = c;
    new_node->type = CIRCLE;
    new_node->next = NULL;

    add_to_scene(new_node);
    return 0;
}

// Fonction pour créer les lignes
int add_new_line(void){
    line_s *l = malloc(sizeof(line_s));
    l->a = malloc(sizeof(point));
    printf("Point A :\n");
    add_new_point(l->a);
    l->b = malloc(sizeof(point));
    printf("Point B :\n");
    add_new_point(l->b);
    l->color = add_color();
    l->translate_x = 0;
    l->translate_y = 0;
    l->rotate = 0;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->fig.line = l;
    new_node->type = LINE;
    new_node->next = NULL;

    add_to_scene(new_node);
    return 0;
}

//fonction principal
int add_new_form(void){
    unsigned char choice;
    bool boucle = true;
    //creation des forme
    while(boucle){
        printf("\nChoix des formes :\n");
        printf("=> 0 - Quittez\n");
        printf("=> 1 - Ligne\n");
        printf("=> 2 - Cercle\n");
        printf("=> 3 - Ellipse\n");
        printf("=> 4 - Carré\n");
        printf("=> 5 - Rectangle\n");
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '0':
            boucle=false;
            break;
        case '1':
            add_new_line();
            break;
        case '2':
            add_new_circle();
            break;
        case '3':
            add_new_ellipse();
            break;
        case '4':
            add_new_square();
            break;
        case '5':
            add_new_rectangle();
            break;
        default:
            printf("Option invalide\n");
            break;
        }
    }
    return 0;
}