#pragma once

#include <stdlib.h>
#include <stdbool.h>







//typedef size_t sommet;      //je sais pas encore comment je vais faire on verra

typedef struct appareil
{
    char type;          //1 pour station, 2 pour switch
    size_t index;          //l'index de l'appareil dans le tableau de sont type
    size_t id;          //l'id de l'appareil dans le graphe
}appareil;

typedef size_t sommet;


typedef struct arete
{
    sommet s1;
    sommet s2;
} arete;

typedef struct graphe
{
    size_t ordre;
    size_t aretes_capacite;
    arete * aretes;
    size_t nb_aretes;
} graphe;




//type pour mac
typedef char addMac[6];
//station
typedef struct station{
    char ip[15];
    addMac mac;
}station;

typedef struct switche
{
    size_t nb_ports;
    size_t id;
    addMac mac;
    //cable *commutation;
} switche;

typedef struct cable
{
    size_t poid;
    arete arete;
}cable;

typedef struct lan
{
    station *stations;
    size_t nb_stations;
    switche *switches;
    size_t nb_switches;

    appareil *appareils;
    size_t nb_appareils;

    cable *cables;
    size_t nb_cables;

    size_t stations_capacite;
    size_t switches_capacite;
    size_t appareils_capacite;
    size_t cables_capacite;


    graphe g; 
    
}lan;

typedef struct trame
{
    size_t preambule[7];
    size_t sfd[1];
    size_t dest[6];
    size_t src[6];
    size_t type[2];
    size_t data[1546];
    size_t fcs[4];
}trame;











static const size_t UNKNOWN_INDEX = -1;

void init_graphe(graphe *g);
void free_graphe(graphe *g);

size_t ordre(graphe const *g);
size_t nb_aretes(graphe const *g);

void ajouter_sommet(graphe *g);
bool existe_arete(graphe const *g, arete a);
bool ajouter_arete(graphe *g, arete a);
size_t index_arete(graphe const *g, arete a);

size_t sommets_adjacents(graphe const *g, sommet s, sommet sa[]);
