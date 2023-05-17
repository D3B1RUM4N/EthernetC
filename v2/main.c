#include "graphe.h"
#include "algos.h"
#include "lan.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
    //partie graphe
    lan l;
    printf("init lan\n");
    init_lan(&l);

    switche sw1;
    switche sw2;

    //sw1
        sw1.id = l.nb_switches;
            sw1.mac[0] = 0x00;
            sw1.mac[1] = 0x00;
            sw1.mac[2] = 0x00;
            sw1.mac[3] = 0x00;
            sw1.mac[4] = 0x00;
            sw1.mac[5] = 0x01;

        ajouter_switch(&l, sw1);

    //sw2
        sw2.id = l.nb_switches;
            sw2.mac[0] = 0x00;
            sw2.mac[1] = 0x00;
            sw2.mac[2] = 0x00;
            sw2.mac[3] = 0x00;
            sw2.mac[4] = 0x00;
            sw2.mac[5] = 0x02;
        ajouter_switch(&l, sw2);

    ajouter_lien(&l,0 , 1);

    //st1
    ajouter_station(&l, "192.168.1.34");
    ajouter_lien(&l,0, 2 );
    ajouter_lien(&l, 1, 2);


    afficher(&l.g);

    return EXIT_SUCCESS;
}

