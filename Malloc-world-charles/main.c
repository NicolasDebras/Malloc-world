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

char* getAllCaractersFromFile(char* all_caracters,int count, FILE* map_file){
    ///This function should :
    /// - get all caracters from "map_file"
    /// - put it in "all_caracters"
    /// - change "count" to match the number of caracters outside the function
    /// - return "all_caracters"
    return all_caracters;
}

char* getOneMapInAString(char* map_string, int map_index, char* all_caracters, int count){
    ///This function should :
    /// - check where are the caracters that we want with "map_index" from "all_caracters"
    /// - put them in "map" to prepare the map shape like that : 7/8/0/./5/65/-7/./0/0/3 ( "|" -> new column and "." -> new row)
    /// - return the string "map"

    ///Create a special string to separate every map and put it in the string (ex: 5|4|0|.|4|3|3|.|2|9|8)

    int zone_2_indicator = 0;
    int zone_3_indicator = 0;
    int can_print = 0;
    int first_line_debug = 0;

    for(int i = 0; i < count; i++){
        if(can_print == 1){
            if(all_caracters[i] == '\n' && all_caracters[i + 1] == '-' && all_caracters[i + 2] == '-' && all_caracters[i - 1] != '='){
                if(zone_2_indicator == 1 && zone_3_indicator == 0) zone_3_indicator = 1;
                if(zone_2_indicator == 0) zone_2_indicator = 1;
            }
            if(all_caracters[i] != ' '){
                if(zone_2_indicator == 0 && zone_3_indicator == 0){
                    if(map_index == 1){
                        if(all_caracters[i] == '\n') map_string = strncat(map_string, "|.|", 3);
                        else map_string = strncat(map_string, &all_caracters[i], 1);
                    }
                }
                else if(zone_2_indicator == 1 && zone_3_indicator == 0){
                    if(map_index == 2) {
                        if (all_caracters[i] == '\n' && first_line_debug == 1) map_string = strncat(map_string, "|.|", 3);
                        else map_string = strncat(map_string, &all_caracters[i], 1);
                        first_line_debug = 1;
                    }
                }
                else if(zone_2_indicator == 1 && zone_3_indicator == 1){
                    if(map_index == 3) {
                        if (all_caracters[i] == '\n' && first_line_debug == 1) map_string = strncat(map_string, "|.|", 3);
                        else map_string = strncat(map_string, &all_caracters[i], 1);
                        first_line_debug = 1;
                    }
                }

            }
            else{
                if(zone_2_indicator == 0 && zone_3_indicator == 0 && map_index == 1) map_string = strncat(map_string,"|",1);
                else if(zone_2_indicator == 1 && zone_3_indicator == 0 && map_index == 2) map_string = strncat(map_string,"|",1);
                else if(zone_2_indicator == 1 && zone_3_indicator == 1 && map_index == 3) map_string = strncat(map_string,"|",1);
            }
        }
        if(all_caracters[i] == '\n' && all_caracters[i - 1] == '-') can_print = 1;
        if(all_caracters[i] == '\n' && all_caracters[i + 1] == '-' && all_caracters[i + 2] == '-' && all_caracters[i - 1] != '=') can_print = 0;
    }
    strncat(map_string,"\0",1);
    if (map_string[0] == '\n') map_string++;
    //printf("\nPremier Character : [%c]",map_string1[0]);
    printf("\nMAP : %s",map_string);
    if(map_index == 3){
        map_string[strlen(map_string)-3] = '\0';
        //printf("\nMAP : %s",map_string1);
    }

    return map_string;
}

int* getRowsAndColumns(char* map_string, int rows, int columns, int size){
    int* rows_and_columns = malloc(sizeof(int)*2);

    int increment = 0;
    int power = 1;
    int find_columns = 0;
    //printf("\nSize : %d",size);

    ///This function should :
    /// - check how much rows there is in the "map"
    /// - check how much columns there is in the "map"
    /// - put it in "rows_and_columns"
    /// - return "rows_and_columns"

    ///Get the number of rows and columns of the map
    while (increment < size){
        if (map_string[increment] != '.') {
            while (map_string[increment] != '|') {
                if (map_string[increment] == '-') {
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

    rows_and_columns[0] = rows;
    rows_and_columns[1] = columns;

    return rows_and_columns;
}

int** fillMap(char* map_string, int rows, int columns, int size, int map_index){

    ///This function should :
    /// - get every number from "map_string"
    /// - put the numbers we got in each index of "map"
    /// - return "map"

    int **map = createMap(rows, columns);
    int get_columns = columns;
    int get_rows = rows;
    int increment = 0;
    int power = 1;
    rows = 0;
    columns = -1;
    int negative = 1;
    int while_condition = 0;

    ///Put every number in an empty map
    while (map_string[increment+1] != '\0' || map_string[increment] != '\0'){
        int current_number = 0;
        if (map_string[increment] != '.') {
            while (map_string[increment] != '|' && increment<size-1) {
                //printf("\n**HERE** %d",increment);
                if (map_string[increment] == '-') {
                    increment++;
                    negative = -1;
                }
                int current_caracter_to_int = map_string[increment] - '0';
                //printf("\nDEBUG -> Chiffre : %d * power[%d]", current_caracter_to_int,power);
                current_number *= power;
                current_number += current_caracter_to_int;
                //printf("\nDEBUG -> Current number : %d\n", current_number);
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
        //printf("\nColonne : [%d] Ligne : [%d]\n", columns, rows);
        if (columns != -1 && columns < get_columns) map[rows][columns] = current_number;
        power = 1;
        negative = 1;
        increment++;
        //if(map_string1[increment] != '|' && map_string1[increment + 1] != '\0') while_condition = 1;
    }
    printf("\nMAP %d :\n",map_index);
    printMap(map, rows + 1, get_columns);

    return map;
}

int** getMapFromSaveFile(int map_index){
    int** map = 0;
    char c;
    int count = 0;
    int zone_2_indicator = 0;
    int zone_3_indicator = 0;
    int can_print = 0;
    int first_line_debug = 0;
    char *all_caracters = malloc(sizeof(char) * 1000);
    FILE* map_file = fopen("save_files/save_map.txt","r");

    if(map_file != NULL){
        char* map_string1 = "";
        ///Get all the characters of the file one by one
        while((c=fgetc(map_file))!=EOF){
            all_caracters[count] = c;
            //printf("%c",all_caracters[count]);
            count++;
        }

        map_string1 = getOneMapInAString(map_string1, map_index, all_caracters, count);

        int increment = 0;
        int power = 1;
        int rows = 1;
        int columns = 0;
        int find_columns = 0;
        int size = strlen(map_string1);
        //printf("\nSize : %d",size);

        int* rows_and_columns = getRowsAndColumns(map_string1,rows,columns,size);
        rows = rows_and_columns[0];
        columns = rows_and_columns[1];

        //printf("\nIl y a %d colonnes et %d lignes",columns,rows);

        map = fillMap(map_string1,rows,columns, size, map_index);
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

    int** get_map_1 = getMapFromSaveFile(1);
    //int** get_map_2 = getMapFromSaveFile(2);
    //int** get_map_3 = getMapFromSaveFile(3);

    int** map_1 = createMap(rows_1,columns_1);
    int** map_2 = createMap(rows_2,columns_2);
    int** map_3 = createMap(rows_3,columns_3);

    //saveMaps(rows_1,columns_1,map_1,rows_2,columns_2,map_2,rows_3,columns_3,map_3);

    return 0;
}
