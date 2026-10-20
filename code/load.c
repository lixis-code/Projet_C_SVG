/**
 * @file load.c
 * @author Vayssiere Alexis
 * @date 2026-10-19
 * @brief Gestion du chargement de sauvegarde.
 */
#include "projet_svg.h"

// Inclusion conditionnelle pour lister les fichiers d'un dossier selon l'OS
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <dirent.h>
#endif

// Variable globale pour le fichier en cours
char current_save_filepath[256] = "";

// Fonction pour afficher et choisir une sauvegarde dans le dossier 'save/'
int list_and_select_save_file(char *filepath_out, size_t max_size) {
    int file_count = 0;
    char filenames[50][256];

    printf("\n--- Liste des sauvegardes disponibles ---\n");

#if defined(_WIN32) || defined(_WIN64)
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("save\\*.svcp", &findFileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                snprintf(filenames[file_count], sizeof(filenames[file_count]), "%s", findFileData.cFileName);
                printf("[%d] %s\n", file_count + 1, filenames[file_count]);
                file_count++;
                if (file_count >= 50) break;
            }
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
#else
    DIR *dir = opendir("save");
    if (dir != NULL) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            size_t len = strlen(entry->d_name);
            if (len > 5 && strcmp(entry->d_name + len - 5, ".svcp") == 0) {
                snprintf(filenames[file_count], sizeof(filenames[file_count]), "%s", entry->d_name);
                printf("[%d] %s\n", file_count + 1, filenames[file_count]);
                file_count++;
                if (file_count >= 50) break;
            }
        }
        closedir(dir);
    }
#endif

    if (file_count == 0) {
        printf("Aucune sauvegarde trouvee dans le dossier 'save/'.\n");
        return 0;
    }

    int choice;
    printf("\nEntrez le numero de la sauvegarde a charger (0 pour annuler) : ");
    if (scanf("%d", &choice) != 1 || choice < 0 || choice > file_count) {
        clear_stdin();
        printf("Choix invalide.\n");
        return 0;
    }
    clear_stdin();

    if (choice == 0) return 0;

    snprintf(filepath_out, max_size, "save/%s", filenames[choice - 1]);
    return 1;
}

// Fonction de lecture de la liste de points (Multi-ligne / Polygone)
void load_points_list(FILE *file, int nb_pts, point_node_t **head_ref) {
    *head_ref = NULL;
    point_node_t *tail = NULL;

    for (int i = 0; i < nb_pts; i++) {
        point_node_t *new_pt = malloc(sizeof(point_node_t));
        if (!new_pt) return;
        new_pt->next = NULL;

        fscanf(file, "%d,%d", &new_pt->pt.x, &new_pt->pt.y);

        if (*head_ref == NULL) {
            *head_ref = new_pt;
        } else {
            tail->next = new_pt;
        }
        tail = new_pt;
    }
}

// Fonction de lecture des commandes d'un Path
void load_path_commands_list(FILE *file, int nb_cmds, path_command_node_t **head_ref) {
    *head_ref = NULL;
    path_command_node_t *tail = NULL;

    for (int i = 0; i < nb_cmds; i++) {
        char d_marker, cmd_type;
        fscanf(file, " %c %c", &d_marker, &cmd_type);

        path_command_node_t *new_cmd = malloc(sizeof(path_command_node_t));
        if (!new_cmd) return;
        new_cmd->next = NULL;

        switch (cmd_type) {
            case 'M':
                new_cmd->type = MOVETO;
                fscanf(file, "%d,%d", &new_cmd->p.x, &new_cmd->p.y);
                break;
            case 'L':
                new_cmd->type = LINETO;
                fscanf(file, "%d,%d", &new_cmd->p.x, &new_cmd->p.y);
                break;
            case 'C':
                new_cmd->type = CURVETO;
                fscanf(file, "%d,%d %d,%d %d,%d", 
                       &new_cmd->ctrl1.x, &new_cmd->ctrl1.y,
                       &new_cmd->ctrl2.x, &new_cmd->ctrl2.y,
                       &new_cmd->p.x, &new_cmd->p.y);
                break;
            case 'S':
                new_cmd->type = SMOOTH_CURVE;
                fscanf(file, "%d,%d %d,%d", 
                       &new_cmd->ctrl2.x, &new_cmd->ctrl2.y,
                       &new_cmd->p.x, &new_cmd->p.y);
                break;
            case 'Q':
                new_cmd->type = QUAD;
                fscanf(file, "%d,%d %d,%d", 
                       &new_cmd->ctrl1.x, &new_cmd->ctrl1.y,
                       &new_cmd->p.x, &new_cmd->p.y);
                break;
            case 'T':
                new_cmd->type = SMOOTH_QUAD;
                fscanf(file, "%d,%d", &new_cmd->p.x, &new_cmd->p.y);
                break;
            case 'Z':
                new_cmd->type = CLOSE;
                new_cmd->p.x = 0;
                new_cmd->p.y = 0;
                break;
        }

        if (*head_ref == NULL) {
            *head_ref = new_cmd;
        } else {
            tail->next = new_cmd;
        }
        tail = new_cmd;
    }
}

node_t* load_figure_from_file(FILE *file);

node_t* load_figure_from_file(FILE *file) {
    char type;
    if (fscanf(file, " %c", &type) != 1) return NULL;

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) return NULL;
    new_node->next = NULL;

    switch (type) {
        case 'L': {
            new_node->type = LINE;
            new_node->fig.line = malloc(sizeof(line_s));
            new_node->fig.line->a = malloc(sizeof(point));
            new_node->fig.line->b = malloc(sizeof(point));
            new_node->fig.line->color = malloc(6*sizeof(char));
            
            fscanf(file, "%d,%d %d,%d %s %d %d %d",
                   &new_node->fig.line->a->x, &new_node->fig.line->a->y,
                   &new_node->fig.line->b->x, &new_node->fig.line->b->y,
                   new_node->fig.line->color,
                   &new_node->fig.line->translate_x, &new_node->fig.line->translate_y,
                   &new_node->fig.line->rotate);
            break;
        }
        case 'C': {
            new_node->type = CIRCLE;
            new_node->fig.circle = malloc(sizeof(circle_s));
            new_node->fig.circle->center = malloc(sizeof(point));
            new_node->fig.circle->color = malloc(6*sizeof(char));
            new_node->fig.circle->color_border = malloc(6*sizeof(char));

            fscanf(file, "%d,%d %d %s %s %d %d %d",
                   &new_node->fig.circle->center->x, &new_node->fig.circle->center->y,
                   &new_node->fig.circle->radius,
                   new_node->fig.circle->color_border, new_node->fig.circle->color,
                   &new_node->fig.circle->translate_x, &new_node->fig.circle->translate_y,
                   &new_node->fig.circle->rotate);
            break;
        }
        case 'E': {
            new_node->type = ELLIPSE;
            new_node->fig.ellipse = malloc(sizeof(ellipse_s));
            new_node->fig.ellipse->center = malloc(sizeof(point));
            new_node->fig.ellipse->color = malloc(6*sizeof(char));
            new_node->fig.ellipse->color_border = malloc(6*sizeof(char));

            fscanf(file, "%d,%d %d %d %s %s %d %d %d",
                   &new_node->fig.ellipse->center->x, &new_node->fig.ellipse->center->y,
                   &new_node->fig.ellipse->radius_x, &new_node->fig.ellipse->radius_y,
                   new_node->fig.ellipse->color_border, new_node->fig.ellipse->color,
                   &new_node->fig.ellipse->translate_x, &new_node->fig.ellipse->translate_y,
                   &new_node->fig.ellipse->rotate);
            break;
        }
        case 'S': {
            new_node->type = SQUARE;
            new_node->fig.square = malloc(sizeof(square_s));
            new_node->fig.square->origin = malloc(sizeof(point));
            new_node->fig.square->color = malloc(6*sizeof(char));
            new_node->fig.square->color_border = malloc(6*sizeof(char));

            fscanf(file, "%d,%d %d %s %s %d %d %d",
                   &new_node->fig.square->origin->x, &new_node->fig.square->origin->y,
                   &new_node->fig.square->widht,
                   new_node->fig.square->color_border, new_node->fig.square->color,
                   &new_node->fig.square->translate_x, &new_node->fig.square->translate_y,
                   &new_node->fig.square->rotate);
            break;
        }
        case 'R': {
            new_node->type = RECTANGLE;
            new_node->fig.rectangle = malloc(sizeof(rectangle_s));
            new_node->fig.rectangle->origin = malloc(sizeof(point));
            new_node->fig.rectangle->color = malloc(6*sizeof(char));
            new_node->fig.rectangle->color_border = malloc(6*sizeof(char));

            fscanf(file, "%d,%d %d %d %s %s %d %d %d",
                   &new_node->fig.rectangle->origin->x, &new_node->fig.rectangle->origin->y,
                   &new_node->fig.rectangle->widht, &new_node->fig.rectangle->height,
                   new_node->fig.rectangle->color_border, new_node->fig.rectangle->color,
                   &new_node->fig.rectangle->translate_x, &new_node->fig.rectangle->translate_y,
                   &new_node->fig.rectangle->rotate);
            break;
        }
        case 'M': {
            new_node->type = MULTI_LINE;
            new_node->fig.multi_line = malloc(sizeof(multi_line_s));
            new_node->fig.multi_line->color = malloc(6*sizeof(char));
            
            int nb_pts;
            fscanf(file, "%d", &nb_pts);
            load_points_list(file, nb_pts, &new_node->fig.multi_line->point_head);
            
            fscanf(file, "%s %d %d %d",
                   new_node->fig.multi_line->color,
                   &new_node->fig.multi_line->translate_x, &new_node->fig.multi_line->translate_y,
                   &new_node->fig.multi_line->rotate);
            break;
        }
        case 'P': {
            new_node->type = POLYGONE;
            new_node->fig.polygone = malloc(sizeof(polygone_s));
            new_node->fig.polygone->color = malloc(6*sizeof(char));
            new_node->fig.polygone->color_border = malloc(6*sizeof(char));

            int nb_pts;
            fscanf(file, "%d", &nb_pts);
            load_points_list(file, nb_pts, &new_node->fig.polygone->point_head);

            fscanf(file, "%s %s %d %d %d",
                   new_node->fig.polygone->color_border, new_node->fig.polygone->color,
                   &new_node->fig.polygone->translate_x, &new_node->fig.polygone->translate_y,
                   &new_node->fig.polygone->rotate);
            break;
        }
        case 'W': {
            new_node->type = PATH;
            new_node->fig.path = malloc(sizeof(path_s));
            new_node->fig.path->color = malloc(6*sizeof(char));
            new_node->fig.path->color_border = malloc(6*sizeof(char));

            fscanf(file, "%s %s %d %d %d %d",
                   new_node->fig.path->color_border, new_node->fig.path->color,
                   &new_node->fig.path->translate_x, &new_node->fig.path->translate_y,
                   &new_node->fig.path->rotate,
                   &new_node->fig.path->nb_commands);

            load_path_commands_list(file, new_node->fig.path->nb_commands, &new_node->fig.path->commands_head);
            break;
        }
        case 'G': {
            new_node->type = GROUP;
            new_node->fig.group = malloc(sizeof(group_s));

            int nb_children;
            fscanf(file, "%d %d %d %d",
                   &new_node->fig.group->translate_x, &new_node->fig.group->translate_y,
                   &new_node->fig.group->rotate,
                   &nb_children);

            new_node->fig.group->children_head = NULL;
            node_t *child_tail = NULL;

            for (int i = 0; i < nb_children; i++) {
                node_t *child_node = load_figure_from_file(file);
                if (child_node != NULL) {
                    if (new_node->fig.group->children_head == NULL) {
                        new_node->fig.group->children_head = child_node;
                    } else {
                        child_tail->next = child_node;
                    }
                    child_tail = child_node;
                }
            }
            break;
        }
        default:
            free(new_node);
            return NULL;
    }
    return new_node;
}

void load_project(void) {
    char filepath[256];

    if (!list_and_select_save_file(filepath, sizeof(filepath))) {
        return;
    }

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier de sauvegarde.\n");
        return;
    }

    int version, total_nodes;
    if (fscanf(file, "%d %d", &version, &total_nodes) != 2) {
        printf("Erreur : Format de fichier invalide.\n");
        fclose(file);
        return;
    }

    ma_scene.head = NULL;

    for (int i = 0; i < total_nodes; i++) {
        add_to_scene(load_figure_from_file(file));
    }

    fclose(file);

    snprintf(current_save_filepath, sizeof(current_save_filepath), "%s", filepath);

    printf("Succes ! Projet charge depuis : %s\n", filepath);
}