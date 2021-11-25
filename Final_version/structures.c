#include "malloc_world.h"

//---------// New Object Creator //---------// 

Obj_Arme* new_arme(Arme objectId, int degat, int durabilite){
    
    Obj_Arme* weapon = malloc(sizeof(Obj_Arme)); 
    weapon->objectId = objectId;
    weapon->degat = degat;
    weapon->durabilite = durabilite;
    return weapon;
}

Obj_Armure* new_armure(Armure objectId, int resistance){
    Obj_Armure* armor = malloc(sizeof(Obj_Armure));
    armor->objectId = objectId;
    armor->resistance = resistance;

    return armor;
}

Obj_Outil* new_outil(Outil objectId, int durabilite){
    Obj_Outil* tool = malloc(sizeof(Obj_Outil));
    tool->objectId = objectId;
    tool->durabilite = durabilite;
    return tool;
}

Obj_Ressource_de_craft* new_ressource_de_craft(Ressource_de_craft objectId){
    Obj_Ressource_de_craft* craft = malloc(sizeof(Obj_Ressource_de_craft));
    craft->objectId = objectId;
    craft->quantity = 0;
    return craft;
}

Obj_Soin* new_soin(Outil objectId, int hp_heal){
    Obj_Soin* potion = malloc(sizeof(Obj_Soin));
    potion->objectId = objectId;
    potion->hp_heal = hp_heal;

    return potion;
}

Object* new_Object(){
    Object* objet = malloc(sizeof(Object));

    objet->arme = malloc(sizeof(Obj_Arme));
    objet->armure = malloc(sizeof(Obj_Armure));
    objet->outil = malloc(sizeof(Obj_Outil));
    objet->ressource_de_craft = malloc(sizeof(Obj_Ressource_de_craft));
    objet->soin = malloc(sizeof(Obj_Soin));
    objet->type = -1;
    objet->category = -1;
    objet->next = NULL;

    return objet;
}

//---------// Object data base //---------// 

 Object** Object_list(){
     Object** objectsList = malloc(34*sizeof(Object*));
    for (int i=0; i<34; i++){
        objectsList[i] = new_Object();
    }

    FILE* f = fopen("Data_Bases/ObjectsDB.txt","r");

    char* objectType = malloc(12*sizeof(char));
    char* objectCategory= malloc(17*sizeof(char));
    char* objectIsSelect = malloc(13*sizeof(char));
    int objectId;
    int objectCapacity;
    int objectDamage;

    int i = 0;
    while (fgetc(f) != '\n'){}
    while ( !feof(f) ){
        fscanf(f, "%s %s %s %d %d %d\n", objectType, objectCategory, objectIsSelect, &objectId, 
        &objectCapacity, &objectDamage);

        if ( strcmp(objectType,"ARME_TYPE") == 0 ){
            objectsList[i]->arme = new_arme(objectId,objectDamage,objectCapacity);
            if ( strcmp(objectCategory,"SWORD_CATEGORY") == 0  ){
                objectsList[i]->category = SWORD_CATEGORY;
            }
            else if ( strcmp(objectCategory,"SPEAR_CATEGORY") == 0  ){
                objectsList[i]->category = SPEAR_CATEGORY;
            }
            else if ( strcmp(objectCategory,"HAMMER_CATEGORY") == 0  ){
                objectsList[i]->category = HAMMER_CATEGORY;
            }
            if ( strcmp(objectIsSelect,"NOT_SELECTED") == 0  ){
                objectsList[i]->isSelected = NOT_SELECTED;
            }
            objectsList[i]->type = ARME_TYPE;
        }
        else if ( strcmp(objectType,"ARMURE_TYPE") == 0 ){
            objectsList[i]->armure = new_armure(objectId,objectCapacity);
            objectsList[i]->type = ARMURE_TYPE;
        }
        else if ( strcmp(objectType,"OUTIL_TYPE") == 0 ){
            objectsList[i]->outil = new_outil(objectId,objectCapacity);
            if ( strcmp(objectCategory,"PICKAXE_CATEGORY") == 0  ){
                objectsList[i]->category = PICKAXE_CATEGORY;
            }
            else if ( strcmp(objectCategory,"SERPE_CATEGORY") == 0  ){
                objectsList[i]->category = SERPE_CATEGORY;
            }
            else if ( strcmp(objectCategory,"AX_CATEGORY") == 0  ){
                objectsList[i]->category = AX_CATEGORY;
            }
            objectsList[i]->type = OUTIL_TYPE;
        }
        else if ( strcmp(objectType,"RDC_TYPE") == 0 ){
            objectsList[i]->ressource_de_craft = new_ressource_de_craft(objectId);
            objectsList[i]->type = RDC_TYPE;
        }
        else if ( strcmp(objectType,"SOIN_TYPE") == 0 ){
            objectsList[i]->soin = new_soin(objectId,objectCapacity);
            objectsList[i]->type = SOIN_TYPE;
        }
        i++;
    }
    return objectsList;
 }


//---------// Getter Object from data base //---------//


Obj_Arme* getDBArme(int objectId){ 
    Obj_Arme* tmp = malloc(sizeof(Obj_Arme));
    tmp = Object_list()[objectId-1][0].arme;
    // printf("Weapon n°%d Damage: %d durability: %d\n",
    //             tmp->objectId,
    //             tmp->degat, tmp->durabilite);
    return tmp;
}
Obj_Armure* getDBArmure(int objectId){
    Obj_Armure* tmp = malloc(sizeof(Obj_Armure));
    tmp = Object_list()[objectId-1][0].armure;
    // printf("Armor n°%d Resistance: %d\n",
    //             tmp->objectId,tmp->resistance);
    return tmp;
}
Obj_Outil* getDBOutils(int objectId){
    Obj_Outil* tmp = malloc(sizeof(Obj_Outil));
    tmp = Object_list()[objectId-1][0].outil;
    // printf("Tool n°%d durability: %d\n",
    //             tmp->objectId, tmp->durabilite);
    return tmp;
}
Obj_Ressource_de_craft* getDBRDC(int objectId){
    Obj_Ressource_de_craft* tmp = malloc(sizeof(Obj_Ressource_de_craft));
    tmp = Object_list()[objectId-1][0].ressource_de_craft;
    // printf("Ressource n°%d quantity: %d\n",
    //             tmp->objectId, tmp->quantity);
    return tmp;
}
Obj_Soin* getDBSoin(int objectId){
    Obj_Soin* tmp = malloc(sizeof(Obj_Soin));
    tmp = Object_list()[objectId-1][0].soin;
    // printf("Potion n°%d hp_heal: %d\n",
    //             tmp->objectId, tmp->hp_heal);
    return tmp;
}

int getDBObjectType(int objectId){
    return Object_list()[objectId-1][0].type;
}

int getDBObjectCategory(int objectId){
    return Object_list()[objectId-1][0].category;
}

Object* getDBObject(int type, int objectId){
    Object* tmp = new_Object();

    if (type == ARME_TYPE){
        tmp->arme = getDBArme(objectId);
        tmp->type = ARME_TYPE;
        tmp->category = getDBObjectCategory(objectId);
        tmp->isSelected = NOT_SELECTED;
    }
    else if (type == ARMURE_TYPE){
        tmp->armure= getDBArmure(objectId);;
        tmp->type = ARMURE_TYPE;
    }
    else if (type == OUTIL_TYPE){
        tmp->outil= getDBOutils(objectId);
        tmp->type = OUTIL_TYPE;
        tmp->category = getDBObjectCategory(objectId);
    }
    else if (type == RDC_TYPE){
        tmp->ressource_de_craft = getDBRDC(objectId);
        tmp->type = RDC_TYPE;
    }
    else if (type == SOIN_TYPE){
        tmp->soin = getDBSoin(objectId);
        tmp->type = SOIN_TYPE;
    }
    return tmp;
}

//---------// Check functions //---------// 

int inventorySize(Object* inventory){
    Object* tmp = inventory;
    int counter = 0;

    if ( inventory->type == -1 ){
        return 0;
    }
    while (tmp != NULL){ 
        counter++;
        tmp = tmp->next;
    }
    if (counter<1){
        printf("***inventorySize Exception: Erreur d'initialisation !!!");
        return ERROR_CODE;
    }
    return counter;
}

int countInventoryArme(Object* inventory){

    Object* tmp = inventory;
    int counter = 0;

    while (tmp != NULL){
        if ( tmp->type == ARME_TYPE ){
            counter++;
        }
        tmp = tmp->next;
    }
    return counter;
}

Object* quantityRDCInc(Object* inventory,int type, int objectId){
    Object* tmp = inventory;

    Object* rdc = searchObjectById(inventory, objectId);
    if ( rdc != NULL ){
        rdc->ressource_de_craft->quantity = rdc->ressource_de_craft->quantity + 1; 
        return inventory;
    }

    if ( inventory->type == -1 ){
        
        tmp = getDBObject(type, objectId);
        tmp->ressource_de_craft->quantity = tmp->ressource_de_craft->quantity + 1;        
        
        return tmp;
    }
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = getDBObject(type, objectId);
    tmp->next->ressource_de_craft->quantity = tmp->next->ressource_de_craft->quantity + 1;         
    
    return inventory;//As false
}

int isArmeInInventory(Object* inventory,int type, int objectId){
    
    if ( searchObjectById(inventory,objectId) != NULL ){
        return 1;
    }
    return 0;
}

//---------// Update Weapon or Tool //---------//


Object* addUpdatedObjectType(Object* inventory, int objectId){
    int OBJECT_TYPE = getDBObjectType(objectId);
    if ( OBJECT_TYPE != ARME_TYPE && OBJECT_TYPE != OUTIL_TYPE ){
        inventory = addObject(inventory, objectId, OBJECT_TYPE);
        return inventory;
    }

    int OBJECT_CATEGORY = getDBObjectCategory(objectId);
    Object* tmp = searchObjectByCategory(inventory, OBJECT_CATEGORY);

    if ( tmp == NULL ){
        inventory = addObject(inventory, objectId, OBJECT_TYPE);
        return inventory;
    }

    int tmpObjectId;
    if ( tmp->type == ARME_TYPE ){
        tmpObjectId = tmp->arme->objectId;
    }
    else if ( tmp->type == OUTIL_TYPE ){
        tmpObjectId = tmp->outil->objectId;
    }
    
    if ( tmpObjectId == objectId ){
        Object* result = new_Object();
        if ( OBJECT_CATEGORY == ARME_TYPE ){
            inventory = deleteObject(inventory,objectId);
            inventory = addObject(inventory, objectId, OBJECT_TYPE);
            Object* tmp2 = searchObjectById(inventory,objectId);
            tmp2->isSelected = tmp->isSelected;
        }
        else{
            inventory = deleteObject(inventory,objectId);
            inventory = addObject(inventory, objectId, OBJECT_TYPE);
            Object* tmp2 = searchObjectById(inventory,objectId);
        }
        
        return inventory;
    }
    
    if ( tmpObjectId < objectId ){
        inventory = deleteObject(inventory, tmpObjectId);
        inventory = addObject(inventory, objectId, OBJECT_TYPE);
        return inventory;
    }
    else{
        printf("***addUpdatedObjectType Exception:There is a powerful weapon than you want to add!\n");
        printf("--Do you want to delete it from the inventory to replace it with the weapon you choosed? (Y/N)\n");
        char answer[1];
        scanf("%c",&answer[0]);
        if ( answer[0] == 'Y' ){
            inventory = deleteObject(inventory, tmpObjectId);
            inventory = addObject(inventory, objectId, OBJECT_TYPE);
            return inventory;
        }
        else{
            printf("--- Okay, no new weapon is added!\n");
            return inventory;
        }
    }
}

//---------// Add object in Inventory //---------// 

Object* addarme(Object* inventory, int type, int objectId){
    int nb_weapon = countInventoryArme(inventory);
    int our_weapon = isArmeInInventory(inventory,type,objectId);
    int size = inventorySize(inventory);
    Object* tmp = inventory;
    
    if ( size < 11 && nb_weapon <= 3 && our_weapon!=1){
        if ( inventory->type == -1 ){

            inventory = getDBObject(type, objectId);

            printf("Object n°%d was added to your inventory\n",inventory->arme->objectId);
            
            return inventory;
        }
        else{
            while(tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next = getDBObject(type, objectId);
            printf("Object n°%d was added to your inventory\n",tmp->next->arme->objectId);    
        }
    }
    else{
        printf("***addarme Exception: We cannot insert more weapon!\n");
        printf("***addarme Exception: There is %d objets in inventory and %d Weapons\n",size, nb_weapon);
    }

    return inventory;
}

Object* addcraft(Object* inventory,int type, int objectId){
    int size = inventorySize(inventory);
    printf("on a %d size.\n", size);

    if ( size < 11 ){

        if ( inventory->type == -1){
            inventory = quantityRDCInc(inventory, type, objectId);
            return inventory;
        }
        inventory = quantityRDCInc(inventory, type, objectId);

        return inventory;
    }
    else{
        printf("***addcraft Exception: We cannot insert more ressources!\n");
        printf("***addcraft Exception: There is %d objets in inventory.\n",size);
        return inventory;
    }
}

Object* addOtherObject(Object* inventory, int type, int objectId){

    int size = inventorySize(inventory);
    Object* tmp = inventory;
    printf("on a %d size.\n", size);
    if ( size < 11 ){

        if ( inventory->type == -1 ){
            inventory = getDBObject(type, objectId);

            printf("Object n°%d was added to your inventory\n",objectId);

            return inventory;
        }
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = getDBObject(type, objectId);
        printf("Object n°%d was added to your inventory\n",objectId);

    }
    else{
        printf("***addOtherObject Exception: We cannot insert more weapon !\n");
        printf("***addOtherObject Exception: There is %d objets in inventory\n",size);
    }

    return inventory;
}

Object* addObject(Object* inventory, int objectId, int objectType){
    switch (objectType)
    {
        case ARME_TYPE:
            inventory = addarme(inventory, objectType, objectId);
            break;
        case RDC_TYPE:
            inventory = addcraft(inventory, objectType, objectId);
            break;
        default:
            inventory = addOtherObject(inventory, objectType, objectId);
            break;
    }
    return inventory;
}

Object* appendNewObject(Object* inventory, int objectId){
    int objectType = getDBObjectType(objectId);
    switch (objectType)
    {
        case ARME_TYPE:
            inventory = addUpdatedObjectType(inventory, objectId);
            break;
        case RDC_TYPE:
            inventory = addcraft(inventory, objectType, objectId);
            break;
        case OUTIL_TYPE:
            inventory = addUpdatedObjectType(inventory, objectId);
            break;
        default:
            inventory = addOtherObject(inventory, objectType, objectId);
            break;
    }
    return inventory;
}
//---------// Search objects functions //---------// 

Object* searchObjectById(Object* inventory, int objectId){
    Object* tmp = inventory;

    while ( tmp!=NULL ){
        if ( tmp->arme->objectId == objectId || tmp->armure->objectId == objectId ||
            tmp->outil->objectId == objectId || tmp->ressource_de_craft->objectId == objectId ||
            tmp->soin->objectId == objectId ){
            return tmp;
        }
        tmp = tmp->next;
    }
    printf("***searchObjectById Exception: This object is not in the inventory\n");
    return NULL;
}

Object* searchObjectByType(Object* inventory, int Objecttype){
    Object* tmp = inventory;

    while ( tmp!=NULL ){
        if ( tmp->type == Objecttype ){
            return tmp;
        }
        tmp = tmp->next;
    }
    printf("***searchObjectByType Exception:There is no object of this type in the inventory\n");
    return NULL;
}

Object* searchSelectedObjectByType(Object* inventory, int objectType){
    Object* tmp = inventory;

    while ( tmp!=NULL ){
        if ( tmp->type == objectType && tmp->isSelected == SELECTED ){
            return tmp;
        }
        tmp = tmp->next;
    }
    printf("***searchSelectedObjectByType Exception: There is no object of this type selected in the inventory\n");
    return NULL;
}

Object* searchObjectByCategory(Object* inventory, int objectCategory){
    Object* tmp = inventory;

    while ( tmp!=NULL ){
        if ( tmp->category == objectCategory){
            return tmp;
        }
        tmp = tmp->next;
    }
    printf("***searchObjectByCategory Exception: There is no object of this category in the inventory\n");
    return NULL;
}

//---------// Utils functions //---------// 

Object* selectObject(Object* inventory, int objectId){
    Object* tmp = searchObjectById(inventory, objectId);

    if ( tmp == NULL ){
        printf("***SelectObject Exception: This object is not in the inventory\n");
        return NULL;
    }
    if ( tmp->type != ARMURE_TYPE && tmp->type != ARME_TYPE && tmp->type != OUTIL_TYPE ){
        printf("***SelectObject Exception: Wrong type of object,  You must select a weapon or Armor or a tool!\n");
        return NULL;
    }

    Object* tmp2 = searchSelectedObjectByType(inventory, tmp->type); 
    if ( tmp2 != NULL && tmp2!=tmp ){
        tmp2->isSelected = NOT_SELECTED;
    }
    if ( tmp->isSelected == SELECTED ){
        printf("***SelectObject Exception: This object is already selected!\n");
        return inventory;
    }
    else{
        tmp->isSelected = SELECTED;
        return inventory;
    }
}

Object* deleteObject(Object* inventory, int objectId){
    Object* tmp = inventory;
    Object* previous = new_Object(); 
    while ( tmp!=NULL )
    {
        if ( tmp->arme->objectId == objectId || tmp->armure->objectId == objectId ||
            tmp->outil->objectId == objectId || tmp->ressource_de_craft->objectId == objectId ||
            tmp->soin->objectId == objectId ){
             
            //If it is the object
            if ( inventorySize(inventory) == 1 ){
                
                inventory = new_Object();
                return inventory;
            }
            //if it is at the end
            if ( tmp->next == NULL ){
                previous->next = NULL;
                free(tmp);
                return inventory;    
            }
            //it is on the first 
            else if( tmp == inventory ){             
                inventory = inventory->next;
                free(tmp);
                return inventory; 
            } 
            //it is on the middle
            else {
                previous->next = tmp->next;
                tmp->next = NULL;
                free(tmp);
                return inventory;
            }
        }
        previous = tmp;
        tmp = tmp->next;
    }
    //We don't change the inventory    
    printf("***deleteObject Exception: This object is not in the inventory\n");
    return inventory;
}

Object* objectMemCpy(Object* object){
    Object* tmp = new_Object();
    tmp->category = object->category;
    tmp->isSelected = object->isSelected;
    tmp->type = object->type;

    switch (tmp->type){
        case ARME_TYPE:
            tmp->arme->objectId = object->arme->objectId;
            tmp->arme->degat = object->arme->degat;
            tmp->arme->durabilite = object->arme->durabilite;
            break;
        case ARMURE_TYPE:
            tmp->armure->objectId = object->armure->objectId;
            tmp->armure->resistance = object->armure->resistance;
            break;
        case OUTIL_TYPE:
            tmp->outil->objectId = object->outil->objectId;
            tmp->outil->durabilite = object->outil->durabilite;
            break;
        case RDC_TYPE:
            tmp->ressource_de_craft->objectId = object->ressource_de_craft->objectId;
            tmp->ressource_de_craft->quantity = object->ressource_de_craft->quantity;
            break;
        case SOIN_TYPE:
            tmp->soin->objectId = object->soin->objectId;
            tmp->soin->hp_heal = object->soin->hp_heal;
            break;
    }
    tmp->next = NULL;
    
    return tmp;
}

void print_inventory(Object* inventory){
    Object* tmp = inventory;

    if ( inventorySize(inventory) > 0 ){
        while( tmp != NULL ){
            switch (tmp->type){

            case ARME_TYPE:
                printf("---Weapon n°%d Damage: %d durability: %d isSelected: %d\n",
                tmp->arme->objectId,
                tmp->arme->degat, tmp->arme->durabilite, tmp->isSelected);
                break;
            case ARMURE_TYPE:
                printf("---Armor n°%d Resistance: %d\n",
                tmp->armure->objectId,tmp->armure->resistance);
                break;
            case OUTIL_TYPE:
                printf("---Tool n°%d durability: %d\n",
                tmp->outil->objectId, tmp->outil->durabilite);
                break;
            case RDC_TYPE:
                printf("---Ressource n°%d quantity: %d\n",
                tmp->ressource_de_craft->objectId, tmp->ressource_de_craft->quantity);
                break;
            case SOIN_TYPE:
                printf("---Potion n°%d hp_heal: %d\n",
                tmp->soin->objectId, tmp->soin->hp_heal);
                break;
            default:
                printf("***print_inventory Exception: Unkown Type of object");
                break;
            }
            tmp = tmp->next;
        }
    }
    printf("\n");
}

void print_player(Player* player){
    printf("----* PLAYER STATUS *----\n");
    printf("-- XP: %d\n", player->xp);
    printf("-- Level: %d\n", player->level);
    printf("-- HP_CURRENT: %d\n", player->hp_current);
    printf("-- HP_MAX: %d\n", player->hp_max);
    printf("----*----*----*----*----*----\n\n");
}

//---------// Initialize the player/ New game //---------// 

Object* init_inventor(){
    

    Object* inventory;

    inventory = new_Object();
    
    inventory = addarme(inventory, ARME_TYPE, WOOD_SWORD);
    inventory->isSelected = SELECTED;

    inventory = addOtherObject(inventory, OUTIL_TYPE,WOODEN_PICKAXE);
    inventory = addOtherObject(inventory, OUTIL_TYPE,WOODEN_SERPE);
    inventory = addOtherObject(inventory, OUTIL_TYPE,WOODEN_AX);
    
    return inventory;
}

Player* init_player(){
    Player* p = malloc(sizeof(Player));

    p->inventory = init_inventor();
    p->xp = 0;
    p->level = 1;
    p->hp_current = 100;
    p->hp_max = 100;
      
    return p;
}

void savePlayer(Player* player, char filename[]){
    FILE* f = fopen(filename,"w");

    fprintf(f,"=== PLAYER ===\n");
    fprintf(f,"{%d}\n", player->level);
    fprintf(f,"{%d}/{XP_NEXT}\n", player->xp);
    fprintf(f,"{%d}/{%d}\n", player->hp_current, player->hp_max);

    fclose(f);
}

void saveInventory(Object* inventory, char filename[]){
    FILE* f = fopen("Data_Bases/saveInventory.txt","a+");
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



// int main(){

//     Player* p = init_player();
//     printf("Player before the attack\n\n");
//     print_player(p);
//     print_inventory(p->inventory);
//     selectObject(p->inventory, DIAMOND_HAMMER);
//     // printf("\n\n");
//     // p->inventory->isSelected = SELECTED;
//     // p->inventory = craftObject(p->inventory,WOODEN_PICKAXE);
//     // print_inventory(p->inventory);

//     // Monster* monster1 = malloc(sizeof(Monster));
//     // monster1->degats = 30;
//     // monster1->armor = 0;
//     // monster1->pv = 100;
//     // monster1->xp_profit = 25;

//     // attackMonster(p, monster1);
//     // receiveDamage(p, monster1);

//     // printf("Player after the attack and monsters pv= %d\n\n", monster1->pv);
//     // print_player(p);

//     Object* chest = new_Object();
//     print_inventory(chest);
//     print_inventory(p->inventory);

//     printf("en ajoutant dans chest\n\n");
//     Object** doubleinventory = addObjectToChest(p->inventory, chest, DIAMOND_HAMMER);
//     chest = doubleinventory[0];
//     p->inventory = doubleinventory[1];
//     print_inventory(chest);
//     print_inventory(p->inventory);

//     printf("en ajoutant dans inventory\n\n");
//     doubleinventory = getObjectFromChest(chest,p->inventory, DIAMOND_HAMMER);
//     chest = doubleinventory[1];
//     p->inventory = doubleinventory[0];
//     print_inventory(chest);
//     print_inventory(p->inventory);

//     return 0;

// }