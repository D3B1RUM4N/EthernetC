#include "graphe.h"
#include <stdio.h>

void init_graphe(graphe *g)
{
    // initialise les champs internes du graphe g
    // - pas de sommets, pas d'arêtes
    // - allocation d'un tableau d'arêtes de capacité initiale 8
    g->ordre = 0;
    g->aretes_capacite = 8;
    g->aretes = malloc(g->aretes_capacite * sizeof(arete));
    g->nb_aretes = 0;
}

void free_graphe(graphe *g)
{
    // réinitialise les champs internes du graphe g
    // libère la mémoire du tableau d'arêtes
    
    free(g->aretes);
}

size_t ordre(graphe const *g)
{
    return g->ordre;
}

size_t nb_aretes(graphe const *g)
{
    return g->nb_aretes;
}

void ajouter_sommet(graphe *g)
{
    sommet s = g->ordre;
    g->ordre++;
}

// une fonction locale "static arete swap_arete(arete a)" pourra être utile
// cette fonction retourne une nouvelle arête dont les sommets sont les même que l'arête reçue mais inversés

bool existe_arete(graphe const *g, arete a)
{
    // retourne true si l'arête a est contenue dans le graphe g, false sinon
    // /!\ l'arête (s1,s2) et l'arête (s2,s1) sont équivalentes

    for(int i = 0; i<nb_aretes(g); i++){
        if((a.s1 == g->aretes[i].s1 && a.s2 == g->aretes[i].s2) || (a.s1 == g->aretes[i].s2 && a.s2 == g->aretes[i].s1)){
            return true;
        }
    }
return false;
        
}

bool ajouter_arete(graphe *g, arete a)
{
    // l'arête a n'est ajoutée que si les conditions suivantes sont remplies :
    //  - les sommets s1 et s2 de a existent dans g
    //  - les sommets s1 et s2 de a sont distincts
    //  - l'arête a n'existe pas dans g

    // /!\ si la capacité actuelle du tableau d'arêtes n'est pas suffisante,
    // /!\ il faut le réallouer.
    // /!\ on peut par exemple doubler la capacité du tableau actuel.

    // retourne true si l'arête a bien été ajoutée, false sinon
    if(a.s1 != a.s2 && !existe_arete(g, a)){
        if(nb_aretes(g) + 1 > g->aretes_capacite){
            g->aretes_capacite *= 2;
            g->aretes = realloc(g->aretes, g->aretes_capacite * sizeof(arete));
        }
        g->aretes[nb_aretes(g)] = a;
        g->nb_aretes++;
        return true;
    }
    //printf("l'arête n'a pas été ajoutée\n");
    return false;
}

size_t index_arete(graphe const *g, arete a)
{
    // retourne l'index de l'arête au sein du tableau d'arêtes de g si l'arête a existe dans g,
    // la valeur UNKNOWN_INDEX sinon

    return UNKNOWN_INDEX;
}

size_t sommets_adjacents(graphe const *g, sommet s, sommet sa[])
{
    // après s'être assuré que le sommet s existe dans g
    // remplit le tableau sa avec les sommets adjacents de s dans g
    // et retourne le nombre de sommets ainsi stockés
    // (le tableau sa est supposé assez grand pour contenir les sommets adjacents)

    return 0;
}
