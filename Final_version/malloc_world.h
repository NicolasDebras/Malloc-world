/*
 * Filename: malloc_world.h
 * Created Date: Friday, October 22nd 2021, 2:01:58 pm
 * Author: Nicolas Debras
 * 
 * Copyright (c) 2021 
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INVENTORY_TYPE 0
#define STORAGE_TYPE 1
#define ARME_TYPE 0
#define ARMURE_TYPE 1
#define OUTIL_TYPE 2
#define RDC_TYPE 3
#define SOIN_TYPE 4
#define SWORD_CATEGORY 111
#define SPEAR_CATEGORY 222
#define HAMMER_CATEGORY 333
#define PICKAXE_CATEGORY 444
#define AX_CATEGORY 555
#define SERPE_CATEGORY 666
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
    int category;
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


/* - struct monster - Nicolas Debras */

typedef struct monster{

    char name[50];
    int pv;
    int level_monster;
    int xp_profit;
    int n;
    int degats;
    int armor;
}monster;

/* - struct map - Nicolas Debras */

typedef struct{
    int rows;
    int column;
    int **map;
    int level;
    int player_x;
    int player_y;

}map;

/* - struct collected ressour - Nicolas Debras */

typedef struct{
    int type;
    int level;
    int pos_x;
    int pos_y;
    int repop_turn;

}ressource_collect;

/* - enum for fill map - Nicolas Debras */

#define MIN3 -3
#define MIN2 -2
#define MIN1 -1

enum {
    portail_zone2 = MIN3,
    portail_zone1 = MIN2,
    wall = MIN1,
    empty,
    player,
    Png,
    plant_zone1,
    rock_zone1,
    tree_zone1,
    plant_zone2,
    rock_zone2,
    tree_zone2,
    plant_zone3,
    rock_zone3,
    tree_zone3
};


typedef struct 
{
    int *movement_tab;
    int n_tour;
    int x;
    int y;
    int nb;
    int nb_monster;
    ressource_collect *collect;
    Player *p;
    Object *chest;
} Declaration;


/* - prototype map.c - Nicolas Debras */

void start_map(map *m, int level);
int **creation_map(int rows, int column);
void fill_map(int rows, int column, int **map);
void print_map(map m);
void initialization_map3(map m);
void initialization_map2(map m);
void initialization_map1(map m);
void check_fill(map m, int rajout);
int RangedRand(int range_min, int range_max);

/* - prototype movement.c - Nicolas Debras */

void movement(map m1, map m2, map m3);
void movement_player(map *m, int *movement_tab);
char input_char();
void clear();

/* - prototype creation_monster.c - Nicolas Debras */

monster *creation_monster();
monster *init_monster(char name[50], int pv, int level_monster, int n, int degats, int armor);

/* - prototype png.c - Nicolas Debras */

void png_interaction();

/* - prototype png.c - Nicolas Debras */

ressource_collect *collect_ressources(int ressources, map *m, int pos_x, int pos_y, int turn, ressource_collect *old, int nb, Player *p);
void check_repop_turn(ressource_collect *r, map *m1, map *m2, map *m3, int turn, int nb);




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
int getDBObjectCategory(int objectId);

//---------// Check functions //---------// 

int inventorySize(Object* inventory);
int countInventoryArme(Object* inventory);
Object* quantityRDCInc(Object* inventory,int type, int objectId);
int isArmeInInventory(Object* inventory,int type, int objectId);

//---------// Update Weapon or Tool //---------//

Object* addUpdatedObjectType(Object* inventory, int objectId);

//---------// Add object in Inventory //---------// 

Object* addarme(Object* inventory, int type, int objectId);
Object* addcraft(Object* inventory,int type, int objectId);
Object* addOtherObject(Object* inventory, int type, int objectId);
Object* addObject(Object* inventory, int objectId, int objectType);
Object* appendNewObject(Object* inventory, int objectId);


//---------// Search objects functions //---------// 

Object* searchObjectById(Object* inventory, int objectId);
Object* searchObjectByType(Object* inventory, int Objecttype);
Object* searchSelectedObjectByType(Object* inventory, int objectType);
Object* searchObjectByCategory(Object* inventory, int objectCategory);

//---------// Utils functions //---------// 

Object* selectObject(Object* inventory, int objectId);
Object* deleteObject(Object* inventory, int objectId);
Object* objectMemCpy(Object* object);
void print_inventory(Object* inventory);
void print_player(Player * player);

//---------// Chest Functions //---------// 

Object** addObjectToChest(Object* inventory,Object* chest, int objectId);
Object** getObjectFromChest(Object* chest, Object* inventory, int objectId);

//---------// Object Getters from inventory functions //---------// 

Object* getPickaxe(Object* inventory);
Object* getAx(Object* inventory);
Object* getSerpe(Object* inventory);
Object* getSelectedWeapon(Object* inventory);
Player* useHealPotion(Player* p, int objectId);

//---------// Crafting Recipes Data Bases //---------// 

int* craftObjectRecipe(int objectId);

//---------// Repair and Craft //---------// 

Object* repairAllObject(Object* inventory);
Object* craftObject(Object* inventory, int objectId);

//---------// Modify Weapon, Armor, ... //---------// 

Object* collectCrafts(Object* inventory, int quantity, int objectId);
Object* lessObjectCapacity(Object* object, int lesscapacity);
Object** toolsGetterFromInventory(Object* inventory);
int collectAndToolUpdateMap1(Object* inventory, int objectIdToCollect, int quantity, Object** tools);
int collectAndToolUpdateMap2(Object* inventory, int objectIdToCollect, int quantity, Object** tools);
int collectAndToolUpdateMap3(Object* inventory, int objectIdToCollect, int quantity, Object** tools);
int collectRessourceAndToolUpdate(Object* inventory, int objectIdToCollect, int quantity, int mapZone);


//---------// Attacks player-monster //---------// 

int attackMonster(Player* player, monster* monster);
int receiveDamage(Player* player, monster* monster);

//---------// Initialize the player/ New game //---------// 

Object* init_inventor();
Player* init_player();


void saveAllGameProperties(Player* p, Object* chest, char filename[]);
void saveChest(Object* chest, char filename[]);
void saveInventory(Object* inventory, char filename[]);
void savePlayer(Player* player, char filename[]);


int input();