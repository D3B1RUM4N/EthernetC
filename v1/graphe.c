#include "graphe.h"

void init_lan(lan *l)
{
    // initialise les champs internes du graphe g
    // - pas de sommets, pas d'arêtes
    // - allocation d'un tableau d'arêtes de capacité initiale 8

    l->lan_capacite = 8;
    l->cables = malloc(l->lan_capacite * sizeof(cable));
    l->nb_cables = 0;
}

