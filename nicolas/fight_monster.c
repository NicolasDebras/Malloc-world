/**
 * @file fight_monster.c
 * @author Nicolas Debras
 * @brief 
 * @version 0.1
 * @date 2021-11-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "malloc_world.h"

monster *init_fighter(monster *liste) {

}

void print_info(monster *m) {

    printf("Name  : %s", m->name);
    printf("pv : %d\n", m->pv);
    printf("degats : %d\n", m->degats);
    printf("armor : %d\n", m->armor);

}
void print_action() {

}

int battle_phase() {

    while(1) {

    }

}


int strat_fight(monster *liste) {

    monster *fight_monster = init_fighter(liste);
    return battle_phase();

}