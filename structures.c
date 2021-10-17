#include <stdio.h>
#include <stdlib.h>

int ARME_TYPE = 0;
int ARMURE_TYPE = 1;
int OUTIL_TYPE = 2;
int RDC_TYPE = 3;
int SOIN_TYPE = 4;
int ERROR_CODE = 9999;

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


typedef struct Objects{
    Obj_Arme* arme;
    Obj_Armure* armure;
    Obj_Outil* outil;
    Obj_Ressource_de_craft* ressource_de_craft;
    Obj_Soin* soin;
    int type;
    struct Objects* next;
}Objects;

typedef struct Player
{
    int* xp;
    int* level;
    int* hp_current;
    int* hp_max;
    Objects* inventor;
}Player;

//---------// New Objects Creator //---------// 

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
    printf("l'erreur est ici avec %d\n",*tool->durabilite);

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

Objects* new_Object(){
    Objects* objet = malloc(sizeof(Objects));

    objet->arme = malloc(sizeof(Obj_Arme));
    objet->armure = malloc(sizeof(Obj_Armure));
    objet->outil = malloc(sizeof(Obj_Outil));
    objet->ressource_de_craft = malloc(sizeof(Obj_Ressource_de_craft));
    objet->soin = malloc(sizeof(Obj_Soin));
    objet->next = NULL;

    return objet;
}

//---------// Objects data base //---------// 
Objects** objects_list(){
    Objects** LIST_OBJECTS = malloc(35*sizeof(Objects*));
    for (int i=0; i<35; i++){
        LIST_OBJECTS[i] = new_Object();
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

    LIST_OBJECTS[0]->type = 0;
    LIST_OBJECTS[0]->arme = new_arme(WOOD_SWORD,1,_10);

    LIST_OBJECTS[1]->type = 2;
    LIST_OBJECTS[1]->outil = new_outil(WOODEN_PICKAXE,_10);
    LIST_OBJECTS[2]->type = 2;
    LIST_OBJECTS[2]->outil = new_outil(WOODEN_SERPE,_10);
    LIST_OBJECTS[3]->type = 2;
    LIST_OBJECTS[3]->outil = new_outil(WOODEN_AX,_10);
    LIST_OBJECTS[4]->type = 3;
    LIST_OBJECTS[4]->ressource_de_craft = new_ressource_de_craft(FIR);
    LIST_OBJECTS[5]->type = 3;
    LIST_OBJECTS[5]->ressource_de_craft = new_ressource_de_craft(STONE);
    LIST_OBJECTS[6]->type = 3;
    LIST_OBJECTS[6]->ressource_de_craft = new_ressource_de_craft(GRASS);

    LIST_OBJECTS[7]->type = 0;
    LIST_OBJECTS[7]->arme = new_arme(STONE_SWORD,2,_10);
    LIST_OBJECTS[8]->type = 0;
    LIST_OBJECTS[8]->arme = new_arme(STONE_SPEAR,3,_8);
    LIST_OBJECTS[9]->type = 0;
    LIST_OBJECTS[9]->arme = new_arme(STONE_HAMMER,4,_5);
    LIST_OBJECTS[10]->type = 1;
    LIST_OBJECTS[10]->armure = new_armure(STONE_CHESTPLATE,_10);
    LIST_OBJECTS[11]->type = 2;
    LIST_OBJECTS[11]->outil = new_outil(STONE_PICKAXE,_10);
    LIST_OBJECTS[12]->type = 2;
    LIST_OBJECTS[12]->outil = new_outil(STONE_SERPE,_10);
    LIST_OBJECTS[13]->type = 2;
    LIST_OBJECTS[13]->outil = new_outil(STONE_AX,_10);
    LIST_OBJECTS[14]->type = 4;
    LIST_OBJECTS[14]->soin = new_soin(HEAL1,30);
    LIST_OBJECTS[15]->type = 3;
    LIST_OBJECTS[15]->ressource_de_craft = new_ressource_de_craft(BEECH);
    LIST_OBJECTS[16]->type = 3;
    LIST_OBJECTS[16]->ressource_de_craft = new_ressource_de_craft(IRON);
    LIST_OBJECTS[17]->type = 3;
    LIST_OBJECTS[17]->ressource_de_craft = new_ressource_de_craft(LAVENDER);

    LIST_OBJECTS[18]->type = 0;
    LIST_OBJECTS[18]->arme = new_arme(IRON_SWORD,5,_10);
    LIST_OBJECTS[19]->type = 0;
    LIST_OBJECTS[19]->arme = new_arme(IRON_SPEAR,7,_8);
    LIST_OBJECTS[20]->type = 0;
    LIST_OBJECTS[20]->arme = new_arme(IRON_HAMMER,4,_5);
    LIST_OBJECTS[21]->type = 1;
    LIST_OBJECTS[21]->armure = new_armure(IRON_CHESTPLATE,_20);
    LIST_OBJECTS[22]->type = 2;
    LIST_OBJECTS[22]->outil = new_outil(IRON_PICKAXE,_10);
    LIST_OBJECTS[23]->type = 2;
    LIST_OBJECTS[23]->outil = new_outil(IRON_SERPE,_10);
    LIST_OBJECTS[24]->type = 2;
    LIST_OBJECTS[24]->outil = new_outil(IRON_AX,_10);
    LIST_OBJECTS[25]->type = 4;
    LIST_OBJECTS[25]->soin = new_soin(HEAL2,80);
    LIST_OBJECTS[26]->type = 3;
    LIST_OBJECTS[26]->ressource_de_craft = new_ressource_de_craft(OAK);
    LIST_OBJECTS[27]->type = 3;
    LIST_OBJECTS[27]->ressource_de_craft = new_ressource_de_craft(DIAMOND);
    LIST_OBJECTS[28]->type = 3;
    LIST_OBJECTS[28]->ressource_de_craft = new_ressource_de_craft(CHANVRE);

    LIST_OBJECTS[29]->type = 0;
    LIST_OBJECTS[29]->arme = new_arme(DIAMOND_SWORD,10,_10);
    LIST_OBJECTS[30]->type = 0;
    LIST_OBJECTS[30]->arme = new_arme(DIAMOND_SPEAR,15,_8);
    LIST_OBJECTS[31]->type = 0;
    LIST_OBJECTS[31]->arme = new_arme(DIAMOND_HAMMER,20,_5);
    LIST_OBJECTS[32]->type = 1;
    LIST_OBJECTS[32]->armure = new_armure(DIAMOND_CHESTPLATE,_40);
    LIST_OBJECTS[33]->type = 4;
    LIST_OBJECTS[33]->soin = new_soin(HEAL3,200);

    return LIST_OBJECTS;
}


//---------// Getter Objects from data base //---------//


Obj_Arme* getArme(int valeur){ 
    int *_10 = malloc(sizeof(int));
    *_10 = 10;
    Obj_Arme* tmp = new_arme(WOOD_SWORD,1,_10);
    // Obj_Arme* tmp = malloc(sizeof(Obj_Arme));
    // *tmp = objects_list()[valeur-1].armure;
    // return tmp;
}

Obj_Armure* getArmure(int valeur){
    int *_10 = malloc(sizeof(int));
    *_10 = 10;
    Obj_Armure* tmp = new_armure(STONE_CHESTPLATE,_10);
    // Obj_Armure* tmp = malloc(sizeof(Obj_Armure));
    // *tmp = objects_list()[valeur-1].armure;
    // return tmp;
}

// Obj_Outil* getOutils(int valeur){
//     Obj_Outil* tmp = malloc(sizeof(Obj_Outil));
//     *tmp = *objects_list()[valeur-1].outil;
//     return tmp;
// }

// Obj_Ressource_de_craft* getRDC(int valeur){
//     Obj_Ressource_de_craft* tmp = malloc(sizeof(Obj_Ressource_de_craft));
//     *tmp = *objects_list()[valeur-1].ressource_de_craft;
//     return tmp;
// }

// Obj_Soin* getSoin(int valeur){
//     Obj_Soin* tmp = malloc(sizeof(Obj_Soin));
//     *tmp = *objects_list()[valeur-1].soin;
//     return tmp;
// }

Objects* getObject(int type, int valeur){
    Objects* tmp = new_Object();

    if (type == ARME_TYPE){
        tmp->arme = getArme(valeur);
        tmp->type = ARME_TYPE;
    }
    else if (type == ARMURE_TYPE){
        tmp->armure= getArmure(valeur);;
        tmp->type = ARMURE_TYPE;
    }
    // else if (type == OUTIL_TYPE){
    //     tmp->outil= getOutils(valeur);;
    //     tmp->type = ARMURE_TYPE;
    // }
    // else if (type == RDC_TYPE){
    //     tmp->type = ARME_TYPE;
    // }
    // else if (type == SOIN_TYPE){
    //     tmp->soin = getSoin(valeur);
    //     tmp->type = ARME_TYPE;
    // }
    return tmp;
}

//DON'T NEED THAT
//---------// Memory copy //---------// 

// void memcpy_arme(Obj_Arme* tmp1, Obj_Arme* tmp2){
    
//     tmp2->valeur = tmp1->valeur;
//     tmp2->degat = tmp1->degat;
    
//     if ( tmp1->durabilite == NULL ){
//         tmp2->durabilite = NULL;
//     }
//     else{
//         *tmp2->durabilite = *tmp1->durabilite;
//     }
// }

// void memcpy_armure(Obj_Armure* tmp1, Obj_Armure* tmp2){
//     tmp2->valeur = tmp1->valeur;
//     if ( tmp1->resistance == NULL ){
//         tmp2->resistance = NULL;
//     }
//     else{
//         *tmp2->resistance = *tmp1->resistance;
//     }
// }

// void memcpy_rdc(Obj_Ressource_de_craft* tmp1, Obj_Ressource_de_craft* tmp2){
//     tmp2->valeur = tmp1->valeur;
//     if ( tmp1->quantity == NULL ){
//         tmp2->quantity = NULL;
//     }
//     else{
//         *tmp2->quantity = *tmp1->quantity;
//     }
// }

// void memcpy_outil(Obj_Outil* tmp1, Obj_Outil* tmp2){
//     tmp2->valeur = tmp1->valeur;
//     if ( tmp1->durabilite == NULL ){
//         tmp2->durabilite = NULL;
//     }
//     else{
//         *tmp2->durabilite = *tmp1->durabilite;
//     }
// }

// void memcpy_soin(Obj_Soin* tmp1, Obj_Soin* tmp2){
//     tmp2->valeur = tmp1->valeur;
//     tmp2->hp_heal = tmp1->hp_heal;
// }

// void memcpy_object(Objects* tmp1, Objects* tmp2){
    
//     memcpy_arme(tmp1->arme,tmp2->arme);
    
//     memcpy_armure(tmp1->armure,tmp2->armure);
//     memcpy_outil(tmp1->outil,tmp2->outil);
//     memcpy_rdc(tmp1->ressource_de_craft,tmp2->ressource_de_craft);
//     memcpy_soin(tmp1->soin,tmp2->soin);
//     tmp2->type = tmp1->type;
// }

//---------// Check functions //---------// 

int objectSize(Objects* inventory){
    Objects* tmp = inventory;

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

int countInventoryArme(Objects* inventory){

    Objects* tmp = inventory;

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

int quantityRDCInc(Objects* inventory,int type, int valeur){
    Objects* tmp = inventory;

    while (inventory != NULL){
        if ( inventory->ressource_de_craft != NULL && 
            inventory->ressource_de_craft->valeur == valeur){
            (*inventory->ressource_de_craft->quantity)++;
            inventory = tmp;
            return 1;//As True
        }
        inventory = inventory->next;
    }
    inventory = tmp;
    return 0;//As false
}

int isArmeInInventory(Objects* inventory,int type, int valeur){
    Objects* tmp = inventory;

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

Objects* addarme(Objects* inventory, int type, int valeur){
    int nb_weapon = countInventoryArme(inventory);
    int our_weapon = isArmeInInventory(inventory,type,valeur);
    int size = objectSize(inventory);
    Objects* tmp = inventory;

    if ( size < 10 && nb_weapon < 4 && our_weapon==0){
        
        while(inventory->next != NULL) {
            inventory = inventory->next;
        }
        inventory->next = getObject(type, valeur);
        printf("on a l'arme %d \n",inventory->next->arme->valeur);
    }
    else{
        printf("We cannot insert any weapon more!\n");
        printf("There is %d objets in inventory and %d Weapons\n",size, nb_weapon);
    }
    inventory = tmp;
    printf("on a %d objets\n",objectSize(inventory));

    return inventory;
}

void addcraft(Objects* inventory,int type, int valeur){

    int size = objectSize(inventory);

    if ( size < 10 ){
        
        int RDC_STATUS = quantityRDCInc(inventory, type, valeur);
        if (  RDC_STATUS == 1 ){
            printf("--Ressource Append Success\n");
        }
        else{
            printf("--No place avaible for this ressource\n");
        }
        return;
    }
    else{
        printf("We cannot insert any ressource more!\n");
        printf("There is %d objets in inventory.\n",size);
        return;
    }
}

Objects* addobject(Objects* inventory, int type, int valeur){

    int size = objectSize(inventory);
    Objects* tmp = inventory;

    if ( size < 10 ){
        while(inventory->next != NULL) {
            inventory = inventory->next;
        }
        inventory->next = getObject(type, valeur);
        
        printf("on a l'armure %d \n",inventory->next->armure->valeur);
    }
    else{
        printf("We cannot insert any weapon more!\n");
        printf("There is %d objets in inventory\n",size);
    }
    inventory = tmp;
    printf("on a %d objets\n",objectSize(inventory));

    return inventory;
}


//---------// Initialize the player/ New game //---------// 

Objects* init_inventor(Objects* inventory){
    
    inventory = new_Object();
    
    inventory = addarme(inventory, ARMURE_TYPE, WOOD_SWORD);
    inventory = addobject(inventory, ARMURE_TYPE,STONE_CHESTPLATE);//for test
    //addcraft(inventory, objectSize, RDC_TYPE, OAK);
    //addobject(inventory, objectSize, OUTIL_TYPE,WOODEN_AX);
    //addobject(inventory, objectSize, OUTIL_TYPE,WOODEN_SERPE);
    // addobject(inventory, objectSize, OUTIL_TYPE,WOODEN_PICKAXE);

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
    *p->level = 0;
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


    printf("Le joueur a %d objets dans son inventaire.\n", objectSize(a->inventor));
    return 0;
}