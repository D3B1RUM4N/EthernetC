#include "algos.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

size_t degre(graphe const *g, sommet s)
{
    size_t nDeg = 0;
    //printf("nb aretes : %d\n", g->nb_aretes);
    for(size_t k = 0; k<g->nb_aretes; k++){
        //printf("s1 : %d, s2 : %d\n", g->aretes[k].s1, g->aretes[k].s2);
        if(s == g->aretes[k].s1 || s == g->aretes[k].s2){
            nDeg ++;
        }
    }
    
    return nDeg;

    // sommet sa[64];
    // return sommets_adjacents(g, s, sa);
}

bool est_regulier(graphe const *g)
{
    size_t deg = degre(g, 0);
    for(sommet i = 0; i<g->ordre; i++){
        if(degre(g, i) != deg){
            return false;
        }
    }
    return true;
}

void afficher(graphe const *g)
{
    printf("# sommets = %zu\n",ordre(g));
    printf("# arretes = %zu\n", nb_aretes(g));
    printf("--SOMMETS--\n");
    for(sommet s = 0; s<g->ordre; s++){
        printf("%zu (degre : %zu)\n", s, degre(g, s));
    }
}

void generer_complet(graphe *g, size_t ordre)
{
    init_graphe(g);
    for(size_t i = 0; i<ordre; i++){
        ajouter_sommet(g);
    }
    for(sommet i = 0; i<ordre; i++){
        for(sommet j = 0; j<ordre; j++){
            if(i != j){
                ajouter_arete(g, (arete){i,j});
            }
        }
    }
}

void visite_composante_connexe(graphe const *g, sommet s, bool *visite)
{
    visite[s] = false;
    sommet sa[degre(g, s)];
    //printf("sommet %zu -> degre %zu\n", s, degre(g, s));
    sommets_adjacents(g, s, sa);
    for(size_t i = 0; i<degre(g, s); i++){
        if(visite[sa[i]])
            visite_composante_connexe(g, sa[i], visite);
    }
}

uint32_t nb_composantes_connexes(graphe const *g)
{
    uint32_t N = ordre(g);
    bool *tab = malloc(sizeof(bool) * N);
    for (size_t i = 0; i < N; i++)
        tab[i] = true;

    size_t nb = 0;
    for(size_t i = 0; i<N; i++){
        if(tab[i]){
            visite_composante_connexe(g, i, tab);
            nb++;
        }
    }
    return nb;
}

bool sont_connectes(graphe const *g, sommet s1, sommet s2)
{
    if(s1>ordre(g) || s2>ordre(g))
        return false;

    uint32_t N = ordre(g);
    bool *tab = malloc(sizeof(bool) * N);
    for (size_t i = 0; i < N; i++)
        tab[i] = true;
    
    visite_composante_connexe(g, s1, tab);

    if(!tab[s2])
        return true;
    
    return false;
    
}

void coloriage_glouton(graphe const *g, uint8_t *couleur_sommet)
{
    for(size_t s = 0; s<ordre(g); s++){
        bool min[255] = {false};
        sommet sa[degre(g, s)];
        sommets_adjacents(g, s, sa);
        for(size_t j = 0; j<degre(g, s); j++){
            min[couleur_sommet[sa[j]]] = true;
        }
        for(uint8_t i = 0; i<255; i++){
            if(!min[i]){
                //printf("sommet %zu, couleur min %zu\n",s ,i);
                couleur_sommet[s] = i; 
                break;
            }
        }
    }
}

void appliquer_permutation(graphe const *src, graphe *dst, size_t const *permutation)
{
}

uint32_t estimation_nb_chromatique(graphe const *g, uint32_t n)
{
    return 0;
}

void generer_aleatoire(graphe *g, size_t ordre, uint32_t k)
{
}

void dijkstra(graphe const *g, sommet s, double const *poids_arete, double *distance_sommet)
{
}

void trier_aretes(arete *aretes_triees, graphe const *g, double const *poids_arete)
{
}

void kruskal(graphe const *g, double const *poids_arete, graphe *acm)
{
}
