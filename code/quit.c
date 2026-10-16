#include "projet_svg.h"

// Libération complète de la mémoire de la figure
void free_figure(node_t *current){
    switch (current->type){
        case LINE:
            free(current->fig.line->color);
            free(current->fig.line->a);
            free(current->fig.line->b);
            free(current->fig.line);
            break;
        case CIRCLE:
            free(current->fig.circle->color);
            free(current->fig.circle->color_border);
            free(current->fig.circle->center);
            free(current->fig.circle);
            break;
        case ELLIPSE:
            free(current->fig.ellipse->center);
            free(current->fig.ellipse->color_border);
            free(current->fig.ellipse->color);
            free(current->fig.ellipse);
            break;
        case SQUARE:
            free(current->fig.square->origin);
            free(current->fig.square->color_border);
            free(current->fig.square->color);
            free(current->fig.square);
            break;
        case RECTANGLE:
            free(current->fig.rectangle->origin);
            free(current->fig.rectangle->color_border);
            free(current->fig.rectangle->color);
            free(current->fig.rectangle);
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