#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"
#include "type.h"

#define chemin "data_vols.csv"
#define MAX 1000

int main()
{

    VOL vol[MAX];
    char ligne[1000];
    time_t now;
    struct tm *now_tm;
    int hour,min,avenir,no_vol=0;

    now = time(NULL);
    now_tm = localtime(&now);
    hour = now_tm->tm_hour;
    min = now_tm->tm_min;

    FILE * file=fopen(chemin, "r");
    if (file==NULL) {
        printf("Echec");
        exit(EXIT_FAILURE);
    }
    while (fgets(ligne, 10000, file) != NULL) {
        lire_entier(file,&vol[no_vol].no_vol);
        lire(file,vol[no_vol].companie);
        lire(file,vol[no_vol].destination);
        lire_entier(file,&vol[no_vol].no_comptoir);
        lire_entier(file,&vol[no_vol].h_debut_enregistrement);
        lire_entier(file,&vol[no_vol].h_fin_enregistrement);
        lire_entier(file,&vol[no_vol].salle_embarquement);
        lire_entier(file,&vol[no_vol].h_debut_embarquement);
        lire_entier(file,&vol[no_vol].h_fin_embarquement);
        lire_entier(file,&vol[no_vol].h_decollage);
        lire(file,vol[no_vol].etat_de_vol);


        no_vol++;
    }
    trie(no_vol,vol);
    for(int i=0;i<no_vol;i++){
            avenir=(((vol[i].h_decollage/100)*60)+vol[i].h_decollage%100) - ((hour*60)+min);
            if(avenir<180 && avenir > 0){
                printf("no_vol: %d\n",vol[i].no_vol);
                printf("companie: %s\n", vol[i].companie);
                printf("destination: %s\n", vol[i].destination);
                printf("no_comptoir: %d\n", vol[i].no_comptoir);
                printf("h_debut_enregistrement: %d\n", vol[i].h_debut_enregistrement);
                printf("h_fin_enregistrement: %d\n", vol[i].h_fin_enregistrement);
                printf("salle_embarquement: %d\n", vol[i].salle_embarquement);
                printf("h_debut_embarquement: %d\n", vol[i].h_debut_embarquement);
                printf("h_fin_embarquement: %d\n", vol[i].h_fin_embarquement);
                printf("h_decollage: %d\n", vol[i].h_decollage);
                printf("etat_de_vol: %s\n", vol[i].etat_de_vol);
                printf("\n");
        }
    }
    fclose(file);
    return 0;
}