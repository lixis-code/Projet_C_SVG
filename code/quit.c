/**
 * @file quit.c
 * @author Vayssiere Alexis
 * @date 2026-10-14
 * @brief Liberation de la memoire a la fermeture du programme.
 */
#include "projet_svg.h"

/**
 * @brief Libère la mémoire allouée pour une ligne.
 * @details Désalloue les points d'extrémité (A et B), la chaîne de caractères 
 *          de la couleur, puis la structure de la ligne elle-même.
 * @param[in,out] current Pointeur vers le nœud contenant la ligne à détruire.
 */
void free_line(node_t *current){
    free(current->fig.line->color);
    free(current->fig.line->a);
    free(current->fig.line->b);
    free(current->fig.line);
}
/**
 * @brief Libère la mémoire allouée pour un cercle.
 * @details Désalloue les couleurs de fond et de bordure, le point central, 
 *          puis la structure du cercle elle-même.
 * @param[in,out] current Pointeur vers le nœud contenant le cercle à détruire.
 */
void free_circle(node_t *current){
    free(current->fig.circle->color);
    free(current->fig.circle->color_border);
    free(current->fig.circle->center);
    free(current->fig.circle);
}
/**
 * @brief Libère la mémoire allouée pour une ellipse.
 * @details Désalloue le point central, les couleurs de bordure et de fond, 
 *          ainsi que la structure de l'ellipse elle-même.
 * @param[in,out] current Pointeur vers le nœud contenant l'ellipse à détruire.
 */
void free_ellipse(node_t *current){
    free(current->fig.ellipse->center);
    free(current->fig.ellipse->color_border);
    free(current->fig.ellipse->color);
    free(current->fig.ellipse);
}
/**
 * @brief Libère la mémoire allouée pour un carré.
 * @details Désalloue le point d'origine, les couleurs de bordure et de fond, 
 *          puis la structure du carré elle-même.
 * @param[in,out] current Pointeur vers le nœud contenant le carré à détruire.
 */
void free_square(node_t *current){
    free(current->fig.square->origin);
    free(current->fig.square->color_border);
    free(current->fig.square->color);
    free(current->fig.square);
}
/**
 * @brief Libère la mémoire allouée pour un rectangle.
 * @details Désalloue le point d'origine, les couleurs de bordure et de fond, 
 *          ainsi que la structure du rectangle elle-même.
 * @param[in,out] current Pointeur vers le nœud contenant le rectangle à détruire.
 */
void free_rectangle(node_t *current){
    free(current->fig.rectangle->origin);
    free(current->fig.rectangle->color_border);
    free(current->fig.rectangle->color);
    free(current->fig.rectangle);
}
/**
 * @brief Libère la mémoire allouée pour une ligne brisée (multi-ligne).
 * @details Parcourt et libère chaque nœud de la liste chaînée de points, 
 *          désalloue la couleur, puis la structure de la multi-ligne.
 * @param[in,out] current Pointeur vers le nœud contenant la multi-ligne à détruire.
 */
void free_multi_line(node_t *current){
    point_node_t *pt_curr = current->fig.multi_line->point_head;
    while (pt_curr != NULL) {
        point_node_t *next_pt = pt_curr->next;
        free(pt_curr);
        pt_curr = next_pt;
    }
    free(current->fig.multi_line->color);
    free(current->fig.multi_line);
}
/**
 * @brief Libère la mémoire allouée pour un polygone.
 * @details Parcourt et libère chaque nœud de la liste chaînée des sommets, 
 *          désalloue les couleurs de bordure et de fond, puis la structure du polygone.
 * @param[in,out] current Pointeur vers le nœud contenant le polygone à détruire.
 */
void free_polygone(node_t *current){
    point_node_t *pt_curr = current->fig.polygone->point_head;
    while (pt_curr != NULL) {
        point_node_t *next_pt = pt_curr->next;
        free(pt_curr);
        pt_curr = next_pt;
    }
    free(current->fig.polygone->color_border);
    free(current->fig.polygone->color);
    free(current->fig.polygone);
}
/**
 * @brief Libère la mémoire allouée pour un chemin complexe (path).
 * @details Parcourt et libère chaque nœud de la liste chaînée des commandes du path, 
 *          désalloue les couleurs de fond et de bordure, puis la structure du path.
 * @param[in,out] current Pointeur vers le nœud contenant le path à détruire.
 */
void free_path(node_t *current){
    path_command_node_t *cmd_curr = current->fig.path->commands_head;
    while (cmd_curr != NULL) {
        path_command_node_t *next_cmd = cmd_curr->next;
        free(cmd_curr);
        cmd_curr = next_cmd;
    }
    free(current->fig.path->color);
    free(current->fig.path->color_border);
    free(current->fig.path); // Note: attention au point-virgule, juste free(current->fig.path)
}
/**
 * @brief Libère la mémoire allouée pour un groupe de figures (Récursif).
 * @details Parcourt récursivement la liste des figures enfants contenues dans le groupe 
 *          pour les libérer une à une, puis désalloue la structure du groupe lui-même.
 * @param[in,out] current Pointeur vers le nœud contenant le groupe à détruire.
 */
void free_group(node_t *current){
    node_t *child = current->fig.group->children_head;
    while (child != NULL) {
        node_t *next_child = child->next;
        free_figure(child);
        child = next_child;
    }
    free(current->fig.group);
}

/**
 * @brief Fonction de routage générique pour libérer la mémoire d'une figure.
 * @details Analyse le type de figure du nœud, appelle la fonction de désallocation 
 *          spécifique correspondante, puis libère le nœud lui-même.
 * @param[in,out] current Pointeur vers le nœud de la figure à libérer.
 */
void free_figure(node_t *current){
    switch (current->type){
        case LINE:
            free_line(current);
            break;
        case CIRCLE:
            free_circle(current);
            break;
        case ELLIPSE:
            free_ellipse(current);
            break;
        case SQUARE:
            free_square(current);
            break;
        case RECTANGLE:
            free_rectangle(current);
            break;
        case MULTI_LINE:
            free_multi_line(current);
            break;
        case POLYGONE:
            free_polygone(current);
            break;
        case PATH:
            free_path(current);
            break;
        case GROUP:
            free_group(current);
            break;
        default:
            break;
        }
        free(current);
}

/**
 * @brief Libère l'intégralité de la mémoire de la scène globale.
 * @details Parcourt toute la liste chaînée principale de la scène, libère chaque figure 
 *          et ses dépendances via `free_figure()`, puis réinitialise la tête de liste 
 *          et le compteur de figures à zéro.
 */
void free_scene(void) {
    node_t *current = ma_scene.head;
    while (current != NULL) {
        node_t *next_node = current->next;
        free_figure(current);
        current = next_node;
    }
    ma_scene.head = NULL;
    ma_scene.count = 0;
}