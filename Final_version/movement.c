/*
 * Filename: movement.c
 * Created Date: Wednesday, October 20th 2021, 2:43:52 pm
 * Author: DEBRAS Nicolas 
 * 
 * Copyright (c) 2021 
 */

#include "malloc_world.h"

void movement_check(int *movement_tab, map m, char c)
{
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

    return new;
}

void movement(map m1, map m2, map m3) {

    map *m = malloc(sizeof(map));
    m = &m1;
    Declaration *d = init_d();


    while (1) {
        print_map(*m);      
        movement_check(d->movement_tab, *m, input_char());
        
        d->x = m->player_x + d->movement_tab[0];
        d->y = m->player_y + d->movement_tab[1];

        if (m->map[d->x][d->y] == 0) {
            movement_player(m, d->movement_tab);
        } else if (m->map[d->x][d->y] == Png) {    
            png_interaction();
        }
        else if (m->map[d->x][d->y] >= plant_zone1 && m->map[d->x][d->y] <= tree_zone3)
        {
            d->collect = collect_ressources(m->map[d->x][d->y], m, d->x, d->y, d->n_tour, d->collect, d->nb, d->p);
            movement_player(m, d->movement_tab);
            d->nb = d->nb + 1;
        } else if (m->map[d->x][d->y] < -1) {
            m = change_map(m,&m1,&m2,&m3, d->x, d->y);  
        } else
            printf("\n||||| RENCONCTRE AVEC UN MONSTRE|||||\n");
        check_repop_turn(d->collect, &m1, &m2, &m3, d->n_tour, d->nb);
        saveAllGameProperties(d->p, d->chest, "Data_Bases/saveInventory.txt");
        print_inventory(d->p->inventory);
        //clear();
        d->n_tour = d->n_tour + 1;
    }
}
