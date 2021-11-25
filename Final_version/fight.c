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

monster *init_fighter(monster *liste, int nb, int n_fighter) {

    monster *m = malloc(sizeof(monster)); 

    int i = 0;

    while(i != nb) {
        if (liste[i].n == n_fighter)
            break;  
        i = i + 1;
    }
    //copie du nombre trouvé dans m

    return m;
}

void print_info(monster *m) {

    printf(" -- STATUT DU MONSTRE -- \n");
    printf("Name  : %s", m->name);
    printf("pv : %d\n", m->pv);
    printf("degats : %d\n", m->degats);
    printf("armor : %d\n", m->armor);

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
int input() {

    char input_char[0];

    int c = atoi(scanf("%s", input));

    return c;
    
}


int battle_phase(monster *m_fighter, int dodge, Player *p) {

    while(1) {
        if (m_fighter->pv == 0)
            return 1;
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
        printf("---- ATTAQUE DU JOUEUR ---- ");
        int c = atoi(input_str());

        while (c != 1 || c != 2 || c != 3)
        {
            c = input();
        }
        
        if (c == 1) {
            //changement d'arme 
            // j'ai décide que c'était punitif donc perte d'un tour de combat

            print_inventory(p->inventory);
            printf("Pour changer d'arme, veuillez saisir l'idée de l'arme : ");
            int d = input(); // le joueur input l'id de l'arme 
            selectWeapon(p->inventory); //Est ce qu'il return qqch d'utile @soulte92 ? et comment je décide de la bonne arme 
            
            /* selectObject(Object* inventory, int objectId);
                voilà le bon prototype, tu mets l'id de ton arme en question, et ça retourne l'inventaire à la fin.
                je pense que tu pourra ne pas faire un truc du genre p->inventory = selectObject...
                sinon, retourne null si le process échoue.
            */
        }
        else if (c == 2) {
            // J'ai rajouté des echeer critique (vive dofus), je trouvais ça drole mdrr

            
            if (RangedRand(0, 1000) != 42)
                attackMonster(p, m_fighter);
            else {
                printf("\n-- Echec critique --\n");
                printf("\n --- Le nombre vous chaarge ---\n");
                if (receiveDamage(p, m_fighter) == 0)
                    return 0;
                printf("\n\n ---- Vie du joueur = %d ---- \n", p->hp_current);
            }


        }
        else if (c == 3) {

            if (print_run_action(dodge, m_fighter) == 2)
                return 2;
        }

    }

}

int strat_fight(monster *liste, Declaration *d, int n_fighter, int level_map) {


    clear();
    monster *fighter_monster = init_fighter(liste, d->nb_monster, n_fighter);
    int dodge = 0;

    if (level_map == 1) {
        dodge = 10;
    } else if (level_map == 1) {
        dodge = 5;
    } else
        dodge = 2;


    return battle_phase(fighter_monster, dodge, d->p);

}