 
/*
*
*   Nicolas Debras - Malloc world
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN3 -3
#define MIN2 -2
#define MIN1 -1


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

int RangedRand(int range_min, int range_max) {
    
    //srand(time(NULL));
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

    check_fill(m, Png);;
    check_fill(m, portail_zone1);

    int c = RangedRand(3, 5);

    for(int i = 0; i != c; i++) {
        check_fill(m, rock_zone1);
        check_fill(m, tree_zone1);
        check_fill(m, plant_zone1);
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


    m->rows = RangedRand(5, 10);
    m->column = RangedRand(5, 10);
    printf("Ligne : %d\n", m->rows);
    printf("Colonne : %d\n", m->column);


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
    initialization_map1(map_zone1);
    print_map(map_zone1);
    
    return 0;
}
