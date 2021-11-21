#include "structures.h"


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

void saveInventory(Object* inventory, char filename[]){
    FILE* f = fopen(filename,"w");
    int inventorylength = inventorySize(inventory);
    Object* tmp = inventory;

    fprintf(f,"--INVENTORY--\n");
    
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



Object* initTestInventory4(){
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

Object* extractorInventoryFromSaveFile(char filename[]){
    FILE* f = fopen(filename,"r");

    if ( f==NULL ){
        printf("***extractorInventoryFromSaveFile Exception: inventory Save file reading Failed\n");
        return NULL;
    }
    
    // char* stopCondition1 = "{0}@{0}@{0}";
    // char* stopCondition2 = "--STORAGE--";
    Object* inventory = new_Object();
    Object* tmp = inventory;
    
    int objectQuantity = 0;
    int objectId = 0;
    int objectDurability = 0;

    int stop = 1;
    // while (fgetc(f) != '\n'){}
    // while (fgetc(f) != '\n'){}
    // while (fgetc(f) != '\n'){}
    // while (fgetc(f) != '\n'){}
    
    while(stop != 0 ){
        if ( feof(f) ){
            stop = 0;
            //printf("on est sorti de la fin\n");
            break;
        }

        stop = fscanf(f,"{%d}@{%d}@{%d}\n",&objectQuantity,
            &objectId, &objectDurability);
        
        if ( objectId == 0 ){
            stop = 0;
            //printf("On a trouvé %d %d %d \n",objectQuantity,
            //objectId, objectDurability);
            //printf("on est sorti par un 0\n");
            break;
        }
        // printf("on est pas sorti\n");
    //printf("#####  %d\n",objectId);
        int objectType = getDBObjectType(objectId); 
        // printf("%d\n",objectType);
        print_inventory(inventory);
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next =  new_Object();
        // if ( inventorySize(inventory) != 0){
            
        //     tmp =
        //     //printf("on est plus null si %d\n",tmp!=NULL);
        // }
        
        switch (objectType){

        case ARME_TYPE:
            tmp->next->arme = new_arme(objectId, objectQuantity,objectDurability);
            // printf("#####  %d\n",tmp->arme->objectId);
            tmp->next->category = getDBObjectCategory(objectId);
            break;
        case ARMURE_TYPE:
            tmp->next->armure = new_armure(objectId, objectQuantity);
            break;
        case OUTIL_TYPE:
            //printf("####\n");
            tmp->next->outil = new_outil(objectId,objectDurability);
            tmp->next->category = getDBObjectCategory(objectId);
            //printf("outil %d et sa cat %d\n",tmp->outil->objectId, tmp->category);
            break;
        case RDC_TYPE:
            tmp->next->ressource_de_craft = new_ressource_de_craft(objectId);
            tmp->next->ressource_de_craft->quantity = objectQuantity;
            break;
        case SOIN_TYPE:
            tmp->next->soin = new_soin(objectId, objectQuantity);
            break;
        }
        tmp->next->type = objectType;
        // print_inventory(tmp);
        tmp = tmp->next;
    }
    
    fclose(f);

    return inventory;
}



int main(){
    Object* inventory = initTestInventory4();
    saveInventory(inventory,"Data_Bases/saveInventory.txt");

    // Object* inventory2 = extractorInventoryFromSaveFile("Data_Bases/saveInventory.txt");

    // print_inventory(inventory2);

    

    //inventoryDBExtractor(inventory);

    // char* age_char = " -013.2 ";
    // int age_int = atoi(age_char);
    // printf("age: %d\n",age_int);

    return 0;
}
