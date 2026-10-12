#include "projet_svg.h"

int main(void){
    unsigned char a;
    printf("------------Projet C SVG------------\n");

    //interface utilisateur console
    while(1){
        printf("\nListe des option :\n");
        printf("=> 0 - Quittez\n");
        printf("=> 1 - Creer un nouveau projet\n");
        printf("=> 2 - Editer le projet courant\n");
        printf("=> 3 - Sauvegarder le projet\n");
        printf("=> 4 - Charger un projet\n");

        scanf("%c",&a);

        switch (a){
        case '0':
            return 0;
            break;
        case '1':
            return 0;
            break;
        case '2':
            return 0;
            break;
        case '3':
            return 0;
            break;
        case '4':
            return 0;
            break;
        
        default:
            printf("Commande invalide\n\n");
            break;
        }
    }
}