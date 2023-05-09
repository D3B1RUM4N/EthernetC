#pragma once

#include <stdlib.h>
#include <stdbool.h>

//type pour ip
typedef unsigned char station[4];
//type pour mac
typedef char addMac[6];


typedef struct switche
{
    size_t switch_capacite;
    size_t id;
    //cable *commutation;
} switche;

typedef struct appareil{
    size_t type;            //1 pour station, 2 pour switche
    switche sw;
    station st;
    addMac mac;
}appareil;



typedef struct cable
{
    appareil a1;
    appareil a2;
    size_t poid;
} cable;

typedef struct lan{
    cable *cables;
    size_t nb_cables;
    size_t lan_capacite;
    size_t nb_appareils;
}lan;





/*typedef struct station
{
    ipv4 ip;
}station;*/

void init_lan(lan *l);
void ajouter_switch(lan const *l);
void ajouter_cable(lan const *l);
void init_switch(appareil *a, lan l);

