#include "projet_svg.h"

void edit_point(point *p, char *m){
    printf("%s", m);
    add_new_point(p);
}
void edit_color(char *color, char*m){
    free(color);
    printf("%s", m);
    color = add_color();
}
int edit_int(char *m){
    printf("%s", m);
    int i = add_int();
    return i;
}

int edit_line(node_t *current, int index){
    char choice;
    printf("\nModification de la Ligne [%d]\n", index);
    printf("=> 1 : Point A\n");
    printf("=> 2 : Point B\n");
    printf("=> 3 : Couleur\n");
    printf("=> 4 : Tout\n");
    while(1){
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '1':
            edit_point(current->fig.line->a, "Nouveau point A :\n");
            return 0;
        case '2':
            edit_point(current->fig.line->b, "Nouveau point B :\n");
            return 0;
        case '3':
            edit_color(current->fig.line->color, "Nouvelle couleur :\n");
            return 0;
        case '4':
            edit_point(current->fig.line->a, "Nouveau point A :\n");
            edit_point(current->fig.line->b, "Nouveau point B :\n");
            edit_color(current->fig.line->color, "Nouvelle couleur :\n");
            return 0;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
}

int edit_circle(node_t *current, int index){
    char choice;
    printf("\nModification du cercle [%d]\n", index);
    printf("=> 1 : Centre\n");
    printf("=> 2 : Rayon\n");
    printf("=> 3 : Couleur de la bordure\n");
    printf("=> 4 : Couleur du fond\n");
    printf("=> 5 : Tout\n");
    while(1){
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '1':
            edit_point(current->fig.circle->center, "Nouveau centre :\n");
            return 0;
        case '2':
            current->fig.circle->radius=edit_int("Nouveau rayon :\n");
            return 0;
        case '3':
            edit_color(current->fig.circle->color_border, "Nouvelle couleur de bordure :\n");
            return 0;
        case '4':
            edit_color(current->fig.circle->color, "Nouvelle couleur de remplissage :\n");
            return 0;
        case '5':
            edit_point(current->fig.circle->center, "Nouveau centre :\n");
            current->fig.circle->radius=edit_int("Nouveau rayon :\n");
            edit_color(current->fig.circle->color_border, "Nouvelle couleur de bordure :\n");
            edit_color(current->fig.circle->color, "Nouvelle couleur de remplissage :\n");
            return 0;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
}

int edit_ellipse(node_t *current, int index){
    char choice;
    printf("\nModification de l ellipse [%d]\n", index);
    printf("=> 1 : Centre\n");
    printf("=> 2 : Rayon x\n");
    printf("=> 3 : Rayon y\n");
    printf("=> 4 : Couleur de la bordure\n");
    printf("=> 5 : Couleur du fond\n");
    printf("=> 6 : Tout\n");
    while(1){
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '1':
            edit_point(current->fig.ellipse->center, "Nouveau centre :\n");
            return 0;
        case '2':
            current->fig.ellipse->radius_x = edit_int("Nouveau rayon x :\n");
            return 0;
        case '3':
            current->fig.ellipse->radius_y = edit_int("Nouveau rayon y :\n");
            return 0;
        case '4':
            edit_color(current->fig.ellipse->color_border, "Nouvelle couleur de bordure :\n");
            return 0;
        case '5':
            edit_color(current->fig.ellipse->color, "Nouvelle couleur de remplissage :\n");
            return 0;
        case '6':
            edit_point(current->fig.ellipse->center, "Nouveau centre :\n");
            current->fig.ellipse->radius_x = edit_int("Nouveau rayon x :\n");
            current->fig.ellipse->radius_y = edit_int("Nouveau rayon y :\n");
            edit_color(current->fig.ellipse->color_border, "Nouvelle couleur de bordure :\n");
            edit_color(current->fig.ellipse->color, "Nouvelle couleur de remplissage :\n");
            return 0;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
}

int edit_square(node_t *current, int index){
    char choice;
    printf("\nModification du carré [%d]\n", index);
    printf("=> 1 : Origine\n");
    printf("=> 2 : Largeur\n");
    printf("=> 3 : Couleur de la bordure\n");
    printf("=> 4 : Couleur du fond\n");
    printf("=> 5 : Tout\n");
    while(1){
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '1':
            edit_point(current->fig.square->origin, "Nouvelle origine :\n");
            return 0;
        case '2':
            current->fig.square->widht = edit_int("Nouvelle largeur :\n");
            return 0;
        case '3':
            edit_color(current->fig.square->color_border, "Nouvelle couleur de bordure :\n");
            return 0;
        case '4':
            edit_color(current->fig.square->color, "Nouvelle couleur de remplissage :\n");
            return 0;
        case '5':
            edit_point(current->fig.square->origin, "Nouvelle origine :\n");
            current->fig.square->widht = edit_int("Nouvelle largeur :\n");
            edit_color(current->fig.square->color_border, "Nouvelle couleur de bordure :\n");
            edit_color(current->fig.square->color, "Nouvelle couleur de remplissage :\n");
            return 0;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
}

int edit_rectangle(node_t *current, int index){
    char choice;
    printf("\nModification du rectangle [%d]\n", index);
    printf("=> 1 : Origine\n");
    printf("=> 2 : Largeur\n");
    printf("=> 3 : Longueur\n");
    printf("=> 4 : Couleur de la bordure\n");
    printf("=> 5 : Couleur du fond\n");
    printf("=> 6 : Tout\n");
    while(1){
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '1':
            edit_point(current->fig.rectangle->origin, "Nouvelle origine :\n");
            return 0;
        case '2':
            current->fig.rectangle->widht = edit_int("Nouvelle largeur :\n");
            return 0;
        case '3':
            current->fig.rectangle->height = edit_int("Nouvelle longueur :\n");
            return 0;
        case '4':
            edit_color(current->fig.rectangle->color_border, "Nouvelle couleur de bordure :\n");
            return 0;
        case '5':
            edit_color(current->fig.rectangle->color, "Nouvelle couleur de remplissage :\n");
            return 0;
        case '6':
            edit_point(current->fig.rectangle->origin, "Nouvelle origine :\n");
            current->fig.rectangle->widht = edit_int("Nouvelle largeur :\n");
            current->fig.rectangle->height = edit_int("Nouvelle longueur :\n");
            edit_color(current->fig.rectangle->color_border, "Nouvelle couleur de bordure :\n");
            edit_color(current->fig.rectangle->color, "Nouvelle couleur de remplissage :\n");
            return 0;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
}

// Modifier un point existant à un index donné
void edit_point_in_list(point_node_t **head_ref, int num_points) {
    int target_idx;
    printf("Entrez l'index du point à modifier (0 à %d) : ", num_points - 1);
    if (scanf("%d", &target_idx) != 1 || target_idx < 0 || target_idx >= num_points) {
        clear_stdin();
        printf("Index invalide.\n");
        return;
    }
    clear_stdin();

    point_node_t *curr = *head_ref;
    for (int i = 0; i < target_idx; i++) {
        curr = curr->next;
    }
    printf("Nouvelles coordonnées pour le point %d :\n", target_idx);
    add_new_point(&(curr->pt));
    printf("Point modifié avec succès !\n");
}

// Ajouter un nouveau point à un index donné
void edit_add_point(point_node_t **head_ref, int *num_points_ref) {
    int target_idx;
    printf("Entrez l'index où insérer le nouveau point (0 à %d) : ", *num_points_ref);
    if (scanf("%d", &target_idx) != 1 || target_idx < 0 || target_idx > *num_points_ref) {
        clear_stdin();
        printf("Index invalide.\n");
        return;
    }
    clear_stdin();

    point_node_t *new_node = malloc(sizeof(point_node_t));
    if (new_node == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }
    
    printf("Coordonnées du nouveau point :\n");
    add_new_point(&(new_node->pt));
    new_node->next = NULL;

    if (target_idx == 0) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        point_node_t *curr = *head_ref;
        for (int i = 0; i < target_idx - 1; i++) {
            curr = curr->next;
        }
        new_node->next = curr->next;
        curr->next = new_node;
    }
    (*num_points_ref)++;
    printf("Point ajouté avec succès !\n");
}

// Supprimer un point à un index donné
void edit_del_point(point_node_t **head_ref, int *num_points_ref, int min_points) {
    if (*num_points_ref <= min_points) {
        printf("Erreur : Impossible de supprimer ce point. Minimum requis : %d points.\n", min_points);
        return;
    }
    
    int target_idx;
    printf("Entrez l'index du point à supprimer (0 à %d) : ", *num_points_ref - 1);
    if (scanf("%d", &target_idx) != 1 || target_idx < 0 || target_idx >= *num_points_ref) {
        clear_stdin();
        printf("Index invalide.\n");
        return;
    }
    clear_stdin();

    point_node_t *to_free = NULL;
    if (target_idx == 0) {
        to_free = *head_ref;
        *head_ref = (*head_ref)->next;
    } else {
        point_node_t *curr = *head_ref;
        for (int i = 0; i < target_idx - 1; i++) {
            curr = curr->next;
        }
        to_free = curr->next;
        curr->next = to_free->next;
    }
    free(to_free);
    (*num_points_ref)--;
    printf("Point supprimé avec succès !\n");
}

// Fonction générique pour éditer, ajouter ou supprimer des points dans une liste chaînée de points
int edit_points_list(point_node_t **head_ref, int *num_points_ref, int min_points) {
    char choice;
    while (1) {
        printf("\n--- Liste des points actuels (%d points) ---\n", *num_points_ref);
        point_node_t *curr = *head_ref;
        int idx = 0;
        while (curr != NULL) {
            printf("[%d] X: %d, Y: %d\n", idx, curr->pt.x, curr->pt.y);
            curr = curr->next;
            idx++;
        }

        printf("\nOptions pour les points :\n");
        printf("=> 1 : Modifier un point\n");
        printf("=> 2 : Ajouter un point\n");
        printf("=> 3 : Supprimer un point\n");
        printf("=> 4 : Terminer\n");
        
        scanf(" %c", &choice);
        clear_stdin();

        switch (choice) {
            case '1':
                edit_point_in_list(head_ref, *num_points_ref);
                break;

            case '2':
                edit_add_point(head_ref, num_points_ref);
                break;

            case '3':
                edit_del_point(head_ref, num_points_ref, min_points);
                break;

            case '4':
                return 0;

            default:
                printf("Choix invalide.\n");
                break;
        }
    }
}

int edit_multi_line(node_t *current, int index){
    char choice;
    printf("\nModification de la Polyline [%d]\n", index);
    printf("=> 1 : Modifier les points\n");
    printf("=> 2 : Couleur\n");
    printf("=> 3 : Tout\n");
    while(1){
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '1':
            edit_points_list(&(current->fig.multi_line->point_head), &(current->fig.multi_line->nb_points), 3);
            return 0;
        case '2':
            edit_color(current->fig.multi_line->color, "Nouvelle couleur :\n");
            return 0;
        case '3':
            edit_points_list(&(current->fig.multi_line->point_head), &(current->fig.multi_line->nb_points), 3);
            edit_color(current->fig.multi_line->color, "Nouvelle couleur :\n");
            return 0;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
}

int edit_polygone(node_t *current, int index){
    char choice;
    printf("\nModification du Polygone [%d]\n", index);
    printf("=> 1 : Modifier les points\n");
    printf("=> 2 : Couleur de la bordure\n");
    printf("=> 3 : Couleur du fond\n");
    printf("=> 4 : Tout\n");
    while(1){
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '1':
            edit_points_list(&(current->fig.polygone->point_head), &(current->fig.polygone->nb_points), 3);
            return 0;
        case '2':
            edit_color(current->fig.polygone->color_border, "Nouvelle couleur de bordure :\n");
            return 0;
        case '3':
            edit_color(current->fig.polygone->color, "Nouvelle couleur de remplissage :\n");
            return 0;
        case '4':
            edit_points_list(&(current->fig.polygone->point_head), &(current->fig.polygone->nb_points), 3);
            edit_color(current->fig.polygone->color_border, "Nouvelle couleur de bordure :\n");
            edit_color(current->fig.polygone->color, "Nouvelle couleur de remplissage :\n");
            return 0;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
}

//----------------------------------Fonction de modification de path-----------------------------------------------------------

// Saisie/mise à jour d'une commande de path selon son type
void prompt_path_command_data(path_command_node_t *cmd) {
    char cmd_choice;
    printf("Type de commande :\n");
    printf("=> 1 - MoveTo (M)\n");
    printf("=> 2 - LineTo (L)\n");
    printf("=> 3 - CurveTo (C - Cubique)\n");
    printf("=> 4 - Smooth Curve (S - Cubique lisse)\n");
    printf("=> 5 - Quad (Q - Quadratique)\n");
    printf("=> 6 - Smooth Quad (T - Quadratique lisse)\n");
    printf("=> 7 - Close (Z)\n");
    scanf(" %c", &cmd_choice);
    clear_stdin();

    switch (cmd_choice) {
        case '1':
            cmd->type = MOVETO;
            printf("Point d'arrivée :\n");
            add_new_point(&cmd->p);
            break;
        case '2':
            cmd->type = LINETO;
            printf("Point d'arrivée :\n");
            add_new_point(&cmd->p);
            break;
        case '3':
            cmd->type = CURVETO;
            printf("Premier point de contrôle (ctrl1) :\n");
            add_new_point(&cmd->ctrl1);
            printf("Second point de contrôle (ctrl2) :\n");
            add_new_point(&cmd->ctrl2);
            printf("Point d'arrivée :\n");
            add_new_point(&cmd->p);
            break;
        case '4':
            cmd->type = SMOOTH_CURVE;
            printf("Second point de contrôle (ctrl2) :\n");
            add_new_point(&cmd->ctrl2);
            printf("Point d'arrivée :\n");
            add_new_point(&cmd->p);
            break;
        case '5':
            cmd->type = QUAD;
            printf("Point de contrôle (ctrl1) :\n");
            add_new_point(&cmd->ctrl1);
            printf("Point d'arrivée :\n");
            add_new_point(&cmd->p);
            break;
        case '6':
            cmd->type = SMOOTH_QUAD;
            printf("Point d'arrivée :\n");
            add_new_point(&cmd->p);
            break;
        case '7':
            cmd->type = CLOSE;
            cmd->p.x = 0;
            cmd->p.y = 0;
            break;
        default:
            printf("Choix invalide. Par défaut défini sur LineTo (L).\n");
            cmd->type = LINETO;
            printf("Point d'arrivée :\n");
            add_new_point(&cmd->p);
            break;
    }
}

// Modifier une commande existante
void edit_command_in_path(path_command_node_t **head_ref, int nb_commands) {
    int target_idx;
    printf("Entrez l'index de la commande à modifier (0 à %d) : ", nb_commands - 1);
    if (scanf("%d", &target_idx) != 1 || target_idx < 0 || target_idx >= nb_commands) {
        clear_stdin();
        printf("Index invalide.\n");
        return;
    }
    clear_stdin();

    path_command_node_t *curr = *head_ref;
    for (int i = 0; i < target_idx; i++) {
        curr = curr->next;
    }
    printf("\nModification de la commande [%d] :\n", target_idx);
    prompt_path_command_data(curr);
    printf("Commande modifiée avec succès !\n");
}

// Ajouter une nouvelle commande à la liste du Path
void edit_add_command_to_path(path_command_node_t **head_ref, int *nb_commands_ref) {
    int target_idx;
    printf("Entrez l'index où insérer la nouvelle commande (0 à %d) : ", *nb_commands_ref);
    if (scanf("%d", &target_idx) != 1 || target_idx < 0 || target_idx > *nb_commands_ref) {
        clear_stdin();
        printf("Index invalide.\n");
        return;
    }
    clear_stdin();

    path_command_node_t *new_node = malloc(sizeof(path_command_node_t));
    if (new_node == NULL) return;
    new_node->next = NULL;

    printf("\nSaisie de la nouvelle commande :\n");
    prompt_path_command_data(new_node);

    if (target_idx == 0) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        path_command_node_t *curr = *head_ref;
        for (int i = 0; i < target_idx - 1; i++) {
            curr = curr->next;
        }
        new_node->next = curr->next;
        curr->next = new_node;
    }
    (*nb_commands_ref)++;
    printf("Commande ajoutée avec succès !\n");
}

// Supprimer une commande du Path
void edit_del_command_from_path(path_command_node_t **head_ref, int *nb_commands_ref) {
    if (*nb_commands_ref <= 1) {
        printf("Erreur : Un Path doit contenir au moins 1 commande.\n");
        return;
    }

    int target_idx;
    printf("Entrez l'index de la commande à supprimer (0 à %d) : ", *nb_commands_ref - 1);
    if (scanf("%d", &target_idx) != 1 || target_idx < 0 || target_idx >= *nb_commands_ref) {
        clear_stdin();
        printf("Index invalide.\n");
        return;
    }
    clear_stdin();

    path_command_node_t *to_free = NULL;
    if (target_idx == 0) {
        to_free = *head_ref;
        *head_ref = (*head_ref)->next;
    } else {
        path_command_node_t *curr = *head_ref;
        for (int i = 0; i < target_idx - 1; i++) {
            curr = curr->next;
        }
        to_free = curr->next;
        curr->next = to_free->next;
    }
    free(to_free);
    (*nb_commands_ref)--;
    printf("Commande supprimée avec succès !\n");
}

// Menu d'édition de la liste chaînée des commandes de Path
int edit_path_commands_list(path_command_node_t **head_ref, int *nb_commands_ref) {
    char choice;
    while (1) {
        printf("\n--- Liste des commandes actuelles (%d commandes) ---\n", *nb_commands_ref);
        path_command_node_t *curr = *head_ref;
        int idx = 0;
        while (curr != NULL) {
            switch (curr->type) {
                case MOVETO:
                    printf("[%d] MoveTo (M) -> Pt: (%d, %d)\n", idx, curr->p.x, curr->p.y);
                    break;
                case LINETO:
                    printf("[%d] LineTo (L) -> Pt: (%d, %d)\n", idx, curr->p.x, curr->p.y);
                    break;
                case CURVETO:
                    printf("[%d] CurveTo (C) -> Ctrl1: (%d, %d), Ctrl2: (%d, %d), Pt: (%d, %d)\n", 
                           idx, curr->ctrl1.x, curr->ctrl1.y, curr->ctrl2.x, curr->ctrl2.y, curr->p.x, curr->p.y);
                    break;
                case SMOOTH_CURVE:
                    printf("[%d] Smooth Curve (S) -> Ctrl2: (%d, %d), Pt: (%d, %d)\n", 
                           idx, curr->ctrl2.x, curr->ctrl2.y, curr->p.x, curr->p.y);
                    break;
                case QUAD:
                    printf("[%d] Quad (Q) -> Ctrl1: (%d, %d), Pt: (%d, %d)\n", 
                           idx, curr->ctrl1.x, curr->ctrl1.y, curr->p.x, curr->p.y);
                    break;
                case SMOOTH_QUAD:
                    printf("[%d] Smooth Quad (T) -> Pt: (%d, %d)\n", idx, curr->p.x, curr->p.y);
                    break;
                case CLOSE:
                    printf("[%d] Close (Z)\n", idx);
                    break;
            }
            curr = curr->next;
            idx++;
        }

        printf("\nOptions pour les commandes du Path :\n");
        printf("=> 1 : Modifier une commande\n");
        printf("=> 2 : Ajouter une commande\n");
        printf("=> 3 : Supprimer une commande\n");
        printf("=> 4 : Terminer\n");

        scanf(" %c", &choice);
        clear_stdin();

        switch (choice) {
            case '1': edit_command_in_path(head_ref, *nb_commands_ref); break;
            case '2': edit_add_command_to_path(head_ref, nb_commands_ref); break;
            case '3': edit_del_command_from_path(head_ref, nb_commands_ref); break;
            case '4': return 0;
            default: printf("Choix invalide.\n"); break;
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------

// Modification d'un Path
int edit_path(node_t *current, int index){
    char choice;
    printf("\nModification du Path [%d]\n", index);
    printf("=> 1 : Modifier la liste des commandes / points de contrôle\n");
    printf("=> 2 : Couleur de la bordure\n");
    printf("=> 3 : Couleur du fond\n");
    printf("=> 4 : Tout\n");
    while(1){
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '1':
            edit_path_commands_list(&(current->fig.path->commands_head), &(current->fig.path->nb_commands));
            return 0;
        case '2':
            edit_color(current->fig.path->color_border, "Nouvelle couleur de bordure :\n");
            return 0;
        case '3':
            edit_color(current->fig.path->color, "Nouvelle couleur de fond :\n");
            return 0;
        case '4':
            edit_path_commands_list(&(current->fig.path->commands_head), &(current->fig.path->nb_commands));
            edit_color(current->fig.path->color_border, "Nouvelle couleur de bordure :\n");
            edit_color(current->fig.path->color, "Nouvelle couleur de fond :\n");
            return 0;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
}

// Modification d'un Groupe (Permet d'éditer la scène interne du groupe)
int edit_group(node_t *current, int index){
    printf("\nModification des elements du Groupe [%d]\n", index);
    
    // Sauvegarde de la scène principale et basculement sur la scène du groupe
    Scene old_scene = ma_scene;
    ma_scene.head = current->fig.group->children_head;
    ma_scene.count = current->fig.group->nb_children;

    // Appel de la fonction edit_form sur les enfants du groupe
    edit_form();

    // Restauration de la scène principale
    current->fig.group->children_head = ma_scene.head;
    current->fig.group->nb_children = ma_scene.count;
    ma_scene = old_scene;

    return 0;
}

int edit(node_t *current, int index){
    switch (current->type)
    {
    case LINE:
        edit_line(current, index);
        break;
    case CIRCLE:
        edit_circle(current, index);
        break;
    case ELLIPSE:
        edit_ellipse(current, index);
        break;
    case SQUARE:
        edit_square(current, index);
        break;
    case RECTANGLE:
        edit_rectangle(current, index);
        break;
    case MULTI_LINE:
        edit_multi_line(current, index);
        break;
    case POLYGONE:
        edit_polygone(current, index);
        break;
    case PATH:
        edit_path(current, index);
        break;
    case GROUP:
        edit_group(current, index);
        break;
    default:
        printf("une erreur est survenu\n");
        return -1;
        break;
    }
    printf("Forme modifiee avec succes !\n");
    return 0;
}

int translate(node_t *current){
    int tx, ty;
    bool verif;
    do{
        printf("Entrez le décalage en X (translate_x) : ");
        verif=scanf("%d", &tx);
        clear_stdin();
    }while(verif!=1);
    verif=0;
    do{
        printf("Entrez le décalage en Y (translate_y) : ");
        verif=scanf("%d", &ty);
        clear_stdin();
    }while(verif!=1);

    switch (current->type){
    case LINE:
        current->fig.line->translate_x=tx;
        current->fig.line->translate_y=ty;
        break;
    case CIRCLE:
        current->fig.circle->translate_x=tx;
        current->fig.circle->translate_y=ty;
        break;
    case ELLIPSE:
        current->fig.ellipse->translate_x=tx;
        current->fig.ellipse->translate_y=ty;
        break;
    case SQUARE:
        current->fig.square->translate_x=tx;
        current->fig.square->translate_y=ty;
        break;
    case RECTANGLE:
        current->fig.rectangle->translate_x=tx;
        current->fig.rectangle->translate_y=ty;
        break;
    case MULTI_LINE:
        current->fig.multi_line->translate_x=tx;
        current->fig.multi_line->translate_y=ty;
        break;
    case POLYGONE:
        current->fig.polygone->translate_x=tx;
        current->fig.polygone->translate_y=ty;
        break;
    case PATH:
        current->fig.path->translate_x=tx;
        current->fig.path->translate_y=ty;
        break;
    case GROUP:
        current->fig.group->translate_x=tx;
        current->fig.group->translate_y=ty;
        break;
    default:
        printf("Une erreur est survenu\n");
        return -1;
        break;
    }
    printf("Déplacement appliqué avec succès !\n");
    return 0;
}

int rotate(node_t *current){
    int angle;
    bool verif;
    do{
        printf("Entrez l'angle de rotation en degrés : ");
        verif=scanf("%d", &angle);
        clear_stdin();
    }while(verif!=1);

    switch (current->type){
    case LINE:
        current->fig.line->rotate=angle;
        break;
    case CIRCLE:
        current->fig.circle->rotate=angle;
        break;
    case ELLIPSE:
        current->fig.ellipse->rotate=angle;
        break;
    case SQUARE:
        current->fig.square->rotate=angle;
        break;
    case RECTANGLE:
        current->fig.rectangle->rotate=angle;
        break;
    case MULTI_LINE:
        current->fig.multi_line->rotate=angle;
        break;
    case POLYGONE:
        current->fig.polygone->rotate=angle;
        break;
    case PATH:
        current->fig.path->rotate=angle;
        break;
    case GROUP:
        current->fig.group->rotate=angle;
        break;
    default:
        printf("Une erreur est survenu\n");
        return -1;
        break;
    }
    printf("Rotation appliquée avec succès !\n");
    return 0;
}

int delete(node_t *current, node_t *prev){
    if (prev == NULL) {
        // Suppression du premier élément
        ma_scene.head = current->next;
    } else {
        // Suppression d'un élément intermédiaire ou de fin
        prev->next = current->next;
    }

    // Libération de la mémoire de l'élément supprimé
    free_figure(current);
    ma_scene.count--;
    printf("Forme supprimee avec succes !\n");
    return 0;
}

//affichage line
void print_line(node_t *current, int i){
    printf("[%d] Ligne (Point A: %d,%d | Point B: %d,%d | Trans: %d,%d | Rot: %d°)\n", 
        i, current->fig.line->a->x, current->fig.line->a->y,
        current->fig.line->b->x, current->fig.line->b->y,
        current->fig.line->translate_x, current->fig.line->translate_y,
        current->fig.line->rotate);
}
//affichage cercle
void print_circle(node_t *current, int i){
    printf("[%d] Cercle (Centre: %d,%d | Rayon: %d | Trans: %d,%d | Rot: %d°)\n", 
        i, current->fig.circle->center->x, current->fig.circle->center->y, 
        current->fig.circle->radius,
        current->fig.circle->translate_x, current->fig.circle->translate_y,
        current->fig.circle->rotate);
}
//affichage ellipse
void print_ellipse(node_t *current, int i){
    printf("[%d] Ellipse (Centre: %d,%d | Rayon x: %d | Rayon y: %d | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.ellipse->center->x, current->fig.ellipse->center->y,
        current->fig.ellipse->radius_x, current->fig.ellipse->radius_y,
        current->fig.ellipse->translate_x, current->fig.ellipse->translate_y,
        current->fig.ellipse->rotate);
}
//affichage carré
void print_square(node_t *current, int i){
    printf("[%d] Carré (Origine: %d,%d | Largeur: %d | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.square->origin->x, current->fig.square->origin->y,
        current->fig.square->widht,
        current->fig.square->translate_x, current->fig.square->translate_y,
        current->fig.square->rotate);
}
//affichage rectangle
void print_rectangle(node_t *current, int i){
    printf("[%d] Rectangle (Origine: %d;%d | Largeur: %d | Longueur: %d | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.rectangle->origin->x, current->fig.rectangle->origin->y,
        current->fig.rectangle->widht, current->fig.rectangle->height,
        current->fig.rectangle->translate_x, current->fig.rectangle->translate_y,
        current->fig.rectangle->rotate);
}
//affiche multi-ligne
void print_multi_line(node_t *current, int i){
    printf("[%d] Multi ligne (%d points | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.multi_line->nb_points,
        current->fig.multi_line->translate_x, current->fig.multi_line->translate_y,
        current->fig.multi_line->rotate);
}
//affiche polygone
void print_polygone(node_t *current, int i){
    printf("[%d] Polygone (%d points | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.polygone->nb_points,
        current->fig.polygone->translate_x, current->fig.polygone->translate_y,
        current->fig.polygone->rotate);
}
//affiche chemin
void print_path(node_t *current, int i){
    printf("[%d] Path (%d commandes | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.path->nb_commands,
        current->fig.path->translate_x, current->fig.path->translate_y,
        current->fig.path->rotate);
}
//affiche groupe
void print_group(node_t *current, int i){
    printf("[%d] Groupe (%d elements | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.group->nb_children,
        current->fig.group->translate_x, current->fig.group->translate_y,
        current->fig.group->rotate);
}

//fonction principal
int edit_form(void) {
    if (ma_scene.count == 0 || ma_scene.head == NULL) {
        printf("\nAucune forme presente dans le projet.\n");
        return 0;
    }

    int index;
    printf("\n--- Liste des formes existantes ---\n");
    
    node_t *current = ma_scene.head;
    int i = 0;
    while (current != NULL) {
        switch (current->type){
        case LINE:
            print_line(current, i);
            break;
        case CIRCLE:
            print_circle(current, i);
            break;
        case ELLIPSE:
            print_ellipse(current, i);
            break;
        case SQUARE:
            print_square(current, i);
            break;
        case RECTANGLE:
            print_rectangle(current, i);
            break;
        case MULTI_LINE:
            print_multi_line(current, i);
            break; 
        case POLYGONE:
            print_polygone(current, i);
            break; 
        case PATH:
            print_path(current, i);
            break;
        case GROUP:
            print_group(current, i);
            break;
        default:
            printf("Une erreur est survenu\n");
            return -1;
            break;
        }
        current = current->next;
        i++;
    }

    int verif;
    do{
        printf("\nEntrez le numero de la forme à modifier (0 à %d) : ", ma_scene.count - 1);
        verif=scanf("%d", &index);
        clear_stdin();
    }while(verif !=1 || index < 0 || index >= ma_scene.count);

    // Recherche du nœud précédent et du nœud cible pour gérer la liste chaînée (notamment en cas de suppression)
    node_t *prev = NULL;
    current = ma_scene.head;
    int current_index = 0;
    while (current != NULL && current_index < index) {
        prev = current;
        current = current->next;
        current_index++;
    }

    if (current == NULL) {
        printf("Erreur : Forme introuvable.\n");
        return -1;
    }

    // Sous-menu d'édition
    unsigned char sub_choice;
    printf("\nOptions d'edition pour la forme [%d] :\n", index);
    printf("=> 1 - Modifier les parametres de base (points/couleurs/rayons...)\n");
    printf("=> 2 - Deplacer (Translate)\n");
    printf("=> 3 - Pivoter (Rotate)\n");
    printf("=> 4 - Supprimer la figure\n");
    scanf(" %c", &sub_choice);
    clear_stdin();

    switch (sub_choice) {
        case '1': // Modification classique
            edit(current, index);
            break;
        case '2': // Déplacement (Translate)
            translate(current);
            break;
        case '3': // Rotation (Rotate)
            rotate(current);
            break;
        case '4': // Suppression avec ré-attachement de la liste
            delete(current, prev);
            break;
        default:
            printf("Option invalide.\n");
            break;
    }
    return 0;
}