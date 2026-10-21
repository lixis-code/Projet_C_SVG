/**
 * @file edit_form.c
 * @author Vayssiere Alexis
 * @date 2026-10-15
 * @brief Gestion de toutes les modifications du projet courant.
 */
#include "projet_svg.h"

/**
 * @brief Modifie les coordonnées d'un point en affichant un message personnalisé.
 * @param[out] p Pointeur vers le point à modifier.
 * @param[in] m Message d'invite à afficher avant la saisie.
 */
void edit_point(point *p, char *m){
    printf("%s", m);
    add_new_point(p);
}

/**
 * @brief Libère l'ancienne couleur, puis en alloue et saisit une nouvelle.
 * @param[in,out] color Pointeur vers la chaîne de caractères de la couleur actuelle.
 * @param[in] m Message d'invite à afficher.
 */
void edit_color(char *color, char*m){
    free(color);
    printf("%s", m);
    color = add_color();
}

/**
 * @brief Saisit un nouvel entier après affichage d'un message.
 * @param[in] m Message d'invite à afficher.
 * @return int L'entier saisi.
 */
int edit_int(char *m){
    printf("%s", m);
    int i = add_int();
    return i;
}

/**
 * @brief Affiche un menu interactif pour modifier une ligne.
 * @param[in,out] current Pointeur vers le nœud contenant la ligne.
 * @param[in] index Position de la forme dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Affiche un menu interactif pour modifier un cercle.
 * @param[in,out] current Pointeur vers le nœud contenant le cercle.
 * @param[in] index Position de la forme dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Affiche un menu interactif pour modifier une ellipse.
 * @param[in,out] current Pointeur vers le nœud contenant l'ellipse.
 * @param[in] index Position de la forme dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Affiche un menu interactif pour modifier un carré.
 * @param[in,out] current Pointeur vers le nœud contenant le carré.
 * @param[in] index Position de la forme dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Affiche un menu interactif pour modifier un rectangle.
 * @param[in,out] current Pointeur vers le nœud contenant le rectangle.
 * @param[in] index Position de la forme dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Modifie un point existant à un index donné dans une liste chaînée de points.
 * @param[in,out] head_ref Pointeur vers la tête de la liste de points.
 * @param[in] num_points Nombre total de points dans la liste.
 */
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

/**
 * @brief Insère un nouveau point à un index donné dans une liste chaînée de points.
 * @param[in,out] head_ref Pointeur vers la tête de la liste de points.
 * @param[in,out] num_points_ref Pointeur vers le compteur du nombre de points.
 */
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

/**
 * @brief Supprime un point d'une liste chaînée de points à un index donné.
 * @param[in,out] head_ref Pointeur vers la tête de la liste de points.
 * @param[in,out] num_points_ref Pointeur vers le compteur du nombre de points.
 * @param[in] min_points Nombre minimal de points requis pour conserver la forme.
 */
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

/**
 * @brief Menu interactif pour éditer la liste des points d'une multi-ligne ou d'un polygone.
 * @param[in,out] head_ref Pointeur vers la tête de la liste de points.
 * @param[in,out] num_points_ref Pointeur vers le nombre total de points.
 * @param[in] min_points Nombre minimal de points requis.
 * @return int Retourne 0 à la fin de l'édition.
 */
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

/**
 * @brief Affiche un menu interactif pour modifier une ligne brisée (polyline).
 * @param[in,out] current Pointeur vers le nœud contenant la multi-ligne.
 * @param[in] index Position de la forme dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Affiche un menu interactif pour modifier un polygone.
 * @param[in,out] current Pointeur vers le nœud contenant le polygone.
 * @param[in] index Position de la forme dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Demande et met à jour les données (type, points, contrôles) d'une commande de path.
 * @param[out] cmd Pointeur vers le nœud de commande du path à configurer.
 */
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
            edit_point(&cmd->p, "Point d'arrivée :\n");
            break;
        case '2':
            cmd->type = LINETO;
            edit_point(&cmd->p, "Point d'arrivée :\n");
            break;
        case '3':
            cmd->type = CURVETO;
            edit_point(&cmd->ctrl1, "Premier point de contrôle (ctrl1) :\n");
            edit_point(&cmd->ctrl2, "Second point de contrôle (ctrl2) :\n");
            edit_point(&cmd->p, "Point d'arrivée :\n");
            break;
        case '4':
            cmd->type = SMOOTH_CURVE;
            edit_point(&cmd->ctrl2, "Second point de contrôle (ctrl2) :\n");
            edit_point(&cmd->p, "Point d'arrivée :\n");
            break;
        case '5':
            cmd->type = QUAD;
            edit_point(&cmd->ctrl1, "Premier point de contrôle (ctrl1) :\n");
            add_new_point(&cmd->ctrl1);
            edit_point(&cmd->p, "Point d'arrivée :\n");
            break;
        case '6':
            cmd->type = SMOOTH_QUAD;
            edit_point(&cmd->p, "Point d'arrivée :\n");
            break;
        case '7':
            cmd->type = CLOSE;
            cmd->p.x = 0;
            cmd->p.y = 0;
            break;
        default:
            printf("Choix invalide. Par défaut défini sur LineTo (L).\n");
            cmd->type = LINETO;
            edit_point(&cmd->p, "Point d'arrivée :\n");
            break;
    }
}

/**
 * @brief Modifie une commande existante dans un path à partir de son index.
 * @param[in,out] head_ref Pointeur vers la tête de la liste des commandes.
 * @param[in] nb_commands Nombre total de commandes.
 */
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

/**
 * @brief Insère une nouvelle commande à un index donné dans un path.
 * @param[in,out] head_ref Pointeur vers la tête de la liste des commandes.
 * @param[in,out] nb_commands_ref Pointeur vers le nombre total de commandes.
 */
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

/**
 * @brief Supprime une commande d'un path à un index donné.
 * @param[in,out] head_ref Pointeur vers la tête de la liste des commandes.
 * @param[in,out] nb_commands_ref Pointeur vers le nombre total de commandes.
 */
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

/**
 * @brief Menu interactif pour gérer les commandes d'un path (modifier, ajouter, supprimer).
 * @param[in,out] head_ref Pointeur vers la tête de la liste des commandes.
 * @param[in,out] nb_commands_ref Pointeur vers le nombre total de commandes.
 * @return int Retourne 0 à la fin de l'édition.
 */
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

/**
 * @brief Affiche un menu interactif pour modifier un path (commandes et couleurs).
 * @param[in,out] current Pointeur vers le nœud contenant le path.
 * @param[in] index Position de la forme dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
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

/**
 * @brief Permet d'éditer les figures enfants contenues à l'intérieur d'un groupe.
 * @details Sauvegarde temporairement la scène globale, bascule sur la liste 
 *          des enfants du groupe, appelle `edit_form()`, puis restaure la scène.
 * @param[in,out] current Pointeur vers le nœud contenant le groupe.
 * @param[in] index Position du groupe dans la scène.
 * @return int Retourne 0 en cas de succès.
 */
int edit_group(node_t *current, int index){
    printf("\nModification des elements du Groupe [%d]\n", index);
    
    Scene old_scene = ma_scene;
    ma_scene.head = current->fig.group->children_head;
    ma_scene.count = current->fig.group->nb_children;

    edit_form();

    current->fig.group->children_head = ma_scene.head;
    current->fig.group->nb_children = ma_scene.count;
    ma_scene = old_scene;

    return 0;
}

/**
 * @brief Fonction de routage générique pour éditer une forme selon son type.
 * @param[in,out] current Pointeur vers le nœud de la figure à modifier.
 * @param[in] index Position de la forme dans la scène.
 * @return int Retourne 0 en cas de succès, -1 en cas d'erreur.
 */
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

/**
 * @brief Applique une translation (déplacement X, Y) à n'importe quel type de figure.
 * @param[in,out] current Pointeur vers le nœud de la figure à translater.
 * @return int Retourne 0 en cas de succès, -1 en cas d'erreur.
 */
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

/**
 * @brief Applique une rotation (en degrés) à n'importe quel type de figure.
 * @param[in,out] current Pointeur vers le nœud de la figure à faire pivoter.
 * @return int Retourne 0 en cas de succès, -1 en cas d'erreur.
 */
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

/**
 * @brief Supprime une figure de la liste chaînée principale de la scène.
 * @param[in,out] current Pointeur vers le nœud à supprimer.
 * @param[in,out] prev Pointeur vers le nœud précédent (NULL si c'est la tête).
 * @return int Retourne 0 en cas de succès.
 */
int delete(node_t *current, node_t *prev){
    if (prev == NULL) {
        ma_scene.head = current->next;
    } else {
        prev->next = current->next;
    }

    free_figure(current);
    ma_scene.count--;
    printf("Forme supprimee avec succes !\n");
    return 0;
}

/**
 * @brief Applique une symétrie (miroir) sur une ligne par rapport à un axe.
 * @details Modifie les coordonnées des points d'extrémité (A et B) de la ligne 
 *          selon l'axe spécifié ('x' ou 'y').
 * @param[in,out] current Pointeur vers le nœud contenant la ligne.
 * @param[in] axe L'axe de symétrie ('x' pour horizontal, 'y' pour vertical).
 */
void mirror_line(node_t *current, char axe){
    switch(axe){
        case 'x':
            current->fig.line->a->y-=current->fig.line->a->y*2;
            current->fig.line->b->y-=current->fig.line->b->y*2;
            break;
        case 'y':
            current->fig.line->a->x-=current->fig.line->a->x*2;
            current->fig.line->b->x-=current->fig.line->b->x*2;
            break;
        default:
            break;
    }
}
/**
 * @brief Applique une symétrie (miroir) sur un cercle par rapport à un axe.
 * @details Inverse la coordonnée du centre du cercle selon l'axe choisi.
 * @param[in,out] current Pointeur vers le nœud contenant le cercle.
 * @param[in] axe L'axe de symétrie ('x' ou 'y').
 */
void mirror_circle(node_t *current, char axe){
    switch(axe){
        case 'x':
            current->fig.circle->center->y-=current->fig.circle->center->y*2;
            break;
        case 'y':
            current->fig.circle->center->x-=current->fig.circle->center->x*2;
            break;
        default:
            break;
    }
}
/**
 * @brief Applique une symétrie (miroir) sur une ellipse par rapport à un axe.
 * @details Inverse la coordonnée du centre de l'ellipse selon l'axe choisi.
 * @param[in,out] current Pointeur vers le nœud contenant l'ellipse.
 * @param[in] axe L'axe de symétrie ('x' ou 'y').
 */
void mirror_ellipse(node_t *current, char axe){
    switch(axe){
        case 'x':
            current->fig.ellipse->center->y-=current->fig.ellipse->center->y*2;
            break;
        case 'y':
            current->fig.ellipse->center->x-=current->fig.ellipse->center->x*2;
            break;
        default:
            break;
    }
}
/**
 * @brief Applique une symétrie (miroir) sur un carré par rapport à un axe.
 * @details Met à jour l'origine du carré en tenant compte de sa largeur pour conserver 
 *          un positionnement géométrique correct après inversion.
 * @param[in,out] current Pointeur vers le nœud contenant le carré.
 * @param[in] axe L'axe de symétrie ('x' ou 'y').
 */
void mirror_square(node_t *current, char axe){
    switch(axe){
        case 'x':
            current->fig.square->origin->y-=current->fig.square->origin->y*2+current->fig.square->widht;
            break;
        case 'y':
            current->fig.square->origin->x-=current->fig.square->origin->x*2+current->fig.square->widht;
            break;
        default:
            break;
    }
}
/**
 * @brief Applique une symétrie (miroir) sur un rectangle par rapport à un axe.
 * @details Met à jour l'origine du rectangle en tenant compte de ses dimensions 
 *          (largeur et hauteur) pour conserver un positionnement correct après inversion.
 * @param[in,out] current Pointeur vers le nœud contenant le rectangle.
 * @param[in] axe L'axe de symétrie ('x' ou 'y').
 */
void mirror_rectangle(node_t *current, char axe){
    switch(axe){
        case 'x':
            current->fig.rectangle->origin->y-=current->fig.rectangle->origin->y*2+current->fig.rectangle->height;
            break;
        case 'y':
            current->fig.rectangle->origin->x-=current->fig.rectangle->origin->x*2+current->fig.rectangle->widht;
            break;
        default:
            break;
    }
}
/**
 * @brief Applique une symétrie (miroir) sur tous les points d'une ligne brisée (multi-ligne).
 * @details Parcourt la liste chaînée des points et inverse leurs coordonnées Y (pour l'axe X) 
 *          ou X (pour l'axe Y).
 * @param[in,out] current Pointeur vers le nœud contenant la multi-ligne.
 * @param[in] axe L'axe de symétrie ('x' ou 'y').
 */
void mirror_multi_line(node_t *current, char axe){
    if (current == NULL || current->fig.multi_line == NULL) return;
    point_node_t *curr_pt = current->fig.multi_line->point_head;
    switch(axe){
        case 'x':
            // Symétrie par rapport à l'axe X (les ordonnées Y sont inversées)
            while (curr_pt != NULL) {
                curr_pt->pt.y = -curr_pt->pt.y;
                curr_pt = curr_pt->next;
            }
            break;
        case 'y':
            // Symétrie par rapport à l'axe Y (les abscisses X sont inversées)
            while (curr_pt != NULL) {
                curr_pt->pt.x = -curr_pt->pt.x;
                curr_pt = curr_pt->next;
            }
            break;
        default:
            break;
    }
}
/**
 * @brief Applique une symétrie (miroir) sur tous les sommets d'un polygone.
 * @details Parcourt la liste chaînée des sommets et inverse leurs coordonnées selon l'axe choisi.
 * @param[in,out] current Pointeur vers le nœud contenant le polygone.
 * @param[in] axe L'axe de symétrie ('x' ou 'y').
 */
void mirror_polygone(node_t *current, char axe){
    if (current == NULL || current->fig.polygone == NULL) return;
    point_node_t *curr_pt = current->fig.polygone->point_head;
    switch(axe){
        case 'x':
            // Symétrie par rapport à l'axe X (les ordonnées Y sont inversées)
            while (curr_pt != NULL) {
                curr_pt->pt.y = -curr_pt->pt.y;
                curr_pt = curr_pt->next;
            }
            break;
        case 'y':
            // Symétrie par rapport à l'axe Y (les abscisses X sont inversées)
            while (curr_pt != NULL) {
                curr_pt->pt.x = -curr_pt->pt.x;
                curr_pt = curr_pt->next;
            }
            break;
        default:
            break;
    }
}

/**
 * @brief Route la symétrie par rapport à l'axe X selon le type de la figure.
 * @param[in,out] current Pointeur vers le nœud de la figure à inverser.
 */
void mirror_x(node_t *current){
    switch (current->type){
    case LINE:
        mirror_line(current, 'x');
        break;
    case CIRCLE:
        mirror_circle(current, 'x');
        break;
    case ELLIPSE:
        mirror_ellipse(current, 'x');
        break;
    case SQUARE:
        mirror_square(current, 'x');
        break;
    case RECTANGLE:
        mirror_rectangle(current, 'x');
        break;
    case MULTI_LINE:
        mirror_multi_line(current, 'x');
        break;
    case POLYGONE:
        mirror_polygone(current, 'x');
        break;
    case PATH:
        printf("Fonctionaliter non implementer\n");
        break;
    case GROUP:
        printf("Fonctionaliter non implementer\n"); //for (tout les forme du groupe) mirror (recusrsif)
        break;
    default:
        break;
    }
}

/**
 * @brief Route la symétrie par rapport à l'axe Y selon le type de la figure.
 * @param[in,out] current Pointeur vers le nœud de la figure à inverser.
 */
void mirror_y(node_t *current){
    switch (current->type){
    case LINE:
        mirror_line(current, 'y');
        break;
    case CIRCLE:
        mirror_circle(current, 'y');
        break;
    case ELLIPSE:
        mirror_ellipse(current, 'y');
        break;
    case SQUARE:
        mirror_square(current, 'y');
        break;
    case RECTANGLE:
        mirror_rectangle(current, 'y');
        break;
    case MULTI_LINE:
        mirror_multi_line(current, 'y');
        break;
    case POLYGONE:
        mirror_polygone(current, 'y');
        break;
    case PATH:
        printf("Fonctionaliter non implementer\n");
        break;
    case GROUP:
        printf("Fonctionaliter non implementer\n"); //for (tout les forme du groupe) mirror (recusrsif)
        break;
    default:
        break;
    }
}

/**
 * @brief Fonction principale interactive pour appliquer une symétrie à une figure.
 * @details Affiche un menu permettant à l'utilisateur de choisir l'axe de réflexion 
 *          (axe X, axe Y, ou les deux), puis déclenche la fonction correspondante.
 * @param[in,out] current Pointeur vers le nœud de la figure à transformer.
 * @return int Retourne 0 en cas de succès.
 */
int mirror(node_t *current){
    printf("\nChoix d'inversion :\n");
    printf("=> 1 : inverser par rapport a l'axe x\n");
    printf("=> 2 : inverser par rapport a l'axe y\n");
    printf("=> 3 : inverser par rapport aux axes x et y\n");
    int verif;
    unsigned int c;
    do{
        printf("\n");
        verif=scanf("%d", &c);
        clear_stdin();
    }while(verif !=1 || c < 1 || c > 3);
    switch (c){
    case 1:
        mirror_x(current);
        break;
    case 2: 
        mirror_y(current);
        break;
    case 3:
        mirror_x(current);
        mirror_y(current);
        break;
    default:
        printf("Unexpected error\n");
        break;
    }
    return 0;
}

/**
 * @brief Affiche un résumé textuel d'une ligne dans la console.
 * @param[in] current Pointeur vers le nœud de la ligne.
 * @param[in] i Index de la ligne.
 */
void print_line(node_t *current, int i){
    printf("[%d] Ligne (Point A: %d,%d | Point B: %d,%d | Trans: %d,%d | Rot: %d°)\n", 
        i, current->fig.line->a->x, current->fig.line->a->y,
        current->fig.line->b->x, current->fig.line->b->y,
        current->fig.line->translate_x, current->fig.line->translate_y,
        current->fig.line->rotate);
}

/**
 * @brief Affiche un résumé textuel d'un cercle dans la console.
 * @param[in] current Pointeur vers le nœud du cercle.
 * @param[in] i Index du cercle.
 */
void print_circle(node_t *current, int i){
    printf("[%d] Cercle (Centre: %d,%d | Rayon: %d | Trans: %d,%d | Rot: %d°)\n", 
        i, current->fig.circle->center->x, current->fig.circle->center->y, 
        current->fig.circle->radius,
        current->fig.circle->translate_x, current->fig.circle->translate_y,
        current->fig.circle->rotate);
}

/**
 * @brief Affiche un résumé textuel d'une ellipse dans la console.
 * @param[in] current Pointeur vers le nœud de l'ellipse.
 * @param[in] i Index de l'ellipse.
 */
void print_ellipse(node_t *current, int i){
    printf("[%d] Ellipse (Centre: %d,%d | Rayon x: %d | Rayon y: %d | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.ellipse->center->x, current->fig.ellipse->center->y,
        current->fig.ellipse->radius_x, current->fig.ellipse->radius_y,
        current->fig.ellipse->translate_x, current->fig.ellipse->translate_y,
        current->fig.ellipse->rotate);
}

/**
 * @brief Affiche un résumé textuel d'un carré dans la console.
 * @param[in] current Pointeur vers le nœud du carré.
 * @param[in] i Index du carré.
 */
void print_square(node_t *current, int i){
    printf("[%d] Carré (Origine: %d,%d | Largeur: %d | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.square->origin->x, current->fig.square->origin->y,
        current->fig.square->widht,
        current->fig.square->translate_x, current->fig.square->translate_y,
        current->fig.square->rotate);
}

/**
 * @brief Affiche un résumé textuel d'un rectangle dans la console.
 * @param[in] current Pointeur vers le nœud du rectangle.
 * @param[in] i Index du rectangle.
 */
void print_rectangle(node_t *current, int i){
    printf("[%d] Rectangle (Origine: %d;%d | Largeur: %d | Longueur: %d | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.rectangle->origin->x, current->fig.rectangle->origin->y,
        current->fig.rectangle->widht, current->fig.rectangle->height,
        current->fig.rectangle->translate_x, current->fig.rectangle->translate_y,
        current->fig.rectangle->rotate);
}

/**
 * @brief Affiche un résumé textuel d'une multi-ligne dans la console.
 * @param[in] current Pointeur vers le nœud de la multi-ligne.
 * @param[in] i Index de la multi-ligne.
 */
void print_multi_line(node_t *current, int i){
    printf("[%d] Multi ligne (%d points | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.multi_line->nb_points,
        current->fig.multi_line->translate_x, current->fig.multi_line->translate_y,
        current->fig.multi_line->rotate);
}

/**
 * @brief Affiche un résumé textuel d'un polygone dans la console.
 * @param[in] current Pointeur vers le nœud du polygone.
 * @param[in] i Index du polygone.
 */
void print_polygone(node_t *current, int i){
    printf("[%d] Polygone (%d points | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.polygone->nb_points,
        current->fig.polygone->translate_x, current->fig.polygone->translate_y,
        current->fig.polygone->rotate);
}

/**
 * @brief Affiche un résumé textuel d'un path dans la console.
 * @param[in] current Pointeur vers le nœud du path.
 * @param[in] i Index du path.
 */
void print_path(node_t *current, int i){
    printf("[%d] Path (%d commandes | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.path->nb_commands,
        current->fig.path->translate_x, current->fig.path->translate_y,
        current->fig.path->rotate);
}

/**
 * @brief Affiche un résumé textuel d'un groupe dans la console.
 * @param[in] current Pointeur vers le nœud du groupe.
 * @param[in] i Index du groupe.
 */
void print_group(node_t *current, int i){
    printf("[%d] Groupe (%d elements | Trans: %d,%d | Rot: %d°)\n",
        i, current->fig.group->nb_children,
        current->fig.group->translate_x, current->fig.group->translate_y,
        current->fig.group->rotate);
}

/**
 * @brief Fonction principale de gestion et d'édition des formes de la scène.
 * @details Affiche la liste de toutes les formes enregistrées, demande à l'utilisateur 
 *          laquelle il souhaite sélectionner, puis propose les actions disponibles 
 *          (modifier, translater, pivoter, supprimer).
 * @return int Retourne 0 en cas de succès, -1 en cas d'erreur.
 */
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

    // Recherche du nœud précédent et du nœud cible
    node_t *prev = NULL;
    current = ma_scene.head;
    for (int j = 0; j < index; j++) {
        prev = current;
        current = current->next;
    }

    printf("\nActions disponibles pour la forme [%d] :\n", index);
    printf("=> 1 : Éditer les propriétés\n");
    printf("=> 2 : Déplacer (Translation)\n");
    printf("=> 3 : Inverser (Mirroire)\n");
    printf("=> 4 : Faire pivoter (Rotation)\n");
    printf("=> 5 : Supprimer\n");
    printf("=> 6 : Annuler\n");
    unsigned char action;
    scanf(" %c", &action);
    clear_stdin();

    switch (action) {
        case '1':
            edit(current, index);
            break;
        case '2':
            translate(current);
            break;
        case '3':
            mirror(current);
            break;
        case '4':
            rotate(current);
            break;
        case '5':
            delete(current, prev);
            break;
        case '6':
            break;
        default:
            printf("Action invalide.\n");
            break;
    }

    return 0;
}