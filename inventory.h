#include<stdio.h>
#include<stdlib.h>

#define ARME_TYPE 0
#define ARMURE_TYPE 1
#define OUTIL_TYPE 2
#define RDC_TYPE 3
#define SOIN_TYPE 4
#define SELECTED 1
#define NOT_SELECTED 0
#define ERROR_CODE 9999

//---------// ENUMERATIONS //---------// 

// Armes
typedef enum Arme{
    WOOD_SWORD = 1,
    STONE_SWORD = 8,
    STONE_SPEAR = 9,
    STONE_HAMMER = 10,
    IRON_SWORD = 19,
    IRON_SPEAR = 20,
    IRON_HAMMER = 21,
    DIAMOND_SWORD = 30,
    DIAMOND_SPEAR = 31,
    DIAMOND_HAMMER = 32
}Arme;

//Armure
typedef enum Armure{
    STONE_CHESTPLATE = 11,
    IRON_CHESTPLATE = 22,
    DIAMOND_CHESTPLATE = 33
}Armure;

//Outils
typedef enum Outil{
    WOODEN_PICKAXE = 2,
    WOODEN_SERPE = 3,
    WOODEN_AX = 4,
    STONE_PICKAXE = 12,
    STONE_SERPE = 13,
    STONE_AX = 14,
    IRON_PICKAXE = 23,
    IRON_SERPE = 24,
    IRON_AX = 25,
}Outil;

//Ressource craft
typedef enum Ressource_de_craft{
    FIR = 5,
    STONE = 6,
    GRASS = 7,
    BEECH = 16,
    IRON = 17,
    LAVENDER = 18,
    OAK = 27,
    DIAMOND = 28,
    HEMP = 29,
}Ressource_de_craft;

//Soins
typedef enum Soin{
    HEAL1 = 15,
    HEAL2 = 26,
    HEAL3 = 34
}Soin;

//---------// STRUCTURES //---------// 

typedef struct Obj_Arme{
    Arme objectId;
    int degat;
    int durabilite;
}Obj_Arme;

typedef struct Obj_Armure{
    Armure objectId;
    int resistance;
}Obj_Armure;

typedef struct Obj_Outil{
    Outil objectId;
    int durabilite;
}Obj_Outil;

typedef struct Obj_Ressource_de_craft{
    Ressource_de_craft objectId;
    int quantity;
}Obj_Ressource_de_craft;

typedef struct Obj_Soin{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    Soin objectId;
    int hp_heal;
}Obj_Soin;


typedef struct Object{
    Obj_Arme* arme;
    Obj_Armure* armure;
    Obj_Outil* outil;
    Obj_Ressource_de_craft* ressource_de_craft;
    Obj_Soin* soin;
    int type;
    int isSelected;
    struct Object* next;
}Object;

typedef struct Player
{
    int xp;
    int level;
    int hp_current;
    int hp_max;
    Object* inventory;
}Player;

//---------// New Object Creator //---------// 

Obj_Arme* new_arme(Arme objectId, int degat, int durabilite);
Obj_Armure* new_armure(Armure objectId, int resistance);
Obj_Outil* new_outil(Outil objectId, int durabilite);
Obj_Ressource_de_craft* new_ressource_de_craft(Ressource_de_craft objectId);
Obj_Soin* new_soin(Outil objectId, int hp_heal);
Object* new_Object();

//---------// Object data base //---------// 

Object** Object_list();

//---------// Getter Object from data base //---------//

Obj_Arme* getDBArme(int objectId);
Obj_Armure* getDBArmure(int objectId);
Obj_Outil* getDBOutils(int objectId);
Obj_Ressource_de_craft* getDBRDC(int objectId);
Obj_Soin* getDBSoin(int objectId);
Object* getDBObject(int type, int objectId);
int getDBObjectType(int objectId);

//---------// Check functions //---------// 

int inventorySize(Object* inventory);
int countInventoryArme(Object* inventory);
Object* quantityRDCInc(Object* inventory,int type, int objectId);
int isArmeInInventory(Object* inventory,int type, int objectId);

//---------// Add object in Inventory //---------// 

Object* addarme(Object* inventory, int type, int objectId);
Object* addcraft(Object* inventory,int type, int objectId);
Object* addOtherObject(Object* inventory, int type, int objectId);
Object* appendNewObject(Object* inventory, int objectId, int objectType);

//---------// Search objects functions //---------// 

Object* searchObjectById(Object* inventory, int objectId);
Object* searchObjectByType(Object* inventory, int Objecttype);
Object* searchSelectedObjectByType(Object* inventory, int objectType);

//---------// Utils functions //---------// 

Object* selectObject(Object* inventory, int objectId);
Object* deleteObject(Object* inventory, int objectId);
void print_inventory(Object* inventory);
void print_player(Player * player);

//---------// Object Getters from inventory functions //---------// 

Object* getSelectedWeapon(Object* inventory);
Object* getSelectedArmor(Object* inventory);
Object* getSelectedTool(Object* inventory);
Player* useHealPotion(Player* p, int objectId);

//---------// Crafting Recipes Data Bases //---------// 
int* craftWeaponRecipe(int objectId);
int* craftArmorRecipe(int objectId);
int* crafToolRecipe(int objectId);
int* crafSoinRecipe(int objectId);
int* craftObjectRecipe(int objectId);

//---------// Repair and Craft //---------// 

Object* repairAllObject(Object* inventory);
Object* craftObject(Object* inventory, int objectId);

//---------// Initialize the player/ New game //---------// 

Object* init_inventor(Object* inventory);
Player* init_player();