#include "inventory.h"

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
    fclose(f);
    return objectsList;
}

int* extractDBObjectsRecipe(int objectId){
    int objectToCraftId;
    int craft1objectId;
    int craft1Quantity; 
    int craft2objectId; 
    int craft2Quantity;
    int* recipeDatas = malloc(4*sizeof(int));

    FILE* f = fopen("ObjectsRecipeDB.txt","r");

    while ( !feof(f) ){
        fscanf(f, "%d %d %d %d %d\n",&objectToCraftId, &craft1objectId, &craft1Quantity, 
        &craft2objectId, &craft2Quantity);

        if ( objectToCraftId == objectId ){
            recipeDatas[0] = craft1objectId;
            recipeDatas[1] = craft1Quantity;
            recipeDatas[2] = craft2objectId;
            recipeDatas[3] = craft2Quantity;
        }
    }
    fclose(f);
    if ( recipeDatas == NULL ){
        printf("extractDBObjectsRecipe Exception: Craft recipe not Found!\n");
        return NULL;
    }
    return recipeDatas;
}

void inventoryDBExtractor(Object* inventory){
    FILE* f = fopen("inventoryDB.txt","r");

    if (f == NULL){
        return;
    }

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
    
    fclose(f);
}

void savePlayer(Player* player, char filename[]){
    FILE* f = fopen(filename,"w");

    fprintf(f,"=== PLAYER ===\n");
    fprintf(f,"{%d}\n", player->level);
    fprintf(f,"{%d}/{XP_NEXT}\n", player->xp);
    fprintf(f,"{%d}/{%d}\n", player->hp_current, player->hp_max);

    fclose(f);
}

#define INVENTORY_TYPE 0
#define STORAGE_TYPE 1

void saveInventory(Object* inventory, char filename[]){
    FILE* f = fopen(filename,"a");
    int inventorylength = inventorySize(inventory);
    Object* tmp = inventory;
    
    fprintf(f,"-- INVENTORY --\n");
    
    if ( inventorylength > 0 && inventorylength < 10 ){
        while( tmp != NULL ){
            switch (tmp->type){

            case ARME_TYPE:
                fprintf(f,"{%d}@{%d}@{%d}\n",tmp->arme->degat,
                tmp->arme->objectId, tmp->arme->durabilite);
                break;
            case ARMURE_TYPE:
                fprintf(f,"{1}@{%d}@{%d}\n",tmp->armure->objectId,
                tmp->armure->resistance);
                break;
            case OUTIL_TYPE:
                fprintf(f,"{1}@{%d}@{%d}\n",tmp->outil->objectId, 
                tmp->outil->durabilite);
                break;
            case RDC_TYPE:
                fprintf(f,"{%d}@{%d}@{0}\n",tmp->ressource_de_craft->quantity, 
                tmp->ressource_de_craft->objectId);
                break;
            case SOIN_TYPE:
                fprintf(f,"{%d}@{%d}@{0}\n",tmp->soin->hp_heal, 
                tmp->soin->objectId);
                break;
            default:
                printf("***print_inventory Exception: Unkown Type of object");
                break;
            }
            tmp = tmp->next;
        }
    }
    if ( 10 - inventorylength > 0 ){
        for (int i = 0; i<10 - inventorylength; i++){
            fprintf(f,"{0}@{0}@{0}\n");
        }
    }
    fclose(f);
}

void saveChest(Object* chest, char filename[]){
    FILE* f = fopen(filename,"a");
    Object* tmp = chest;
    
    fprintf(f,"-- STORAGE --\n");

    while( tmp != NULL ){
        switch (tmp->type){
        case ARME_TYPE:
            fprintf(f,"{1}@{%d}\n",tmp->arme->objectId);
            break;
        case ARMURE_TYPE:
            fprintf(f,"{1}@{%d}\n",tmp->armure->objectId);
            break;
        case OUTIL_TYPE:
            fprintf(f,"{1}@{%d}\n",tmp->outil->objectId);
            break;
        case RDC_TYPE:
            fprintf(f,"{%d}@{%d}\n",tmp->ressource_de_craft->quantity, 
            tmp->ressource_de_craft->objectId);
            break;
        case SOIN_TYPE:
            fprintf(f,"{1}@{%d}\n", tmp->soin->objectId);
            break;
        default:
            printf("***print_inventory Exception: Unkown Type of object");
            break;
        }
        tmp = tmp->next;
    }
    fclose(f);
}

void saveAllGameProperties(Player* p, Object* chest, char filename[]){
    savePlayer(p,filename);
    saveInventory(p->inventory,filename);
    saveChest(chest, filename);
}

Object* initTestInventory8(){
    Object* inventory = new_Object();
    inventory->type = ARME_TYPE;
    inventory->arme = getDBArme(WOOD_SWORD);
    inventory->category = SWORD_CATEGORY;

    inventory->next = new_Object();
    inventory->next->type = OUTIL_TYPE;
    inventory->next->outil = getDBOutils(IRON_AX);

    inventory->next->next = new_Object();
    inventory->next->next->type = RDC_TYPE;
    inventory->next->next->ressource_de_craft = getDBRDC(FIR);
    inventory->next->next->ressource_de_craft->quantity = 7;

    inventory->next->next->next = new_Object();
    inventory->next->next->next->type = RDC_TYPE;
    inventory->next->next->next->ressource_de_craft = getDBRDC(STONE);
    inventory->next->next->next->ressource_de_craft->quantity = 13;

    return inventory;
}

void extractFromSaveFile(Player *p, Object* chest, char filename[]){

    p = extractorPlayerFromSaveFile(filename);
    p->inventory = extractorInventoryFromSaveFile(filename);
    chest = extractChestFromSaveFile(filename);
}

Player* extractorPlayerFromSaveFile(char filename[]){
    FILE* f = fopen(filename,"r");

    if ( f==NULL ){
        printf("***extractorInventoryFromSaveFile Exception: inventory Save file reading Failed\n");
        return NULL;
    }    
    Player* p = malloc(sizeof(Player));

    while (fgetc(f) != '\n'){}
    fscanf(f, "{%d}\n",&p->level);
    fscanf(f, "{%d}/{XP_NEXT}\n", &p->xp);
    int a, b;
    fscanf(f, "{%d}/{%d}\n",&a,&b);
    p->hp_current = a;
    p->hp_max = b;
    p->inventory = new_Object();
    fclose(f);
    return p;
}

Object* extractorInventoryFromSaveFile(char filename[]){
    FILE* f = fopen(filename,"r");

    if ( f==NULL ){
        printf("***extractorInventoryFromSaveFile Exception: inventory Save file reading Failed\n");
        return NULL;
    }    
    Object* inventory = new_Object();
    Object* tmp = inventory;
    
    int objectQuantity = 0;
    int objectId = 0;
    int objectDurability = 0;
    int stop = 1;
    int counter =  0;
    for (int i=0; i<5; i++){
        while (fgetc(f) != '\n'){}
    }
    
    while(stop != 0 ){
        if ( feof(f) ){
            stop = 0;
            break;
        }
        stop = fscanf(f,"{%d}@{%d}@{%d}\n",&objectQuantity,
            &objectId, &objectDurability);
        if ( objectId == 0 ){
            stop = 0;
            break;
        }

        int objectType = getDBObjectType(objectId);
        if ( tmp->type != -1 ) {
            while(tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next =  new_Object();
            tmp = tmp->next;
        }
        
        switch (objectType){
        case ARME_TYPE:
            tmp->arme = new_arme(objectId, objectQuantity,objectDurability);
            tmp->category = getDBObjectCategory(objectId);
            tmp->isSelected = NOT_SELECTED;
            break;
        case ARMURE_TYPE:
            tmp->armure = new_armure(objectId, objectQuantity);
            break;
        case OUTIL_TYPE:
            tmp->outil = new_outil(objectId,objectDurability);
            tmp->category = getDBObjectCategory(objectId);
            break;
        case RDC_TYPE:
            tmp->ressource_de_craft = new_ressource_de_craft(objectId);
            tmp->ressource_de_craft->quantity = objectQuantity;
            break;
        case SOIN_TYPE:
            tmp->soin = new_soin(objectId, objectQuantity);
            break;
        }
        tmp->type = objectType;
        tmp = inventory;
        //print_inventory(tmp);
        counter++;
    }
    if (counter<10){
        for (int j=0; j<10-counter; j++){
            while (fgetc(f) != '\n'){}
        }
    }
    fclose(f);
    return inventory;
}

Object* extractChestFromSaveFile(char filename[]){
    FILE* f = fopen(filename,"r");

    if ( f==NULL ){
        printf("***extractorInventoryFromSaveFile Exception: inventory Save file reading Failed\n");
        return NULL;
    }    
    for (int i=0; i<16; i++){
        while (fgetc(f) != '\n'){}
    }
    Object* chest = new_Object();
    Object* tmp = chest;
    
    int objectQuantity = 0;
    int objectId = 0;
    
    
    while( !feof(f) ){

        fscanf(f,"{%d}@{%d}\n",&objectQuantity,
            &objectId);

        int objectType = getDBObjectType(objectId);
        if ( tmp->type != -1 ) {
            while(tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next =  new_Object();
            tmp = tmp->next;
        }

        tmp = getDBObject(objectType, objectId);
        tmp->type = objectType;

        // if ( objectType != RDC_TYPE ){
        //     tmp = getDBObject(objectType, objectId);
        // }
        // else {
        //     Object* tmp2 = searchObjectById(chest, objectId);
        //     if ( tmp2==NULL ){
        //         collectCrafts(chest, objectQuantity, objectId);
        //     }
        //     else if ( tmp2->ressource_de_craft->quantity + objectQuantity < 20 ){
        //         tmp2->ressource_de_craft->quantity = tmp2->ressource_de_craft->quantity 
        //         + objectQuantity;
        //     }
        //     else{
        //         tmp2->ressource_de_craft->quantity = 20;
        //         if ( tmp2->ressource_de_craft->quantity + objectQuantity -20 > 0 ){
        //             tmp =  new_Object();
        //             tmp->ressource_de_craft = new_ressource_de_craft(objectId);
        //             tmp->type = objectType;
        //             tmp->ressource_de_craft->quantity = tmp2->ressource_de_craft->quantity 
        //             + objectQuantity -20;
        //         }
        //     }
        // }
        
        tmp = chest;
        //print_inventory(tmp);
    }
    fclose(f);
    return chest;
}

int* checkMapSize(char filename[], int map1Index, char* mapStr){
    FILE *f = fopen(filename, "r");
    int a = fseek(f, map1Index, SEEK_SET);
    
    // char* tmpStr = malloc(14*sizeof(char));
    // tmpStr = fgets(tmpStr, 14,f);
    // printf("on a trouvé %d\n %s %s\n", strcmp(tmpStr,mapStr)==10, tmpStr, mapStr);
    int columns = 0;
    int rows = 0;
    int totalNumber = 0;
    int tmp;
    while (fgetc(f)!=atoi('-')){
        printf("error here %d\n", a);
        fseek(f, -13, SEEK_CUR);
        while (fgetc(f) != '\n'){}
        rows++;
    }
    // fseek(f, map1Index, SEEK_SET);
    // while ( strcmp(fgets(tmpStr, 14,f),mapStr) == 0){
    //     fseek(f, -13, SEEK_CUR);
    //     fscanf(f, "%d", &tmp);
    //     totalNumber++;
    // }
    // columns = totalNumber/rows;
    int *tab = malloc(2*sizeof(int));
    // tab[0] = rows;
    // tab[1] = columns;
    // fclose(f);
    return tab;
}

int* checkMap2Size(char filename[], int map2Index){
    
}

int* checkMap3Size(char filename[], int map3Index){
    
}



void extractMapFromSaveFile(char filename[]){
    FILE *f = fopen(filename, "r");

    char* mapStr = malloc(12*sizeof(char));
    char* map1Str = malloc(13*sizeof(char));
    char* map2Str = malloc(13*sizeof(char));
    map2Str = "-- ZONE 2 --\n";
    char* map3Str = malloc(13*sizeof(char));
    map3Str = "-- ZONE 3 --\n";

    while (fgetc(f) != '\n'){}
    while (fgetc(f) != '\n'){}

    int currenIndex = ftell(f);
    

}


Player* initTestPlayer8(){
    Player* p = malloc(sizeof(Player));

    p->xp = 0;
    p->level = 1;
    p->hp_current = 100;
    p->hp_max = 100;
    p->inventory = malloc(sizeof(Object));
    p->inventory = new_Object();
    p->inventory->soin = getDBSoin(HEAL2);
    p->inventory->type = SOIN_TYPE;
    p->inventory->next = NULL;
    return p;
}

// int main(){
//     // Object* inventory = initTestInventory8();
//     // Player* p = initTestPlayer8();
//     // saveAllGameProperties(p, inventory, "Data_Bases/saveInventory.txt");

//     char* map2Str = malloc(14*sizeof(char));
//     map2Str = "-- ZONE2 --";

//     int *res = checkMapSize("test.txt",0,map2Str);
//     printf("on a %d et %d \n", res[0], res[1]);
    
//     // Object* chest2 = extractChestFromSaveFile("Data_Bases/saveInventory.txt");
//     // Player* p2 = extractorPlayerFromSaveFile("Data_Bases/saveInventory.txt");
//     // p2->inventory = extractorInventoryFromSaveFile("Data_Bases/saveInventory.txt");

//     // print_player(p2);
//     // print_inventory(p2->inventory);
//     // print_inventory(chest2);

    

//     //inventoryDBExtractor(inventory);

//     // char* age_char = " -013.2 ";
//     // int age_int = atoi(age_char);
//     // printf("age: %d\n",age_int);

//     return 0;
// }
