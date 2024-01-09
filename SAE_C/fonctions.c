#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"
#include "type.h"


void lire(FILE * file,char *mot) {
    char carac='b';
    int i=0;
    while(carac!=',' && carac != '(' && carac!='\"' && carac != '\n' && !feof(file) ){
        carac=fgetc(file);
        if(carac!=',' && carac!='\"')
            mot[i]=carac;
        i++;
    }
}


void trie(int max,VOL vol[max]){
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
