#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printMap(int** map, int rows, int columns){

    for(int i = 0; i < rows; i++){
        for(int y = 0; y < columns; y++){
            printf("%d ",map[i][y]);
        }
        printf("\n");
    }
}

void saveMaps(int rows_1, int columns_1, int** map_1, int rows_2, int columns_2, int** map_2, int rows_3, int columns_3, int** map_3){
    FILE* map_file = fopen("save_files/save_map.txt","w");
    if(map_file != NULL){ //check if file is open
        fprintf(map_file,"=== MAP ===\n");
        fprintf(map_file,"-- ZONE 1 --\n");
        for(int i = 0; i < rows_1; i++){
            for(int y = 0; y < columns_1; y++) fprintf(map_file,"%d ",map_1[i][y]);
            fprintf(map_file,"\n"); //add each placement of map1
        }

        fprintf(map_file,"-- ZONE 2 --\n");
        for(int i = 0; i < rows_2; i++){
            for(int y = 0; y < columns_2; y++) fprintf(map_file,"%d ",map_2[i][y]);
            fprintf(map_file,"\n"); //add each placement of map2
        }

        fprintf(map_file,"-- ZONE 3 --\n");
        for(int i = 0; i < rows_3; i++){
            for(int y = 0; y < columns_3; y++) fprintf(map_file,"%d ",map_3[i][y]);
            fprintf(map_file,"\n"); //add each placement of map3
        }

        fclose(map_file);
        //printf("Niquel !");
    }
    else printf("Erreur à l'ouverture du fichier");
}

int** createMap(int rows,int columns){

    int** map = malloc(sizeof(int**)*rows);
    for(int i = 0; i < rows; i++) map[i] = malloc(sizeof(int*)*columns);

    for(int i = 0; i < rows; i++){
        for(int y = 0; y < columns; y++){
            map[i][y] = 0;
        }
    }
    //printMap(map,rows, columns);
    //printf("\n- - - - - - -\n\n");
    return map;
}

int** getMapFromSaveFile(int map_index){
    int** map = 0;
    char c;
    int count = 0;
    int zone_2_indicator = 0;
    int zone_3_indicator = 0;
    char* map_string1 = "";
    int can_print = 0;
    char *all_strings = malloc(sizeof(char) * 1000);
    FILE* map_file = fopen("save_files/save_map.txt","r");

    if(map_file != NULL){

        while((c=fgetc(map_file))!=EOF){
            all_strings[count] = c;
            //printf("%c",all_strings[count]);
            count++;
        }

        for(int i = 0; i < count; i++){
            if(can_print == 1){
                if(all_strings[i] == '\n' && all_strings[i+1] == '-' && all_strings[i+2] == '-' && all_strings[i-1] != '='){
                    if(zone_2_indicator == 1 && zone_3_indicator == 0) zone_3_indicator = 1;
                    if(zone_2_indicator == 0) zone_2_indicator = 1;
                }
                if(all_strings[i] != ' '){
                    if(zone_2_indicator == 0 && zone_3_indicator == 0){
                        if(all_strings[i] == '\n') map_string1 = strncat(map_string1,"|.|",3);
                        else map_string1 = strncat(map_string1,&all_strings[i],1);
                    }
                    else if(zone_2_indicator == 1 && zone_3_indicator == 0){
                        if(all_strings[i] == '\n') map_string1 = strncat(map_string1,"|..|",4);
                        else map_string1 = strncat(map_string1,&all_strings[i],1);
                    }
                    else if(zone_2_indicator == 1 && zone_3_indicator == 1){
                        if(all_strings[i] == '\n') map_string1 = strncat(map_string1,"|...|",5);
                        else map_string1 = strncat(map_string1,&all_strings[i],1);
                    }

                }
                else{
                    map_string1 = strncat(map_string1,"|",1);
                }
            }
            if(all_strings[i] == '\n' && all_strings[i-1] == '-') can_print = 1;
            if(all_strings[i] == '\n' && all_strings[i+1] == '-' && all_strings[i+2] == '-' && all_strings[i-1] != '=') can_print = 0;
        }

        printf("%s",map_string1);
        if(map_index == 1) {
            int increment = 0;
            int power = 1;
            int rows = 1;
            int columns = 0;
            int find_columns = 0;
            while (map_string1[increment] != '.' || map_string1[increment + 1] != '.') {
                int current_number = 0;
                if (map_string1[increment] != '.') {
                    while (map_string1[increment] != '|') {
                        if (map_string1[increment] == '-') {
                            increment++;
                        }
                        increment++;
                    }
                    find_columns++;
                } else {
                    rows++;
                    if (columns == 0) columns = find_columns;
                }
                increment++;
            }

            //printf("\nIl y a %d colonnes et %d lignes",columns,rows);

            int **map_1 = createMap(rows, columns);

            increment = 0;
            power = 1;
            rows = 0;
            columns = -1;
            int negative = 1;
            while (map_string1[increment] != '.' || map_string1[increment + 1] != '.') {
                int current_number = 0;
                if (map_string1[increment] != '.') {
                    while (map_string1[increment] != '|') {
                        if (map_string1[increment] == '-') {
                            increment++;
                            negative = -1;
                        }
                        int current_caracter_to_int = map_string1[increment] - '0';
                        printf("\nDEBUG -> Chiffre : %d", current_caracter_to_int);
                        current_number *= power;
                        current_number += current_caracter_to_int;
                        printf("\nDEBUG -> Current number : %d\n", current_number);
                        power *= 10;
                        increment++;
                    }
                    columns++;
                } else {
                    rows++;
                    columns = -1;
                    current_number = -999;
                    increment++;
                }
                current_number *= negative;
                printf("\nColonne : [%d] Ligne : [%d]\n", columns, rows);

                if (columns != -1) map_1[rows][columns] = current_number;
                power = 1;
                negative = 1;
                increment++;
            }

            printMap(map_1, rows + 1, columns + 1);
        }
        else if(map_index == 2){
            int increment = 0;
            int power = 1;
            int rows = 1;
            int columns = 0;
            int find_columns = 0;
            int use_zone_2 = 0;
            int array_index = 0;
            while (!(map_string1[increment] == '.' && map_string1[increment+1] == '.' && map_string1[increment+2] == '.')) {
                int current_number = 0;
                if(use_zone_2 == 1){
                    if (map_string1[increment] != '.') {
                        while (map_string1[increment] != '|') {
                            if (map_string1[increment] == '-') {
                                increment++;
                            }
                            increment++;
                        }
                        find_columns++;
                    } else {
                        rows++;
                        //printf("\nLigne +1 = %d, value_index = %d",rows,increment);
                        increment++;
                        if (columns == 0) columns = find_columns;
                    }
                }
                else if (map_string1[increment] == '.' && map_string1[increment + 1] == '.'){
                    use_zone_2 = 1;
                    increment++;
                }
                increment++;
            }
            columns--;
            printf("\nIl y a %d colonnes et %d lignes",columns,rows);
            int **map_1 = createMap(rows, columns);
            int map_rows = rows;
            int map_columns = columns;
            increment = 0;
            power = 1;
            rows = 0;
            columns = 0;
            int negative = 1;
            int tab_index = 0;
            use_zone_2 = 0;
            while (map_string1[increment] != '.' || map_string1[increment + 1] != '.' || map_string1[increment + 2] != '.') {
                int current_number = 0;
                if(use_zone_2 == 1) {
                    if (map_string1[increment] != '.') {
                        while (map_string1[increment] != '|') {
                            if (map_string1[increment] == '-') {
                                increment++;
                                negative = -1;
                            }
                            int current_caracter_to_int = map_string1[increment] - '0';
                            printf("\nDEBUG -> Chiffre : %d", current_caracter_to_int);
                            current_number *= power;
                            current_number += current_caracter_to_int;
                            power *= 10;
                            increment++;
                        }
                        columns++;
                    } else {
                        rows++;
                        columns = -1;
                        current_number = -999;
                        increment++;
                    }
                    current_number *= negative;
                    printf("\nColonne : [%d] Ligne : [%d]\n", columns, rows-1);
                    if (columns != -1 && rows < map_rows-1 && columns < map_columns){
                        map_1[rows-1][columns] = current_number;
                        printf("\nDEBUG -> Current number : %d\n", current_number);
                    }
                }
                if (map_string1[increment] == '.' && map_string1[increment + 1] == '.') use_zone_2 = 1;
                power = 1;
                negative = 1;
                increment++;
            }

            printMap(map_1, map_rows, map_columns);
        }
        fclose(map_file);
    }
    else printf("Erreur à l'ouverture du fichier");

    return map;
}



int main() {
    int rows_1 = 3;
    int columns_1 = 3;
    int rows_2 = 4;
    int columns_2 = 7;
    int rows_3 = 7;
    int columns_3 = 4;

    int** map_test = getMapFromSaveFile(2);

    int** map_1 = createMap(rows_1,columns_1);
    int** map_2 = createMap(rows_2,columns_2);
    int** map_3 = createMap(rows_3,columns_3);

    //saveMaps(rows_1,columns_1,map_1,rows_2,columns_2,map_2,rows_3,columns_3,map_3);

    return 0;
}
