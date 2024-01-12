#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"
#include "type.h"


/* lire du ficher */
void lire(FILE * file,char *mot) {
    char carac='b';
    int i=0;
    while(carac!=',' && carac != '(' && carac!='\"' && carac != '\n' && !feof(file) ){
        carac=fgetc(file);
        if(carac!=',' && carac!='\"' && carac != '(')
            mot[i]=carac;
        i++;
    }
}

/* tri avec insertion */

void trie_decollage(int max,VOL vol[max]){
    for(int i=1;i<max;i++){
        VOL tmp = vol[i];
        int j=i-1;
        while(j>=0 && tmp.h_decollage < vol[j].h_decollage){
            vol[j+1]= vol[j];
            j--;
        }
        vol[j+1]=tmp;
    }
}

/* passager */
void tri_billet(int no_vol, VOL vol[]) {
    int x=-1,debut=-1;
    do{
        x++;
    }while(vol[x].salle_embarquement!=0 && vol[x].no_vol!=no_vol);
    if(vol[x].salle_embarquement!=0){
        for (int i = 1;vol[x].liste_passager[i].prix_billet!=0; i++) {
                PASSAGER tmp = vol[x].liste_passager[i];
                int age = 2024 - tmp.date_naissance.annee;
                int j = i - 1;
                while (j >= 0 && age < (2024 - vol[x].liste_passager[j].date_naissance.annee)) {
                    vol[x].liste_passager[j+1] = vol[x].liste_passager[j];
                    j--;
                }
                vol[x].liste_passager[j+1] = tmp;
        }/* trouver indice de 12 */
        do{
            debut++;
        }while(vol[x].liste_passager[debut].prix_billet!=0 &&(2024 - vol[x].liste_passager[debut].date_naissance.annee)<=12);
        for (int i = debut+2;vol[x].liste_passager[i].prix_billet!=0; i++) {
                PASSAGER tmp = vol[x].liste_passager[i];
                int j = i - 1;
                while (j >= debut && tmp.prix_billet > vol[x].liste_passager[j].prix_billet) {
                    vol[x].liste_passager[j+1] = vol[x].liste_passager[j];
                    j--;
                }
                vol[x].liste_passager[j+1] = tmp;
        }
        for (int i = 1;vol[x].liste_passager[i].prix_billet!=vol[x].liste_passager[debut].prix_billet; i++) {
                PASSAGER tmp = vol[x].liste_passager[i];
                int j = i - 1;
                while (j >= 0 && tmp.prix_billet > vol[x].liste_passager[j].prix_billet) {
                    vol[x].liste_passager[j+1] = vol[x].liste_passager[j];
                    j--;
                }
                vol[x].liste_passager[j+1] = tmp;
        }
        PASSAGER tmp;
        for(int i = 1;vol[x].liste_passager[i].prix_billet!=0; i++){
                if(vol[x].liste_passager[i].prix_billet==vol[x].liste_passager[i-1].prix_billet){
                        for(int i=0;vol[x].liste_passager[i].nom[i]!='\0';i++){
                                if(vol[x].liste_passager[i].nom[i-1]>vol[x].liste_passager[i].nom[i-1]){
                                    tmp = vol[x].liste_passager[i];
                                    vol[x].liste_passager[i]=vol[x].liste_passager[i-1];
                                    vol[x].liste_passager[i-1]=tmp;
                                }
                        }
                }
        }
        printf(" ----------------------------------------------------------------------\n");
        printf("| Nom \t    Prenom \t Date de naissance \t numero siege  prix   |\n");
        printf("|---------------------------------------------------------------------|\n");
        for(int i = 0;vol[x].liste_passager[i].prix_billet!=0; i++){
            printf("| %-10s%-10s \t  %2d/%2d/%2d\t\t %2d\t\t%.2f|\n",vol[x].liste_passager[i].nom,vol[x].liste_passager[i].prenom,vol[x].liste_passager[i].date_naissance.jour,vol[x].liste_passager[i].date_naissance.mois,vol[x].liste_passager[i].date_naissance.annee,vol[x].liste_passager[i].no_siege,vol[x].liste_passager[i].prix_billet);
        printf("|---------------------------------------------------------------------|\n");    }
    }else{
        printf("il n'y a pas de vol avec ce numéro\n\n.");
    }

}

/* gestion du retard */

int change_heure(int decollage,int plus){
    int heure_main;
    int heure=decollage / 100;
    int minute=decollage % 100;

    minute=minute+plus;
    while (minute > 59) {
        heure= (heure + 1) % 24;
        minute= minute-60;
    }
    heure_main=heure*100+minute;
    if(heure_main>2259)
        heure_main=9999;
    return heure_main;
}

void gestion_temp(int max,VOL vol[max]){
    VOL retarde[max];
    int x,dif,cpt=0;
    printf("| Les retarde : \n");
    printf(" --------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| heure de decollage \t numero de vol \t nom de la compagnie \t destination \t comptoir d enregistrement \t salle d embarquement  etat du vol\n");
    printf("|--------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<max;i++){
        if(vol[i].etat_de_vol.etat[0]=='R'){
            printf("| %2d:%2d \t\t %2d \t\t %-15s \t %-15s  %4d \t\t\t\t %4d \t\t                %-10s  \n",vol[i].h_decollage/100,vol[i].h_decollage%100,vol[i].no_vol,vol[i].companie,vol[i].destination,vol[i].h_debut_enregistrement,vol[i].h_debut_embarquement,vol[i].etat_de_vol.etat);
            printf("|--------------------------------------------------------------------------------------------------------------------------------------------------\n");
            vol[i].h_decollage=change_heure(vol[i].h_decollage,vol[i].etat_de_vol.minute);
            vol[i].etat_de_vol.minute=0;
        }
    }
    trie_decollage(max,vol);
    do{
        x=0;
        for(int i=max;i>0;i--){
            if(vol[i].etat_de_vol.etat[0]=='R'){
                dif=vol[i].h_decollage-vol[i-1].h_decollage;
            if(dif<5){
                vol[i].h_decollage=vol[i].h_decollage+(5-dif);
                x++;
            }
            dif=vol[i+1].h_decollage-vol[i].h_decollage;
            if(dif<5){
                vol[i].h_decollage=vol[i+1].h_decollage+(5-dif);
                x++;
            }
        }
        trie_decollage(max,vol);
        }
    }while(x!=0);
    printf("| change a : \n");
    printf(" --------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| heure de decollage \t numero de vol \t nom de la compagnie \t destination \t comptoir d enregistrement \t salle d embarquement  etat du vol\n");
    printf("|--------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<max;i++){
            if(vol[i].etat_de_vol.etat[0]=='R'){
                *vol[i].etat_de_vol.etat="A l heure";
                printf("| %2d:%2d \t\t %2d \t\t %-15s \t %-15s  %4d \t\t\t\t %4d \t\t                %-10s  \n",vol[i].h_decollage/100,vol[i].h_decollage%100,vol[i].no_vol,vol[i].companie,vol[i].destination,vol[i].h_debut_enregistrement,vol[i].h_debut_embarquement,vol[i].etat_de_vol.etat);
                printf("|--------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
    }
}

void trouver_ligne(char mot[]){
    for(int i=0;mot[i]!='\0';i++){
        if(mot[i]=='\n'){
            mot[i]='\0';
        }
    }
}
