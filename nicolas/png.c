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

    printf("votre choix : \n-1 :  \n-2 \n-3\n");

}

//fonction principal
void png_interaction() {

    read_print_png();
    print_info();
    
}
