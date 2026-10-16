#include "projet_svg.h"

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