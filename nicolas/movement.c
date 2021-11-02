/*
 * Filename: movement.c
 * Created Date: Wednesday, October 20th 2021, 2:43:52 pm
 * Author: DEBRAS Nicolas 
 * 
 * Copyright (c) 2021 
 */

#include "malloc_world.h"


void movement(map m, map m1, map m2, map m3){

    char c;
    char input[255];
    int movement_tab[1];
    if (m.level > 1) {
            printf("toto");
            m.map[0][0] = player;
        }
    while (1) {
        print_map(m);
        scanf("%s", &input);

        c = input[0];

        //conditions 
        movement_tab[0] = 0;
        movement_tab[1] = 0;

        //mettre dans une focntion 
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
            printf("crash ou break, %s", input);
            break;
        }
        
        //mouvemant
        if (m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] == 0 ) {
            // faire une fonction
            m.map[m.player_x][m.player_y] = 0;
            m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] = player;
            m.player_x = m.player_x + movement_tab[0];
            m.player_y = m.player_y + movement_tab[1];
        } else if (m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] == Png) {
            printf("\n||||| RENCONCTRE AVEC LE PNG|||||\n");
            // focntion rencontre avec le png 
        } else if (m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] >= plant_zone1 && m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] <= tree_zone3) {
            printf("\n||||| RENCONCTRE AVEC UN ELEMENT UTILE |||||\n");
            //focntion element utile 
        } else if (m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] < -1) {
            printf("\n||||| CHANGEMENT DE MAP |||||\n");
            // faire une fonction changement map
            if (m.level == 1) {
                // mettre le player sur la seconde map (fonction : check autour de la zone du portail des zero afin de placer le player                     
                m2.player_x = 0;
                m2.player_y = 0;
                movement(m2, m1, m2, m3);
                break;
            } else if (m.map[m.player_x+movement_tab[0]][m.player_y+movement_tab[1]] == -1 ) {
                movement(m2, m1, m2, m3);
                break;

            }
        } else
            printf("\n||||| RENCONCTRE AVEC UN MONSTRE|||||\n");
            // fonction combat de monstre 
        
        //system("clear");
    }
    
}
