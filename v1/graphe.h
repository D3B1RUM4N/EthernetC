#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef size_t appareil;

//type pour ip
typedef unsigned char ipv4[4];
//type pour mac
typedef char addMac[6];



typedef struct cable
{
    appareil s1;
    appareil s2;
    size_t poid;
} cable;


typedef struct lan{
    cable *cables;
    size_t nb_cables;
    size_t lan_capacite;
}


typedef struct appareil{
    size_t type;            //1 pour station, 2 pour switche
    switche sw;
    station st;
    addMac mac;
}appareil;


typedef struct switche
{
    size_t switch_capacite;
    size_t id;
    cable *commutation;
} switche;

typedef struct station
{
    ipv4 ip;
}station;

void init_lan(lan *l);

