#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include "type.h"

/**
 * Lit le fichier jusqu'� la prochaine virgule, guillemet, parenth�se ou fin de ligne,
 * stocke le r�sultat dans la cha�ne de caract�res mot.
 *
 * entr�es/sorties file: FILE
 * entr�es/sorties mot: char
 *
 * pr�-cond: il faut que le fichier ce soit bien ouvert
 */
void lire(FILE file[],char mot[]);
/**
 * Trie le tableau de vols par heure de d�collage en utilisant le tri par insertion.
 *
 * entr�e/sortie max: int
 * entr�e/sortie vol[max]: VOL
 *
 * pr�-cond: il faut que le fichier ce soit bien ouvert
 */
void trie_decollage(int max,VOL vol[max]);
/**
 * Modifie l'heure de d�collage en ajoutant une certaine quantit� de minutes.
 *
 * entr�e decollage: int
 * entr�e plus: int
 * sortie heure_main: int
 *
 * pr�-cond: il faut que le fichier ce soit bien ouvert
 */
int change_heure(int decollage,int plus);
/**
 * G�re les retards des vols en ajustant les heures de d�collage selon certaines r�gles.
 *
 * entr�es/sorties max: int
 * entr�es/sorties vol[max]: VOL
 *
 * pr�-cond: il faut que le fichier ce soit bien ouvert
 */
void gestion_temp(int max,VOL vol[max]);
/**
 * Trie les passagers d'un vol par �ge et par prix de billet.
 *
 * entr�es/sorties no_vol: int
 * entr�es/sorties vol[]: VOL
 *
 * pr�-cond: il faut que le fichier ce soit bien ouvert
 */
void tri_billet(int no_vol, VOL vol[]);
void trouver_ligne(char mot[]);

#endif // FONCTIONS_H_INCLUDED
