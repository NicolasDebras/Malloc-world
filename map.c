#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int rows;
    int column;
    int **map;
    int level;

}map;

int random(int max) {

    int n;

    srand(time(NULL));
    n = rand() % (max);

    return n;
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


    m->rows = random(10);
    m->column = random(10);
    printf("%d ", m->rows);
    printf("%d", m->column);


    m->level = level;
    m->map = creation_map(m->rows, m->column);
    fill_map(m->rows, m->column, m->map);
}

int main(void) {

    map map_zone1;
    map map_zone2;
    map map_zone3;

    start_map(&map_zone1, 1);
    print_map(map_zone1);
    
    return 0;
}