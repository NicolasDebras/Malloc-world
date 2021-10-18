#include <stdio.h>
#include <stdlib.h>

#define ARME_TYPE 0
#define ARMURE_TYPE 1
#define OUTIL_TYPE 2
#define RDC_TYPE 3
#define SOIN_TYPE 4
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
    CHANVRE = 29,
}Ressource_de_craft;

//Soins
typedef enum Soin{
    HEAL1 = 15,
    HEAL2 = 26,
    HEAL3 = 34
}Soin;

//---------// STRUCTURES //---------// 

typedef struct Obj_Arme{
    Arme valeur;
    int degat;
    int* durabilite;
}Obj_Arme;

typedef struct Obj_Armure{
    Armure valeur;
    int* resistance;
}Obj_Armure;

typedef struct Obj_Outil{
    Outil valeur;
    int* durabilite;
}Obj_Outil;

typedef struct Obj_Ressource_de_craft{
    Ressource_de_craft valeur;
    int* quantity;
}Obj_Ressource_de_craft;

typedef struct Obj_Soin{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    Soin valeur;
    int hp_heal;
}Obj_Soin;


typedef struct Object{
    Obj_Arme* arme;
    Obj_Armure* armure;
    Obj_Outil* outil;
    Obj_Ressource_de_craft* ressource_de_craft;
    Obj_Soin* soin;
    int type;
    struct Object* next;
}Object;

typedef struct Player
{
    int* xp;
    int* level;
    int* hp_current;
    int* hp_max;
    Object* inventor;
}Player;

//---------// New Object Creator //---------// 

Obj_Arme* new_arme(Arme valeur, int degat, int* durabilite){
    
    Obj_Arme* weapon = malloc(sizeof(Obj_Arme)); 
    weapon->valeur = valeur;
    weapon->degat = degat;    
    weapon->durabilite = malloc(sizeof(int));
    *weapon->durabilite = *durabilite;

    return weapon;
}

Obj_Armure* new_armure(Armure valeur, int* resistance){
    Obj_Armure* armor = malloc(sizeof(Obj_Armure));
    armor->valeur = valeur;
    armor->resistance = malloc(sizeof(int));
    *armor->resistance = *resistance;

    return armor;
}

Obj_Outil* new_outil(Outil valeur, int* durabilite){
    Obj_Outil* tool = malloc(sizeof(Obj_Outil));
    tool->valeur = valeur;
    tool->durabilite = malloc(sizeof(int));
    *tool->durabilite = *durabilite;

    return tool;
}

Obj_Ressource_de_craft* new_ressource_de_craft(Ressource_de_craft valeur){
    Obj_Ressource_de_craft* craft = malloc(sizeof(Obj_Ressource_de_craft));
    craft->valeur = valeur;
    craft->quantity = malloc(sizeof(int));
    *craft->quantity = 0;

    return craft;
}

Obj_Soin* new_soin(Outil valeur, int hp_heal){
    Obj_Soin* potion = malloc(sizeof(Obj_Soin));
    potion->valeur = valeur;
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
    objet->next = NULL;

    return objet;
}

//---------// Object data base //---------// 
Object** Object_list(){
    Object** LIST_Object = malloc(35*sizeof(Object*));
    for (int i=0; i<35; i++){
        LIST_Object[i] = new_Object();
    }

    int *_5 = malloc(sizeof(int));
    *_5 = 5;
    int *_8 = malloc(sizeof(int));
    *_8 = 8;
    int *_10 = malloc(sizeof(int));
    *_10 = 10;
    int *_20 = malloc(sizeof(int));
    *_20 = 20;
    int *_40 = malloc(sizeof(int));
    *_40 = 40;

    LIST_Object[0]->type = 0;
    LIST_Object[0]->arme = new_arme(WOOD_SWORD,1,_10);

    LIST_Object[1]->type = 2;
    LIST_Object[1]->outil = new_outil(WOODEN_PICKAXE,_10);
    LIST_Object[2]->type = 2;
    LIST_Object[2]->outil = new_outil(WOODEN_SERPE,_10);
    LIST_Object[3]->type = 2;
    LIST_Object[3]->outil = new_outil(WOODEN_AX,_10);
    LIST_Object[4]->type = 3;
    LIST_Object[4]->ressource_de_craft = new_ressource_de_craft(FIR);
    LIST_Object[5]->type = 3;
    LIST_Object[5]->ressource_de_craft = new_ressource_de_craft(STONE);
    LIST_Object[6]->type = 3;
    LIST_Object[6]->ressource_de_craft = new_ressource_de_craft(GRASS);

    LIST_Object[7]->type = 0;
    LIST_Object[7]->arme = new_arme(STONE_SWORD,2,_10);
    LIST_Object[8]->type = 0;
    LIST_Object[8]->arme = new_arme(STONE_SPEAR,3,_8);
    LIST_Object[9]->type = 0;
    LIST_Object[9]->arme = new_arme(STONE_HAMMER,4,_5);
    LIST_Object[10]->type = 1;
    LIST_Object[10]->armure = new_armure(STONE_CHESTPLATE,_10);
    LIST_Object[11]->type = 2;
    LIST_Object[11]->outil = new_outil(STONE_PICKAXE,_10);
    LIST_Object[12]->type = 2;
    LIST_Object[12]->outil = new_outil(STONE_SERPE,_10);
    LIST_Object[13]->type = 2;
    LIST_Object[13]->outil = new_outil(STONE_AX,_10);
    LIST_Object[14]->type = 4;
    LIST_Object[14]->soin = new_soin(HEAL1,30);
    LIST_Object[15]->type = 3;
    LIST_Object[15]->ressource_de_craft = new_ressource_de_craft(BEECH);
    LIST_Object[16]->type = 3;
    LIST_Object[16]->ressource_de_craft = new_ressource_de_craft(IRON);
    LIST_Object[17]->type = 3;
    LIST_Object[17]->ressource_de_craft = new_ressource_de_craft(LAVENDER);

    LIST_Object[18]->type = 0;
    LIST_Object[18]->arme = new_arme(IRON_SWORD,5,_10);
    LIST_Object[19]->type = 0;
    LIST_Object[19]->arme = new_arme(IRON_SPEAR,7,_8);
    LIST_Object[20]->type = 0;
    LIST_Object[20]->arme = new_arme(IRON_HAMMER,4,_5);
    LIST_Object[21]->type = 1;
    LIST_Object[21]->armure = new_armure(IRON_CHESTPLATE,_20);
    LIST_Object[22]->type = 2;
    LIST_Object[22]->outil = new_outil(IRON_PICKAXE,_10);
    LIST_Object[23]->type = 2;
    LIST_Object[23]->outil = new_outil(IRON_SERPE,_10);
    LIST_Object[24]->type = 2;
    LIST_Object[24]->outil = new_outil(IRON_AX,_10);
    LIST_Object[25]->type = 4;
    LIST_Object[25]->soin = new_soin(HEAL2,80);
    LIST_Object[26]->type = 3;
    LIST_Object[26]->ressource_de_craft = new_ressource_de_craft(OAK);
    LIST_Object[27]->type = 3;
    LIST_Object[27]->ressource_de_craft = new_ressource_de_craft(DIAMOND);
    LIST_Object[28]->type = 3;
    LIST_Object[28]->ressource_de_craft = new_ressource_de_craft(CHANVRE);

    LIST_Object[29]->type = 0;
    LIST_Object[29]->arme = new_arme(DIAMOND_SWORD,10,_10);
    LIST_Object[30]->type = 0;
    LIST_Object[30]->arme = new_arme(DIAMOND_SPEAR,15,_8);
    LIST_Object[31]->type = 0;
    LIST_Object[31]->arme = new_arme(DIAMOND_HAMMER,20,_5);
    LIST_Object[32]->type = 1;
    LIST_Object[32]->armure = new_armure(DIAMOND_CHESTPLATE,_40);
    LIST_Object[33]->type = 4;
    LIST_Object[33]->soin = new_soin(HEAL3,200);

    return LIST_Object;
}


//---------// Getter Object from data base //---------//


Obj_Arme* getArme(int valeur){ 
    // int *_10 = malloc(sizeof(int));
    // *_10 = 10;
    // Obj_Arme* tmp = new_arme(valeur,1,_10);
    Obj_Arme* tmp = malloc(sizeof(Obj_Arme));
    tmp = Object_list()[valeur-1][0].arme;
    return tmp;
}

Obj_Armure* getArmure(int valeur){
    // int *_10 = malloc(sizeof(int));
    // *_10 = 10;
    // Obj_Armure* tmp = new_armure(valeur,_10);
    Obj_Armure* tmp = malloc(sizeof(Obj_Armure));
    tmp = Object_list()[valeur-1][0].armure;
    return tmp;
}

Obj_Outil* getOutils(int valeur){
    Obj_Outil* tmp = malloc(sizeof(Obj_Outil));
    tmp = Object_list()[valeur-1][0].outil;
    return tmp;
}
Obj_Ressource_de_craft* getRDC(int valeur){
    Obj_Ressource_de_craft* tmp = malloc(sizeof(Obj_Ressource_de_craft));
    tmp = Object_list()[valeur-1][0].ressource_de_craft;
    return tmp;
}
Obj_Soin* getSoin(int valeur){
    Obj_Soin* tmp = malloc(sizeof(Obj_Soin));
    tmp = Object_list()[valeur-1][0].soin;
    return tmp;
}

Object* getObject(int type, int valeur){
    Object* tmp = new_Object();

    if (type == ARME_TYPE){
        tmp->arme = getArme(valeur);
        tmp->type = ARME_TYPE;
    }
    else if (type == ARMURE_TYPE){
        tmp->armure= getArmure(valeur);;
        tmp->type = ARMURE_TYPE;
    }
    else if (type == OUTIL_TYPE){
        tmp->outil= getOutils(valeur);
        tmp->type = ARMURE_TYPE;
    }
    else if (type == RDC_TYPE){
        tmp->type = ARME_TYPE;
    }
    else if (type == SOIN_TYPE){
        tmp->soin = getSoin(valeur);
        tmp->type = ARME_TYPE;
    }
    return tmp;
}

//---------// Check functions //---------// 

int inventorySize(Object* inventory){
    Object* tmp = inventory;

    int counter = 0;
    while (inventory != NULL)
    {
        counter++;
        inventory = inventory->next;
    }
    inventory = tmp;

    if (counter<1){
        printf("Erreur d'initialisation !!!");
        return ERROR_CODE;
    }
    return counter-1;
}

int countInventoryArme(Object* inventory){

    Object* tmp = inventory;

    int counter = 0;
    while (inventory != NULL){
        if ( inventory->arme != NULL ){
            counter++;
        }
        inventory = inventory->next;
    }

    inventory = tmp;

    return counter;
}

Object* appendObject(Object* head, Object* last){
    while(head->next != NULL) {
        head = head->next;
    }
    head->next = last;
}

Object* quantityRDCInc(Object* inventory,int type, int valeur){
    Object* tmp = inventory;

    int status = 0;;
    while (inventory != NULL){
        if ( inventory->ressource_de_craft != NULL && 
            inventory->ressource_de_craft->valeur == valeur){
            (*inventory->ressource_de_craft->quantity) = (*inventory->ressource_de_craft->quantity) +1 ;
            printf("Craft n°%d was added to your inventory, we have %d of this craft\n",
            inventory->ressource_de_craft->valeur, *inventory->ressource_de_craft->quantity);
            inventory = tmp;
            status = 1;//As True
        }
        inventory = inventory->next;
    }
    inventory = tmp;
    if (status == 0){
        while(inventory->next != NULL) {
            inventory = inventory->next;
        }
        inventory->next = getObject(type, valeur);

        
    (*inventory->ressource_de_craft->quantity) = (*inventory->ressource_de_craft->quantity) +1 ;        
        printf("Craft n°%d was added to your inventory, we have %d of this craft\n",
            inventory->ressource_de_craft->valeur, *inventory->ressource_de_craft->quantity);
    }
    inventory = tmp;
    return inventory;//As false
}

int isArmeInInventory(Object* inventory,int type, int valeur){
    Object* tmp = inventory;

    while (inventory != NULL){
        if ( inventory->arme != NULL && 
             inventory->arme->valeur == valeur){
            return 1;
        }
        inventory = inventory->next;
    }
    inventory = tmp;
    return 0;
}

//---------// Add object in Inventory //---------// 

Object* addarme(Object* inventory, int type, int valeur){
    int nb_weapon = countInventoryArme(inventory);
    int our_weapon = isArmeInInventory(inventory,type,valeur);
    int size = inventorySize(inventory);
    Object* tmp = inventory;
    
    if ( size < 10 && nb_weapon <= 3 && !our_weapon){
        
        while(inventory->next != NULL) {
            inventory = inventory->next;
        }
        inventory->next = getObject(type, valeur);
        printf("Object n°%d was added to your inventory\n",inventory->next->arme->valeur);
    }
    else{
        printf("We cannot insert more weapon!\n");
        printf("There is %d objets in inventory and %d Weapons\n",size, nb_weapon);
    }
    inventory = tmp;

    return inventory;
}

Object* addcraft(Object* inventory,int type, int valeur){

    int size = inventorySize(inventory);

    if ( size < 10 ){
        
        inventory = quantityRDCInc(inventory, type, valeur);
        return inventory;
    }
    else{
        printf("We cannot insert more ressources!\n");
        printf("There is %d objets in inventory.\n",size);
        return inventory;
    }
}

Object* addobject(Object* inventory, int type, int valeur){

    int size = inventorySize(inventory);
    Object* tmp = inventory;

    if ( size < 10 ){
        while(inventory->next != NULL) {
            inventory = inventory->next;
        }
        inventory->next = getObject(type, valeur);
        printf("Object n°%d was added to your inventory\n",valeur);

    }
    else{
        printf("We cannot insert more weapon !\n");
        printf("There is %d objets in inventory\n",size);
    }
    inventory = tmp;

    return inventory;
}


//---------// Initialize the player/ New game //---------// 

Object* init_inventor(Object* inventory){
    
    inventory = new_Object();
    
    inventory = addarme(inventory, ARMURE_TYPE, WOOD_SWORD);
    inventory = addobject(inventory, ARMURE_TYPE,STONE_CHESTPLATE);//for test
    //inventory = addcraft(inventory, RDC_TYPE, OAK);
    inventory = addobject(inventory, OUTIL_TYPE,WOODEN_AX);
    inventory = addobject(inventory, OUTIL_TYPE,WOODEN_SERPE);
    inventory = addobject(inventory, OUTIL_TYPE,WOODEN_PICKAXE);

    return inventory;
}

Player* init_player(){
    Player* p = malloc(sizeof(Player));

    p->xp = malloc(sizeof(int));
    p->level = malloc(sizeof(int));
    p->hp_current = malloc(sizeof(int));
    p->hp_max = malloc(sizeof(int));
    p->inventor = init_inventor(p->inventor);

    *p->xp = 0;
    *p->level = 1;
    *p->hp_current = 0;
    *p->hp_max = 100;
      
    return p;
}


int main(){
    Player* a = init_player();
    
    printf("Le joueur a l'arme %d et l'armure %d\n",
       a->inventor->arme->valeur, a->inventor->next->armure->valeur);
    
    // printf("Le joueur a l'outil %d \n",
    //     a->inventor[0]->outil->valeur);


    printf("Le joueur a %d objets dans son inventaire.\n", inventorySize(a->inventor));
    return 0;
}