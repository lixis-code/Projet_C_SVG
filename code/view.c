#include "projet_svg.h"

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
        case LINE:
            line_s *l = current->fig.line;
            fprintf(file, "  <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"#%s\" />\n", l->a->x, l->a->y, l->b->x, l->b->y, l->color);
            break;
        case CIRCLE:
            circle_s *c = current->fig.circle;
            fprintf(file, "  <circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"#%s\" fill=\"#%s\"/>\n", c->center->x, c->center->y, c->radius, c->color_border, c->color);
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