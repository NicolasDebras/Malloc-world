#include "malloc_world.h"

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
     /* 
    Get an object from the chest to the inventory by the object id
    Parameters: 
        - Fistsly the chest (source)
        - Secondly the inventory (destination)
        - at last the object id
    Returns a table pour object two object list:
        - at first the inventory
        - and at second the chest
    */
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
        printf("***Craft object exception:Craft n??%d has been deleted\n", objectRecipe[0]);
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
            printf("***Craft object exception:Craft n??%d has been deleted\n",objectRecipe[2]);
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

int receiveDamage(Player* player, monster* monster){
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
        printf("*** HEART Player ***\n");
        return 1;
    }
}

int attackMonster(Player* player, monster* monster){
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
        weapon->arme->durabilite = weapon->arme->durabilite -1;
        printf("*** The monster died ***\n");
        return 0;
    }
    else{
        monster->pv = monster->pv - lessedDamage;
        weapon->arme->durabilite = weapon->arme->durabilite -1;
        printf("*** HEART Monster ***\n");
        return 1;
    }
}

void updatePlayerHpWithLevel(Player* p){
    int current_level = p->level;
    if ( current_level == 2 ){
        p->hp_current = p->hp_max;
        p->hp_max = p->hp_max +10; 
    }
    else if ( current_level == 3 ){
        p->hp_current = p->hp_max;
        p->hp_max = p->hp_max +20;
    }
    else if ( current_level == 4 ){
        p->hp_current = p->hp_max;
        p->hp_max = p->hp_max +30;
    }
    else if ( current_level == 5 ){
        p->hp_current = p->hp_max;
        p->hp_max = p->hp_max +40;
    }
    else if ( current_level >= 6 & current_level <= 8){
        p->hp_current = p->hp_max;
        p->hp_max = p->hp_max +50;
    }
    else if ( current_level == 9 || current_level == 10 ){
        p->hp_current = p->hp_max;
        p->hp_max = p->hp_max +75;
    }
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
    
    
    int objectQuantity = 0;
    int objectId = 0;

    while( !feof(f) ){

        fscanf(f,"{%d}@{%d}\n",&objectQuantity,
            &objectId);

        int objectType = getDBObjectType(objectId);
        
        chest = addObject(chest, objectId, objectType);
        Object* tmp = chest;

        while ( tmp!=NULL ){
            if ( tmp->ressource_de_craft->objectId == objectId ){
                tmp->ressource_de_craft->quantity = 20;
            }
            tmp = tmp->next;
        }
    }
    fclose(f);
    return chest;
}