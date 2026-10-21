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
        printf("=> 1 - Ajouter des formes\n");
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
            save_project();
            break;
        case '4':
            free_scene();
            load_project();
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
/*
*   liste des modification a apporter : 
*   1- ajouter des system("clear") avant chaque affichage pour un meilleur rendu + styliser l affichage
*   2- ajouter une option "nouveau projet" qui vide la memoire et demande si l utilisateur veut sauvegarder le projet courant si il a ete modifier depuis sa derniere sauvegarde
*   3- ajouter une verif de sauvegarde pour que si elle est corompu, elle le signale et retourne une forme NULL
*   4- ajouter la possibiliter d inverser celon l axe x et y (miroire) pour les path et les groupes
*   5- faire de l optimisation (et se renseigner au prealable sur les meilleur pratique)
*/