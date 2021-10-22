/*
 * Filename: movement_tab.c
 * Created Date: Wednesday, October 20th 2021, 2:43:52 pm
 * Author: DEBRAS Nicolas 
 * 
 * Copyright (c) 2021 
 */
#include "malloc_world.h"



void movement(map m){

    char c;
    int movement_tab[1];
    //printf("Ceci est un test ");

    printf("\nLe player se trouve a la cases : %d et %d\n", m.player_x, m.player_y); 
    
    while (1) {
        print_map(m);
        system("pause");
        scanf("\nVeuillez saisir un déplacement (z q d s) : ", &c);

        //conditions 
        if (c == 'z' && (m.player_x-1) >= 0 ) {
            movement_tab[0] = -1;
            movement_tab[1] = 0;
        }
        else if (c == 'q' && (m.player_y-1) >= 0) {
            movement_tab[0] = 0;
            movement_tab[1] = -1;
        }   
        else if (c == 'd' && (m.player_y+1) <= m.column ) {
            movement_tab[0] = 0;
            movement_tab[1] = 1;
        }
        else if (c == 's' && (m.player_x-1) <= m.rows ) {
            movement_tab[0] = 1;
            movement_tab[1] = 0;
        } else {
            printf("crash ou break");
            break;
        }
        
        //check
        if (m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] == 0 ) {
            m.map[m.player_x][m.player_y] = 0;
            m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] = 1;
        } else if (m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] == Png) {
            printf("\n||||| RENCONCTRE AVEC LE PNG|||||\n");
        } else if (m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] >= plant_zone1 && m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] <= tree_zone3) {
            printf("\n||||| RENCONCTRE AVEC UN ELEMENT UTILE|||||\n");
        } else
            printf("\n||||| RENCONCTRE AVEC UN MONSTRE|||||\n");
        
        system("clear");
    }
    
}
