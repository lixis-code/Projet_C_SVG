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
    }line;

    //fonction pre-charger
    int add_new_form(void);
#endif