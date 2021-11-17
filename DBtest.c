

#include"structures.c"

void inventoryDBExtractor(Object* inventory){
    FILE* f = fopen("inventoryDB.txt","r");

    if (f == NULL){
        return;
    }

    // while(fgets(string, 255, f) != NULL){

    //     char* stringTok = strtok(string," ");
    //     saveInteger = malloc(sizeof(int) * 10);
	//     counterInt = 0;

    //     while (stringTok != NULL) {
    //         saveInteger[counterInt] = atoi(stringTok);
    //         stringTok = strtok(NULL, " ");
    //         counterInt += 1;
    //     }
	// row += 1;
    // }


    int OBJECT_TYPE_BUFFER = 10;
    int OBJECT_ID_BUFFER = 5; 
    int OBJECT_CAPACITY = 15;
    int OBJECT_DAMAGE_BUFFER = 11;
    int OBJECT_ISSELECTED_BUFFER = 13;
    int NUMBER_READ_BUFFER = 3;

    char* weapon = "Weapon    ";
    char* armor = "Armor     ";
    char* ressource = "Ressource ";
    char* tool = "Tool      ";
    char* potion = "Potion    ";

    char* durabilty = "Durability: ";
    char* resistance = "Resistance: ";
    char* quantity = "Quantity:   ";
    char* hp_heal = "Hp_heal:    ";

    char* damage = "Damage: ";

    char* isSelected = "IsSelected: ";

    char* type = malloc(11*sizeof(char));
    char* capacity_char = malloc(16*sizeof(char));
    int objectId;
    int capacity_int;
    char* damage_char = malloc(12*sizeof(char));
    int damage_int;
    char* isSelected_char = malloc(12*sizeof(char));
    int isSelected_int;

    fscanf(f, "%s n°%d %s %d %s %d %s %d",type,&objectId, capacity_char, &capacity_int,
    damage_char,&damage_int,isSelected_char,&isSelected_int);

    if ( strcmp(type,"Weapon") == 0 ){
    printf("ma première ligne:\n%s n°%d %s %d\n",type, objectId, capacity_char, capacity_int);
    }

    fscanf(f, "%s n°%d %s %d %s %d %s %d",type,&objectId, capacity_char, &capacity_int,
    damage_char,&damage_int,isSelected_char,&isSelected_int);
    if ( strcmp(type,"Armor") == 0 ){
    printf("ma première ligne:\n%s n°%d %s %d\n",type, objectId, capacity_char, capacity_int);
    }

    // if ( strcmp(type, weapon) == 0 ){
    //     if ( strcmp(capacity_char,durabilty) == 0 && strcmp(damage_char,damage) == 0
    //          && strcmp(isSelected_char, isSelected) == 0 ){

    //     }
    //     else{
    //         printf(" Object Data Base Edition error: Please check that you have the good format\n");

    //     }
    // }
    // else if ( strcmp(type, armor) == 0 ){
        
    // }
    // else if ( strcmp(type, ressource) == 0 ){
        
    // }
    // else if ( strcmp(type, tool) == 0 ){
        
    // }
    // else if ( strcmp(type, potion) == 0 ){
        
    // }

    // char* age_char = " 13.2 ";
    // int age_int = atoi(age_char);
    // printf("age: %d\n",age_int);
    
    fclose(f);
}

Object** extractDBObjects(){
    Object** objectsList = malloc(34*sizeof(Object*));
    for (int i=0; i<34; i++){
        objectsList[i] = new_Object();
    }

    FILE* f = fopen("ObjetsDB.txt","r");

    char* objectType = malloc(12*sizeof(char));
    char* objectCategory= malloc(17*sizeof(char));
    char* objectIsSelect = malloc(13*sizeof(char));
    int objectId;
    int objectCapacity;
    int objectDamage;

    int i = 0;
    while ( !feof(f) ){
        fscanf(f, "%s %s %s %d %d %d\n", objectType, objectCategory, objectIsSelect, &objectId, 
        &objectCapacity, &objectDamage);

        if ( strcmp(objectType,"ARME_TYPE") == 0 ){
            objectsList[i]->arme = new_arme(objectId,objectDamage,objectCapacity);
        }
        else if ( strcmp(objectType,"ARMURE_TYPE") == 0 ){
            objectsList[i]->armure = new_armure(objectId,objectCapacity);
        }
        else if ( strcmp(objectType,"OUTIL_TYPE") == 0 ){
            objectsList[i]->outil = new_outil(objectId,objectCapacity);
        }
        else if ( strcmp(objectType,"RDC_TYPE") == 0 ){
            objectsList[i]->ressource_de_craft = new_ressource_de_craft(objectId);
        }
        else if ( strcmp(objectType,"SOIN_TYPE") == 0 ){
            objectsList[i]->soin = new_soin(objectId,objectCapacity);
        }
        i++;
    }
    return objectsList;
}


int main(){
    Object* inventory = new_Object();

    inventoryDBExtractor(inventory);

    char* age_char = " -013.2 ";
    int age_int = atoi(age_char);
    printf("age: %d\n",age_int);

    return 0;
}
