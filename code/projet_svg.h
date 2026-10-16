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
        RECTANGLE
    } figure_type_t;

    //couleur en exa sous la forme suivante #ffffff => stroke = border, fill = remplissage
    //variable
    //point
    typedef struct point_t{
        int x;
        int y;
    }point;

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
    typedef struct ellipse_t{ //<ellipse cx="100" cy="50" rx="100" ry="50" />
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
    typedef struct square_t{//<rect x="0" y="0" width="100" height="100" /> on donnera la meme valeur a width et height
        char *color;
        char *color_border;
        point *origin;
        int widht;
        int translate_x;
        int translate_y;
        int rotate;
    }square_s;

    //rectangle
    typedef struct rectangle_t{//<rect x="0" y="0" width="100" height="100" />
        char *color;
        char *color_border;
        point *origin;
        int widht;
        int height;
        int translate_x;
        int translate_y;
        int rotate;
    }rectangle_s;
    
    //ajouter enchainement de ligne / trajectoire (chemin) / polygone / groupe

    //figures
    typedef union figure_t{
        line_s *line;
        circle_s *circle;
        ellipse_s *ellipse;
        square_s *square;
        rectangle_s *rectangle;
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

    //fonction principal des different programme
    int add_new_form(void);
    int edit_form(void);
    void save_scene_to_html(void);
    void free_scene(void);
#endif