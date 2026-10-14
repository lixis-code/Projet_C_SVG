#ifndef PROJET_SVG
    #define PROJET_SVG

    //bibliotheques 
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <ctype.h>

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
    }line_s;

    typedef struct circle_t{
        char *color;
        char *color_border;
        point *center;
        int radius;
    }circle_s;

    typedef union figure_t{
        line_s *line;
        circle_s *circle;
    }figure;

    //fonction pre-charger
    void clear_stdin(void);
    int add_new_form(void);
    int edit_form(void);
#endif