/*
 * Filename: png.c
 * Created Date: Tuesday, November 2nd 2021, 6:29:43 pm
 * Author: Nicolas Debras
 * 
 * Copyright (c) 2021 
 */
#include "malloc_world.h"

//fonction leacture et affiche du png en code ascii 
void read_print_png() {

    printf("\n||||| RENCONCTRE AVEC LE PNG|||||\n");

    FILE* fichier = NULL;
    char chaine[255] = "";
 
    fichier = fopen("file/marchant.txt", "r");
 
    if (fichier != NULL) {
        while (fgets(chaine, 255, fichier) != NULL) {
            printf("%s", chaine); 
        }
        fclose(fichier);
    }
}

// fonction qui affiche les diff info et option dispo avec le png
void print_info() {

    printf("\nVotre choix : \n");
    printf("1 : CRAFTER ELEMENTS\n");
    printf("2 : REPARATION\n");
    printf("3 : VOTRE BANQUE\n");
    printf("4 : QUITTER\n");
    printf("\n\n\n");
    printf("Veuillez saisir le numéro de votre choix ");

}
// a completer avec toutes les differents uppgrade possible
void print_menu_up_tool(Player *p) {

    printf("\nMENU CRAFT : \n");
    printf("1 : CRAFTER ELEMENTS\n");
    printf("2 : REPARATION\n");
    printf("3 : VOTRE BANQUE\n");
    printf("4 : QUITTER\n");
    printf("\n\n\n");
    printf("Veuillez saisir le numéro de votre choix ");
    int c = input();
    p->inventory = craftObject(p->inventory, c);
    // fonction de craft @soulte92 

    /*
        Object* craftObject(Object* inventory, int objectId)
        retourne l'inventaire
    */

}
int correct_input_int_4() {

    int c = input();

    if (c == 1|| c == 2 || c == 3 || c == 4) {
        return c;
    } else {
        printf("mauvais input \n");
        c = correct_input_int_4();
    }
}

int selected_choose(int c, Player *p)
{
    printf("%d", c);
    if (c == 1) {
        print_menu_up_tool(p);
        return 0;

    }
    else if (c == 2) {
        repairAllObject(p->inventory);
        return 0;
    }
    else if (c == 3) {
        //banque @soulte92 

        /*
        Stokage: 
            option1 récupération du coffre:
            Object** getObjectFromChest(Object* chest, Object* inventory, int objectId)
            Attention: Retourne un tableau de liste d'object taille 2
            result (ici notre tableau de retour):
                result[0] = inventory;
                result[1] = chest;
            il faudra bien réaffecter respective l'invetory et le chest
            !!! Faire attention, ce ne sont pas les indices et valeurs de retour !!!!
            option2 Déposer dans le coffre:
            Object** addObjectToChest(Object* inventory,Object* chest, int objectId)
            Attention: Retourne un tableau de liste d'object taille 2
            result (ici notre tableau de retour):
                result[0] = chest;
                result[1] = inventory;
            il faudra bien réaffecter respective l'invetory et le chest
        */
        return 0;
    }
    else if (c == 4) {
        return 1;
    }
    else
        return 42;
}

//fonction principal
void png_interaction(Player *p) {

    clear();
    read_print_png();
    while(1) {
        print_info();
        int c = correct_input_int_4();
        if (selected_choose(c, p) == 1)
            break;
    }
    
}
