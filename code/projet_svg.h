#ifndef PROJET_SVG
    #define PROJET_SVG

    //bibliotheques 
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <ctype.h>

    typedef enum {
        LINE,
        CIRCLE,
        ELLIPSE,
        SQUARE,
        RECTANGLE,
        MULTI_LINE,
        POLYGONE,
        PATH,
        GROUP
    } figure_type_t;

    // Types de commandes possibles pour le Path (M, L, C, S, Q, T, Z)
    typedef enum {
        MOVETO,        // M
        LINETO,        // L
        CURVETO,       // C (Cubique classique)
        SMOOTH_CURVE,  // S (Cubique lisse)
        QUAD,          // Q (Quadratique)
        SMOOTH_QUAD,   // T (Quadratique lisse)
        CLOSE          // Z
    } path_cmd_type_t;

    //couleur en exa sous la forme suivante #ffffff => stroke = border, fill = remplissage
    //structure

    //point
    typedef struct point_t{
        int x;
        int y;
    }point;

    //liste chainer de point
    typedef struct point_node_t {
        point pt;
        struct point_node_t *next;
    } point_node_t;

    // Noeud d'une commande pour la liste chaînée du Path
    typedef struct path_command_node_t {
        path_cmd_type_t type;
        point p;              // Point d'arrivée
        point ctrl1;          // Point de contrôle 1 (ou unique pour Q)
        point ctrl2;          // Point de contrôle 2 (pour C et S)
        struct path_command_node_t *next;
    } path_command_node_t;

    //ligne
    typedef struct line_t{
        char *color;
        point *a;
        point *b;
        int translate_x;
        int translate_y;
        int rotate;
    }line_s;

    //cercle
    typedef struct circle_t{
        char *color;
        char *color_border;
        point *center;
        int radius;
        int translate_x;
        int translate_y;
        int rotate;
    }circle_s;

    //ellipse
    typedef struct ellipse_t{
        char *color;
        char *color_border;
        point *center;
        int radius_x;
        int radius_y;
        int translate_x;
        int translate_y;
        int rotate;
    }ellipse_s;

    //carré
    typedef struct square_t{
        char *color;
        char *color_border;
        point *origin;
        int widht;
        int translate_x;
        int translate_y;
        int rotate;
    }square_s;

    //rectangle
    typedef struct rectangle_t{
        char *color;
        char *color_border;
        point *origin;
        int widht;
        int height;
        int translate_x;
        int translate_y;
        int rotate;
    }rectangle_s;
    
    //multi-ligne
    typedef struct multi_line_t{
        char *color;
        point_node_t *point_head;
        int nb_points;
        int translate_x;
        int translate_y;
        int rotate;
    }multi_line_s;

    //polygone
    typedef struct polygone_t{
        char *color;
        char *color_border;
        point_node_t *point_head;
        int nb_points;
        int translate_x;
        int translate_y;
        int rotate;
    }polygone_s;

    typedef struct path_t {
        char *color;
        char *color_border;
        path_command_node_t *commands_head;
        int nb_commands;
        int translate_x;
        int translate_y;
        int rotate;
    } path_s;

    typedef struct node_t node_t; // Declaration anticiper pour passer la compilation

    typedef struct group_t {
        node_t *children_head; // Sous-liste des figures contenues dans le groupe
        int nb_children;      // Nombre de figures dans le groupe
        int translate_x;
        int translate_y;
        int rotate;
    } group_s;

    //figures
    typedef union figure_t{
        line_s *line;
        circle_s *circle;
        ellipse_s *ellipse;
        square_s *square;
        rectangle_s *rectangle;
        multi_line_s *multi_line;
        polygone_s *polygone;
        path_s *path;
        group_s *group;
    }figure;

    // Élément de la liste chaînée
    typedef struct node_t {
        figure fig;
        figure_type_t type;
        struct node_t *next;
    } node_t;

    // Structure de la scène pointant vers le début de la liste
    typedef struct {
        node_t *head;
        int count;
    } Scene;

    // Déclaration de la scène globale
    extern Scene ma_scene;

    //fonction utilitaire commune
    char* add_color(void);
    void clear_stdin(void);
    int add_new_point(point *p);
    int add_int(void);
    void free_figure(node_t *current);
    void print_figure_to_html(FILE *file, node_t *current);
    void free_figure(node_t *current);

    //fonction principal des different programme
    int add_new_form(void);
    int edit_form(void);
    void save_scene_to_html(void);
    void free_scene(void);
#endif