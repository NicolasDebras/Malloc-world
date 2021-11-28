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

void print_info_monster (monster *m) {

    printf(" -- STATUT DU MONSTRE -- \n");
    printf("Name  : %s", m->name);
    printf("pv : %d\n", m->pv);
    printf("degats : %d\n", m->degats);
    printf("armor : %d\n", m->armor);

}

monster *init_fighter(monster *liste, int nb, int n_fighter) {

    monster *m = malloc(sizeof(monster)); 

    int i = 0;

    while(i != nb) {
        if (liste[i].n == n_fighter)
            break;  
        i = i + 1;
    }
    m->armor = liste[i].armor;
    m->level_monster = liste[i].level_monster;
    m->n = liste[i].n;
    strcpy(m->name, liste[i].name);
    m->pv = liste[i].pv;
    m->degats = liste[i].degats;
    m->xp_profit = liste[i].xp_profit;
    print_info_monster(m);

    return m;
}


int print_run_action(int dodge, monster *m_fighter) {

    printf("\n\n ---- Vous avez %d de chance de fuir %s ---- \n\n", dodge-1, m_fighter->name);
    if (RangedRand(0, 100) < dodge-1) {
        printf("\n\n ---- Vous avez reussi a fuir le monstre ---- \n\n");
        return 2;
    } else 
        printf("\n\n ---- Vous n'avez pas reussi a fuir le monstre ---- \n");
    return 0;

}
int print_fight_action(Player *p, monster *m_fighter) {

    if (RangedRand(0, 100) != 42)
        attackMonster(p, m_fighter);
    else {
        printf("\n-- Echec critique --\n");
        printf("\n --- Le nombre vous chaarge ---\n");
        if (receiveDamage(p, m_fighter) == 0)
            return 0;
        printf("\n\n ---- Vie du joueur = %d ---- \n", p->hp_current);
    }
    return 10;

}
int input() {

    char input_char[2];

    scanf("%s", input_char);

    int c = atoi(input_char);

    return c;
    
}
int correct_input_int() {

    int c = input();

    if (c == 1|| c == 2 || c == 3) {
        return c;
    } else {
        printf("mauvais input \n");
        c = correct_input_int();
    }
}
int print_menu_action() {

    printf("---------- ACTION DU JOUEUR --------- \n\n\n");
    printf("**************************************\n");
    printf("*         Action possible            *\n");
    printf("*                                    *\n");
    printf("* 1 : changement d'arme              *\n");
    printf("*                                    *\n");
    printf("* 2 : attaquer                       *\n");
    printf("*                                    *\n");
    printf("* 3 : fuir                           *\n");
    printf("**************************************\n");
    return correct_input_int();

}

int battle_phase(monster *m_fighter, int dodge, Player *p) {

    while(1) {
        if (m_fighter->pv == 0 && m_fighter->pv != 99)
            return 1;
        else if (m_fighter->pv == 0 && m_fighter->pv == 99)
            return 0;
        printf("---- ATTAQUE DU MONSTRE ---- ");
        printf("\n\n ---- Vous avez %d de chance d'esquiver l'attaque de %s ---- \n\n", dodge, m_fighter->name);
        if (RangedRand(0, 100) < dodge)
            printf("\n\n ---- Vous avez reussi a esquiver l'attaque du monstre ---- \n\n");
        else {
            if (receiveDamage(p, m_fighter) == 0)
                return 0;
            printf("\n\n ---- Vous n'avez pas reussi a esquiver l'attaque du monstre ---- \n");
            printf("\n\n ---- Vie du joueur = %d ---- \n", p->hp_current);
        }
        int c = print_menu_action();
        if (c == 1) {
            print_inventory(p->inventory);
            printf("Pour changer d'arme, veuillez saisir l'idée de l'arme : ");
            int d = input(); 
            selectObject(p->inventory, d);
        }
        else if (c == 2) {
            if(print_fight_action(p, m_fighter) == 1)
                return 1;
        } else if (c == 3) {
            if (print_run_action(dodge, m_fighter) == 2)
                return 2;
        }
    }
}

int strat_fight(Declaration *d, int level_map) {


    clear();
    monster *fighter_monster = init_fighter(d->liste_monster, d->nb_monster, d->n_fighter);
    int dodge = 0;

    if (level_map == 1) {
        dodge = 10;
    } else if (level_map == 1) {
        dodge = 5;
    } else
        dodge = 2;


    int res = battle_phase(fighter_monster, dodge, d->p);
    if (d->p->xp >= (d->p->level *100) ) {
        updatePlayerHpWithLevel(d->p);
        d->p->xp = 0;
    }
    return res;
}