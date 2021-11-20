/*
 * Filename: png.c
 * Created Date: Tuesday, November 2nd 2021, 6:29:43 pm
 * Author: Nicolas Debras
 * 
 * Copyright (c) 2021 
 */
#include "malloc_world.h"

//foncyion leacture et affiche du png en code ascii 
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

    printf("votre choix : \n");
    printf("1 : CRAFTER ELEMENTS\n");
    printf("2 : REPARATION\n");
    printf("3 : VOTRE BANQUE\n");
    printf("4 : QUITTER\n");
    printf("\n\n\n");
    printf("Veuillez saisir le numéro de votre choix ");

}
// a completer avec toutes les differents uppgrade possible
void print_menu_up_tool() {

    printf("votre choix : \n");
    printf("1 : CRAFTER ELEMENTS\n");
    printf("2 : REPARATION\n");
    printf("3 : VOTRE BANQUE\n");
    printf("4 : QUITTER\n");
    printf("\n\n\n");
    printf("Veuillez saisir le numéro de votre choix ");
    int c = atoi(input_char());
    // fonction de craft @soulte92

}

int selected_choose(int c)
{

    if (c == 1) {
        print_menu_up_tool();
        return 0;

    }
    else if (c == 2) {
        // fonction de reparation @soulte92
        return 0;
    }
    else if (c == 3) {
        //banque @soulte92 
        return 0;
    }
    else if (c == 4) {
        // banque @soulte92
        return 1;
    }
    else
        return 42;
}

//fonction principal
void png_interaction() {

    read_print_png();
    while(1) {
        print_info();
        int c = atoi(input_char());
        if (selected_choose(c) == 1)
            break;
    }
    
}
