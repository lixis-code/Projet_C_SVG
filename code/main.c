/**
 * @file main.c
 * @author Vayssiere Alexis
 * @date 2026-10-12
 * @brief Point d'entrée principal pour le projet de manipulation de fichiers SVG.
 */
#include "projet_svg.h"
/**
 * @brief Fonction principale du programme (Point d'entrée).
 * @return int Retourne 0 si le programme s'arrête normalement (quitté par l'utilisateur).
 */
int main(void){
    unsigned char choice;
    printf("------------Projet C SVG------------\n");
    while(1){
        printf("\nListe des option :\n");
        printf("=> 0 - Quittez\n");
        printf("=> 1 - Creer un nouveau projet\n");
        printf("=> 2 - Editer le projet\n");
        printf("=> 3 - Sauvegarder le projet\n");
        printf("=> 4 - Charger un projet\n");
        printf("=> 5 - Visualiser le projet\n");
        scanf(" %c",&choice);
        clear_stdin();
        switch (choice){//gestion des choix
        case '0':
            free_scene();
            return 0;
            break;
        case '1':
            add_new_form();
            break;
        case '2':
            edit_form();
            break;
        case '3':
            printf("pas encore implementer\n");
            break;
        case '4':
            printf("pas encore implementer\n");
            break;
        case '5':
            save_scene_to_html();
            break;
        default:
            printf("\nCommande invalide\n");
            break;
        }
    }
}