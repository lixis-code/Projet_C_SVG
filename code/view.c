/**
 * @file view.c
 * @author Vayssiere Alexis
 * @date 2026-10-14
 * @brief Gestion de l'affichage des forme dans un format SVG.
 */
#include "projet_svg.h"

/**
 * @brief Récupère et formate tous les points d'une liste chaînée en une chaîne SVG.
 * @details Parcourt la liste chaînée de points et concatène leurs coordonnées 
 *          au format "x,y " dans un buffer de destination tout en respectant 
 *          la taille maximale allouée pour éviter les dépassements de mémoire.
 * @param[in] pt_curr Pointeur vers le premier nœud de la liste de points.
 * @param[out] buffer Chaîne de caractères de destination pour stocker les points formatés.
 * @param[in] max_size Taille maximale autorisée du buffer.
 */
void print_points_list(point_node_t *pt_curr, char *buffer, size_t max_size){
    buffer[0] = '\0'; // Initialise le buffer comme une chaîne vide
    
    while (pt_curr != NULL) {
        char pt_str[32];
        sprintf(pt_str, "%d,%d ", pt_curr->pt.x, pt_curr->pt.y);
        
        // Sécurité pour éviter le dépassement de mémoire du buffer
        if (strlen(buffer) + strlen(pt_str) < max_size) {
            strcat(buffer, pt_str);
        }
        pt_curr = pt_curr->next;
    }
}

/**
 * @brief Traduit la liste des commandes du Path en une chaîne de caractères SVG (attribut d).
 * @details Parcourt la liste chaînée des commandes et convertit chaque type 
 *          (MoveTo, LineTo, CurveTo, etc.) ainsi que ses points et points de contrôle 
 *          en syntaxe de chemin SVG officielle.
 * @param[in] cmd_curr Pointeur vers la première commande du path.
 * @param[out] buffer Chaîne de destination pour stocker la séquence de commandes SVG.
 * @param[in] max_size Taille maximale autorisée du buffer.
 */
void print_path_commands_list(path_command_node_t *cmd_curr, char *buffer, size_t max_size){
    buffer[0] = '\0';
    while (cmd_curr != NULL) {
        char cmd_str[64];
        switch (cmd_curr->type) {
            case MOVETO:
                sprintf(cmd_str, "m %d %d ", cmd_curr->p.x, cmd_curr->p.y);
                break;
            case LINETO:
                sprintf(cmd_str, "l %d %d ", cmd_curr->p.x, cmd_curr->p.y);
                break;
            case CURVETO:
                sprintf(cmd_str, "c %d %d, %d %d, %d %d ", 
                        cmd_curr->ctrl1.x, cmd_curr->ctrl1.y,
                        cmd_curr->ctrl2.x, cmd_curr->ctrl2.y,
                        cmd_curr->p.x, cmd_curr->p.y);
                break;
            case SMOOTH_CURVE:
                sprintf(cmd_str, "s %d %d, %d %d ", cmd_curr->ctrl2.x, cmd_curr->ctrl2.y, cmd_curr->p.x, cmd_curr->p.y);
                break;
            case QUAD:
                sprintf(cmd_str, "q %d %d, %d %d ", cmd_curr->ctrl1.x, cmd_curr->ctrl1.y, cmd_curr->p.x, cmd_curr->p.y);
                break;
            case SMOOTH_QUAD:
                sprintf(cmd_str, "t %d %d ", cmd_curr->p.x, cmd_curr->p.y);
                break;
            case CLOSE:
                sprintf(cmd_str, "z ");
                break;
        }
        if (strlen(buffer) + strlen(cmd_str) < max_size) {
            strcat(buffer, cmd_str);
        }
        cmd_curr = cmd_curr->next;
    }
}

/**
 * @brief Écrit le code SVG correspondant à une ligne simple dans le fichier HTML.
 * @param[out] file Pointeur vers le fichier HTML de sortie.
 * @param[in] current Pointeur vers le nœud de la figure contenant la ligne.
 */
void print_line_to_html(FILE *file, node_t *current){
    fprintf(file, "  <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n", 
        current->fig.line->a->x, current->fig.line->a->y, 
        current->fig.line->b->x, current->fig.line->b->y, 
        current->fig.line->color, 
        current->fig.line->translate_x, current->fig.line->translate_y, 
        current->fig.line->rotate);
}
/**
 * @brief Écrit le code SVG correspondant à un cercle dans le fichier HTML.
 * @param[out] file Pointeur vers le fichier HTML de sortie.
 * @param[in] current Pointeur vers le nœud de la figure contenant le cercle.
 */
void print_circle_to_html(FILE *file, node_t *current){
    fprintf(file, "  <circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"#%s\" fill=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n", 
        current->fig.circle->center->x, current->fig.circle->center->y, 
        current->fig.circle->radius, 
        current->fig.circle->color_border, current->fig.circle->color, 
        current->fig.circle->translate_x, current->fig.circle->translate_y, 
        current->fig.circle->rotate);
}
/**
 * @brief Écrit le code SVG correspondant à une ellipse dans le fichier HTML.
 * @param[out] file Pointeur vers le fichier HTML de sortie.
 * @param[in] current Pointeur vers le nœud de la figure contenant l'ellipse.
 */
void print_ellipse_to_html(FILE *file, node_t *current){
    fprintf(file, "  <ellipse cx=\"%d\" cy=\"%d\" rx=\"%d\" ry=\"%d\" stroke=\"#%s\" fill=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n",
        current->fig.ellipse->center->x, current->fig.ellipse->center->y,
        current->fig.ellipse->radius_x, current->fig.ellipse->radius_y,
        current->fig.ellipse->color_border, current->fig.ellipse->color, 
        current->fig.ellipse->translate_x, current->fig.ellipse->translate_y,
        current->fig.ellipse->rotate);
}
/**
 * @brief Écrit le code SVG correspondant à un carré dans le fichier HTML.
 * @param[out] file Pointeur vers le fichier HTML de sortie.
 * @param[in] current Pointeur vers le nœud de la figure contenant le carré.
 */
void print_square_to_html(FILE *file, node_t *current){
    fprintf(file, "  <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"#%s\" fill=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n",
        current->fig.square->origin->x, current->fig.square->origin->y,
        current->fig.square->widht, current->fig.square->widht,
        current->fig.square->color_border, current->fig.square->color,
        current->fig.square->translate_x, current->fig.square->translate_y,
        current->fig.square->rotate);
}
/**
 * @brief Écrit le code SVG correspondant à un rectangle dans le fichier HTML.
 * @param[out] file Pointeur vers le fichier HTML de sortie.
 * @param[in] current Pointeur vers le nœud de la figure contenant le rectangle.
 */
void print_rectangle_to_html(FILE *file, node_t *current){
    fprintf(file, "  <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" stroke=\"#%s\" fill=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n",
        current->fig.rectangle->origin->x, current->fig.rectangle->origin->y,
        current->fig.rectangle->widht, current->fig.rectangle->height,
        current->fig.rectangle->color_border, current->fig.rectangle->color,
        current->fig.rectangle->translate_x, current->fig.rectangle->translate_y,
        current->fig.rectangle->rotate);
}
/**
 * @brief Écrit le code SVG correspondant à une ligne brisée (polyline) dans le fichier HTML.
 * @param[out] file Pointeur vers le fichier HTML de sortie.
 * @param[in] current Pointeur vers le nœud de la figure contenant la multi-ligne.
 */
void print_multi_line_to_html(FILE *file, node_t *current){
    char points_buf[1024]="";
    print_points_list(current->fig.multi_line->point_head, points_buf, sizeof(points_buf));
    fprintf(file, "  <polyline points=\"%s\" stroke=\"#%s\" fill=\"none\" transform=\"translate(%d,%d) rotate(%d)\"/>\n",
        points_buf, current->fig.multi_line->color,
        current->fig.multi_line->translate_x, current->fig.multi_line->translate_y,
        current->fig.multi_line->rotate);
}
/**
 * @brief Écrit le code SVG correspondant à un polygone dans le fichier HTML.
 * @param[out] file Pointeur vers le fichier HTML de sortie.
 * @param[in] current Pointeur vers le nœud de la figure contenant le polygone.
 */
void print_polygone_to_html(FILE *file, node_t *current){
    char points_buf[1024]="";
    print_points_list(current->fig.polygone->point_head, points_buf, sizeof(points_buf));
    fprintf(file, "  <polygon points=\"%s\" stroke=\"#%s\" fill=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n",
        points_buf, current->fig.polygone->color_border, current->fig.polygone->color,
        current->fig.polygone->translate_x, current->fig.polygone->translate_y,
        current->fig.polygone->rotate);
}
/**
 * @brief Écrit le code SVG correspondant à un chemin complexe (path) dans le fichier HTML.
 * @param[out] file Pointeur vers le fichier HTML de sortie.
 * @param[in] current Pointeur vers le nœud de la figure contenant le path.
 */
void print_path_to_html(FILE *file, node_t *current){
    char d_buf[2048] = "";
    print_path_commands_list(current->fig.path->commands_head, d_buf, sizeof(d_buf));
    fprintf(file, "  <path d=\"%s\" stroke=\"#%s\" fill=\"#%s\" transform=\"translate(%d,%d) rotate(%d)\"/>\n",
        d_buf, current->fig.path->color_border, current->fig.path->color,
        current->fig.path->translate_x, current->fig.path->translate_y,
        current->fig.path->rotate);
}
/**
 * @brief Écrit le code SVG correspondant à un groupe de figures dans le fichier HTML (Récursif).
 * @details Ouvre une balise de groupe SVG (`<g>`), applique les transformations globales, 
 *          parcourt et exporte récursivement chaque figure enfant contenue dans le groupe, 
 *          puis ferme la balise (`</g>`).
 * @param[out] file Pointeur vers le fichier HTML de sortie.
 * @param[in] current Pointeur vers le nœud contenant le groupe.
 */
void print_group_to_html(FILE *file, node_t *current){
    fprintf(file, "  <g transform=\"translate(%d,%d) rotate(%d)\">\n",
        current->fig.group->translate_x, current->fig.group->translate_y,
        current->fig.group->rotate);
    node_t *child = current->fig.group->children_head;
    while (child != NULL) {
        print_figure_to_html(file, child);
        child = child->next;
    }
    fprintf(file, "  </g>\n");
}

/**
 * @brief Fonction générique de routage pour l'export SVG d'une figure.
 * @details Analyse le type de la figure contenue dans le nœud et appelle 
 *          la fonction d'export HTML/SVG spécialisée correspondante.
 * @param[out] file Pointeur vers le fichier HTML de sortie.
 * @param[in] current Pointeur vers le nœud de la figure à exporter.
 */
void print_figure_to_html(FILE *file, node_t *current){
    switch (current->type){
        case LINE:
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
        case MULTI_LINE:
            print_multi_line_to_html(file, current);
            break;
        case POLYGONE:
            print_polygone_to_html(file, current);
            break;
        case PATH:
            print_path_to_html(file, current);
            break;
        case GROUP:
            print_group_to_html(file, current);
            break;
        default:
            break;
    }
}

/**
 * @brief Ouvre automatiquement le fichier HTML généré dans le navigateur web par défaut.
 * @details Détecte le système d'exploitation hôte (Windows, macOS ou Linux/WSL) 
 *          et exécute la commande système adéquate pour lancer le navigateur.
 */
void open_html(void){
    char command[512];
    const char *filename = "index/index.html";

#if defined(_WIN32) || defined(_WIN64)
    // Windows
    sprintf(command, "start %s", filename);
#elif defined(__APPLE__)
    // macOS
    sprintf(command, "open %s", filename);
#else
    // Linux / WSL (redirection des sorties pour éviter de polluer le terminal)
    sprintf(command, "cmd.exe /c start %s > /dev/null 2>&1", filename);
#endif

    int ret = system(command);
    if (ret == -1) {
        printf("Impossible d'ouvrir automatiquement le navigateur.\n");
    }
}

/**
 * @brief Sauvegarde l'intégralité de la scène globale au format HTML/SVG.
 * @details Crée ou écrase le fichier HTML de sortie, écrit l'en-tête SVG global 
 *          avec ses dimensions (viewBox), parcourt toute la liste chaînée des figures 
 *          de la scène pour les transcrire en SVG, ferme le fichier puis déclenche 
 *          son ouverture automatique dans le navigateur.
 */
void save_scene_to_html(void) {
    FILE *file = fopen("index/index.html", "w");
    if(file == NULL){
        printf("Une erreur est survenue lors de l'ouverture du fichier HTML.\n");
        return;
    }

    fprintf(file, "<svg viewBox=\"-250 -250 500 500\" xmlns=\"http://www.w3.org/2000/svg\">\n");

    node_t *current = ma_scene.head;
    while (current != NULL) {
        print_figure_to_html(file, current);
        current = current->next;
    }
    fprintf(file, "</svg>\n");
    fclose(file);
    open_html();
}