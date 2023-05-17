#include "graphe.h"
#include "lan.h"
#include <stdlib.h>
#include <stdio.h>

#define SWITCH 2;
#define STATION 1;

void init_lan(lan *l)
{
    graphe g;
    init_graphe(&g);

    l->stations_capacite = 8;
    l->switches_capacite = 8;
    l->appareils_capacite = 16;
    l->nb_stations = 0;
    l->nb_switches = 0;
    l->nb_appareils = 0;
    l->g = g;

    l->stations = malloc(l->stations_capacite * sizeof(station));
    l->switches = malloc(l->switches_capacite * sizeof(switche));
    l->appareils = malloc(l->appareils_capacite * sizeof(appareil));

}

void free_lan(lan *l)
{
    free_graphe(&l->g);
    free(l->stations);
    free(l->switches);
    free(l->appareils);

}

void ajouter_switch(lan *l, switche sw){
    if(l->nb_switches == l->switches_capacite){
        l->switches_capacite *= 2;
        l->switches = realloc(l->switches, l->switches_capacite * sizeof(switche));
    }

    l->switches[l->nb_switches] = sw;
    l->nb_switches ++;

    appareil a;
    a.type = SWITCH;
    a.id = l->g.ordre;
    a.index = l->nb_switches - 1;

    if(l->nb_appareils == l->appareils_capacite){
        l->appareils_capacite *= 2;
        l->appareils = realloc(l->appareils, l->appareils_capacite * sizeof(appareil));
    }
    l->appareils[l->nb_appareils] = a;
    l->nb_appareils ++;

    ajouter_sommet(&l->g);
}

void ajouter_station(lan *l, station st){
    if(l->nb_stations == l->stations_capacite){
        l->stations_capacite *= 2;
        l->stations = realloc(l->stations, l->stations_capacite * sizeof(station));
    }
    l->stations[l->nb_stations][0] = st[0];
    l->stations[l->nb_stations][1] = st[1];
    l->stations[l->nb_stations][2] = st[2];
    l->stations[l->nb_stations][3] = st[3];
    
    //l->stations[l->nb_stations] = &st;
    l->nb_stations ++;

    appareil a;
    a.type = STATION;
    a.id = l->g.ordre;
    a.index = l->nb_stations - 1;    


    if(l->nb_appareils == l->appareils_capacite){
        l->appareils_capacite *= 2;
        l->appareils = realloc(l->appareils, l->appareils_capacite * sizeof(appareil));
    }
    l->appareils[l->nb_appareils] = a;
    l->nb_appareils ++;


    ajouter_sommet(&l->g);
}



void ajouter_lien(lan *l, sommet s1, sommet s2){
    arete a;
    a.s1 = s1;
    a.s2 = s2;
    ajouter_arete(&l->g, a);
}
    


