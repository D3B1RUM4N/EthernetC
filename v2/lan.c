#include "graphe.h"
#include "lan.h"

void init_lan(lan *l)
{
    graphe g;
    init_graphe(&g);

    l->stations_capacite = 8,
    l->switches_capacite = 8,
    l->appareils_capacite = 16,
    l->nb_stations = 0,
    l->nb_switches = 0,
    l->g = g;
}