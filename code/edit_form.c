#include "projet_svg.h"//decouper le code en plusieur fonction car c pas beau

//fonction principal
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
            printf("[%d] Ligne (Point A: %d,%d | Point B: %d,%d | Trans: %d,%d | Rot: %d°)\n", 
                   i, current->fig.line->a->x, current->fig.line->a->y,
                   current->fig.line->b->x, current->fig.line->b->y,
                   current->fig.line->translate_x, current->fig.line->translate_y,
                   current->fig.line->rotate);
            break;
        case CIRCLE:
            printf("[%d] Cercle (Centre: %d,%d | Rayon: %d | Trans: %d,%d | Rot: %d°)\n", 
                   i, current->fig.circle->center->x, 
                   current->fig.circle->center->y, 
                   current->fig.circle->radius,
                   current->fig.circle->translate_x, current->fig.circle->translate_y,
                   current->fig.circle->rotate);
            break;
        default:
            break;
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

    // Recherche du nœud précédent et du nœud cible pour gérer la liste chaînée (notamment en cas de suppression)
    node_t *prev = NULL;
    current = ma_scene.head;
    int current_index = 0;
    while (current != NULL && current_index < index) {
        prev = current;
        current = current->next;
        current_index++;
    }

    if (current == NULL) {
        printf("Erreur : Forme introuvable.\n");
        return -1;
    }

    // Sous-menu d'édition
    unsigned char sub_choice;
    printf("\nOptions d'edition pour la forme [%d] :\n", index);
    printf("=> 1 - Modifier les parametres de base (points/couleurs/rayons)\n");
    printf("=> 2 - Deplacer (Translate)\n");
    printf("=> 3 - Pivoter (Rotate)\n");
    printf("=> 4 - Supprimer la figure\n");
    scanf(" %c", &sub_choice);
    clear_stdin();

    switch (sub_choice) {
        case '1': // Modification classique
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
            printf("Forme modifiee avec succes !\n");
            break;

        case '2': // Déplacement (Translate)
            {
                int tx, ty;
                printf("Entrez le décalage en X (translate_x) : ");
                scanf("%d", &tx);
                clear_stdin();
                printf("Entrez le décalage en Y (translate_y) : ");
                scanf("%d", &ty);
                clear_stdin();

                if (current->type == LINE) {
                    current->fig.line->translate_x = tx;
                    current->fig.line->translate_y = ty;
                } else {
                    current->fig.circle->translate_x = tx;
                    current->fig.circle->translate_y = ty;
                }
                printf("Déplacement appliqué avec succès !\n");
            }
            break;

        case '3': // Rotation (Rotate)
            {
                int angle;
                printf("Entrez l'angle de rotation en degrés : ");
                scanf("%d", &angle);
                clear_stdin();

                if (current->type == LINE) {
                    current->fig.line->rotate = angle;
                } else {
                    current->fig.circle->rotate = angle;
                }
                printf("Rotation appliquée avec succès !\n");
            }
            break;

        case '4': // Suppression avec ré-attachement de la liste
            if (prev == NULL) {
                // Suppression du premier élément
                ma_scene.head = current->next;
            } else {
                // Suppression d'un élément intermédiaire ou de fin
                prev->next = current->next;
            }

            // Libération de la mémoire de l'élément supprimé
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
            ma_scene.count--;
            printf("Forme supprimee avec succes !\n");
            break;

        default:
            printf("Option invalide.\n");
            break;
    }
    return 0;
}