/*
 * Filename: malloc_world.h
 * Created Date: Friday, October 22nd 2021, 2:01:58 pm
 * Author: Nicolas Debras
 * 
 * Copyright (c) 2021 
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



/* - struct monster - Nicolas Debras */

typedef struct monster{

    char name[50];
    int pv;
    int level_monster;
    int xp_profit;
    int n;
    int degats;
    int armor;
}monster;

/* - struct map - Nicolas Debras */

typedef struct{
    int rows;
    int column;
    int **map;
    int level;
    int player_x;
    int player_y;

}map;

/* - struct collected ressour - Nicolas Debras */

typedef struct{
    int type;
    int level;
    int pos_x;
    int pos_y;
    int repop_turn;

}ressource_collect;

/* - enum for fill map - Nicolas Debras */

#define MIN3 -3
#define MIN2 -2
#define MIN1 -1

enum {
    portail_zone2 = MIN3,
    portail_zone1 = MIN2,
    wall = MIN1,
    empty,
    player,
    Png,
    plant_zone1,
    rock_zone1,
    tree_zone1,
    plant_zone2,
    rock_zone2,
    tree_zone2,
    plant_zone3,
    rock_zone3,
    tree_zone3
};

/* - prototype map.c - Nicolas Debras */

void start_map(map *m, int level);
int **creation_map(int rows, int column);
void fill_map(int rows, int column, int **map);
void print_map(map m);
void initialization_map3(map m);
void initialization_map2(map m);
void initialization_map1(map m);
void check_fill(map m, int rajout);
int RangedRand(int range_min, int range_max);

/* - prototype movement.c - Nicolas Debras */

void movement(map m1, map m2, map m3);
void movement_player(map *m, int *movement_tab);
char input_char();

/* - prototype creation_monster.c - Nicolas Debras */

monster *creation_monster();
monster *init_monster(char name[50], int pv, int level_monster, int n, int degats, int armor);

/* - prototype png.c - Nicolas Debras */

void png_interaction();

/* - prototype png.c - Nicolas Debras */

ressource_collect *collect_ressources(int ressources, map *m, int pos_x, int pos_y, int turn, ressource_collect *old, int nb);
void check_repop_turn(ressource_collect *r, map *m1, map *m2, map *m3, int turn, int nb);