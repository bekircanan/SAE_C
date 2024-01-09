#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

typedef struct {
    int jour, mois, annee;
}DATE;

typedef struct {
    char etat[20];
    int minute;
}ETAT_VOL;

typedef struct {
    char nom[30];
    char prenom[30];
    DATE date_naissance;
    int no_siege;
    float prix_billet;
}PASSAGER;

typedef struct{
    int no_vol ;
    char companie[30], destination[30];
    int no_comptoir, h_debut_enregistrement, h_fin_enregistrement, salle_embarquement, h_debut_embarquement, h_fin_embarquement, h_decollage;
    ETAT_VOL etat_de_vol;
    PASSAGER liste_passager[20];
}VOL;


#endif // TYPE_H_INCLUDED
