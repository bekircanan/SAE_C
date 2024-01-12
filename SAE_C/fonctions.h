#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include "type.h"

void lire(FILE file[],char mot[]);
void trie_decollage(int max,VOL vol[max]);
int change_heure(int decollage,int plus);
void gestion_temp(int max,VOL vol[max]);
void tri_billet(int no_vol, VOL vol[]);
int trouver_indice_vol(int no_vol, VOL vol[]);

#endif // FONCTIONS_H_INCLUDED
