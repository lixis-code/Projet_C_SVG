#include "projet_svg.h"

// Libération complète de la mémoire de la liste chaînée
void free_scene(void) {
    node_t *current = ma_scene.head;
    while (current != NULL) {
        node_t *next_node = current->next;
        if (current->type == LINE) {
            free(current->fig.line->color);
            free(current->fig.line->a);
            free(current->fig.line->b);
            free(current->fig.line);
        } else if (current->type == CIRCLE) {
            free(current->fig.circle->color);
            free(current->fig.circle->color_border);
            free(current->fig.circle->center);
            free(current->fig.circle);
        }
        free(current);
        current = next_node;
    }
    ma_scene.head = NULL;
    ma_scene.count = 0;
}