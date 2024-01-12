#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fonctions.h"
#include "type.h"

#define chemin "data_vols.csv"
#define MAX 56

int main(){
    VOL vol[MAX];
    char ligne[500],temp,destinationRecherche[30],compagnieRecherche[30];
    int heure,avenir,i,vol_total=0,choice,id_vol,heuredecolageRecherche;

    FILE * file=fopen(chemin, "r");
    if (file==NULL) {
        printf("Echec");
        exit(EXIT_FAILURE);
    }
    fgets(ligne, 1000, file);
    do{
        fscanf(file,"%d,",&vol[vol_total].no_vol);
        lire(file,vol[vol_total].companie);
        lire(file,vol[vol_total].destination);
        fscanf(file,"%d,",&vol[vol_total].no_comptoir);
        fscanf(file,"%d,",&vol[vol_total].h_debut_enregistrement);
        fscanf(file,"%d,",&vol[vol_total].h_fin_enregistrement);
        fscanf(file,"%d,",&vol[vol_total].salle_embarquement);
        fscanf(file,"%d,",&vol[vol_total].h_debut_embarquement);
        fscanf(file,"%d,",&vol[vol_total].h_fin_embarquement);
        fscanf(file,"%d,",&vol[vol_total].h_decollage);
        lire(file,vol[vol_total].etat_de_vol.etat);
        if(vol[vol_total].etat_de_vol.etat[0]=='R'){
            fscanf(file,"%d min),",&vol[vol_total].etat_de_vol.minute);
        }else{
            vol[vol_total].etat_de_vol.minute = 0;
        }
        i=0;
        temp='b';
        fgetc(file);
        while (!feof(file) && temp != '"') {
            lire(file, vol[vol_total].liste_passager[i].nom);
            lire(file, vol[vol_total].liste_passager[i].prenom);
            fscanf(file,"%d/", &vol[vol_total].liste_passager[i].date_naissance.jour);
            fscanf(file,"%d/", &vol[vol_total].liste_passager[i].date_naissance.mois);
            fscanf(file,"%d,", &vol[vol_total].liste_passager[i].date_naissance.annee);
            fscanf(file,"%d,", &vol[vol_total].liste_passager[i].no_siege);
            fscanf(file,"%f", &vol[vol_total].liste_passager[i].prix_billet);
            i++;
            temp = fgetc(file);
        }
        vol[vol_total].liste_passager[i].prix_billet=0;
        vol_total++;
    }while(!feof(file));
    fclose(file);
    vol[vol_total].salle_embarquement=0;
    trie_decollage(vol_total-1,vol);
    do{
        printf("\n");
        printf("----------------------------------------------------------------------\n");
        printf("| 1 pour afficher les informations sur les vols.                     |\n");
        printf("|--------------------------------------------------------------------|\n");
        printf("| 2 pour rechercher un vol.                                          |\n");
        printf("|--------------------------------------------------------------------|\n");
        printf("| 3 pour consulter les ecrans d'affichage des salles d'embarquement. |\n");
        printf("|--------------------------------------------------------------------|\n");
        printf("| 4 pour visialiser la gestion des retards et des annulations.       |\n");
        printf("|--------------------------------------------------------------------|\n");
        printf("| 0 pour arreter le programme.                                       |\n");
        printf("----------------------------------------------------------------------\n");
        printf("\n");
        printf("Saisissez celui que vous souhaitez : ");
        scanf("%d",&choice);

        switch(choice){
            case 0:break;
            case 1: do{
                       printf("Enter votre heure de decollage sur format HHMM: ");
                        scanf("%d",&heure);
                    }while((heure%100)>59 || (heure/100)>23 || (heure/100)<1);
                    printf(" --------------------------------------------------------------------------------------------------------------------\n");
                    printf("| heure decollage\tnumero vol\tnom compagnie\tdestination\t comptoir \t  salle \t   etat vol |\n");
                    printf("|-------------------------------------------------------------------------------------------------------------------|\n");
                     for(int i=0;i<=vol_total;i++){
                        avenir=(((vol[i].h_decollage/100)*60)+vol[i].h_decollage%100) - (((heure/100)*60)+heure%100);
                        if(avenir<=180 && avenir > 0){
                            printf("| %2d:%2d \t\t %2d \t\t %-15s  %-15s %4d \t\t %4d \t\t  %-10s|\n",vol[i].h_decollage/100,vol[i].h_decollage%100,vol[i].no_vol,vol[i].companie,vol[i].destination,vol[i].no_comptoir,vol[i].salle_embarquement,vol[i].etat_de_vol.etat);
                            printf("|-------------------------------------------------------------------------------------------------------------------|\n");
                        }
                    }
                    printf("\n");
                    break;

            case 2:
                    printf("\nRecherche:\n\n");
                    printf("Saisissez 0 si vous ne voulez pas utiliser la recherche par rapport aux criteres proposes.\n\n");
                    printf("Entrez l'heure de decollage format HHMM de votre vol: ");
                    scanf("%d", &heuredecolageRecherche );
                    getchar();
                    printf("Entrez la destination de votre vol: "); /*faire les commentaire et expliquer que pr pas rechercher il faut faire 0*/
                    fgets(destinationRecherche, 30, stdin);
                    trouver_ligne(destinationRecherche);
                    printf("Entrez la compagnie de votre vol: ");
                    fgets(compagnieRecherche, 30, stdin);
                    trouver_ligne(compagnieRecherche);
                    printf(" --------------------------------------------------------------------------------------------------------------------\n");
                    printf("| heure decollage\tnumero vol\tnom compagnie\tdestination\t comptoir \t  salle \t   etat vol |\n");
                    printf("|-------------------------------------------------------------------------------------------------------------------|\n");
                    for(int i = 0; i<vol_total; i++){
                        if((destinationRecherche[0] == '0' || strstr(vol[i].destination, destinationRecherche) != NULL) && (compagnieRecherche[0] == '0' || strstr(vol[i].companie, compagnieRecherche) != NULL) && (heuredecolageRecherche == 0 || vol[i].h_decollage == heuredecolageRecherche)){
                            printf("| %2d:%2d \t\t %2d \t\t %-15s  %-15s %4d \t\t %4d \t\t  %-10s|\n",vol[i].h_decollage/100,vol[i].h_decollage%100,vol[i].no_vol,vol[i].companie,vol[i].destination,vol[i].no_comptoir,vol[i].salle_embarquement,vol[i].etat_de_vol.etat);
                            printf("|-------------------------------------------------------------------------------------------------------------------|\n");
                        }
                    }
                    break;
            case 3:printf("Entrez le numero de vol dont vous souhaitez voir les passagers : ");
                    scanf("%d",&id_vol);
                    tri_billet(id_vol,vol);
                    break;
            case 4:gestion_temp(vol_total,vol);
                    break;
            default:printf("Essayez encore\n");
                    break;
        }
    }while((choice!=0));
    return 0;
}
