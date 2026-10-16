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
        CIRCLE
    } figure_type_t;
    //couleur en exa sous la forme suivante #ffffff => stroke = border, fill = remplissage
    //variable
    typedef struct point_t{
        int x;
        int y;
    }point;

    typedef struct line_t{
        char *color;
        point *a;
        point *b;
        int translate_x;
        int translate_y;
        int rotate;
    }line_s;

    typedef struct circle_t{
        char *color;
        char *color_border;
        point *center;
        int radius;
        int translate_x;
        int translate_y;
        int rotate;
    }circle_s;

    typedef union figure_t{
        line_s *line;
        circle_s *circle;
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
    int add_radius(void);
    void free_figure(node_t *current);

    //fonction principal des different programme
    int add_new_form(void);
    int edit_form(void);
    void save_scene_to_html(void);
    void free_scene(void);
#endif