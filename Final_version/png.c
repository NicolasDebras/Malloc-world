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
    printf("3 : VOTRE COFFRE\n");
    printf("4 : QUITTER\n");
    printf("\n\n\n");
    printf("Veuillez saisir le numéro de votre choix ");

}
// a completer avec toutes les differents uppgrade possible
void print_menu_up_tool(Player *p) {

    printf("---- Menu Craft ---- \n\n\n");
    printf("***********************************************\n");
    printf("* Veuillez saisir l'id de l'élément a craft   *\n");
    printf("***********************************************\n");
    int c = input();
    p->inventory = craftObject(p->inventory, c);

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
void print_chest(Object *chest) {
    printf("- - - - - - - VOTRE COFFRE - - - - - - \n");
    printf("***************************************\n");
    printf("*         Options possibles           *\n");
    printf("*                                     *\n");
    printf("* 1 : Ajouter un objet dans le coffre *\n");
    printf("*                                     *\n");
    printf("* 2 : Retirer un objet du coffre      *\n");
    printf("*                                     *\n");
    printf("***************************************\n");
    printf("\n\nCOFFRE :\n");
    print_inventory(chest);
}

int selected_choose(int c, Player *p, Object *chest)
{
    if (c == 1) {
        print_menu_up_tool(p);
        return 0;
    } else if (c == 2) {
        repairAllObject(p->inventory);
        return 0;
    } else if (c == 3) {
        print_chest(chest);
        printf("\nINVENTAIRE :\n");
        print_inventory(p->inventory);
        int c = correct_input_int();
        if (c == 1) {
           printf("\n Saississez l'ID de l'objet a ajouter dans le coffre : ");
           int id = input();
           Object **temp = addObjectToChest(p->inventory, chest, id);
           chest = temp[0];
           p->inventory = temp[1];
       } else if (c == 2) {
           printf("\n Saississez l'ID de l'objet a retirer du coffre et a mettre dans l'inventaire : ");
           int id = input();
           Object **temp = getObjectFromChest(chest, p->inventory, id);
           chest = temp[1];
           p->inventory = temp[0];
       }
        printf("\nCOFFRE APRES CHANGEMENT :\n");
        print_chest(chest);
        printf("\nINVENTAIRE APRES CHANGEMENT :\n");
        print_inventory(p->inventory);
        return 0;
    } else if (c == 4) {
        return 1;
    } else
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
