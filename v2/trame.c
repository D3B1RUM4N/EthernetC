#include "graphe.h"
#include "lan.h"
#include <stdlib.h>
#include <stdio.h>

//test d'envoi de tram de la station 1 à la station 2
void test1(lan *l){
    trame t;
    init_trame(&t);

}

void init_trame(trame *t){
    //preambule en bit
    t->preambule = 0xAAAAAAA;
    //SFD
    t->sfd = 0xAB;
}