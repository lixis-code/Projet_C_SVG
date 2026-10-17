#include "projet_svg.h"

//ajout de line dans le html
void print_line_to_html(FILE *file, node_t *current){
    fprintf(file, "  <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n", 
        current->fig.line->a->x, current->fig.line->a->y, 
        current->fig.line->b->x, current->fig.line->b->y, 
        current->fig.line->color, 
        current->fig.line->translate_x, current->fig.line->translate_y, 
        current->fig.line->rotate);
}
//ajout de cercle dans le html
void print_circle_to_html(FILE *file, node_t *current){
    fprintf(file, "  <circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"#%s\" fill=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n", 
        current->fig.circle->center->x, current->fig.circle->center->y, 
        current->fig.circle->radius, 
        current->fig.circle->color_border, current->fig.circle->color, 
        current->fig.circle->translate_x, current->fig.circle->translate_y, 
        current->fig.circle->rotate);
}
//ajout d ellipse dans le html
void print_ellipse_to_html(FILE *file, node_t *current){
    fprintf(file, "  <ellipse cx=\"%d\" cy=\"%d\" rx=\"%d\" ry=\"%d\" stroke=\"#%s\" fill=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n",
        current->fig.ellipse->center->x, current->fig.ellipse->center->y,
        current->fig.ellipse->radius_x, current->fig.ellipse->radius_y,
        current->fig.ellipse->color_border, current->fig.ellipse->color, 
        current->fig.ellipse->translate_x, current->fig.ellipse->translate_y,
        current->fig.ellipse->rotate);
}
//ajout de carré dans le html
void print_square_to_html(FILE *file, node_t *current){
    fprintf(file, "  <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"#%s\" fill=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n",
        current->fig.square->origin->x, current->fig.square->origin->y,
        current->fig.square->widht, current->fig.square->widht,
        current->fig.square->color_border, current->fig.square->color,
        current->fig.square->translate_x, current->fig.square->translate_y,
        current->fig.square->rotate);
}
//ajout de rectangle dans le html
void print_rectangle_to_html(FILE *file, node_t *current){
    fprintf(file, "  <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"#%s\" fill=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n",
        current->fig.rectangle->origin->x, current->fig.rectangle->origin->y,
        current->fig.rectangle->widht, current->fig.rectangle->height,
        current->fig.rectangle->color_border, current->fig.rectangle->color,
        current->fig.rectangle->translate_x, current->fig.rectangle->translate_y,
        current->fig.rectangle->rotate);
}

// Fonction pour exporter toute la liste chaînée vers le fichier HTML/SVG
void save_scene_to_html(void) {
    FILE *file = fopen("index/index.html", "w");
    if(file == NULL){
        printf("Une erreur est survenue lors de l'ouverture du fichier HTML.\n");
        return;
    }

    fprintf(file, "<svg viewBox=\"-250 -250 500 500\" xmlns=\"http://www.w3.org/2000/svg\">\n");

    node_t *current = ma_scene.head;
    while (current != NULL) {
        switch (current->type){
        case LINE: //mettre les print dans des fonction tierce pour rendre le code plus lisible (a apliquer aussi dans le edit, quit er create)
            print_line_to_html(file, current);
            break;
        case CIRCLE:
            print_circle_to_html(file, current);
            break;
        case ELLIPSE:
            print_ellipse_to_html(file, current);
            break;
        case SQUARE:
            print_square_to_html(file, current);
            break;
        case RECTANGLE:
            print_rectangle_to_html(file, current);
            break;
        default:
            break;
        }
        current = current->next;
    }

    fprintf(file, "</svg>\n");
    fclose(file);
/*
//chercher comment le faire marcer plus tard (car pour le moment sa marche pas)
    // Commande système pour ouvrir le fichier HTML selon l'OS / environnement
    char command[512];
    #if defined(_WIN32) || defined(_WIN64)
        sprintf(command, "start %s", filename);
    #elif defined(__APPLE__)
        sprintf(command, "open %s", filename);
    #else
        // Linux / WSL
        sprintf(command, "xdg-open %s > /dev/null 2>&1 &", file);
    #endif
    system(command);*/
}