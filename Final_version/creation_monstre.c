 #include "malloc_world.h"

monster *creation_monster() {

    FILE *file = fopen("file/monstre.txt", "r");
    char *nombre = malloc(sizeof(char)*10);
    monster *ret;

    if ( file != NULL) {
        fgets(nombre, 255, file);
        ret = malloc(sizeof(monster*) * atoi(nombre));
        int i = 0;
        int cpt = 0;
        char chaine[7][255];

        while (fgets(chaine[i], 255, file) != NULL) 
        {
            if (i == 6) {
                i = 0;
                strcpy(ret[cpt].name, chaine[0]);
                ret[cpt].pv = atoi(chaine[1]);
                ret[cpt].level_monster = atoi(chaine[2]);
                ret[cpt].xp_profit = atoi(chaine[3]);
                ret[cpt].n = atoi(chaine[4]);
                ret[cpt].degats  = atoi(chaine[5]);
                ret[cpt].armor = atoi(chaine[6]);
                cpt = cpt + 1;
            } else
                i = i + 1;
        }
    } else 
        printf("erreur dans la lecture du fichier des monstres");
    return ret;
}

    