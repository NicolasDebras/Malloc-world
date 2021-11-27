#include "inventory.h"


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
        tmp->armure= getDBArmure(objectId);
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
        printf("Craft n°%d was added to your inventory, we have %d of this craft\n",
            tmp->ressource_de_craft->objectId, tmp->ressource_de_craft->quantity);

        return inventory;
    }

    if ( inventory->type == -1 ){
        
        tmp = getDBObject(type, objectId);
        tmp->ressource_de_craft->quantity = tmp->ressource_de_craft->quantity + 1;        
        
        printf("Craft n°%d was added to your inventory, we have %d of this craft\n",
            tmp->ressource_de_craft->objectId, tmp->ressource_de_craft->quantity);
        
        return tmp;
    }
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = getDBObject(type, objectId);
    tmp->next->ressource_de_craft->quantity = tmp->next->ressource_de_craft->quantity + 1;        
    
    printf("Craft n°%d was added to your inventory, we have %d of this craft\n",
        tmp->next->ressource_de_craft->objectId, tmp->next->ressource_de_craft->quantity);    
    
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
#include "math.h"

int calculateLessedByPercent(int number, int nbPercent){
    float tmp = number;
    printf("#### on a %f ####\n",tmp);
    float tmp2 = nbPercent;
    printf("#### et %f ####\n",tmp2);
    int res = roundf((tmp2*number)/100);
    printf("####### j'ai produit %d #######\n",res);
    return res;
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
    printf("----*Player Descriptions*----\n");
    printf("-- XP: %d\n", player->xp);
    printf("-- Level: %d\n", player->level);
    printf("-- HP_CURRENT: %d\n", player->hp_current);
    printf("-- HP_MAX: %d\n", player->hp_max);
    printf("----*----*----*----*----*----\n\n");
}

//---------// Chest Functions //---------// 

Object** addObjectToChest(Object* inventory,Object* chest, int objectId){
    /* 
    Put a object from the inventory to the chest by the object id
    Parameters: 
        - Fistsly the inventory (source)
        - Secondly the chest (destination)
        - at last the object id
    Returns a table pour object two object list:
        - at first the chest
        - and at second the inventory
    */
    Object* tmp = searchObjectById(inventory, objectId);
    Object** result = malloc(2*sizeof(Object*));
    if ( tmp == NULL ){
        result[0] = chest;
        result[1] = inventory;
        return result;
    }
    if ( chest->type == -1 ){
        chest = objectMemCpy(tmp);
        inventory = deleteObject(inventory, objectId);
        result[0] = chest;
        result[1] = inventory;
        return result;
    }
    Object* tmp2 = chest;
    while ( tmp2->next != NULL ){
        tmp2 = tmp2->next;
    }
    tmp2->next = objectMemCpy(tmp);
    inventory = deleteObject(inventory, objectId);
    result[0] = chest;
    result[1] = inventory;
    return result;
}

Object** getObjectFromChest(Object* chest, Object* inventory, int objectId){
    Object* tmp = searchObjectById(chest, objectId);
    Object** result = malloc(2*sizeof(Object*));
    if ( tmp == NULL ){
        printf("***getObjectFromChest Exception: This oject is not in your chest.");
        result[0] = inventory;
        result[1] = chest;
        return result;
    }
    if ( inventorySize(inventory) == 10 ){
        printf("***getObjectFromChest Exception: Your inventory is already full.");
        result[0] = inventory;
        result[1] = chest;
        return result;
    }
    if ( inventorySize(inventory) == 0  ){
        inventory = objectMemCpy(tmp);
        chest = deleteObject(chest, objectId);
        result[0] = inventory;
        result[1] = chest;
        return result;
    }
    Object* tmp2 = inventory;
    while ( tmp2->next != NULL ){
        tmp2 = tmp2->next;
    }
    tmp2->next = objectMemCpy(tmp);
    chest = deleteObject(chest, objectId);

    result[0] = inventory;
    result[1] = chest;
    return result;
}

//---------// Object Getters from inventory functions //---------// 

Object* getSelectedWeapon(Object* inventory){
    Object* tmp = searchSelectedObjectByType(inventory, ARME_TYPE);
    if ( tmp == NULL){
        printf("***getSelectedWeapon Exception: No selected weapon found!\n");
        return NULL;
    }
    return tmp;
}

Object* getPickaxe(Object* inventory){
    Object* tmp = inventory;

    while ( tmp!=NULL ){
        if ( tmp->category == PICKAXE_CATEGORY ){
            return tmp;
        }
        tmp = tmp->next;
    }
    
    printf("***Getting Pickaxe Exception: There is no pickaxe in your inventory\n");
    return NULL;
}

Object* getAx(Object* inventory){
    Object* tmp = inventory;

    while ( tmp!=NULL ){
        if ( tmp->category == AX_CATEGORY ){
            return tmp;
        }
        tmp = tmp->next;
    }
    printf("***Getting Ax Exception: There is no Ax in your inventory\n");
    return NULL;
}

Object* getSerpe(Object* inventory){
    Object* tmp = inventory;

    while ( tmp!=NULL ){
        if ( tmp->category == SERPE_CATEGORY ){
            return tmp;
        }
        tmp = tmp->next;
    }
    printf("***Getting Serpe Exception: There is no Serpe in your inventory\n");
    return NULL;
}

Player* useHealPotion(Player* p, int objectId){
    Object* tmp = searchObjectById(p->inventory, objectId);
    if ( tmp == NULL ){
        printf("***useHealPotion Exception: Heal Potion not found!\n");
        return NULL;
    }
    printf("--- You are using  HEAL1 potion heal hp : %d ...\n", tmp->soin->hp_heal);
    if ( (p->hp_current + tmp->soin->hp_heal) >= p->hp_max){
        
        p->hp_current = p->hp_max;
        return p;
    }
    else{
        p->hp_current = p->hp_current + tmp->soin->hp_heal;
        return p;
    }
}

//---------// Crafting Recipes Data Bases //---------// 

int* craftObjectRecipe(int objectId){
    int objectToCraftId;
    int craft1objectId;
    int craft1Quantity; 
    int craft2objectId; 
    int craft2Quantity;
    int* recipeDatas = malloc(4*sizeof(int));

    FILE* f = fopen("Data_Bases/ObjectsRecipeDB.txt","r");
    while (fgetc(f) != '\n'){}
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

//---------// Repair and Craft //---------// 

Object* repairAllObject(Object* inventory){
    
    Object* tmp = inventory;
    while (tmp != NULL){
        switch (tmp->type)
        {
            case ARME_TYPE:
                if ( tmp->arme->objectId == WOOD_SWORD || tmp->arme->objectId == STONE_SWORD ||
                    tmp->arme->objectId == IRON_SWORD || tmp->arme->objectId == DIAMOND_SWORD ){
                        tmp->arme->durabilite = 10;
                }
                else if ( tmp->arme->objectId == STONE_SPEAR || tmp->arme->objectId == IRON_SPEAR || 
                    tmp->arme->objectId == DIAMOND_SPEAR ){
                        tmp->arme->durabilite = 8;
                }
                else if ( tmp->arme->objectId == STONE_HAMMER || tmp->arme->objectId == IRON_HAMMER || 
                    tmp->arme->objectId == DIAMOND_HAMMER ){
                        tmp->arme->durabilite = 5;
                }
                break;
            case OUTIL_TYPE:
                tmp->outil->durabilite = 10;
        }
        tmp = tmp->next;
    }
    printf("--- All objects was repaired! ---\n");
    return inventory;
}

Object* craftObject(Object* inventory, int objectId){
    if ( inventorySize(inventory) == 10 ){
        printf("***Craft object Exception: The inventory is already full");
        return inventory;
    }

    int* objectRecipe = craftObjectRecipe(objectId);
    int objectType = getDBObjectType(objectId);

    Object* craft1 = searchObjectById(inventory, objectRecipe[0]);
    if ( craft1 == NULL || craft1->ressource_de_craft->quantity < objectRecipe[1] ){
        printf("***Craft object exception: Not enought crafts in the inventory or you already have this weapon in your inventory!\n");
        printf("***Help:To repair your weapon use the function repairAllObject.\n");
        return inventory;
    }
    
    if ( craft1->ressource_de_craft->quantity - objectRecipe[1] == 0 ){
        deleteObject(inventory, objectRecipe[0]);
        printf("***Craft object exception:Craft n°%d has been deleted\n", objectRecipe[0]);
    }
    else{
        craft1->ressource_de_craft->quantity = craft1->ressource_de_craft->quantity - objectRecipe[1] ;
    }

    if ( objectRecipe[2] != -1 ){
        Object* craft2 = searchObjectById(inventory, objectRecipe[2]);
        
        if ( craft2 == NULL || craft2->ressource_de_craft->quantity < objectRecipe[3] ){
            printf("***Craft object exception: Not enought crafts in the inventory or you already have this weapon in your inventory!\n");
            printf("***Help:To repair your weapon use the function repair craft.\n");
            return inventory;
        }
        if ( craft2->ressource_de_craft->quantity - objectRecipe[3] == 0 ){
            deleteObject(inventory, objectRecipe[2]);
            printf("***Craft object exception:Craft n°%d has been deleted\n",objectRecipe[2]);
        }
        else{
            craft2->ressource_de_craft->quantity = craft2->ressource_de_craft->quantity - objectRecipe[3];
        }
    }
    
    inventory = appendNewObject(inventory, objectId);
    
    return inventory;
}

//---------// Modify Weapon, Armor, ... //---------// 

Object* collectCrafts(Object* inventory, int quantity, int objectId){
    int size = inventorySize(inventory);
   
    Object* tmp = searchObjectById(inventory, objectId);
    if ( size == 10 && tmp == NULL ){
         
        printf("CollectCraft Exception: your inventory is already full!\n");
        return inventory;
    }
    if (tmp==NULL){
        for (int i=0; i<quantity; i++){
            inventory = addcraft(inventory, RDC_TYPE, objectId);
        }
        return inventory;
    }
    for (int i=0; i<quantity; i++){
        if ( tmp->ressource_de_craft->quantity < 20 ){
            inventory = addcraft(inventory, RDC_TYPE, objectId);
        }
    }
    return inventory;
}

Object* lessObjectCapacity(Object* object, int lesscapacity){
    switch (object->type)
    {
    case ARME_TYPE:
        if ( object->arme->durabilite - lesscapacity <= 0 ){
            object->arme->durabilite = 0;
        }
        else{
            object->arme->durabilite = object->arme->durabilite - lesscapacity;
        }
        break;
    case OUTIL_TYPE:
        if ( object->outil->durabilite - lesscapacity <= 0 ){
            object->outil->durabilite = 0;
        }
        else{
            object->outil->durabilite = object->outil->durabilite - lesscapacity;
        }
        break;
    default:
        printf("***lessObject Capacity Exception: Cannot less the capacity of this object.\n");
        break;
    }
    return object;
}

Object** toolsGetterFromInventory(Object* inventory){
    Object** tools = malloc(3*sizeof(Object));

    tools[0] = searchObjectByCategory(inventory, PICKAXE_CATEGORY);
    tools[1] = searchObjectByCategory(inventory, AX_CATEGORY);
    tools[2] = searchObjectByCategory(inventory, SERPE_CATEGORY);

    return tools;
}

int collectAndToolUpdateMap1(Object* inventory, int objectIdToCollect, int quantity, Object** tools){
    if (objectIdToCollect == STONE){
        if ( tools[0] != NULL && tools[0]->outil->objectId >= WOODEN_PICKAXE && 
                tools[0]->outil->durabilite >= calculateLessedByPercent(tools[0]->outil->durabilite, 10)){
            lessObjectCapacity(tools[0], calculateLessedByPercent(tools[0]->outil->durabilite, 10));
            collectCrafts(inventory, quantity, objectIdToCollect);
            return 1;
        }
    }
    else if (objectIdToCollect == FIR){
        if ( tools[1] != NULL && tools[1]->outil->objectId >= WOODEN_AX && 
                tools[0]->outil->durabilite >=  calculateLessedByPercent(tools[1]->outil->durabilite, 10) ){
            lessObjectCapacity(tools[1], calculateLessedByPercent(tools[1]->outil->durabilite, 10));
            collectCrafts(inventory, quantity, objectIdToCollect);
            return 1;
        }
    }
    else if (objectIdToCollect == GRASS){
        if ( tools[2] != NULL && tools[2]->outil->objectId >= WOODEN_SERPE && 
                tools[2]->outil->durabilite >= calculateLessedByPercent(tools[2]->outil->durabilite, 10) ){
            lessObjectCapacity(tools[2], calculateLessedByPercent(tools[2]->outil->durabilite, 10));
            collectCrafts(inventory, quantity, objectIdToCollect);
            return 1;
        }
    }
    printf("***collectAndToolUpdate Exception: Invalid ressource in map zone! or tool broken or unfound tool\n");
    return 0;
}

int collectAndToolUpdateMap2(Object* inventory, int objectIdToCollect, int quantity, Object** tools){
    if (objectIdToCollect == IRON){
        if ( tools[0] != NULL && tools[0]->outil->objectId >= STONE_PICKAXE && 
            tools[0]->outil->durabilite >= calculateLessedByPercent(tools[0]->outil->durabilite, 20) ){
            lessObjectCapacity(tools[0], calculateLessedByPercent(tools[0]->outil->durabilite, 20));
            collectCrafts(inventory, quantity, objectIdToCollect);
            return 1;
        }
    }
    else if (objectIdToCollect == BEECH){
        if ( tools[1] != NULL && tools[1]->outil->objectId >= STONE_AX && 
            tools[1]->outil->durabilite >= calculateLessedByPercent(tools[1]->outil->durabilite, 20)){
            lessObjectCapacity(tools[1], calculateLessedByPercent(tools[1]->outil->durabilite, 20));
            collectCrafts(inventory, quantity, objectIdToCollect);
            return 1;
        }
    }
    else if (objectIdToCollect == LAVENDER){
        if ( tools[2] != NULL && tools[2]->outil->objectId >= STONE_SERPE && 
            tools[2]->outil->durabilite >= calculateLessedByPercent(tools[2]->outil->durabilite, 20)){
            lessObjectCapacity(tools[2], calculateLessedByPercent(tools[2]->outil->durabilite, 20));
            collectCrafts(inventory, quantity, objectIdToCollect);
            return 1;
        }
    }
    printf("***collectAndToolUpdate Exception: Invalid ressource in map zone! or tool broken or unfound tool\n");
    return 0;
}

int collectAndToolUpdateMap3(Object* inventory, int objectIdToCollect, int quantity, Object** tools){
    if (objectIdToCollect == DIAMOND){
        if ( tools[0] != NULL && tools[0]->outil->objectId >= IRON_PICKAXE && 
            tools[0]->outil->durabilite >= calculateLessedByPercent(tools[0]->outil->durabilite, 40) ){
            lessObjectCapacity(tools[0], calculateLessedByPercent(tools[0]->outil->durabilite, 40));
            collectCrafts(inventory, quantity, objectIdToCollect);
            return 1;
        }
    }
    else if (objectIdToCollect == OAK){
        if ( tools[1] != NULL && tools[1]->outil->objectId >= IRON_AX && 
            tools[1]->outil->durabilite >= calculateLessedByPercent(tools[1]->outil->durabilite, 40)){
            lessObjectCapacity(tools[1], calculateLessedByPercent(tools[1]->outil->durabilite, 40));
            collectCrafts(inventory, quantity, objectIdToCollect);
            return 1;
        }
    }
    else if (objectIdToCollect == HEMP){
        if ( tools[2] != NULL && tools[2]->outil->objectId >= IRON_SERPE && 
            tools[2]->outil->durabilite >= calculateLessedByPercent(tools[2]->outil->durabilite, 40)){
            lessObjectCapacity(tools[2], calculateLessedByPercent(tools[2]->outil->durabilite, 40));
            collectCrafts(inventory, quantity, objectIdToCollect);
            return 1;
        }
    }
    printf("***collectAndToolUpdate Exception: Invalid ressource in map zone! or tool broken or unfound tool\n");
    return 0;
}

int collectRessourceAndToolUpdate(Object* inventory, int objectIdToCollect, int quantity, int mapZone){
    Object** tools = toolsGetterFromInventory(inventory);

    switch (mapZone){
    case 1:
        return collectAndToolUpdateMap1(inventory, objectIdToCollect, quantity, tools);
        break;
    case 2:
        return collectAndToolUpdateMap2(inventory, objectIdToCollect, quantity, tools);
        break;
    case 3:
        return collectAndToolUpdateMap3(inventory, objectIdToCollect, quantity, tools);
        break;
    }
}

//---------// Attacks player-monster //---------// 

int receiveDamage(Player* player, Monster* monster){
    /*
        Returns 1 if the player still alive after the monster attacks him
        or 
        Returns 0 else
    */
    Object* armor = searchObjectByType(player->inventory, ARMURE_TYPE);
    int lessedDamage = 0;
    int lessDamage = 0;
    if ( player->hp_current == 0 ){
        return 0;
    }
    if ( armor != NULL){
        float tmp = monster->degats;
        float tmp2 = armor->armure->resistance;
        lessDamage = tmp * (tmp2/100.0);
        lessedDamage = monster->degats - lessDamage;
    }
    else{
        lessedDamage = monster->degats;
    }

    if ( player->hp_current <= lessedDamage ){
        player->hp_current = 0;
        printf("*** The player died ***\n");
        return 0;
    }
    else{
        player->hp_current = player->hp_current - lessedDamage;
        printf("*** HEART ***\n");
        return 1;
    }
}

int attackMonster(Player* player, Monster* monster){
    /*
        Returns 1 if the monster still alive after the player attacks him
        or 
        Returns 0 else
    */
    Object* weapon = searchSelectedObjectByType(player->inventory, ARME_TYPE);
    if ( monster->pv == 0 ){
        return 0;
    }
    if ( weapon == NULL ){
        printf("***attackMonster Exception: No weapon is selected.\n");
        printf("Please select a weapon\n");
        return 1;
    }
    if ( weapon->arme->durabilite == 0){
        printf("***attackMonster Exception: your selected weapon is broken!");
        return 1;
    }
    int lessedDamage = 0;
    int lessDamage = 0;

    if ( monster->armor != 0 ){
        float tmp = weapon->arme->degat;
        float tmp2 = monster->armor;
        lessDamage = tmp * (tmp2/100.0);
        lessedDamage = weapon->arme->degat - lessDamage;
    }
    else{
        lessedDamage = weapon->arme->degat;
    }

    if ( monster->pv <= lessedDamage ){
        monster->pv = 0;
        player->xp = player->xp + monster->xp_profit;
        printf("*** The monster died ***\n");
        return 0;
    }
    else{
        monster->pv = monster->pv - lessedDamage;
        printf("*** HEART ***\n");
        return 1;
    }
}

//---------// Initialize the player/ New game //---------// 

Object* init_inventor(Object* inventory){
    
    inventory = new_Object();
    
    inventory = addarme(inventory, ARME_TYPE, WOOD_SWORD);

    inventory = addOtherObject(inventory, OUTIL_TYPE,WOODEN_PICKAXE);
    inventory = addOtherObject(inventory, OUTIL_TYPE,WOODEN_SERPE);
    inventory = addOtherObject(inventory, OUTIL_TYPE,WOODEN_AX);
    
    return inventory;
}

Player* init_player(){
    Player* p = malloc(sizeof(Player));

    p->inventory = init_inventor(p->inventory);
    p->xp = 0;
    p->level = 1;
    p->hp_current = 100;
    p->hp_max = 100;
      
    return p;
}



int main(){

    Player* p = init_player();
    print_inventory(p->inventory);
    int i = collectRessourceAndToolUpdate(p->inventory, FIR, 3, 1);
    i = collectRessourceAndToolUpdate(p->inventory, STONE, 2, 1);
    i = collectRessourceAndToolUpdate(p->inventory, STONE, 2, 1);
    print_inventory(p->inventory);

    // printf("Player before the attack\n\n");
    // print_player(p);
    // print_inventory(p->inventory);
    // selectObject(p->inventory, DIAMOND_HAMMER);
    // printf("\n\n");
    // p->inventory->isSelected = SELECTED;
    // p->inventory = craftObject(p->inventory,WOODEN_PICKAXE);
    // print_inventory(p->inventory);

    // Monster* monster1 = malloc(sizeof(Monster));
    // monster1->degats = 30;
    // monster1->armor = 0;
    // monster1->pv = 100;
    // monster1->xp_profit = 25;

    // attackMonster(p, monster1);
    // receiveDamage(p, monster1);

    // printf("Player after the attack and monsters pv= %d\n\n", monster1->pv);
    // print_player(p);

    // Object* chest = new_Object();
    // print_inventory(chest);
    // print_inventory(p->inventory);

    // printf("en ajoutant dans chest\n\n");
    // Object** doubleinventory = addObjectToChest(p->inventory, chest, DIAMOND_HAMMER);
    // chest = doubleinventory[0];
    // p->inventory = doubleinventory[1];
    // print_inventory(chest);
    // print_inventory(p->inventory);

    // printf("en ajoutant dans inventory\n\n");
    // doubleinventory = getObjectFromChest(chest,p->inventory, DIAMOND_HAMMER);
    // chest = doubleinventory[1];
    // p->inventory = doubleinventory[0];
    // print_inventory(chest);
    // print_inventory(p->inventory);

    return 0;

}