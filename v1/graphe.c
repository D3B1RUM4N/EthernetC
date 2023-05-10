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
    l->nb_appareils++;
}

void init_switch(appareil *a, lan l)
{
    a = {
        //typedef char addMac[6];
        .mac = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        .type = 2,
        .st = NULL,
        .sw = {
            .switch_capacite = 8,
            .id = l->nb_appareils,
            .commutation = malloc(a->sw.switch_capacite * sizeof(cable))
        }
    };
}

size_t nb_cable(lan const *l)
{
    return l->nb_cables;
}

bool existe_cable(lan const *l, cable a)
{
    // retourne true si l'arête a est contenue dans le graphe g, false sinon
    // /!\ l'arête (s1,s2) et l'arête (s2,s1) sont équivalentes

    for(int i = 0; i<nb_cable(l); i++){
        if((a.a1 == l->cables[i].a1 && a.a2 == l->cables[i].a2) || (a.a1 == l->cables[i].a2 && a.a2 == l->cables[i].a1)){
            return true;
        }
    }
return false;
        
}

bool ajouter_cable(lan *l, cable a)
{
    // l'arête a n'est ajoutée que si les conditions suivantes sont remplies :
    //  - les sommets s1 et s2 de a existent dans g
    //  - les sommets s1 et s2 de a sont distincts
    //  - l'arête a n'existe pas dans g

    // /!\ si la capacité actuelle du tableau d'arêtes n'est pas suffisante,
    // /!\ il faut le réallouer.
    // /!\ on peut par exemple doubler la capacité du tableau actuel.

    // retourne true si l'arête a bien été ajoutée, false sinon
    if(a.a1 != a.a2 && !existe_cable(l, a)){
        if(nb_cable(l) + 1 > l->lan_capacite){
            l->lan_capacite *= 2;
            l->cables = realloc(l->cables, l->lan_capaciteg->aretes_capacite * sizeof(cable));
        }
        l->cables[nb_aretes(l)] = a;
        return true;
    }

    return false;
}
