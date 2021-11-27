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

int selected_choose(int c, Player *p, Object *chest)
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
       int c = correct_input_int();
    
        print_inventory(chest);
        //menu
        if (c == 1) {
           print_inventory(p->inventory);
           int id = input();
           Object **temp = addObjectToChest(p->inventory, chest, id);
           chest = temp[0];
           p->inventory = temp[1];

       } else if (c == 2) {
            print_inventory(p->inventory);
           int id = input();
           Object **temp = getObjectFromChest(chest, p->inventory, id);
           chest = temp[1];
           p->inventory = temp[0];

       } 
        return 0;
    }
    else if (c == 4) {
        return 1;
    }
    else
        return 42;
}

//fonction principal
void png_interaction(Player *p, Object *chest) {

    clear();
    read_print_png();
    while(1) {
        print_info();
        int c = correct_input_int_4();
        if (selected_choose(c, p, chest) == 1)
            break;
    }
    
}
