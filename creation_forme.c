#include "projet_svg.h"


int add_new_form(void){
    unsigned char choice;
    bool boucle = true;

    //ouvre le fichier htlm, le créer si il n'existe pas
    FILE *file = fopen("index.htlm", "w");
    fprintf(file, "<svg viewBox=\"0 0 100 100\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    if(file==NULL){
        printf("Une erreur est survenu lors du chargement du fichier");
        return 0;
    }
    //creation des forme dans le fichier
    while(boucle){
        printf("\nChoix des formes :\n");
        printf("=> 0 - Quittez\n");
        printf("=> 1 - Ligne\n");
        printf("=> 2 - Cercle\n");
        scanf(" %c",&choice);
        switch (choice){
        case '0':
            boucle=false;
            break;
        case '1':
            //code de creation des forme
            break;
        case '2':
            //code de creation des forme
            break;
        default:
            printf("Option invalide\n");
            break;
        }
    }
    //fermeture du fichier
    fprintf(file, "</svg>");
    fclose(file);
    return 0;
}