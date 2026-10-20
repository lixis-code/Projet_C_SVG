/**
 * @file projet_svg.h
 * @author Vayssiere Alexis
 * @date 2026-10-12
 * @brief Bibliothèque principale du projet SVG.
 * @details Contient toutes les bibliothèques, énumérations, structures de données 
 *          et prototypes de fonctions nécessaires à la gestion et au rendu des formes SVG.
 */
#ifndef PROJET_SVG
    #define PROJET_SVG

    // --- Bibliothèques ---
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <ctype.h>

    /**
     * @brief Types de figures géométriques supportés.
     */
    typedef enum {
        LINE,          /**< Ligne simple */
        CIRCLE,        /**< Cercle */
        ELLIPSE,       /**< Ellipse */
        SQUARE,        /**< Carré */
        RECTANGLE,     /**< Rectangle */
        MULTI_LINE,    /**< Ligne brisée (polyline) */
        POLYGONE,      /**< Polygone fermé */
        PATH,          /**< Chemin complexe (path) */
        GROUP          /**< Groupe de figures */
    } figure_type_t;

    /**
     * @brief Types de commandes possibles pour un chemin (Path SVG : M, L, C, S, Q, T, Z).
     */
    typedef enum {
        MOVETO,        /**< M - Déplacement vers un point */
        LINETO,        /**< L - Ligne droite vers un point */
        CURVETO,       /**< C - Courbe de Bézier cubique classique */
        SMOOTH_CURVE,  /**< S - Courbe de Bézier cubique lisse */
        QUAD,          /**< Q - Courbe de Bézier quadratique */
        SMOOTH_QUAD,   /**< T - Courbe de Bézier quadratique lisse */
        CLOSE          /**< Z - Fermeture du chemin */
    } path_cmd_type_t;

    // --- Structures ---

    /**
     * @brief Représente un point en coordonnées 2D.
     */
    typedef struct point_t {
        int x; /**< Coordonnée horizontale */
        int y; /**< Coordonnée verticale */
    } point;

    /**
     * @brief Élément d'une liste chaînée de points.
     */
    typedef struct point_node_t {
        point pt;                   /**< Coordonnées du point */
        struct point_node_t *next;  /**< Pointeur vers le point suivant */
    } point_node_t;

    /**
     * @brief Noeud d'une commande pour la liste chaînée d'un Path.
     */
    typedef struct path_command_node_t {
        path_cmd_type_t type;         /**< Type de commande SVG */
        point p;                      /**< Point d'arrivée */
        point ctrl1;                  /**< Point de contrôle 1 (ou unique pour Q) */
        point ctrl2;                  /**< Point de contrôle 2 (pour C et S) */
        struct path_command_node_t *next; /**< Commande suivante dans le chemin */
    } path_command_node_t;

    /**
     * @brief Structure représentant une ligne.
     */
    typedef struct line_t {
        char *color;        /**< Couleur de la ligne */
        point *a;           /**< Point de départ */
        point *b;           /**< Point d'arrivée */
        int translate_x;    /**< Translation sur l'axe X */
        int translate_y;    /**< Translation sur l'axe Y */
        int rotate;         /**< Angle de rotation en degrés */
    } line_s;

    /**
     * @brief Structure représentant un cercle.
     */
    typedef struct circle_t {
        char *color;          /**< Couleur de remplissage */
        char *color_border;   /**< Couleur de la bordure */
        point *center;        /**< Point central du cercle */
        int radius;           /**< Rayon */
        int translate_x;      /**< Translation sur l'axe X */
        int translate_y;      /**< Translation sur l'axe Y */
        int rotate;           /**< Angle de rotation en degrés */
    } circle_s;

    /**
     * @brief Structure représentant une ellipse.
     */
    typedef struct ellipse_t {
        char *color;          /**< Couleur de remplissage */
        char *color_border;   /**< Couleur de la bordure */
        point *center;        /**< Point central de l'ellipse */
        int radius_x;         /**< Rayon horizontal */
        int radius_y;         /**< Rayon vertical */
        int translate_x;      /**< Translation sur l'axe X */
        int translate_y;      /**< Translation sur l'axe Y */
        int rotate;           /**< Angle de rotation en degrés */
    } ellipse_s;

    /**
     * @brief Structure représentant un carré.
     */
    typedef struct square_t {
        char *color;          /**< Couleur de remplissage */
        char *color_border;   /**< Couleur de la bordure */
        point *origin;        /**< Point d'origine (coin supérieur gauche) */
        int widht;            /**< Largeur / Longueur du côté */
        int translate_x;      /**< Translation sur l'axe X */
        int translate_y;      /**< Translation sur l'axe Y */
        int rotate;           /**< Angle de rotation en degrés */
    } square_s;

    /**
     * @brief Structure représentant un rectangle.
     */
    typedef struct rectangle_t {
        char *color;          /**< Couleur de remplissage */
        char *color_border;   /**< Couleur de la bordure */
        point *origin;        /**< Point d'origine (coin supérieur gauche) */
        int widht;            /**< Largeur */
        int height;           /**< Hauteur */
        int translate_x;      /**< Translation sur l'axe X */
        int translate_y;      /**< Translation sur l'axe Y */
        int rotate;           /**< Angle de rotation en degrés */
    } rectangle_s;
    
    /**
     * @brief Structure représentant une ligne multiple (polyline).
     */
    typedef struct multi_line_t {
        char *color;            /**< Couleur du trait */
        point_node_t *point_head; /**< Tête de la liste chaînée des points */
        int nb_points;          /**< Nombre total de points */
        int translate_x;        /**< Translation sur l'axe X */
        int translate_y;        /**< Translation sur l'axe Y */
        int rotate;             /**< Angle de rotation en degrés */
    } multi_line_s;

    /**
     * @brief Structure représentant un polygone.
     */
    typedef struct polygone_t {
        char *color;            /**< Couleur de remplissage */
        char *color_border;     /**< Couleur de la bordure */
        point_node_t *point_head; /**< Tête de la liste chaînée des sommets */
        int nb_points;          /**< Nombre total de sommets */
        int translate_x;        /**< Translation sur l'axe X */
        int translate_y;        /**< Translation sur l'axe Y */
        int rotate;             /**< Angle de rotation en degrés */
    } polygone_s;

    /**
     * @brief Structure représentant un chemin complexe (path).
     */
    typedef struct path_t {
        char *color;                  /**< Couleur de remplissage */
        char *color_border;           /**< Couleur de la bordure */
        path_command_node_t *commands_head; /**< Tête de la liste des commandes du path */
        int nb_commands;              /**< Nombre de commandes */
        int translate_x;              /**< Translation sur l'axe X */
        int translate_y;              /**< Translation sur l'axe Y */
        int rotate;                   /**< Angle de rotation en degrés */
    } path_s;

    // Déclaration anticipée pour passer la compilation croisée des groupes
    typedef struct node_t node_t; 

    /**
     * @brief Structure représentant un groupe de figures.
     */
    typedef struct group_t {
        node_t *children_head; /**< Sous-liste des figures contenues dans le groupe */
        int nb_children;       /**< Nombre de figures dans le groupe */
        int translate_x;       /**< Translation sur l'axe X */
        int translate_y;       /**< Translation sur l'axe Y */
        int rotate;            /**< Angle de rotation en degrés */
    } group_s;

    /**
     * @brief Union représentant n'importe quel type de figure géométrique.
     */
    typedef union figure_t {
        line_s *line;               /**< Pointeur vers une ligne */
        circle_s *circle;           /**< Pointeur vers un cercle */
        ellipse_s *ellipse;         /**< Pointeur vers une ellipse */
        square_s *square;           /**< Pointeur vers un carré */
        rectangle_s *rectangle;     /**< Pointeur vers un rectangle */
        multi_line_s *multi_line;   /**< Pointeur vers une multi-ligne */
        polygone_s *polygone;       /**< Pointeur vers un polygone */
        path_s *path;               /**< Pointeur vers un path */
        group_s *group;             /**< Pointeur vers un groupe */
    } figure;

    /**
     * @brief Élément de la liste chaînée globale de la scène.
     */
    typedef struct node_t {
        figure fig;            /**< La figure stockée */
        figure_type_t type;    /**< Le type de la figure */
        struct node_t *next;   /**< Pointeur vers le noeud suivant */
    } node_t;

    /**
     * @brief Structure globale de la scène contenant la liste des figures.
     */
    typedef struct {
        node_t *head;          /**< Premier élément de la liste chaînée de figures */
        int count;             /**< Nombre total de figures dans la scène */
    } Scene;

    // Déclaration de la scène globale
    extern Scene ma_scene;

    // --- Fonctions utilitaires communes ---

    char* add_color(void);
    void clear_stdin(void);
    int add_new_point(point *p);
    int add_int(void);
    void free_figure(node_t *current);
    void print_figure_to_html(FILE *file, node_t *current);

    // --- Fonctions principales des différents programmes ---

    int add_new_form(void);
    int edit_form(void);
    void save_scene_to_html(void);
    void free_scene(void);
    void save_project(void);

#endif