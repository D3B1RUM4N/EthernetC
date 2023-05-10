#pragma once

#include <stdlib.h>
#include <stdbool.h>

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



typedef struct arete
{
    appareil s1;
    appareil s2;
} arete;

typedef struct graphe
{
    size_t ordre;
    size_t aretes_capacite;
    arete * aretes;
    size_t nb_aretes;
} graphe;








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
