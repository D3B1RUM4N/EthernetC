#include "graphe.h"

void init_graphe(graphe *g)
{
    // initialise les champs internes du graphe g
    // - pas de sommets, pas d'arêtes
    // - allocation d'un tableau d'arêtes de capacité initiale 8
}

void free_graphe(graphe *g)
{
    // réinitialise les champs internes du graphe g
    // libère la mémoire du tableau d'arêtes
}

size_t ordre(graphe const *g)
{
    return 0;
}

size_t nb_aretes(graphe const *g)
{
    return 0;
}

void ajouter_sommet(graphe *g)
{
}

// une fonction locale "static arete swap_arete(arete a)" pourra être utile
// cette fonction retourne une nouvelle arête dont les sommets sont les même que l'arête reçue mais inversés

bool existe_arete(graphe const *g, arete a)
{
    // retourne true si l'arête a est contenue dans le graphe g, false sinon
    // /!\ l'arête (s1,s2) et l'arête (s2,s1) sont équivalentes

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
