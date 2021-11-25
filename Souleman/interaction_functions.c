#include "structures.c"

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
    default:
        printf("***lessObject Capacity Exception: Cannot less the capacity of this object.\n");
        break;
    }
    return object;
}

int getToolForRessourceCollecte(Object* inventory, int objectIdToCollect, int mapZone){

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