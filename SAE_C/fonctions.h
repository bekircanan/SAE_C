#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include "type.h"

/**
 * Lit le fichier jusqu'à la prochaine virgule, guillemet, parenthèse ou fin de ligne,
 * stocke le résultat dans la chaîne de caractères mot.
 *
 * entrées/sorties file: FILE
 * entrées/sorties mot: char
 *
 * pré-cond: il faut que le fichier ce soit bien ouvert
 */
void lire(FILE file[],char mot[]);
/**
 * Trie le tableau de vols par heure de décollage en utilisant le tri par insertion.
 *
 * entrée/sortie max: int
 * entrée/sortie vol[max]: VOL
 *
 * pré-cond: il faut que le fichier ce soit bien ouvert
 */
void trie_decollage(int max,VOL vol[max]);
/**
 * Modifie l'heure de décollage en ajoutant une certaine quantité de minutes.
 *
 * entrée decollage: int
 * entrée plus: int
 * sortie heure_main: int
 *
 * pré-cond: il faut que le fichier ce soit bien ouvert
 */
int change_heure(int decollage,int plus);
/**
 * Gère les retards des vols en ajustant les heures de décollage selon certaines règles.
 *
 * entrées/sorties max: int
 * entrées/sorties vol[max]: VOL
 *
 * pré-cond: il faut que le fichier ce soit bien ouvert
 */
void gestion_temp(int max,VOL vol[max]);
/**
 * Trie les passagers d'un vol par âge et par prix de billet.
 *
 * entrées/sorties no_vol: int
 * entrées/sorties vol[]: VOL
 *
 * pré-cond: il faut que le fichier ce soit bien ouvert
 */
void tri_billet(int no_vol, VOL vol[]);
void trouver_ligne(char mot[]);

#endif // FONCTIONS_H_INCLUDED
