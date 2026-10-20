/**
 * @file save.c
 * @author Vayssiere Alexis
 * @date 2026-10-19
 * @brief Gestion des sauvegarde.
 */
#include "projet_svg.h"

// Fonction utilitaire pour vérifier si un fichier existe déjà
int file_exists(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1; // Le fichier existe
    }
    return 0; // Le fichier n'existe pas
}

// Fonction pour demander un nom de fichier unique et ajouter automatiquement .svcp
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

// Fonction pour compter récursivement le nombre total de figures principales de la scène
int count_scene_nodes(node_t *head) {
    int count = 0;
    node_t *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

// Sauvegarde de la liste des points (pour Multi-ligne et Polygone)
void save_points_list(FILE *file, point_node_t *pt_curr) {
    point_node_t *curr = pt_curr;
    while (curr != NULL) {
        fprintf(file, " %d,%d", curr->pt.x, curr->pt.y);
        curr = curr->next;
    }
}

// Sauvegarde de la liste des commandes d'un Path
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

void save_line(FILE *file, node_t *current){
    fprintf(file, "L %d,%d %d,%d %s %d %d %d\n",
        current->fig.line->a->x, current->fig.line->a->y,
        current->fig.line->b->x, current->fig.line->b->y,
        current->fig.line->color,
        current->fig.line->translate_x, current->fig.line->translate_y,
        current->fig.line->rotate);
}
void save_circle(FILE *file, node_t *current){
    fprintf(file, "C %d,%d %d %s %s %d %d %d\n",
        current->fig.circle->center->x, current->fig.circle->center->y,
        current->fig.circle->radius,
        current->fig.circle->color_border, current->fig.circle->color,
        current->fig.circle->translate_x, current->fig.circle->translate_y,
        current->fig.circle->rotate);
}
void save_ellipse(FILE *file, node_t *current){
    fprintf(file, "E %d,%d %d %d %s %s %d %d %d\n",
        current->fig.ellipse->center->x, current->fig.ellipse->center->y,
        current->fig.ellipse->radius_x, current->fig.ellipse->radius_y,
        current->fig.ellipse->color_border, current->fig.ellipse->color,
        current->fig.ellipse->translate_x, current->fig.ellipse->translate_y,
        current->fig.ellipse->rotate);
}
void save_square(FILE *file, node_t *current){
    fprintf(file, "S %d,%d %d %s %s %d %d %d\n",
        current->fig.square->origin->x, current->fig.square->origin->y,
        current->fig.square->widht,
        current->fig.square->color_border, current->fig.square->color,
        current->fig.square->translate_x, current->fig.square->translate_y,
        current->fig.square->rotate);
}
void save_rectangle(FILE *file, node_t *current){
    fprintf(file, "R %d,%d %d %d %s %s %d %d %d\n",
        current->fig.rectangle->origin->x, current->fig.rectangle->origin->y,
        current->fig.rectangle->widht, current->fig.rectangle->height,
        current->fig.rectangle->color_border, current->fig.rectangle->color,
        current->fig.rectangle->translate_x, current->fig.rectangle->translate_y,
        current->fig.rectangle->rotate);
}
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
void save_path(FILE *file, node_t *current){
    fprintf(file, "W %s %s %d %d %d %d\n",
        current->fig.path->color_border, current->fig.path->color,
        current->fig.path->translate_x, current->fig.path->translate_y,
        current->fig.path->rotate,
        current->fig.path->nb_commands);
    save_path_commands_list(file, current->fig.path->commands_head);
}
void save_figure_to_file(FILE *file, node_t *current);//defini a l avanc pour la compilation
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

// Fonction récursive pour sauvegarder une figure et ses enfants (si c'est un groupe)
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

// Fonction principale de sauvegarde du projet
void save_project(void) {
    char filepath[256];
    
    // 1. Demande du nom et vérification d'unicité
    get_unique_save_filepath(filepath, sizeof(filepath));

    // 2. Ouverture du fichier en écriture
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Erreur critique : Impossible de creer le fichier de sauvegarde.\n");
        return;
    }

    // 3. Écriture de l'en-tête (Version = 1, Nombre total de figures principales)
    int total_nodes = count_scene_nodes(ma_scene.head);
    fprintf(file, "1 %d\n", total_nodes);

    // 4. Parcours et écriture de chaque figure de la scène
    node_t *current = ma_scene.head;
    while (current != NULL) {
        save_figure_to_file(file, current);
        current = current->next;
    }

    fclose(file);
    printf("Succes ! Projet sauvegarde dans : %s\n", filepath);
}