/**
 * @file create_form.c
 * @author Vayssiere Alexis
 * @date 2026-10-13
 * @brief Gestion des fonction lier a la creation de forme.
 */
#include "projet_svg.h"

// Définition de la scène globale
Scene ma_scene = { .count = 0 };

/**
 * @brief Vide le buffer d'entrée standard (stdin).
 * @details Lit et supprime tous les caractères restants dans le tampon clavier 
 *          jusqu'au retour à la ligne (`\n`) ou à la fin de fichier (`EOF`).
 */
void clear_stdin(void) {
    int c;
    while ((c = getc(stdin)) != '\n' && c != EOF);
}

/**
 * @brief Ajoute un nœud (figure) à la fin de la liste chaînée de la scène globale.
 * @details Si la scène est vide, le nœud devient la tête de liste. Sinon, 
 *          la fonction parcourt la liste jusqu'au dernier élément pour y attacher 
 *          le nouveau nœud et incrémente le compteur global.
 * @param[in,out] node Pointeur vers le nœud de figure à ajouter à la scène.
 */
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

/**
 * @brief Demande et valide le nombre de points souhaité auprès de l'utilisateur.
 * @details Boucle tant que la saisie n'est pas un entier valide ou qu'elle est 
 *          inférieure au seuil minimal spécifié.
 * @param[in] min_points Le nombre minimal de points requis.
 * @return int Le nombre de points valide saisi par l'utilisateur.
 */
int add_nb_points(int min_points) {
    int n;
    int verif;
    do {
        printf("Entrer le nombre de points (minimum %d) : ", min_points);
        verif = scanf("%d", &n);
        clear_stdin();
    } while (verif != 1 || n < min_points);
    return n;
}

/**
 * @brief Demande, valide et alloue dynamiquement une couleur au format hexadécimal (RRGGBB).
 * @details Vérifie que la saisie comporte exactement 6 caractères et qu'ils sont 
 *          tous des caractères hexadécimaux valides (0-9, A-F). En cas de succès, 
 *          alloue dynamiquement une chaîne pour stocker la couleur.
 * @return char* Un pointeur vers la chaîne de caractères allouée dynamiquement 
 *               contenant la couleur, ou NULL en cas d'échec d'allocation.
 * @note La mémoire allouée par cette fonction devra être libérée par la suite.
 */
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

/**
 * @brief Demande et valide les coordonnées (abscisse et ordonnée) d'un point 2D.
 * @details Invite l'utilisateur à saisir séparément x et y en s'assurant qu'il s'agit 
 *          d'entiers compris de manière inclusive entre -250 et 250.
 * @param[out] p Pointeur vers la structure point à initialiser et remplir.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Demande et valide la saisie d'un entier strictement positif.
 * @details Généralement utilisé pour définir des rayons, des largeurs ou des hauteurs. 
 *          Boucle tant que la valeur saisie n'est pas un entier ou est inférieure ou égale à 0.
 * @return int L'entier strictement positif saisi.
 */
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

/**
 * @brief Crée et ajoute un nouveau rectangle à la scène.
 * @details Alloue dynamiquement une structure de rectangle, demande à l'utilisateur 
 *          son point d'origine, ses couleurs de bordure et de fond, ainsi que 
 *          sa largeur et sa hauteur. Initialise les transformations (translation, rotation) 
 *          à zéro, encapsule le tout dans un nœud et l'ajoute à la scène globale.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Crée et ajoute un nouveau carré à la scène.
 * @details Alloue dynamiquement une structure de carré, demande son point d'origine, 
 *          ses couleurs de bordure et de fond, ainsi que la largeur de ses côtés. 
 *          Initialise les transformations à zéro, puis insère le nœud dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Crée et ajoute une nouvelle ellipse à la scène.
 * @details Alloue dynamiquement une structure d'ellipse, récupère le point central, 
 *          les rayons horizontal et vertical, ainsi que les couleurs de bordure et de fond. 
 *          Initialise les transformations à zéro et ajoute la forme à la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Crée et ajoute un nouveau cercle à la scène.
 * @details Alloue dynamiquement une structure de cercle, demande son centre, son rayon, 
 *          ses couleurs de bordure et de fond. Initialise les transformations à zéro 
 *          et ajoute le cercle à la scène globale.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Crée et ajoute une nouvelle ligne simple à la scène.
 * @details Alloue dynamiquement une structure de ligne, demande les coordonnées 
 *          des deux points d'extrémité (A et B) ainsi que sa couleur. 
 *          Initialise les transformations à zéro et l'ajoute à la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Crée et ajoute une ligne brisée (multi-ligne) à la scène.
 * @details Demande le nombre de points requis (minimum 3), alloue dynamiquement 
 *          une liste chaînée de points pour les stocker, puis demande la couleur 
 *          de la multi-ligne avant de l'insérer dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
int add_new_multi_line(void){
    multi_line_s *ml=malloc(sizeof(multi_line_s));
    ml->nb_points=add_nb_points(3);
    ml->point_head=NULL;
    point_node_t *last_pt_node=NULL;
    for(int i=0; i < ml->nb_points; i++){
        point_node_t *new_pt_node=malloc(sizeof(point_node_t));
        printf("Saisie du point %d :\n", i+1);
        add_new_point(&new_pt_node->pt);
        new_pt_node->next=NULL;
        if(ml->point_head==NULL){
            ml->point_head=new_pt_node;
        } else {
            last_pt_node->next=new_pt_node;
        }
        last_pt_node=new_pt_node;
    }
    ml->color=add_color();
    ml->translate_x=0;
    ml->translate_y=0;
    ml->rotate=0;

    node_t *new_node=malloc(sizeof(node_t));
    new_node->fig.multi_line=ml;
    new_node->type=MULTI_LINE;
    new_node->next=NULL;

    add_to_scene(new_node);
    return 0;
}

/**
 * @brief Crée et ajoute un nouveau polygone fermé à la scène.
 * @details Demande le nombre de sommets (minimum 3), construit dynamiquement 
 *          la liste chaînée des points correspondants, puis récupère les couleurs 
 *          de bordure et de fond avant d'ajouter le polygone à la scène.
 * @return int Retourne 0 en cas de succès.
 */
int add_new_polygone(void){
    polygone_s *p=malloc(sizeof(polygone_s));
    p->nb_points=add_nb_points(3);
    p->point_head=NULL;
    point_node_t *last_pt_node=NULL;
    for(int i=0; i < p->nb_points; i++){
        point_node_t *new_pt_node=malloc(sizeof(point_node_t));
        printf("Saisie du point %d :\n", i+1);
        add_new_point(&new_pt_node->pt);
        new_pt_node->next=NULL;
        if(p->point_head==NULL){
            p->point_head=new_pt_node;
        } else {
            last_pt_node->next=new_pt_node;
        }
        last_pt_node=new_pt_node;
    }
    printf("Couleur de la bordure :\n");
    p->color_border=add_color();
    printf("Couleur du fond :\n");
    p->color=add_color();
    p->translate_x=0;
    p->translate_y=0;
    p->rotate=0;

    node_t *new_node=malloc(sizeof(node_t));
    new_node->fig.polygone=p;
    new_node->type=POLYGONE;
    new_node->next=NULL;

    add_to_scene(new_node);
    return 0;
}

/**
 * @brief Crée et ajoute un chemin complexe (Path SVG) à la scène.
 * @details Alloue dynamiquement une structure de path, initialise ses couleurs, 
 *          ses transformations à zéro et sa liste de commandes vide. Entre ensuite 
 *          dans une boucle interactive permettant à l'utilisateur d'ajouter 
 *          successivement des commandes de tracé (MoveTo, LineTo, CurveTo, Close) 
 *          jusqu'à la fin de la saisie, puis ajoute le path à la scène.
 * @return int Retourne 0 en cas de succès.
 */
int add_new_path(void){
    path_s *p = malloc(sizeof(path_s));
    printf("Couleur de la bordure :\n");
    p->color_border = add_color();
    printf("Couleur du fond :\n");
    p->color = add_color();
    p->translate_x = 0;
    p->translate_y = 0;
    p->rotate = 0;
    p->commands_head = NULL;
    p->nb_commands = 0;

    path_command_node_t *last_cmd = NULL;
    bool building = true;

    printf("\n--- Construction du Path ---\n");
    while (building) {
        unsigned char cmd_choice;
        printf("Choisissez une commande :\n");
        printf("=> 0 - Fin du path\n");
        printf("=> 1 - MoveTo (M)\n");
        printf("=> 2 - LineTo (L)\n");
        printf("=> 3 - CurveTo (C - Cubique)\n");
        printf("=> 4 - Close (Z)\n");
        scanf(" %c", &cmd_choice);
        clear_stdin();

        path_command_node_t *new_cmd = malloc(sizeof(path_command_node_t));
        new_cmd->next = NULL;

        switch (cmd_choice) {
            case '0':
                free(new_cmd);
                building = false;
                continue;
            case '1':
                new_cmd->type = MOVETO;
                printf("Point d'arrivée :\n");
                add_new_point(&new_cmd->p);
                break;
            case '2':
                new_cmd->type = LINETO;
                printf("Point d'arrivée :\n");
                add_new_point(&new_cmd->p);
                break;
            case '3':
                new_cmd->type = CURVETO;
                printf("Premier point de contrôle (ctrl1) :\n");
                add_new_point(&new_cmd->ctrl1);
                printf("Second point de contrôle (ctrl2) :\n");
                add_new_point(&new_cmd->ctrl2);
                printf("Point d'arrivée :\n");
                add_new_point(&new_cmd->p);
                break;
            case '4':
                new_cmd->type = CLOSE;
                new_cmd->p.x = 0;
                new_cmd->p.y = 0;
                building = false; // Souvent le Z termine le path
                break;
            default:
                printf("Commande invalide\n");
                free(new_cmd);
                continue;
        }

        if (p->commands_head == NULL) {
            p->commands_head = new_cmd;
        } else {
            last_cmd->next = new_cmd;
        }
        last_cmd = new_cmd;
        p->nb_commands++;
    }

    node_t *new_node = malloc(sizeof(node_t));
    new_node->fig.path = p;
    new_node->type = PATH;
    new_node->next = NULL;

    add_to_scene(new_node);
    return 0;
}

/**
 * @brief Crée et ajoute un groupe de figures à la scène.
 * @details Alloue dynamiquement une structure de groupe, sauvegarde temporairement 
 *          la scène principale, puis redirige l'utilisateur vers le menu de création 
 *          pour ajouter les figures qui composeront ce groupe. Une fois terminé, 
 *          les enfants sont rattachés au groupe, la scène principale est restaurée, 
 *          et le groupe est inséré dans la scène globale.
 * @return int Retourne 0 en cas de succès.
 */
int add_new_group(void){
    group_s *g = malloc(sizeof(group_s));
    g->translate_x = 0;
    g->translate_y = 0;
    g->rotate = 0;
    g->children_head = NULL;
    g->nb_children = 0;

    printf("\n--- Creation d'un Groupe ---\n");
    // Sauvegarde temporaire de la scène globale pour ajouter des enfants au groupe
    Scene old_scene = ma_scene;
    ma_scene.head = NULL;
    ma_scene.count = 0;

    // L'utilisateur ajoute des formes qui appartiendront au groupe
    add_new_form();

    // Récupération des enfants créés
    g->children_head = ma_scene.head;
    g->nb_children = ma_scene.count;

    // Restauration de la scène principale
    ma_scene = old_scene;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->fig.group = g;
    new_node->type = GROUP;
    new_node->next = NULL;

    add_to_scene(new_node);
    return 0;
}

/**
 * @brief Fonction principale de sélection et de création de formes.
 * @details Affiche un menu interactif en boucle permettant à l'utilisateur 
 *          de choisir quel type de figure (ligne, cercle, ellipse, carré, rectangle, 
 *          multi-ligne, polygone, path, groupe) il souhaite créer et ajouter 
 *          à la scène courante, jusqu'à ce qu'il choisisse de quitter.
 * @return int Retourne 0 lorsque l'utilisateur sort du menu.
 */
int add_new_form(void){
    unsigned char choice;
    bool boucle = true;
    while(boucle){
        printf("\nChoix des formes :\n");
        printf("=> 0 - Quittez\n");
        printf("=> 1 - Ligne\n");
        printf("=> 2 - Cercle\n");
        printf("=> 3 - Ellipse\n");
        printf("=> 4 - Carré\n");
        printf("=> 5 - Rectangle\n");
        printf("=> 6 - Multi ligne\n");
        printf("=> 7 - Polygone\n");
        printf("=> 8 - Chemin\n");
        printf("=> 9 - Groupe\n");
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
        case '6':
            add_new_multi_line();
            break;
        case '7':
            add_new_polygone();
            break;
        case '8':
            add_new_path();
            break;
        case '9':
            add_new_group();
            break;
        default:
            printf("Option invalide\n");
            break;
        }
    }
    return 0;
}