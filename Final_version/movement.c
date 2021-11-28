/*
 * Filename: movement.c
 * Created Date: Wednesday, October 20th 2021, 2:43:52 pm
 * Author: DEBRAS Nicolas 
 * 
 * Copyright (c) 2021 
 */

#include "malloc_world.h"

int print_menu_Affichages() {

    printf("-------------- AFFICHAGES  ------------- \n\n\n");
    printf("*****************************************\n");
    printf("*         Options possibles             *\n");
    printf("*                                       *\n");
    printf("* 1 : Afficher l'inventaire             *\n");
    printf("*                                       *\n");
    printf("* 2 : Affhicer les propriétés du joueur *\n");
    printf("*                                       *\n");
    printf("* 3 : Tables des références inventaires *\n");
    printf("* (option 3: indisponible)              *\n");
    printf("*****************************************\n");
    return correct_input_int();

}

void interation_menu_Affichage(Declaration *d){
    int validStatus = 1;
        int status;
        while (validStatus){
            status = print_menu_Affichages();
            if ( status==1 || status==2 || status==3 ){
                validStatus = 0;
            }
        }
        if ( status == 1 ){
            print_inventory(d->p->inventory);
        }
        else if ( status == 2){
            print_player(d->p);
        }
        else if ( status == 3){
            // Affichage de la table des référence
        }
}

int print_menu_fonctionnalites() {

    printf("--------- Fonctionniolatités  ---------- \n\n\n");
    printf("*****************************************\n");
    printf("*         Options possible              *\n");
    printf("*                                       *\n");
    printf("* 1 : Utiliser une potion               *\n");
    printf("*                                       *\n");
    printf("* 2 : Selectionner une arme             *\n");
    printf("*                                       *\n");
    printf("* 3 : Supprimer un objet                *\n");
    printf("*                                       *\n");
    printf("*****************************************\n");
    return correct_input_int();

}
void interation_menu_Fonctionnalites(Declaration *d){
    int validStatus = 1;
        int status;
        while (validStatus){
            status = print_menu_fonctionnalites();
            if ( status==1 || status==2 || status==3 ){
                validStatus = 0;
            }
        }
        if ( status == 1 ){
            printf("* Veuillez Saisir l'identifiant de votre potion *\n\n");
            int entre = input();
            while ( getDBObjectType(entre) != SOIN_TYPE ){
                printf("*Mauvaises saisi: saisissez l'identifiant d'une potion valide*\n\n");
                entre = input();
            }
            d->p = useHealPotion(d->p, entre);
        }
        else if ( status == 2){
            printf("* Veuillez Saisir l'identifiant de l'arme à selectionné *\n\n");
            int entre = input();
            while ( getDBObjectType(entre) != ARME_TYPE ){
                printf("*Mauvaises saisi: saisissez l'identifiant d'une arme valide*\n\n");
                entre = input();
            }
            selectObject(d->p->inventory, entre);
        }
        else if ( status == 3){
            printf("* Veuillez Saisir l'identifiant de l'objet à supprimé *\n\n");
            int entre = input();
            while ( getDBObjectType(entre) != SOIN_TYPE && getDBObjectType(entre) != ARME_TYPE &&
                    getDBObjectType(entre) != ARMURE_TYPE && getDBObjectType(entre) != RDC_TYPE &&
                    getDBObjectType(entre) != OUTIL_TYPE ){
                printf("*Mauvaises saisi: saisissez l'identifiant d'un objet valide*\n\n");
                entre = input();
            }
            d->p->inventory = deleteObject(d->p->inventory, entre);
        }
}

int movement_check(Declaration *d, map m, char c)
{
    int *movement_tab = d->movement_tab;
    movement_tab[0] = 0;
    movement_tab[1] = 0;

    if (c == 'z' && (m.player_x - 1) >= 0)
    {
        movement_tab[0] = -1;
        movement_tab[1] = 0;
    }
    else if (c == 'q' && (m.player_y - 1) >= 0)
    {
        movement_tab[0] = 0;
        movement_tab[1] = -1;
    }
    else if (c == 'd' && (m.player_y + 1) <= m.column)
    {
        movement_tab[0] = 0;
        movement_tab[1] = 1;
    }
    else if (c == 's' && (m.player_x - 1) <= m.rows)
    {
        movement_tab[0] = 1;
        movement_tab[1] = 0;
    }
    else if (c == 'p')
    {
        interation_menu_Affichage(d);
    }
    else if (c == 'i')
    {
        interation_menu_Fonctionnalites(d);
    }
    else if (c == 'v')
    {
        return 1;
    }
    return 0;
}
void movement_player(map *m, int *movement_tab){

    m->map[m->player_x][m->player_y] = 0;
    m->map[m->player_x + movement_tab[0]][m->player_y + movement_tab[1]] = player;
    m->player_x = m->player_x + movement_tab[0];
    m->player_y = m->player_y + movement_tab[1];

}

void find_portal(map *m, int portal){

    int x = 0;
    int y = 0;
    int check = 0;

    for(int i = 0; i != m->rows; i++) {
        for(int d = 0; d != m->column; d++) {
            if (m->map[i][d] == portal) {
                check = check + 1;
            } if (m->map[i][d] == 0 && check ==  1) {
                m->player_x = i;
                m->player_y = d;
                check = check + 1;
            }
        }
    }
    m->map[m->player_x][m->player_y] = player;
}
map *change_map(map *m, map *m1, map *m2, map *m3, int x, int y) {

    printf("\n||||| CHANGEMENT DE MAP |||||\n");

    if (m->level == 1)
    {
        find_portal(m2, m->map[x][y]);
        return m2;
    }
    else if (m->map[x][y] == -2 && m->level == 2) {
        return m1;
    } else if (m->map[x][y] == -3 && m->level == 2) {
        find_portal(m3, m->map[x][y]);
        return m3;
    } else 
        return m2;

}
char input_char() {

    char c;
    char input[255];

    scanf("%s", input);
    c = input[0];

    return c;
}

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}
Declaration *init_d() {
    
    Declaration *new = malloc(sizeof(Declaration));

    new->movement_tab = malloc(sizeof(int) * 2);
    new->nb = 0;
    new->n_tour = 0;
    new->p = init_player();
    new->chest = new_Object();
    new->chest = init_inventor();
    new->liste_monster = creation_monster();
    new->nb_monster = 8;

    return new;
}
char corect_input() {
    
    char c = input_char();

    if (c == 'z'|| c == 's' || c == 'd'|| c == 'q'|| c == 'v') {
        return c;
    } else {
        printf("mauvais input \n");
        c = corect_input();
    }
}

int print_menu_Debut_de_Jeu() {

    printf("---------- COMMENCER LE JEU --------- \n\n\n");
    printf("**************************************\n");
    printf("*         Option possible            *\n");
    printf("*                                    *\n");
    printf("* 1 : Nouveau jeux                   *\n");
    printf("*                                    *\n");
    printf("* 2 : Charger une partie             *\n");
    printf("*                                    *\n");
    printf("**************************************\n");
    return correct_input_int();

}

void movement(map m1, map m2, map m3) {

    map *m = malloc(sizeof(map));
    m = &m1;

    int validGameStatus = 1;
    int gameStartStatus;
    while (validGameStatus){
        gameStartStatus = print_menu_Debut_de_Jeu();
        if ( gameStartStatus==1 || gameStartStatus==2 ){
            validGameStatus = 0;
        }
        else{
            printf("**************************************\n");
            printf("* Mauvais choix d'option veuillez    *\n");
            printf("  retapez une option                 *\n");
            printf("**************************************\n");
        }
    }
    
    Declaration *d = init_d();
    if ( gameStartStatus == 2 ){
        extractFromSaveFile(d->p, d->chest, "Data_Bases/saveInventory.txt");
    }

    while (1) {
        print_map(*m);      
        if (movement_check(d, *m, corect_input()) == 1)
            break;
        
        d->x = m->player_x + d->movement_tab[0];
        d->y = m->player_y + d->movement_tab[1];

        if (m->map[d->x][d->y] == 0) {
            movement_player(m, d->movement_tab);
        } else if (m->map[d->x][d->y] == Png) {    
            png_interaction(d->p, d->chest);
        }
        else if (m->map[d->x][d->y] >= plant_zone1 && m->map[d->x][d->y] <= tree_zone3)
        {
            d->collect = collect_ressources(m->map[d->x][d->y], m, d->x, d->y, d->n_tour, d->collect, d->nb, d->p);
            movement_player(m, d->movement_tab);
            d->nb = d->nb + 1;
        } else if (m->map[d->x][d->y] < -1) {
            m = change_map(m,&m1,&m2,&m3, d->x, d->y);  
        } else if (m->map[d->x][d->y] >= 12 && m->map[d->x][d->y] <= 99) {
            d->n_fighter = m->map[d->x][d->y];
            if (strat_fight(d, m->level) == 0)
                break;
            movement_player(m, d->movement_tab);
        } else {
            printf("\n||||| RENCONCTRE AVEC UN MUR |||||\n");
        }
        check_repop_turn(d->collect, &m1, &m2, &m3, d->n_tour, d->nb);
        saveAllGameProperties(d->p, d->chest, "Data_Bases/saveInventory.txt");
        print_inventory(d->p->inventory);
        //clear();
        d->n_tour = d->n_tour + 1;
    }
}
