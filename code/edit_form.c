#include "projet_svg.h"

int edit_form(void) {
    if (ma_scene.count == 0 || ma_scene.head == NULL) {
        printf("\nAucune forme presente dans le projet.\n");
        return 0;
    }

    int index;
    printf("\n--- Liste des formes existantes ---\n");
    
    node_t *current = ma_scene.head;
    int i = 0;
    while (current != NULL) { //implementer un switch a therme
        if (current->type == LINE) {
            printf("[%d] Ligne (Point A: %d,%d | Point B: %d,%d)\n", 
                   i, current->fig.line->a->x, current->fig.line->a->y,
                   current->fig.line->b->x, current->fig.line->b->y);
        } else if (current->type == CIRCLE) {
            printf("[%d] Cercle (Centre: %d,%d | Rayon: %d)\n", 
                   i, current->fig.circle->center->x, 
                   current->fig.circle->center->y, 
                   current->fig.circle->radius);
        }
        current = current->next;
        i++;
    }

    printf("\nEntrez le numero de la forme a modifier (0 à %d) : ", ma_scene.count - 1);
    if (scanf("%d", &index) != 1 || index < 0 || index >= ma_scene.count) {
        clear_stdin();
        printf("Index invalide.\n");
        return -1;
    }
    clear_stdin();

    // Recherche du nœud correspondant dans la liste chaînée
    current = ma_scene.head;
    int current_index = 0;
    while (current != NULL && current_index < index) {
        current = current->next;
        current_index++;
    }

    if (current == NULL) {
        printf("Erreur : Forme introuvable.\n");
        return -1;
    }

    // Modification selon le type (via l'énumérateur)
    if (current->type == LINE) {
        printf("\nModification de la Ligne [%d]\n", index);
        printf("Nouveau point A :\n");
        add_new_point(current->fig.line->a);
        printf("Nouveau point B :\n");
        add_new_point(current->fig.line->b);
        
        free(current->fig.line->color);
        printf("Nouvelle couleur :\n");
        current->fig.line->color = add_color();
    } else if (current->type == CIRCLE) {
        printf("\nModification du Cercle [%d]\n", index);
        printf("Nouveau centre :\n");
        add_new_point(current->fig.circle->center);
        
        current->fig.circle->radius = add_radius();
        
        free(current->fig.circle->color_border);
        printf("Nouvelle couleur de bordure :\n");
        current->fig.circle->color_border = add_color();
        
        free(current->fig.circle->color);
        printf("Nouvelle couleur de remplissage :\n");
        current->fig.circle->color = add_color();
    }
    return 0;
}