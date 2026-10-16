#include "projet_svg.h"

int modification_line(node_t *current, int index){
    char choice;
    printf("\nModification de la Ligne [%d]\n", index);
    printf("=> 1 : Point A\n");
    printf("=> 2 : Point B\n");
    printf("=> 3 : Couleur\n");
    printf("=> 4 : Tout\n");
    while(1){
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '1':
            printf("Nouveau point A :\n");
            add_new_point(current->fig.line->a);
            return 0;
            break;
        case '2':
            printf("Nouveau point B :\n");
            add_new_point(current->fig.line->b);
            return 0;
            break;
        case '3':
            free(current->fig.line->color);
            printf("Nouvelle couleur :\n");
            current->fig.line->color = add_color();
            return 0;
            break;
        case '4':
            printf("Nouveau point A :\n");
            add_new_point(current->fig.line->a);
            printf("Nouveau point B :\n");
            add_new_point(current->fig.line->b);
            
            free(current->fig.line->color);
            printf("Nouvelle couleur :\n");
            current->fig.line->color = add_color();
            return 0;
            break;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
}

int modification_circle(node_t *current, int index){
    char choice;
    printf("\nModification du cercle [%d]\n", index);
    printf("=> 1 : Centre\n");
    printf("=> 2 : Rayon\n");
    printf("=> 3 : Couleur de la bordure\n");
    printf("=> 4 : Couleur du fond\n");
    printf("=> 5 : Tout\n");
    while(1){
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){
        case '1':
            printf("Nouveau centre :\n");
            add_new_point(current->fig.circle->center);
            return 0;
            break;
        case '2':
            printf("Nouveau rayon :\n");
            current->fig.circle->radius = add_radius();
            return 0;
            break;
        case '3':
            free(current->fig.circle->color_border);
            printf("Nouvelle couleur de bordure :\n");
            current->fig.circle->color_border = add_color();
            return 0;
            break;
        case '4':
            free(current->fig.circle->color);
            printf("Nouvelle couleur de remplissage :\n");
            current->fig.circle->color = add_color();
            return 0;
            break;
        case '5':
            printf("Nouveau centre :\n");
            add_new_point(current->fig.circle->center);
            
            printf("Nouveau rayon :\n");
            current->fig.circle->radius = add_radius();
            
            free(current->fig.circle->color_border);
            printf("Nouvelle couleur de bordure :\n");
            current->fig.circle->color_border = add_color();
            
            free(current->fig.circle->color);
            printf("Nouvelle couleur de remplissage :\n");
            current->fig.circle->color = add_color();
            return 0;
            break;
        default:
            printf("Choix invalide\n");
            break;
        }
    }
}

int modification(node_t *current, int index){
    switch (current->type)
    {
    case LINE:
        modification_line(current, index);
        break;
    case CIRCLE:
        modification_circle(current, index);
        break;
    default:
        printf("une erreur est survenu\n");
        return -1;
        break;
    }
    printf("Forme modifiee avec succes !\n");
    return 0;
}

int translate(node_t *current){
    int tx, ty;
    printf("Entrez le décalage en X (translate_x) : ");
    scanf("%d", &tx);
    clear_stdin();
    printf("Entrez le décalage en Y (translate_y) : ");
    scanf("%d", &ty);
    clear_stdin();

    switch (current->type){
    case LINE:
        current->fig.line->translate_x = tx;
        current->fig.line->translate_y = ty;
        break;
    case CIRCLE:
        current->fig.circle->translate_x = tx;
        current->fig.circle->translate_y = ty;
        break;
    default:
        printf("Une erreur est survenu\n");
        return -1;
        break;
    }
    printf("Déplacement appliqué avec succès !\n");
    return 0;
}

int rotate(node_t *current){
    int angle;
    printf("Entrez l'angle de rotation en degrés : ");
    scanf("%d", &angle);
    clear_stdin();

    switch (current->type){
    case LINE:
        current->fig.line->rotate = angle;
        break;
    case CIRCLE:
        current->fig.circle->rotate = angle;
        break;
    default:
        printf("Une erreur est survenu\n");
        return -1;
        break;
    }
    printf("Rotation appliquée avec succès !\n");
    return 0;
}

int delete(node_t *current, node_t *prev){
    if (prev == NULL) {
        // Suppression du premier élément
        ma_scene.head = current->next;
    } else {
        // Suppression d'un élément intermédiaire ou de fin
        prev->next = current->next;
    }

    // Libération de la mémoire de l'élément supprimé
    free_figure(current);
    ma_scene.count--;
    printf("Forme supprimee avec succes !\n");
    return 0;
}

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
            printf("Une erreur est survenu\n");
            return -1;
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
            modification(current, index);
            break;

        case '2': // Déplacement (Translate)
            translate(current);
            break;
        case '3': // Rotation (Rotate)
            rotate(current);
            break;

        case '4': // Suppression avec ré-attachement de la liste
            delete(current, prev);
            break;

        default:
            printf("Option invalide.\n");
            break;
    }
    return 0;
}