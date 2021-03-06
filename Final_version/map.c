/*
 * Filename: map.c
 * Created Date: Sunday, October 17th 2021, 9:47:55 pm
 * Author: Nicolas Debras
 * 
 * Copyright (c) 2021 
 */


#include "malloc_world.h"




int RangedRand(int range_min, int range_max) {
    
    int nombre = 0; 
    nombre = (rand() % (range_max + 1 - range_min)) + range_min;
    return nombre;
    
}

void check_fill(map m, int rajout) {


    int c = RangedRand(0, m.column-1);
    int r = RangedRand(0, m.rows-1);

    if (m.map[r][c] != 0)
        check_fill(m, rajout);
    else
        m.map[r][c] = rajout;
}
void initialization_map1(map m) {

    m.map[m.player_x][m.player_y] = 1;
    check_fill(m, Png);;
    check_fill(m, portail_zone1);

    int c = RangedRand(3, 5);

    for(int i = 0; i != c; i++) {
        check_fill(m, rock_zone1);
        check_fill(m, tree_zone1);
        check_fill(m, plant_zone1);
        check_fill(m, 12);
        check_fill(m, 13);
        check_fill(m, 14);
    }
}
void initialization_map2(map m) {

    check_fill(m, Png);
    check_fill(m, portail_zone1);
    check_fill(m, portail_zone2);

    int c = RangedRand(3, 5);

    for(int i = 0; i != c; i++) {
        check_fill(m, rock_zone2);
        check_fill(m, tree_zone2);
        check_fill(m, plant_zone2);
        check_fill(m, 15);
        check_fill(m, 16);
        check_fill(m, 17);
    }   

}
void initialization_map3(map m) {

    check_fill(m, Png);
    check_fill(m, portail_zone2);

    int c = RangedRand(3, 5);

    for(int i = 0; i != c; i++) {
        check_fill(m, rock_zone3);
        check_fill(m, tree_zone3);
        check_fill(m, plant_zone3);
        check_fill(m, 18);
        check_fill(m, 19);
        check_fill(m, 20);
        check_fill(m, 21);
        check_fill(m, 99);
    }   

}
void print_map(map m) {

    
    printf("=== MAP LEVEL %d ===\n", m.level);
    for(int i = 0; i != m.rows; i++) {
        for(int d = 0; d != m.column; d++) {
            printf("%d ", m.map[i][d]);
        }
        printf("\n");
    }   
}
void fill_map(int rows, int column, int **map) {

    for(int i = 0; i != rows; i++) {
        for(int d = 0; d != column; d++) {
            map[i][d] = 0;
        }
    }

}
int **creation_map(int rows, int column) {

    int **map = malloc(sizeof(int*)*rows);

    for (int i = 0; i != rows; i++) {
        map[i] = malloc(sizeof(int)*column);
    }

    return map;

}
void start_map(map *m, int level) {

    m->rows = RangedRand(6, 12);
    m->column = RangedRand(6, 12);
    m->player_y = RangedRand(0, m->rows-2);
    m->player_x = RangedRand(0, m->column-1);


    m->level = level;
    m->map = creation_map(m->rows, m->column);
    fill_map(m->rows, m->column, m->map);
}

int main(int argc, char *argv[]) {

    map map_zone1;
    map map_zone2;
    map map_zone3;

    srand(time(NULL));

    start_map(&map_zone1, 1);
    start_map(&map_zone2, 2);
    start_map(&map_zone3, 3);
    initialization_map1(map_zone1);
    initialization_map2(map_zone2);
    initialization_map3(map_zone3);
    movement(map_zone1, map_zone2, map_zone3);
    
    return 0;
}
