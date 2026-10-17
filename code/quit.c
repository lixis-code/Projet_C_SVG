#include "projet_svg.h"

// Liberation de la memoire d'une ligne
void free_line(node_t *current){
    free(current->fig.line->color);
    free(current->fig.line->a);
    free(current->fig.line->b);
    free(current->fig.line);
}
// Liberation de la memoire d'un cercle
void free_circle(node_t *current){
    free(current->fig.circle->color);
    free(current->fig.circle->color_border);
    free(current->fig.circle->center);
    free(current->fig.circle);
}
// Liberation de la memoire d'une ellipse
void free_ellipse(node_t *current){
    free(current->fig.ellipse->center);
    free(current->fig.ellipse->color_border);
    free(current->fig.ellipse->color);
    free(current->fig.ellipse);
}
// Liberation de la memoire d'un carré
void free_square(node_t *current){
    free(current->fig.square->origin);
    free(current->fig.square->color_border);
    free(current->fig.square->color);
    free(current->fig.square);
}
// Liberation de la memoire d'un rectangle
void free_rectangle(node_t *current){
    free(current->fig.rectangle->origin);
    free(current->fig.rectangle->color_border);
    free(current->fig.rectangle->color);
    free(current->fig.rectangle);
}
// Liberation de la memoire d'un multi ligne
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
// Liberation de la memoire d'un polygone
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

// Libération complète de la mémoire de la figure
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
        default:
            break;
        }
        free(current);
}

// Libération complète de la mémoire de la liste chaînée
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