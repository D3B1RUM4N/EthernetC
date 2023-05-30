#include "graphe.h"
#include "lan.h"
#include <stdlib.h>
#include <stdio.h>


void init_trame(trame *t){
    //preambule en bit
    t->preambule = 0xAAAAAAA;
    //SFD
    t->sfd = 0xAB;
}

//test d'envoi de tram de la station 1 à la station 2
void test1(lan *l){
    trame t;
    init_trame(&t);

    for(size_t i = 0; i<0; i++){
        t->src[i] = l->station[0].mac[i];   
    }
    for(size_t i = 0; i<0; i++){
        t->dest[i] = l->station[1].mac[i]; 
    }

    t->type = 0x0800;
    t->data = "ceci est un teste";
    t->fcs = 0xABCD;
    
    test2(l, &t);
}

void test2(lan *l, trame *t){
    //trouver quel appareil est la source
    appareil src = trouver_appareil_mac(&l, t->src);
    //ici
    sommets_adjacents();
}

appareil trouver_appareil_mac(lan *l, addMac mac){
    for(size_t i = 0; i<l->nb_appareils; i++){
        if(l->appareils[i].type == STATION){
            //comparer le tableau
            size_t same = 1;
            for(size_t j = 0; j<6; i++){
                if(l->stations[l->appareils[i].index].mac[i] != mac[i]){
                    same = 0;
                    j = 6; 
                }
            }
            if(same == 1){
                return l->appareils[i];
            }
        }
    }
}

