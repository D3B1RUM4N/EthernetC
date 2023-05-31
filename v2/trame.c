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

    for(size_t i = 0; i<6; i++){
        t.src[i] = l->stations[0].mac[i];   
        t.dest[i] = l->stations[1].mac[i];
    }


    t.type = 0x0800;
    strcat(t.data, "ceci est un test\0");
    t.fcs = 0xABCD;
    
    test2(l, &t);
}

void test2(lan *l, trame *t){
    //trouver quel appareil est la source et destination
    appareil src = trouver_appareil_mac(l, t->src);
    appareil dest = trouver_appareil_mac(l, t->dest);

    //parcourire la lan
}



