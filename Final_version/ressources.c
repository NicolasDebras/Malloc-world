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
    new[nb].type = type;
    new[nb].pos_x = pos_x;
    new[nb].pos_y = pos_y;
    new[nb].repop_turn = repop_turn;

    return new;


}
void delete(ressource_collect *r, int nb){

    for (int i = 0; i != nb; i++) {
        r[i] = r[i+1];
    } 

}

void check_repop_turn(ressource_collect *r, map *m1, map *m2, map *m3, int turn, int nb){

    if (nb > 0) {
        if (r[0].repop_turn <= turn) {
            if (r[0].level == 1) {
                m1->map[r[0].pos_x][r[0].pos_y] = r[0].type;
                delete(r, nb);
            } else if (r[0].level == 2) {
                m2->map[r[0].pos_x][r[0].pos_y] = r[0].type;
                delete(r, nb);
            } else {
                m3->map[r[0].pos_x][r[0].pos_y] = r[0].type;
                delete(r, nb);
            }

        }
    }

}
int map_id_to_inv_id(int map_id){

    int tab[12];

    tab[3] = GRASS; 
    tab[4] = STONE; 
    tab[5] = FIR;

    tab[6] = LAVENDER; //p
    tab[7] = IRON; // r
    tab[8] = BEECH; //b

    tab[9] = HEMP;
    tab[10] = DIAMOND;
    tab[11] = OAK;

    return tab[map_id];


}

ressource_collect *collect_ressources(int ressources, map *m, int pos_x, int pos_y, int turn, ressource_collect *old, int nb, Player *p) {

    ressource_collect *new;


    printf("\n||||| RENCONCTRE AVEC UN ELEMENT UTILE |||||\n");

    if (m->level == 1) {
        new = add_element(old, nb, ressources, m->level, pos_x, pos_y, turn);
        // collectRessourceAndToolUpdate(p->inventory,map_id_to_inv_id(ressources),RangedRand(3,5),mapZone);
        collectCrafts(p->inventory, RangedRand(3, 5),map_id_to_inv_id(ressources));
        //fonction qui ajoute des ressources dans l'inventaire @soulte92
    } else if (m->level == 2 ) {
        new = add_element(old, nb, ressources, m->level, pos_x, pos_y, turn);
        // collectRessourceAndToolUpdate(p->inventory,map_id_to_inv_id(ressources),RangedRand(3,5),mapZone);
        collectCrafts(p->inventory, RangedRand(3, 5),map_id_to_inv_id(ressources));
        //fonction qui ajoute des ressources dans l'inventaire  @soulte92
    } else {
        new = add_element(old, nb, ressources, m->level, pos_x, pos_y, turn);
        // collectRessourceAndToolUpdate(p->inventory,map_id_to_inv_id(ressources),RangedRand(3,5),mapZone);
        collectCrafts(p->inventory, RangedRand(3, 5),map_id_to_inv_id(ressources));
        //fonction qui ajoute des ressources dans l'inventaire @soulte92
    }
    return new;

}