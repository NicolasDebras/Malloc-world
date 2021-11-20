/*
 * Filename: ressources.c
 * Created Date: Tuesday, November 5nd 2021, 10:02:43 pm
 * Author: Nicolas Debras
 * 
 * Copyright (c) 2021 
 */

#include "malloc_world.h"


/* - Add new element to tab when player collect new resssources -- Nicolas Debras - */

ressource_collect *add_element(ressource_collect *old, int nb, int type, int level, int pos_x, int pos_y, int repop_turn) {

    ressource_collect *new = malloc(sizeof(ressource_collect*)* (255)); // 255 a changer... 


    for (int i = 0; i != nb; i++) {
        new[i] = old[i];
    }
    new[nb].level = level;
    new[nb].type = pos_x;
    new[nb].pos_x = pos_y;
    new[nb].pos_y = pos_y;
    new[nb].repop_turn = repop_turn;

    return new;


}

ressource_collect *collect_ressources(int ressources, map *m, int pos_x, int pos_y, int turn, ressource_collect *old, int nb) {

    ressource_collect *new;
    int movement_tab[1];

    movement_tab[0] = pos_x;
    movement_tab[1] = pos_y;

    printf("\n||||| RENCONCTRE AVEC UN ELEMENT UTILE |||||\n");

    if (m->level == 1) {
        new = add_element(old, nb, ressources, m->level, pos_x, pos_y, turn+10);
        movement_player(m, movement_tab);
        printf("ceci est un essai : %d\n" , new[nb].repop_turn);
        //fonction qui ajoute des ressources dans l'inventaire
    } else if (m->level == 2 ) {
        new = add_element(old, nb, ressources, m->level, pos_x, pos_y, turn+10);
        movement_player(m, movement_tab);
        printf("ceci est un essai : %d\n" , new[nb].repop_turn);
        //fonction qui ajoute des ressources dans l'inventaire
    } else {
        new = add_element(old, nb, ressources, m->level, pos_x, pos_y, turn+10);
        movement_player(m, movement_tab);
        printf("ceci est un essai : %d\n" , new[nb].repop_turn);
        //fonction qui ajoute des ressources dans l'inventaire
    }
    return new;

}