#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN3 -3
#define MIN2 -2
#define MIN1 -1

typedef struct monster{

    char name[50];
    int pv;
    int level_monster;
    int xp_profit;
    int n;
    int degats;
    int armor;
}monster;

typedef struct{
    int rows;
    int column;
    int **map;
    int level;

}map;
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
    tree_zone3};

void creation_monster();
monster *init_monster(char name[50], int pv, int level_monster, int n, int degats, int armor);