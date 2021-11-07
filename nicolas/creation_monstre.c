 #include "malloc_World.h"


monster *init_monster(char name[50], int pv, int level_monster, int n, int degats, int armor) {

    monster *m = malloc(sizeof(monster));
    
    strcat(m->name, name);
    m->pv = pv;
    m->level_monster = level_monster;
    m->n = n;
    m->degats  = degats;
    m->armor = armor;

    return m;
    
}


char **creation_monster() {

    FILE *file = fopen("file/monstre.txt", "r");
    char nombre[2];
    char **chaine;

    if ( file != NULL) {
        fgets(nombre, 4, file);
        chaine = malloc(sizeof(char*)*atoi(nombre)*6);

        for (int cpt = 0; cpt =! (atoi(nombre)*6); cpt++ )
            chaine[cpt] = malloc(sizeof(char)*255);

        int i = 0;
        while (fgets(chaine[i], 255, file) != NULL) 
        {
            printf("%s", chaine[i]);
            i = i + 1;
        }
    } else 
        printf("erreur dans la lecture du fichier des monstres");

    return chaine;
}

int main(int argc, char *argv[]) {


    printf("Ceci est un test\n");
    char **c = creation_monster();

    printf("ceci est un test %s", c[3]);
    return 0;
}
    