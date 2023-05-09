#include "algos.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

size_t degre(graphe const *g, sommet s)
{
    int nDeg = 0;
    for(int j = 0; j<g->nb_aretes; j++){
        s = g->aretes[j].s1;
        for(int k = 0; k<g->nb_aretes; k++){
            if(s == g->aretes[k].s1 || s == g->aretes[k].s2){
                nDeg ++;
            }
        }
    }
    return 0;
}

bool est_regulier(graphe const *g)
{
    return false;
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
            }s
        }
    }
}

void visite_composante_connexe(graphe const *g, sommet s, bool *visite)
{
}

uint32_t nb_composantes_connexes(graphe const *g)
{
    return 0;
}

bool sont_connectes(graphe const *g, sommet s1, sommet s2)
{
    return false;
}

void coloriage_glouton(graphe const *g, uint8_t *couleur_sommet)
{
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
