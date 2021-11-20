
#include "structures.c"

Object* initTestInventory1(){
    Object* inventory = new_Object();

    inventory->type = ARME_TYPE;
    inventory->arme = getDBArme(WOOD_SWORD);
    inventory->isSelected = SELECTED;

    inventory->next = new_Object();
    inventory->next->type = OUTIL_TYPE;
    inventory->next->category = AX_CATEGORY;
    inventory->next->outil = getDBOutils(IRON_AX);

    return inventory;
}

Object* initTestInventory2(){
    Object* inventory = new_Object();
    inventory->type = ARME_TYPE;
    inventory->arme = getDBArme(WOOD_SWORD);
    inventory->category = SWORD_CATEGORY;

    inventory->next = new_Object();
    inventory->next->type = ARME_TYPE;
    inventory->next->arme = getDBArme(IRON_SWORD);

    inventory->next->next = new_Object();
    inventory->next->next->type = RDC_TYPE;
    inventory->next->next->ressource_de_craft = getDBRDC(LAVENDER);

    return inventory;
}

Object* initTestInventory3(){
    Object* inventory = new_Object();
    inventory->type = ARME_TYPE;
    inventory->arme = getDBArme(WOOD_SWORD);
    inventory->category = SWORD_CATEGORY;
    inventory->isSelected = NOT_SELECTED;

    inventory->next = new_Object();
    inventory->next->type = ARMURE_TYPE;
    inventory->next->armure = getDBArmure(IRON_CHESTPLATE);

    inventory->next->next = new_Object();
    inventory->next->next->type = RDC_TYPE;
    inventory->next->next->ressource_de_craft = getDBRDC(LAVENDER);
    inventory->next->next->ressource_de_craft->quantity = 3;

    return inventory;
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


Player* initTestPlayer1(){
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

void initTestPrintInventory(){
    printf("Armor n°22 Resistance: 20\n");
    printf("Ressource n°18 quantity: 3\n");
}

void startTreatmentLog(){
    printf("\n\n---------- Test Treatment ----------\n\n");
    printf("\n---- Test Treatment started...\n");
}

void finishedTreatmentLog(){
    printf("\n---- Test Treatment finished");
    printf("\n\n------------------------------------\n\n");
    printf("\n\n");
}

void freeObject(Object* object){
    free(object->arme);
    free(object->armure);
    free(object->next);
    free(object->outil);
    free(object->ressource_de_craft);
    free(object->soin);
    free(object);
}

void testPrintPlayer(){
    printf("----*Player Descriptions*----\n");
    printf("-- XP: 0\n");
    printf("-- Level: 1\n");
    printf("-- HP_CURRENT: 100\n");
    printf("-- HP_MAX: 100\n");
    printf("----*----*----*----*----*----\n\n");
}

    //---------// Test New Object Creator //---------// 

void testNewObjectCreatorfunctions(){
    printf("//---------// Test New Object Creator //---------//\n");

    startTreatmentLog();

    Obj_Arme* epeeEnDiamant = new_arme( DIAMOND_SWORD,  10,  10);
    Obj_Armure* armureEnDiamant = new_armure( DIAMOND_CHESTPLATE,  10);
    Obj_Outil* serpeEnFer = new_outil( IRON_SERPE,  10);
    Obj_Ressource_de_craft* lavande = new_ressource_de_craft( LAVENDER);
    Obj_Soin* soin1 = new_soin( HEAL1,  10);
    Object* objet = new_Object();

    finishedTreatmentLog();

    printf("--Test new_arme function...                                     Result: %d\n",epeeEnDiamant!=NULL);
    printf("--Test new_armure function...                                   Result: %d\n",armureEnDiamant!=NULL);
    printf("--Test new_outil function...                                    Result: %d\n",serpeEnFer!=NULL);
    printf("--Test new_ressource_de_craft function...                       Result: %d\n",lavande!=NULL);
    printf("--Test new_soin function...                                     Result: %d\n",soin1!=NULL);
    printf("--Test new_Object function...                                   Result: %d\n",objet!=NULL);
    printf("\n\n");
    free(epeeEnDiamant);
    free(armureEnDiamant);
    free(serpeEnFer);
    free(lavande);
    free(soin1);
    free(objet);
}

    //---------// Object data base //---------// 

void testObjectDataBasefunctions(){
    printf("//---------// Test Object data base Functions //---------//\n");

    startTreatmentLog();

    Object** list_of_object = Object_list();

    finishedTreatmentLog();

    printf("--Test Object_list function...                                  Result: %d\n",list_of_object!=NULL);
    for (int i=0; i<34; i++){
        printf("--Test Object_list function element n°%d...                     Result: %d\n",i+1,list_of_object[i]!=NULL);
        free(list_of_object[i]);
    }
    free(list_of_object);
    printf("\n\n");
}

    //---------// Getter Object from data base //---------//

void testGetterObjectFromDataBasefunctions(){
    printf("//---------// Test Getter Object from data base Functions //---------//\n");

    startTreatmentLog();

    Obj_Arme* epeeEnDiamant = getDBArme(DIAMOND_SWORD);
    Obj_Armure* armureEnDiamant = getDBArmure(DIAMOND_CHESTPLATE);
    Obj_Outil* serpeEnFer = getDBOutils(IRON_SERPE);
    Obj_Ressource_de_craft* lavande = getDBRDC(LAVENDER);
    Obj_Soin* soin1 = getDBSoin(HEAL1);
    Object* objet1 = getDBObject(ARME_TYPE, DIAMOND_SWORD);
    Object* objet2 = getDBObject(ARMURE_TYPE, DIAMOND_CHESTPLATE);
    Object* objet3 = getDBObject(OUTIL_TYPE, IRON_SERPE);
    Object* objet4 = getDBObject(RDC_TYPE, LAVENDER);
    Object* objet5 = getDBObject(SOIN_TYPE, HEAL1);
    int serpeEnFerType = getDBObjectType(IRON_SERPE);
    int serpeEnFerCategory = getDBObjectCategory(IRON_SERPE);

    finishedTreatmentLog();

    printf("--Test getDBArme function...                                    Result: %d\n",epeeEnDiamant!=NULL);
    printf("--Test getDBArmure function...                                  Result: %d\n",armureEnDiamant!=NULL);
    printf("--Test getDBOutils function...                                  Result: %d\n",serpeEnFer!=NULL);
    printf("--Test getDBRDC function...                                     Result: %d\n",lavande!=NULL);
    printf("--Test getDBSoin function...                                    Result: %d\n",soin1!=NULL);
    printf("--Test getDBObject objet1 function...                           Result: %d\n",objet1!=NULL);
    printf("--Test getDBObject objet2 function...                           Result: %d\n",objet2!=NULL);
    printf("--Test getDBObject objet3 function...                           Result: %d\n",objet3!=NULL);
    printf("--Test getDBObject objet4 function...                           Result: %d\n",objet4!=NULL);
    printf("--Test getDBObject objet5 function...                           Result: %d\n",objet5!=NULL);
    printf("--Test getDBObjectType function...                              Result: %d\n",serpeEnFerType==OUTIL_TYPE);
    printf("--Test getDBObjectCategory function...                          Result: %d\n",serpeEnFerCategory==SERPE_CATEGORY);
    printf("\n\n");
    free(epeeEnDiamant);
    free(armureEnDiamant);
    free(serpeEnFer);
    free(lavande);
    free(soin1);
    freeObject(objet1);
    freeObject(objet2);
    freeObject(objet3);
    freeObject(objet4);
    freeObject(objet5);
}

    //---------// Search objects functions //---------// 

void testSearchObjectfunctions(){
    printf("//---------//Test Search objects functions //---------//\n");

    startTreatmentLog();

    Object* inventory = initTestInventory1();
    printf("\n\n");
    Object* isObjectId = searchObjectById(inventory,WOOD_SWORD);
    Object* isNotObjectId = searchObjectById(inventory,DIAMOND_SWORD);
    Object* isObjectType = searchObjectByType(inventory, ARME_TYPE);
    Object* isNotObjectType = searchObjectByType(inventory, RDC_TYPE);
    Object* isSelectedObjectType = searchSelectedObjectByType(inventory, ARME_TYPE);
    Object* isNotSelectedObjectType = searchSelectedObjectByType(inventory, ARMURE_TYPE);
    Object* isObjectCategory = searchObjectByCategory(inventory, AX_CATEGORY);
    Object* isNotObjectCategory = searchObjectByCategory(inventory, SERPE_CATEGORY);

    finishedTreatmentLog();

    printf("--Test searchObjectById with existent function...               Result: %d\n",isObjectId!=NULL);
    printf("--Test searchObjectById with non-existent function...           Result: %d\n",isNotObjectId==NULL);
    printf("--Test searchObjectByType with existent function...             Result: %d\n",isObjectType!=NULL);
    printf("--Test searchObjectByType with non-existent function...         Result: %d\n",isNotObjectType==NULL);
    printf("--Test searchSelectedObjectByType with existent function...     Result: %d\n",isSelectedObjectType!=NULL);
    printf("--Test searchSelectedObjectByType with non-existent function... Result: %d\n",isNotSelectedObjectType==NULL);
    printf("--Test searchObjectByCategory with existent function...         Result: %d\n",isObjectCategory!=NULL);
    printf("--Test searchObjectByCategory with non-existent function...     Result: %d\n",isNotObjectCategory==NULL);
    printf("\n\n");
    // freeObject(isObjectId);
    // freeObject(isObjectType);
    // freeObject(isSelectedObjectType);
    // freeObject(isObjectCategory);
    // freeObject(inventory);
}

    //---------// Check functions //---------// 

void testCheckfunctions(){
    printf("//---------//Test Check functions //---------// \n");

    startTreatmentLog();

    Object* inventory = initTestInventory2();
    
    printf("\n");
    int size = inventorySize(inventory);
    int nbArme = countInventoryArme(inventory);
    Object* rdcQuantity = quantityRDCInc(inventory,RDC_TYPE, LAVENDER);
    int isInArme = isArmeInInventory(inventory,ARME_TYPE, IRON_SWORD);
    int isNotInArme = isArmeInInventory(inventory,ARME_TYPE, STONE_SWORD);

    finishedTreatmentLog();

    printf("--Test inventorySize function...                                Result: %d\n",size==3);
    printf("--Test countInventoryArme function...                           Result: %d\n",nbArme==2);
    printf("--Test isArmeInInventory with existent object function...       Result: %d\n",isInArme==1);
    printf("--Test isArmeInInventory with non-existent object function...   Result: %d\n",isNotInArme==0);
    printf("--Test quantityRDCInc function... Result: %d\n",rdcQuantity!=NULL);
    printf("\n\n");
    // free(inventory->next->next);
    // free(inventory->next);
    // free(inventory);
    // free(rdcQuantity);
}

//---------// Object Getters from inventory functions //---------// 
void testObjectGettersFromInventoryFuntions(){
    printf("//---------//Test Object Getters from inventory functions //---------//\n");

    startTreatmentLog();

    Object* inventory = new_Object();
    Object* isNotPiocheFer = getPickaxe(inventory);
    inventory->type = OUTIL_TYPE;
    inventory->category = PICKAXE_CATEGORY;
    inventory->outil = getDBOutils(IRON_PICKAXE);
    Object* isPiocheFer = getPickaxe(inventory);

    Object* isNotHacheFer = getAx(inventory);
    inventory->next = new_Object();
    inventory->next->type = OUTIL_TYPE;
    inventory->next->category = AX_CATEGORY;
    inventory->next->outil = getDBOutils(IRON_AX);
    Object* isHacheFer = getAx(inventory);

    Object* isNotSerpeFer = getSerpe(inventory);
    inventory->next->next = new_Object();
    inventory->next->next->type = OUTIL_TYPE;
    inventory->next->category = SERPE_CATEGORY;
    inventory->next->next->outil = getDBOutils(IRON_SERPE);
    Object* isSerpeFer = getSerpe(inventory);
    
    inventory->next->next->next = new_Object();
    inventory->next->next->next->type = ARME_TYPE;
    inventory->next->next->next->isSelected = NOT_SELECTED;
    Object* isNotEpeeBois = getSelectedWeapon(inventory);
    inventory->next->next->next->arme = getDBArme(WOOD_SWORD);
    inventory->next->next->next->isSelected = SELECTED;
    Object* isEpeeBois = getSelectedWeapon(inventory);

    Player* p = malloc(sizeof(Player));
    p = initTestPlayer1();
    p = useHealPotion(p, HEAL2);

    finishedTreatmentLog();

    printf("--Test getPickaxe with non-existent object function...          Result: %d\n",isNotPiocheFer==NULL);
    printf("--Test getPickaxe with existent object function...              Result: %d\n",isPiocheFer!=NULL);
    printf("--Test getAx with non-existent object function...               Result: %d\n",isNotHacheFer==NULL);
    printf("--Test getAx with existent object function...                   Result: %d\n",isHacheFer!=NULL);
    printf("--Test getSerpe with non-existent object function...            Result: %d\n",isNotSerpeFer==NULL);
    printf("--Test getSerpe with existent object function...                Result: %d\n",isSerpeFer!=NULL);
    printf("--Test getSelectedWeapon with existent object function...       Result: %d\n",isNotEpeeBois==NULL);
    printf("--Test getSelectedWeapon with non-existent object function...   Result: %d\n",isEpeeBois!=NULL);
    printf("--Test useHealPotion function...                                Result: %d\n",p->hp_current==100);
    printf("\n\n");
    free(isPiocheFer);
    free(isHacheFer);
    free(isEpeeBois);
    free(p);
}

    //---------// Utils functions //---------// 
void testUtilsFuntions(){
    printf("//---------// Test Utils Functions //---------//\n");

    startTreatmentLog();

    Object* inventory = initTestInventory3();

    Object* isNotSelectObject = searchSelectedObjectByType(inventory,ARME_TYPE);
    inventory = selectObject(inventory, WOOD_SWORD);
    Object* isSelectObject = searchSelectedObjectByType(inventory,ARME_TYPE);

    inventory = deleteObject(inventory, WOOD_SWORD);
    Object* isDeletedObject = searchObjectById(inventory, WOOD_SWORD);
    Object* isNotDeletedObject = deleteObject(inventory, DIAMOND_SWORD);

    Player* player = initTestPlayer1();

    print_inventory(inventory);
    print_player(player);

    finishedTreatmentLog();

    printf("--Test selectObject with non-existent object function...        Result: %d\n",isNotSelectObject==NULL);
    printf("--Test selectObject with existent object function...            Result: %d\n",isSelectObject!=NULL);
    printf("--Test deleteObject with non-existent object function...        Result: %d\n",isDeletedObject==NULL);
    printf("--Test deleteObject with existent object function...            Result: %d\n",isNotDeletedObject==inventory);
    printf("\n");
    printf("--Test print_inventory function...\n\n");
    printf("--Please check if you have the same printing in the traitment as after\n");
    initTestPrintInventory();
    printf("\n");
    printf("--Test print_inventory function...\n\n");
    printf("--Please check if you have the same printing in the traitment as after\n");
    testPrintPlayer();
    printf("\n\n");
    // free(inventory);
    // free(isNotSelectObject);
    // free(isSelectObject);
    // free(isDeletedObject);
    // free(player);
}



    //---------// Add object in Inventory Functions //---------// 
void testAddObjectInInventoryFunctions(){
    printf("//---------// Test Add object in Inventory Functions //---------//\n");

    startTreatmentLog();

    Object* inventory = initTestInventory4();
    inventory = addarme(inventory, ARME_TYPE, STONE_SWORD);
    Object* isAddedWeapon = searchObjectById(inventory,STONE_SWORD);
    inventory = addcraft(inventory,RDC_TYPE, LAVENDER);
    Object* isAddedCraft = searchObjectById(inventory,LAVENDER);
    inventory = addOtherObject(inventory, OUTIL_TYPE, STONE_AX);
    Object* isAddedObject = searchObjectById(inventory, STONE_AX);
    inventory = appendNewObject(inventory, STONE_SWORD);
    Object* isAppendObject = searchObjectById(inventory, STONE_SWORD);

    int addarmeCondition = isAddedWeapon!=NULL;
    int addcraftCondition = isAddedCraft!=NULL;
    int addOtherObjectCondition = isAddedObject!=NULL;;
    int appendNewObjectCondition = isAppendObject!=NULL;;

    finishedTreatmentLog();

    printf("--Test addarme function...                                      Result: %d\n",addarmeCondition);
    printf("--Test addcraft function...                                     Result: %d\n",addcraftCondition);
    printf("--Test addOtherObject function...                               Result: %d\n",addOtherObjectCondition);
    printf("--Test appendNewObject function...                              Result: %d\n",appendNewObjectCondition);
    printf("\n\n");
}

    //---------// Update Weapon or Tool Functions //---------//

void testUpdateWeaponOrToolFunctions(){
    printf("//---------// Test Update Weapon or Tool Functions //---------//\n");

    startTreatmentLog();

    Object* inventory = initTestInventory4();
    
    inventory = addUpdatedObjectType(inventory, STONE_SWORD);
    int UpdatedCondition = searchObjectById(inventory,WOOD_SWORD)==NULL && searchObjectById(inventory, STONE_SWORD)!= NULL;
    // printf("UpdatedCondition: %d\n",UpdatedCondition);

    inventory = addUpdatedObjectType(inventory, WOOD_SWORD);
    int ReplacedCondition =  searchObjectById(inventory,WOOD_SWORD)!=NULL && searchObjectById(inventory, STONE_SWORD)==NULL;
    // printf("ReplacedCondition: %d searchObjectById(inventory,WOOD_SWORD)!=NULL: %d\n",ReplacedCondition,searchObjectById(inventory,WOOD_SWORD)!=NULL);
    // printf("ReplacedCondition: %d searchObjectById(inventory, STONE_SWORD)==NULL: %d\n",ReplacedCondition,searchObjectById(inventory, STONE_SWORD)==NULL);

    Object* isCreatedMarteauPierre = addUpdatedObjectType(inventory, STONE_HAMMER);
    inventory = addUpdatedObjectType(inventory, STONE_HAMMER);
    int CreationNewCondition = searchObjectById(inventory,STONE_HAMMER)!=NULL;
    // printf("CreationNewCondition: %d\n",CreationNewCondition);
    finishedTreatmentLog();

    printf("--Test addUpdatedObjectType function...                        Result: %d\n",UpdatedCondition && ReplacedCondition && CreationNewCondition);

    // Object* addUpdatedObjectType(Object* inventory, int objectId);

    printf("\n\n");
}

    //---------// Initialize the player/ New game Functions//---------// 

void testInitializePlayer_NewGame(){
    printf("//---------// Initialize the player/ New game //---------//\n");
    printf("\n\n");

    startTreatmentLog();

    Player* player = init_player();
    Object* inventory = inventory = init_inventor(inventory);
    printf("\n\n");

    finishedTreatmentLog();

    printf("--Test init_player function...                                  Result: %d\n",player!=NULL);
    printf("--Test init_inventor function...                                Result: %d\n",inventory!=NULL);
    printf("\n\n");
}

    //---------// Crafting Recipes Data Base Functions//---------// 
void testCraftRecipesDataBaseFunctions(){
    printf("//---------// Test Crafting Recipes Data Base Functions //---------//\n");

    startTreatmentLog();

    int* craftRecipe1 = craftWeaponRecipe(WOOD_SWORD);
    int* craftRecipe2 = craftArmorRecipe(IRON_CHESTPLATE);
    int* craftRecipe3 = craftToolRecipe(IRON_AX);
    int* craftRecipe4 = craftSoinRecipe(HEAL2);
    int* craftRecipe5 = craftObjectRecipe(DIAMOND_HAMMER);

    finishedTreatmentLog();

    printf("--Test craftWeaponRecipe function...                            Result: %d\n",craftRecipe1!=NULL);
    printf("--Test craftArmorRecipe function...                             Result: %d\n",craftRecipe2!=NULL);
    printf("--Test crafToolRecipe function...                               Result: %d\n",craftRecipe3!=NULL);
    printf("--Test crafSoinRecipe function...                               Result: %d\n",craftRecipe4!=NULL);
    printf("--Test craftObjectRecipe function...                            Result: %d\n",craftRecipe5!=NULL);
    printf("\n\n");
    free(craftRecipe1);
    free(craftRecipe2);
    free(craftRecipe3);
    free(craftRecipe4);
    free(craftRecipe5);
}

    //---------// Repair and Craft Functions//---------// 
void testRepairAndCraftFunctions(){
    printf("//---------// Test Repair and Craft Functions //---------//\n");

    startTreatmentLog();

    Object* inventory = initTestInventory4();
    inventory->arme->durabilite = 5;
    inventory->next->outil->durabilite = 3;
    inventory = repairAllObject(inventory);
    int areRepairedCondition = (inventory->arme->durabilite==10)&&(inventory->next->outil->durabilite==10);
    inventory = craftObject(inventory, STONE_SPEAR);
    
    Object* isCraftedObject = searchObjectById(inventory,STONE_SPEAR);
    inventory = craftObject(inventory, DIAMOND_SWORD);
    Object* isNotCraftedObject = searchObjectById(inventory,DIAMOND_HAMMER);

    finishedTreatmentLog();

    printf("--Test repairAllObject function... Result: %d\n",areRepairedCondition);
    printf("--Test craftObject with craftable object function...            Result: %d\n",isCraftedObject!=NULL);
    printf("--Test craftObject with uncraftable object function...          Result: %d\n",isNotCraftedObject==NULL);
    printf("\n\n");
    // freeObject(isCraftedObject);
    // freeObject(inventory);
}

    //---------// Modify Object Properties Functions //---------// 
void testModifyObjectPropertiesFunctions(){
    printf("//---------// Test Modify Object Properties Functions //---------//\n");

    startTreatmentLog();

    Object* isNotIninventory = malloc(sizeof(Object));
    isNotIninventory = new_Object();
    isNotIninventory = collectCrafts(isNotIninventory, 5, LAVENDER);
    Object* isIninventory = malloc(sizeof(Object));
    isIninventory = new_Object();
    isIninventory = addcraft(isIninventory, RDC_TYPE, LAVENDER);
    isIninventory = collectCrafts(isIninventory, 4, LAVENDER);

    Object* inventory = initTestInventory1();
    Object* isLessedWeapon = getSelectedWeapon(inventory);
    isLessedWeapon = lessObjectCapacity(isLessedWeapon, 5);
    int lessedWeaponCondition1 = isLessedWeapon->arme->durabilite==5;
    isLessedWeapon = lessObjectCapacity(isLessedWeapon, 5);
    int lessedWeaponCondition2 = isLessedWeapon->arme->durabilite==0;
    int lessedWeaponCondition = lessedWeaponCondition1 && lessedWeaponCondition2;



    Object* isLessedTool = getAx(inventory);
    isLessedTool = lessObjectCapacity(isLessedTool, 5);
    int isLessedToolCondition1 = inventory->next->outil->durabilite==5;
    isLessedTool = lessObjectCapacity(isLessedTool, 5);
    int isLessedToolCondition2 = inventory->next->outil->durabilite==0;
    int isLessedToolCondition = isLessedToolCondition1 && isLessedToolCondition2;

    finishedTreatmentLog();

    printf("--Test collectCrafts with non-existent craft function...        Result: %d\n",isNotIninventory->ressource_de_craft->quantity==5);
    printf("--Test collectCrafts with 1 existent craft function...          Result: %d\n",isIninventory->ressource_de_craft->quantity==5);
    printf("--Test lessObjectCapacity with weapon function...               Result: %d\n",lessedWeaponCondition);
    printf("--Test lessObjectCapacity with tool function...                 Result: %d\n",isLessedToolCondition);
    printf("\n\n");
    free(isNotIninventory);
    free(isIninventory);
}


    
int main(){

    testNewObjectCreatorfunctions();
    testObjectDataBasefunctions();
    testGetterObjectFromDataBasefunctions();
    testSearchObjectfunctions();
    testCheckfunctions();
    testObjectGettersFromInventoryFuntions();
    testUtilsFuntions();
    testUpdateWeaponOrToolFunctions();
    testAddObjectInInventoryFunctions();
    testInitializePlayer_NewGame();
    testCraftRecipesDataBaseFunctions();
    testRepairAndCraftFunctions();
    testModifyObjectPropertiesFunctions();

    return 0;
}

//For Nicolas

// void receiveDamage(Player* player, Monster* monster){
//     Object* armor = searchObjectByType(player->inventory, ARMURE_TYPE);
//     int lessedDamage = 0;
//     int lessDamage = 0;
//     if ( armor == NULL){
//         printf("***SearchObjectByType Exception: This object is not in your inventory!")
//          return;
//     }
//     lessDamage = monster->degat*(armor->armure->resistance/100);
//     lessedDamage = monster->degat - lessDamage;

//     if ( player->hp_current < lessedDamage ){
//         player->hp_current = 0;
//         printf("*** The player died ***\n");
//     }
//     else{
//         player->hp_current = player->hp_current - lessedDamage;
//         printf("*** HEART ***\n");
//     }
// }

// void attackMonster(Player* player, Monster* monster){
//     // Object* armor = searchObjectByType(player->inventory, ARMURE_TYPE);
//     // int lessedDamage = 0;
//     // int lessDamage = 0;
//     // if ( armor != NULL ){
//     //     lessDamage = monster->degat*(armor->armure->resistance/100);
//     // }

//     int lessedDamage = 0;
//     int lessDamage = 0;

//     Object* weapon = searchObjectByType(player->inventory, ARME_TYPE);
//     if ( weapon != NULL ){
//        printf("***SearchObjectByType Exception: This object is not in your inventory!")
//      return;
//      }

//     lessDamage = weapon->arme->degat*(monster->armor/100);

//     lessedDamage = weapon->arme->degat - lessDamage;

//     if ( player->hp_current < lessedDamage ){
//         player->hp_current = 0;
//         printf("*** The player died ***\n");
//     }
//     else{
//         player->hp_current = player->hp_current - lessedDamage;
//         printf("*** HEART ***\n");
//     }
// }

