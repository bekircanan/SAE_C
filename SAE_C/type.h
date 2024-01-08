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
    char nom[100], prenom[100];
    DATE date_naissance;
    int no_siege;
    float prix_billet;
}PASSAGER;

typedef struct{
    int no_vol ;
    char companie[50], destination[50];
    int no_comptoir, h_debut_enregistrement, h_fin_enregistrement, salle_embarquement, h_debut_embarquement, h_fin_embarquement, h_decollage;
    char etat_de_vol[50];
    PASSAGER liste_passager;
}VOL;


#endif // TYPE_H_INCLUDED
