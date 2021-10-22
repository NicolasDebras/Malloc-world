#include <stdio.h>
#include <stdlib.h>
void saveMaps(int rows_1, int columns_1, int** map_1, int rows_2, int columns_2, int** map_2, int rows_3, int columns_3, int** map_3){
    FILE* map_file = fopen("C:/Users/charl/CLionProjects/Malloc-world/save_map.txt","w");
    if(map_file != NULL){
        fprintf(map_file,"=== MAP ===\n");
        fprintf(map_file,"-- ZONE 1 --\n");
        for(int i = 0; i < rows_1; i++){
            for(int y = 0; y < columns_1; y++) fprintf(map_file,"%d ",map_1[i][y]);
            fprintf(map_file,"\n");
        }

        fprintf(map_file,"-- ZONE 2 --\n");
        for(int i = 0; i < rows_2; i++){
            for(int y = 0; y < columns_2; y++) fprintf(map_file,"%d ",map_2[i][y]);
            fprintf(map_file,"\n");
        }

        fprintf(map_file,"-- ZONE 3 --\n");
        for(int i = 0; i < rows_3; i++){
            for(int y = 0; y < columns_3; y++) fprintf(map_file,"%d ",map_3[i][y]);
            fprintf(map_file,"\n");
        }

        fclose(map_file);
        //printf("Niquel !");
    }
    else printf("Erreur à l'ouverture du fichier");
}

void printMap(int** map, int rows, int columns){

    for(int i = 0; i < rows; i++){
        for(int y = 0; y < columns; y++){
            printf("%d ",map[i][y]);
        }
        printf("\n");
    }

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

int main() {
    int rows_1 = 3;
    int columns_1 = 3;
    int rows_2 = 4;
    int columns_2 = 10;
    int rows_3 = 7;
    int columns_3 = 4;

    int** map_1 = createMap(rows_1,columns_1);
    int** map_2 = createMap(rows_2,columns_2);
    int** map_3 = createMap(rows_3,columns_3);

    saveMaps(rows_1,columns_1,map_1,rows_2,columns_2,map_2,rows_3,columns_3,map_3);

    return 0;
}
