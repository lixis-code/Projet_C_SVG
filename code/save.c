/**
 * @file save.c
 * @author Vayssiere Alexis
 * @date 2026-10-19
 * @brief Gestion des sauvegarde.
 */
#include "projet_svg.h"

/**
 * @brief Vérifie si un fichier existe déjà sur le disque.
 * @param[in] filepath Chemin complet du fichier à tester.
 * @return int Retourne 1 si le fichier existe, 0 s'il n'existe pas.
 */
int file_exists(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1; // Le fichier existe
    }
    return 0; // Le fichier n'existe pas
}

/**
 * @brief Demande un nom de fichier unique à l'utilisateur et ajoute l'extension `.svcp`.
 * @details Invite l'utilisateur à saisir un nom, vérifie l'unicité du fichier 
 *          dans le dossier de sauvegarde, et boucle tant que le nom existe déjà.
 * 
 * @param[out] filepath_out Pointeur vers le buffer de destination pour le chemin complet.
 * @param[in] max_size Taille maximale du buffer de sortie.
 */
void get_unique_save_filepath(char *filepath_out, size_t max_size) {
    char filename[128];

    while (1) {
        printf("\nEntrez le nom du fichier de sauvegarde (sans extension) : ");
        if (scanf("%127s", filename) != 1) {
            clear_stdin();
            continue;
        }
        clear_stdin();

        // Ajout automatique de l'extension .svcp au nom saisi
        snprintf(filepath_out, max_size, "save/%s.svcp", filename);

        if (file_exists(filepath_out)) {
            printf("Erreur : Un fichier portant le nom '%s' existe deja.\n", filepath_out);
            printf("Veuillez choisir un autre nom.\n");
        } else {
            break;
        }
    }
}

/**
 * @brief Compte récursivement le nombre total de figures principales de la scène.
 * @param[in] head Pointeur vers le premier nœud de la scène.
 * @return int Le nombre total de figures.
 */
int count_scene_nodes(node_t *head) {
    int count = 0;
    node_t *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

/**
 * @brief Sauvegarde une liste chaînée de points dans le fichier de sauvegarde.
 * @param[out] file Pointeur vers le fichier de sauvegarde ouvert en écriture.
 * @param[in] pt_curr Pointeur vers le premier point de la liste (multi-ligne ou polygone).
 */
void save_points_list(FILE *file, point_node_t *pt_curr) {
    point_node_t *curr = pt_curr;
    while (curr != NULL) {
        fprintf(file, " %d,%d", curr->pt.x, curr->pt.y);
        curr = curr->next;
    }
}

/**
 * @brief Sauvegarde la liste des commandes d'un Path dans le fichier.
 * @param[out] file Pointeur vers le fichier de sauvegarde ouvert en écriture.
 * @param[in] cmd_curr Pointeur vers la première commande du path.
 */
void save_path_commands_list(FILE *file, path_command_node_t *cmd_curr) {
    path_command_node_t *curr = cmd_curr;
    while (curr != NULL) {
        fprintf(file, "\tD ");
        switch (curr->type) {
            case MOVETO:
                fprintf(file, "M %d,%d\n", curr->p.x, curr->p.y);
                break;
            case LINETO:
                fprintf(file, "L %d,%d\n", curr->p.x, curr->p.y);
                break;
            case CURVETO:
                fprintf(file, "C %d,%d %d,%d %d,%d\n", 
                        curr->ctrl1.x, curr->ctrl1.y, 
                        curr->ctrl2.x, curr->ctrl2.y, 
                        curr->p.x, curr->p.y);
                break;
            case SMOOTH_CURVE:
                fprintf(file, "S %d,%d %d,%d\n", 
                        curr->ctrl2.x, curr->ctrl2.y, 
                        curr->p.x, curr->p.y);
                break;
            case QUAD:
                fprintf(file, "Q %d,%d %d,%d\n", 
                        curr->ctrl1.x, curr->ctrl1.y, 
                        curr->p.x, curr->p.y);
                break;
            case SMOOTH_QUAD:
                fprintf(file, "T %d,%d\n", curr->p.x, curr->p.y);
                break;
            case CLOSE:
                fprintf(file, "Z\n");
                break;
        }
        curr = curr->next;
    }
}

/**
 * @brief Sérialise et écrit les données d'une ligne dans le fichier.
 * @param[out] file Pointeur vers le fichier de sauvegarde.
 * @param[in] current Pointeur vers le nœud contenant la ligne.
 */
void save_line(FILE *file, node_t *current){
    fprintf(file, "L %d,%d %d,%d %s %d %d %d\n",
        current->fig.line->a->x, current->fig.line->a->y,
        current->fig.line->b->x, current->fig.line->b->y,
        current->fig.line->color,
        current->fig.line->translate_x, current->fig.line->translate_y,
        current->fig.line->rotate);
}
/**
 * @brief Sérialise et écrit les données d'un cercle dans le fichier.
 * @param[out] file Pointeur vers le fichier de sauvegarde.
 * @param[in] current Pointeur vers le nœud contenant le cercle.
 */
void save_circle(FILE *file, node_t *current){
    fprintf(file, "C %d,%d %d %s %s %d %d %d\n",
        current->fig.circle->center->x, current->fig.circle->center->y,
        current->fig.circle->radius,
        current->fig.circle->color_border, current->fig.circle->color,
        current->fig.circle->translate_x, current->fig.circle->translate_y,
        current->fig.circle->rotate);
}
/**
 * @brief Sérialise et écrit les données d'une ellipse dans le fichier.
 * @param[out] file Pointeur vers le fichier de sauvegarde.
 * @param[in] current Pointeur vers le nœud contenant l'ellipse.
 */
void save_ellipse(FILE *file, node_t *current){
    fprintf(file, "E %d,%d %d %d %s %s %d %d %d\n",
        current->fig.ellipse->center->x, current->fig.ellipse->center->y,
        current->fig.ellipse->radius_x, current->fig.ellipse->radius_y,
        current->fig.ellipse->color_border, current->fig.ellipse->color,
        current->fig.ellipse->translate_x, current->fig.ellipse->translate_y,
        current->fig.ellipse->rotate);
}
/**
 * @brief Sérialise et écrit les données d'un carré dans le fichier.
 * @param[out] file Pointeur vers le fichier de sauvegarde.
 * @param[in] current Pointeur vers le nœud contenant le carré.
 */
void save_square(FILE *file, node_t *current){
    fprintf(file, "S %d,%d %d %s %s %d %d %d\n",
        current->fig.square->origin->x, current->fig.square->origin->y,
        current->fig.square->widht,
        current->fig.square->color_border, current->fig.square->color,
        current->fig.square->translate_x, current->fig.square->translate_y,
        current->fig.square->rotate);
}
/**
 * @brief Sérialise et écrit les données d'un rectangle dans le fichier.
 * @param[out] file Pointeur vers le fichier de sauvegarde.
 * @param[in] current Pointeur vers le nœud contenant le rectangle.
 */
void save_rectangle(FILE *file, node_t *current){
    fprintf(file, "R %d,%d %d %d %s %s %d %d %d\n",
        current->fig.rectangle->origin->x, current->fig.rectangle->origin->y,
        current->fig.rectangle->widht, current->fig.rectangle->height,
        current->fig.rectangle->color_border, current->fig.rectangle->color,
        current->fig.rectangle->translate_x, current->fig.rectangle->translate_y,
        current->fig.rectangle->rotate);
}
/**
 * @brief Sérialise et écrit les données d'une multi-ligne (polyline) dans le fichier.
 * @param[out] file Pointeur vers le fichier de sauvegarde.
 * @param[in] current Pointeur vers le nœud contenant la multi-ligne.
 */
void save_multi_line(FILE *file, node_t *current){
    int nb_pts = 0;
    point_node_t *p_curr = current->fig.multi_line->point_head;
    while (p_curr != NULL) { nb_pts++; p_curr = p_curr->next; }

    fprintf(file, "M %d", nb_pts);
    save_points_list(file, current->fig.multi_line->point_head);
    fprintf(file, " %s %d %d %d\n",
        current->fig.multi_line->color,
        current->fig.multi_line->translate_x, current->fig.multi_line->translate_y,
        current->fig.multi_line->rotate);
}
/**
 * @brief Sérialise et écrit les données d'un polygone dans le fichier.
 * @param[out] file Pointeur vers le fichier de sauvegarde.
 * @param[in] current Pointeur vers le nœud contenant le polygone.
 */
void save_polygone(FILE *file, node_t *current){
    int nb_pts = 0;
    point_node_t *p_curr = current->fig.polygone->point_head;
    while (p_curr != NULL) { nb_pts++; p_curr = p_curr->next; }

    fprintf(file, "P %d", nb_pts);
    save_points_list(file, current->fig.polygone->point_head);
    fprintf(file, " %s %s %d %d %d\n",
        current->fig.polygone->color_border, current->fig.polygone->color,
        current->fig.polygone->translate_x, current->fig.polygone->translate_y,
        current->fig.polygone->rotate);
}
/**
 * @brief Sérialise et écrit les données d'un path et de ses commandes dans le fichier.
 * @param[out] file Pointeur vers le fichier de sauvegarde.
 * @param[in] current Pointeur vers le nœud contenant le path.
 */
void save_path(FILE *file, node_t *current){
    fprintf(file, "W %s %s %d %d %d %d\n",
        current->fig.path->color_border, current->fig.path->color,
        current->fig.path->translate_x, current->fig.path->translate_y,
        current->fig.path->rotate,
        current->fig.path->nb_commands);
    save_path_commands_list(file, current->fig.path->commands_head);
}
// Déclaration anticipée pour la compilation croisée
void save_figure_to_file(FILE *file, node_t *current);
/**
 * @brief Sérialise et écrit les données d'un groupe et de ses figures enfants de manière récursive.
 * @param[out] file Pointeur vers le fichier de sauvegarde.
 * @param[in] current Pointeur vers le nœud contenant le groupe.
 */
void save_group(FILE *file, node_t *current){
    int nb_children = 0;
    node_t *child = current->fig.group->children_head;
    while (child != NULL) { nb_children++; child = child->next; }

    fprintf(file, "G %d %d %d %d\n",
            current->fig.group->translate_x, current->fig.group->translate_y,
            current->fig.group->rotate,
            nb_children);

    child = current->fig.group->children_head;
    while (child != NULL) {
        fprintf(file, "\t");
        save_figure_to_file(file, child);
        child = child->next;
    }
}

/**
 * @brief Fonction de routage générique pour sauvegarder une figure selon son type.
 * @param[out] file Pointeur vers le fichier de sauvegarde.
 * @param[in] current Pointeur vers le nœud de la figure à sérialiser.
 */
void save_figure_to_file(FILE *file, node_t *current) {
    if (current == NULL) return;

    switch (current->type) {
        case LINE:
            save_line(file, current);
            break;
        case CIRCLE:
            save_circle(file, current);
            break;
        case ELLIPSE:
            save_ellipse(file, current);
            break;
        case SQUARE:
            save_square(file, current);
            break;
        case RECTANGLE:
            save_rectangle(file, current);
            break;
        case MULTI_LINE: 
            save_multi_line(file, current);
            break;
        case POLYGONE: 
            save_polygone(file, current);
            break;
        case PATH:
            save_path(file, current);
            break;
        case GROUP:
            save_group(file, current);
            break;
        default:
            break;
    }
}

/**
 * @brief Sauvegarde le projet courant dans un fichier (avec option d'écrasement ou nouveau nom).
 * @details Vérifie si un chemin de sauvegarde est déjà associé au projet courant. 
 *          Si oui, demande à l'utilisateur s'il souhaite écraser ce fichier existant 
 *          ou en créer un nouveau. Sinon, demande directement un nouveau nom de fichier unique. 
 *          Ouvre ensuite le fichier en écriture, écrit l'en-tête (version et nombre de figures), 
 *          sérialise l'intégralité de la scène, met à jour le fichier courant et ferme le flux.
 */
void save_project(void) {
    system("clear");
    char filepath[256];
    
    // Si un fichier est déjà en cours (chargé ou sauvegardé précédemment)
    if (current_save_filepath[0] != '\0') {
        char choice;
        printf("\nVoulez-vous ecraser le fichier actuel (%s) ? (o/n) : ", current_save_filepath);
        scanf(" %c", &choice);
        clear_stdin();
        
        if (choice == 'o' || choice == 'O') {
            snprintf(filepath, sizeof(filepath), "%s", current_save_filepath);
        } else {
            get_unique_save_filepath(filepath, sizeof(filepath));
        }
    } else {
        get_unique_save_filepath(filepath, sizeof(filepath));
    }

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Erreur critique : Impossible de creer le fichier de sauvegarde.\n");
        sleep(2);
        return;
    }

    int total_nodes = count_scene_nodes(ma_scene.head);
    fprintf(file, "1 %d\n", total_nodes);

    node_t *current = ma_scene.head;
    while (current != NULL) {
        save_figure_to_file(file, current);
        current = current->next;
    }

    fclose(file);
    
    // Mettre à jour le fichier courant
    snprintf(current_save_filepath, sizeof(current_save_filepath), "%s", filepath);
    printf("Succes ! Projet sauvegarde dans : %s\n", filepath);
    sleep(2);
}