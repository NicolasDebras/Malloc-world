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
// Object** Object_list(){
//     Object** LIST_Object = malloc(34*sizeof(Object*));
//     for (int i=0; i<34; i++){
//         LIST_Object[i] = new_Object();
//     }

//     LIST_Object[0]->type = ARME_TYPE;
//     LIST_Object[0]->category = SWORD_CATEGORY;
//     LIST_Object[0]->isSelected = NOT_SELECTED;
//     LIST_Object[0]->arme = new_arme(WOOD_SWORD,1,10);

//     LIST_Object[1]->type = OUTIL_TYPE;
//     LIST_Object[1]->category = PICKAXE_CATEGORY;
//     LIST_Object[1]->isSelected = NOT_SELECTED;
//     LIST_Object[1]->outil = new_outil(WOODEN_PICKAXE,10);
//     LIST_Object[2]->type = OUTIL_TYPE;
//     LIST_Object[2]->category = SERPE_CATEGORY;
//     LIST_Object[2]->isSelected = NOT_SELECTED;
//     LIST_Object[2]->outil = new_outil(WOODEN_SERPE,10);
//     LIST_Object[3]->type = OUTIL_TYPE;
//     LIST_Object[3]->category = AX_CATEGORY;
//     LIST_Object[3]->isSelected = NOT_SELECTED;
//     LIST_Object[3]->outil = new_outil(WOODEN_AX,10);
//     LIST_Object[4]->type = RDC_TYPE;
//     LIST_Object[4]->ressource_de_craft = new_ressource_de_craft(FIR);
//     LIST_Object[5]->type = RDC_TYPE;
//     LIST_Object[5]->ressource_de_craft = new_ressource_de_craft(STONE);
//     LIST_Object[6]->type = RDC_TYPE;
//     LIST_Object[6]->ressource_de_craft = new_ressource_de_craft(GRASS);

//     LIST_Object[7]->type = ARME_TYPE;
//     LIST_Object[7]->category = SWORD_CATEGORY;
//     LIST_Object[7]->isSelected = NOT_SELECTED;
//     LIST_Object[7]->arme = new_arme(STONE_SWORD,2,10);
//     LIST_Object[8]->type = ARME_TYPE;
//     LIST_Object[8]->category = SPEAR_CATEGORY;
//     LIST_Object[8]->isSelected = NOT_SELECTED;
//     LIST_Object[8]->arme = new_arme(STONE_SPEAR,3,8);
//     LIST_Object[9]->type = ARME_TYPE;
//     LIST_Object[9]->category = HAMMER_CATEGORY;
//     LIST_Object[9]->isSelected = NOT_SELECTED;
//     LIST_Object[9]->arme = new_arme(STONE_HAMMER,4,5);

//     LIST_Object[10]->type = ARMURE_TYPE;
//     LIST_Object[10]->isSelected = NOT_SELECTED;
//     LIST_Object[10]->armure = new_armure(STONE_CHESTPLATE,10);
//     LIST_Object[11]->type = OUTIL_TYPE;
//     LIST_Object[11]->category = PICKAXE_CATEGORY;
//     LIST_Object[11]->isSelected = NOT_SELECTED;
//     LIST_Object[11]->outil = new_outil(STONE_PICKAXE,10);
//     LIST_Object[12]->type = OUTIL_TYPE;
//     LIST_Object[12]->category = SERPE_CATEGORY;
//     LIST_Object[12]->isSelected = NOT_SELECTED;
//     LIST_Object[12]->outil = new_outil(STONE_SERPE,10);
//     LIST_Object[13]->type = OUTIL_TYPE;
//     LIST_Object[13]->category = AX_CATEGORY;
//     LIST_Object[13]->isSelected = NOT_SELECTED;
//     LIST_Object[13]->outil = new_outil(STONE_AX,10);
//     LIST_Object[14]->type = SOIN_TYPE;
//     LIST_Object[14]->soin = new_soin(HEAL1,30);
//     LIST_Object[15]->type = RDC_TYPE;
//     LIST_Object[15]->ressource_de_craft = new_ressource_de_craft(BEECH);
//     LIST_Object[16]->type = RDC_TYPE;
//     LIST_Object[16]->ressource_de_craft = new_ressource_de_craft(IRON);
//     LIST_Object[17]->type = RDC_TYPE;
//     LIST_Object[17]->ressource_de_craft = new_ressource_de_craft(LAVENDER);

//     LIST_Object[18]->type = ARME_TYPE;
//     LIST_Object[18]->category = SWORD_CATEGORY;
//     LIST_Object[18]->isSelected = NOT_SELECTED;
//     LIST_Object[18]->arme = new_arme(IRON_SWORD,5,10);
//     LIST_Object[19]->type = ARME_TYPE;
//     LIST_Object[19]->category = SPEAR_CATEGORY;
//     LIST_Object[19]->isSelected = NOT_SELECTED;
//     LIST_Object[19]->arme = new_arme(IRON_SPEAR,7,8);
//     LIST_Object[20]->type = ARME_TYPE;
//     LIST_Object[20]->category = HAMMER_CATEGORY;
//     LIST_Object[20]->isSelected = NOT_SELECTED;
//     LIST_Object[20]->arme = new_arme(IRON_HAMMER,4,5);
//     LIST_Object[21]->type = ARMURE_TYPE;
//     LIST_Object[21]->isSelected = NOT_SELECTED;
//     LIST_Object[21]->armure = new_armure(IRON_CHESTPLATE,20);
//     LIST_Object[22]->type = OUTIL_TYPE;
//     LIST_Object[22]->category = PICKAXE_CATEGORY;
//     LIST_Object[22]->isSelected = NOT_SELECTED;
//     LIST_Object[22]->outil = new_outil(IRON_PICKAXE,10);
//     LIST_Object[23]->type = OUTIL_TYPE;
//     LIST_Object[23]->category = SERPE_CATEGORY;
//     LIST_Object[23]->isSelected = NOT_SELECTED;
//     LIST_Object[23]->outil = new_outil(IRON_SERPE,10);
//     LIST_Object[24]->type = OUTIL_TYPE;
//     LIST_Object[24]->category = AX_CATEGORY;
//     LIST_Object[24]->isSelected = NOT_SELECTED;
//     LIST_Object[24]->outil = new_outil(IRON_AX,10);
//     LIST_Object[25]->type = SOIN_TYPE;
//     LIST_Object[25]->soin = new_soin(HEAL2,80);
//     LIST_Object[26]->type = RDC_TYPE;
//     LIST_Object[26]->ressource_de_craft = new_ressource_de_craft(OAK);
//     LIST_Object[27]->type = RDC_TYPE;
//     LIST_Object[27]->ressource_de_craft = new_ressource_de_craft(DIAMOND);
//     LIST_Object[28]->type = RDC_TYPE;
//     LIST_Object[28]->ressource_de_craft = new_ressource_de_craft(HEMP);

//     LIST_Object[29]->type = ARME_TYPE;
//     LIST_Object[29]->category = SWORD_CATEGORY;
//     LIST_Object[29]->isSelected = NOT_SELECTED;
//     LIST_Object[29]->arme = new_arme(DIAMOND_SWORD,10,10);
//     LIST_Object[30]->type = ARME_TYPE;
//     LIST_Object[30]->category = SPEAR_CATEGORY;
//     LIST_Object[30]->isSelected = NOT_SELECTED;
//     LIST_Object[30]->arme = new_arme(DIAMOND_SPEAR,15,8);
//     LIST_Object[31]->type = ARME_TYPE;
//     LIST_Object[31]->category = HAMMER_CATEGORY;
//     LIST_Object[31]->isSelected = NOT_SELECTED;
//     LIST_Object[31]->arme = new_arme(DIAMOND_HAMMER,20,5);
//     LIST_Object[32]->type = ARMURE_TYPE;
//     LIST_Object[32]->isSelected = NOT_SELECTED;
//     LIST_Object[32]->armure = new_armure(DIAMOND_CHESTPLATE,40);
//     LIST_Object[33]->type = SOIN_TYPE;
//     LIST_Object[33]->soin = new_soin(HEAL3,200);

//     return LIST_Object;
// }

 Object** Object_list(){
     Object** objectsList = malloc(34*sizeof(Object*));
    for (int i=0; i<34; i++){
        objectsList[i] = new_Object();
    }

    FILE* f = fopen("ObjectsDB.txt","r");

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

int* craftWeaponRecipe(int objectId){
    int craft1objectId = 0;
    int craft1Quantity = 1; 
    int craft2objectId = 2; 
    int craft2Quantity = 3;
    int* recipeDatas = malloc(4*sizeof(int));

    switch (objectId){   
        //SWORDS
        case WOOD_SWORD:
            recipeDatas[craft1objectId] = FIR;
            recipeDatas[craft1Quantity] = 3;
            recipeDatas[craft2objectId] = -1;
            recipeDatas[craft2Quantity] = -1;
            break;
        case STONE_SWORD:
            recipeDatas[craft1objectId] = FIR;
            recipeDatas[craft1Quantity] = 2;
            recipeDatas[craft2objectId] = STONE;
            recipeDatas[craft2Quantity] = 3;
            break;
        case IRON_SWORD:
            recipeDatas[craft1objectId] = BEECH;
            recipeDatas[craft1Quantity] = 2;
            recipeDatas[craft2objectId] = IRON;
            recipeDatas[craft2Quantity] = 4;
            break;
        case DIAMOND_SWORD:
            recipeDatas[craft1objectId] = OAK;
            recipeDatas[craft1Quantity] = 3;
            recipeDatas[craft2objectId] = DIAMOND;
            recipeDatas[craft2Quantity] = 5;
            break;
        //SPEARS
        case STONE_SPEAR:
            recipeDatas[craft1objectId] = FIR;
            recipeDatas[craft1Quantity] = 3;
            recipeDatas[craft2objectId] = STONE;
            recipeDatas[craft2Quantity] = 4;
            break;
        case IRON_SPEAR:
            recipeDatas[craft1objectId] = BEECH;
            recipeDatas[craft1Quantity] = 3;
            recipeDatas[craft2objectId] = IRON;
            recipeDatas[craft2Quantity] = 5;
            break;
        case DIAMOND_SPEAR:
            recipeDatas[craft1objectId] = OAK;
            recipeDatas[craft1Quantity] = 3;
            recipeDatas[craft2objectId] = DIAMOND;
            recipeDatas[craft2Quantity] = 6;
            break;
        //HAMMERS
        case STONE_HAMMER:
            recipeDatas[craft1objectId] = FIR;
            recipeDatas[craft1Quantity] = 2;
            recipeDatas[craft2objectId] = STONE;
            recipeDatas[craft2Quantity] = 6;
            break;
        case IRON_HAMMER:
            recipeDatas[craft1objectId] = BEECH;
            recipeDatas[craft1Quantity] = 2;
            recipeDatas[craft2objectId] = IRON;
            recipeDatas[craft2Quantity] = 7;
            break;
        case DIAMOND_HAMMER:
            recipeDatas[craft1objectId] = OAK;
            recipeDatas[craft1Quantity] = 2;
            recipeDatas[craft2objectId] = DIAMOND;
            recipeDatas[craft2Quantity] = 8;
            break;
    }
    return recipeDatas;
}

int* craftArmorRecipe(int objectId){
    int craft1objectId = 0;
    int craft1Quantity = 1; 
    int craft2objectId = 2; 
    int craft2Quantity = 3;
    int* recipeDatas = malloc(4*sizeof(int));

    switch (objectId){
        //CHESTPLATES
        case STONE_CHESTPLATE:
            recipeDatas[craft1objectId] = STONE;
            recipeDatas[craft1Quantity] = 10;
            recipeDatas[craft2objectId] = -1;
            recipeDatas[craft2Quantity] = -1;
            break;
        case IRON_CHESTPLATE:
            recipeDatas[craft1objectId] = IRON;
            recipeDatas[craft1Quantity] = 12;
            recipeDatas[craft2objectId] = -1;
            recipeDatas[craft2Quantity] = -1;
            break;
        case DIAMOND_CHESTPLATE:
            recipeDatas[craft1objectId] = DIAMOND;
            recipeDatas[craft1Quantity] = 16;
            recipeDatas[craft2objectId] = -1;
            recipeDatas[craft2Quantity] = -1;
            break;
    }
    return recipeDatas;
}

int* craftToolRecipe(int objectId){
    int craft1objectId = 0;
    int craft1Quantity = 1; 
    int craft2objectId = 2; 
    int craft2Quantity = 3;
    int* recipeDatas = malloc(4*sizeof(int));

    if ( objectId == WOODEN_PICKAXE || objectId == WOODEN_AX|| objectId == WOODEN_SERPE){
        recipeDatas[craft1objectId] = FIR;
        recipeDatas[craft1Quantity] = 3;
        recipeDatas[craft2objectId] = -1;
        recipeDatas[craft2Quantity] = -1;
    }
    else if ( objectId == STONE_PICKAXE || objectId == STONE_AX|| objectId == STONE_SERPE){
        recipeDatas[craft1objectId] = FIR;
        recipeDatas[craft1Quantity] = 2;
        recipeDatas[craft2objectId] = STONE;
        recipeDatas[craft2Quantity] = 3;
    }
    else if ( objectId == IRON_PICKAXE || objectId == IRON_AX|| objectId == IRON_SERPE){
        recipeDatas[craft1objectId] = BEECH;
        recipeDatas[craft1Quantity] = 2;
        recipeDatas[craft2objectId] = IRON;
        recipeDatas[craft2Quantity] = 4;
    }
    return recipeDatas; 
}

int* craftSoinRecipe(int objectId ){
    int craft1objectId = 0;
    int craft1Quantity = 1; 
    int craft2objectId = 2; 
    int craft2Quantity = 3;
    int* recipeDatas = malloc(4*sizeof(int));

    if ( objectId == HEAL1 ){
        recipeDatas[craft1objectId] = GRASS;
        recipeDatas[craft1Quantity] = 3;
        recipeDatas[craft2objectId] = -1;
        recipeDatas[craft2Quantity] = -1;
    }
    else if ( objectId == HEAL2 ){
        recipeDatas[craft1objectId] = LAVENDER;
        recipeDatas[craft1Quantity] = 2;
        recipeDatas[craft2objectId] = -1;
        recipeDatas[craft2Quantity] = -1;
    }
    else if ( objectId == HEAL3 ){
        recipeDatas[craft1objectId] = HEMP;
        recipeDatas[craft1Quantity] = 2;
        recipeDatas[craft2objectId] = -1;
        recipeDatas[craft2Quantity] = -1;
    }
    return recipeDatas; 
}

int* craftObjectRecipe(int objectId){
    int objectType = getDBObjectType(objectId);

    switch (objectType)
    {
        case ARME_TYPE:
            return craftWeaponRecipe(objectId);
            break;
         case ARMURE_TYPE:
            return craftArmorRecipe(objectId);
            break;
        case OUTIL_TYPE:
            return craftToolRecipe(objectId);
            break;
        case SOIN_TYPE:
            return craftSoinRecipe(objectId);
            break;
        default:
            printf("***CraftObjectRecipe Exception: Incorrect objectId\n");
            return NULL;
            break;
    }
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
            printf("is ####\n");
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

//---------// Initialize the player/ New game //---------// 

Object* init_inventor(Object* inventory){
    
    inventory = new_Object();
    
    inventory = addarme(inventory, ARME_TYPE, IRON_SWORD);
    inventory = addOtherObject(inventory, ARMURE_TYPE,STONE_CHESTPLATE);

    inventory = addcraft(inventory, RDC_TYPE, FIR);
    inventory = addcraft(inventory, RDC_TYPE, FIR);
    inventory = addcraft(inventory, RDC_TYPE, FIR);

    inventory = addcraft(inventory, RDC_TYPE, BEECH);
    inventory = addcraft(inventory, RDC_TYPE, BEECH);

    inventory = addcraft(inventory, RDC_TYPE, IRON);
    inventory = addcraft(inventory, RDC_TYPE, IRON);
    inventory = addcraft(inventory, RDC_TYPE, IRON);
    inventory = addcraft(inventory, RDC_TYPE, IRON);

    inventory = addOtherObject(inventory, OUTIL_TYPE,IRON_PICKAXE);
    inventory = addOtherObject(inventory, OUTIL_TYPE,WOODEN_SERPE);
    inventory = addOtherObject(inventory, OUTIL_TYPE,WOODEN_AX);

    inventory = addOtherObject(inventory, SOIN_TYPE, HEAL1);
    
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


// int main(){

//     Player* p = init_player();
//     print_inventory(p->inventory);

//     printf("\n\n");
//     p->inventory->isSelected = SELECTED;
//     p->inventory = craftObject(p->inventory,WOODEN_PICKAXE);
//     print_inventory(p->inventory);
//     return 0;

// }