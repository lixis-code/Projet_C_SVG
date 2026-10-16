#include "projet_svg.h"

int main(void){
    unsigned char choice;

    printf("------------Projet C SVG------------\n");

    //interface utilisateur console
    while(1){
        printf("\nListe des option :\n");
        printf("=> 0 - Quittez\n");
        printf("=> 1 - Creer un nouveau projet\n");
        printf("=> 2 - Editer le projet\n");
        printf("=> 3 - Sauvegarder le projet\n");
        printf("=> 4 - Charger un projet\n");
        printf("=> 5 - Visualiser le projet\n");

        scanf(" %c",&choice);
        //vide le buffer d entrer
        clear_stdin();

        //gestion des choix
        switch (choice){
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