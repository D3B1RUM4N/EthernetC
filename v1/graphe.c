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

void ajouter_switch(lan *l)
{
    //switche sw = l->nb_appareils;
    appareil a;
    init_switch(&a, l);
    a.st = NULL;
    g->nb_appareils++;
}

void init_switch(appareil *a, lan l)
{
    a->type = 2;
    a->sw.switch_capacite = 8;
    a->sw.id = l->nb_appareils;
    a->sw.commutation = malloc(a->sw.switch_capacite * sizeof(cable));
}

size_t nb_cable(lan const *l)
{
    return l->nb_cables;
}
