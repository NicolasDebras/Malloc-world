 #include "malloc_World.h"

monster *creation_monster() {

    FILE *file = fopen("file/monstre.txt", "r");
    char *nombre = malloc(sizeof(char)*10);
    monster *ret;

    if ( file != NULL) {
        fgets(nombre, 255, file);
        ret = malloc(sizeof(monster*) * atoi(nombre));
        int i = 0;
        int cpt = 0;
        char chaine[6][255];

        while (fgets(chaine[i], 255, file) != NULL) 
        {
            if (i == 5) {
                i = 0;
                strcpy(ret[cpt].name, chaine[0]);
                ret[cpt].pv = atoi(chaine[1]);
                ret[cpt].level_monster = atoi(chaine[2]);
                ret[cpt].n = atoi(chaine[3]);
                ret[cpt].degats  = atoi(chaine[4]);
                ret[cpt].armor = atoi(chaine[5]);
                cpt = cpt + 1;
            } else
                i = i + 1;
        }
    } else 
        printf("erreur dans la lecture du fichier des monstres");
    return ret;
}

int main(int argc, char *argv[]) {


    monster *ret = creation_monster();

    printf("Name struct 1 : %s", ret[1].name);
    printf("pv struct 1 : %d\n", ret[1].pv);
    printf("level struct 1 : %d\n", ret[1].level_monster);
    printf("n struct 1 : %d\n", ret[1].n);
    printf("degats struct 1 : %d\n", ret[1].degats);
    printf("armor struct 1 : %d\n", ret[1].armor);
    return 0;
}
    