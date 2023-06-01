#include "algos.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

size_t degre(graphe const *g, sommet s)
{
    if(s >= ordre(g)){
        return 0;
    }
    size_t nb = 0;
    for(size_t i = 0; i<nb_aretes(g); i++){
        if(g->aretes[i].s1 == s){
            nb ++;
        }
        else if(g->aretes[i].s2 == s){
            nb ++;
        }
    }

    return nb;
}

bool est_regulier(graphe const *g)
{
    return false;
}

void afficher(graphe const *g)
{
    printf("AFFICHE GRAPHE\n");
    printf("# sommets = %zu\n",ordre(g));
    printf("# arretes = %zu\n", nb_aretes(g));
    printf("===============\n");
    printf("--SOMMETS--\n");
    for(size_t i=0;i<ordre(g);i++){
        printf("%zu (degre : %zu) <-> ",i,degre(g,i));
        for(size_t c = 0;c<nb_aretes(g);c++){
            if(sont_connectes(g,i,c)){
                printf("%zu ",c);
            }
        }
        printf("\n");
    }
    printf("--ARETES--\n");
    for(size_t i=0;i<g->nb_aretes;i++){
        printf("%zu : %zu - %zu\n",i,g->aretes[i].s1,g->aretes[i].s2);
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
