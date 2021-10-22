/*
 * Filename: movement.c
 * Created Date: Wednesday, October 20th 2021, 2:43:52 pm
 * Author: DEBRAS Nicolas 
 * 
 * Copyright (c) 2021 
 */
#include "malloc_world.h"

void find_player(map m, int *x, int *y) {

    for(*y = 0; *y != m.rows; *y++) 
        for(*x = 0; m.map[*y][*x] != 1 ; *x++)
}
int **check_input(char c) {

    int *movement = malloc(sizeof(int)*2)

    if (c == 'z' && (x-1) >= 0 ) {
            movement[0] = -1;
            movement[1] = 0;
        }
        else if (c == 'q' && (x-1) >= 0) {
            movement[0] = 0;
            movement[1] = -1;
        }
        else if (c == 'd' && (x-1) <= m.column ) {
            movement[0] = 0;
            movement[1] = 1;
        }
        else if (c == 's' && (x-1) <= m.rows   {
            movement[0] = 1;
            movement[1] = 0;
        }
    return movement;

}

void movement(map m){

    int x;
    int y;
    char c;
    int movement[1];

    check_fill(m, player);
    find_player(m, &x, &y);

    //test
    printf("\nNormalement doit etre égale a 1 : %d", m.map[y][x]); 
    
    while (true) {
        print_map(m);
        system("pause");
        scanf("\nVeuillez saisir un déplacement (z q d s) : ", &c);

        //conditions 
        if (c == 'z' && (x-1) >= 0 ) {
            movement[0] = -1;
            movement[1] = 0;
        }
        else if (c == 'q' && (x-1) >= 0) {
            movement[0] = 0;
            movement[1] = -1;
        }
        else if (c == 'd' && (x-1) <= m.column ) {
            movement[0] = 0;
            movement[1] = 1;
        }
        else if (c == 's' && (x-1) <= m.rows   {
            movement[0] = 1;
            movement[1] = 0;
        } else 
            break;
        
        //check
        if (m.map[x+movement[0]][y+movement[1]] == 0 ) {
            m.map[x][y] = 0;
            m.map[x+movement[0]][y+movement[1]] = 1;
        } else if (m.map[x+movement[0]][y+movement[1]] == Png) {
            printf("\n||||| RENCONCTRE AVEC LE PNG|||||\n");
        } else if (m.map[x+movement[0]][y+movement[1]] => plant_zone1 && m.map[x+movement[0]][y+movement[1]] =< tree_zone3) {
            printf("\n||||| RENCONCTRE AVEC UN ELEMENT UTILE|||||\n");
        } else
            printf("\n||||| RENCONCTRE AVEC UN MONSTRE|||||\n");
        
        system("clear");
    }
    
}
