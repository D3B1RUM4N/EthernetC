#pragma once

#include "graphe.h"
#include <stdint.h>

//size_t degre(lan const *g, cable s);
bool est_regulier(lan const *g);

void afficher(lan const *g);

void generer_complet(lan *g, size_t ordre);

void visite_composante_connexe(lan const *g, cable s, bool *visite);
uint32_t nb_composantes_connexes(lan const *g);

bool sont_connectes(lan const *g, cable s1, cable s2);

void coloriage_glouton(lan const *g, uint8_t *couleur_cable);
void appliquer_permutation(lan const *src, lan *dst, size_t const *permutation);
uint32_t estimation_nb_chromatique(lan const *g, uint32_t n);
void generer_aleatoire(lan *g, size_t ordre, uint32_t k);

void dijkstra(lan const *g, cable s, double const *poids_arete, double *distance_cable);

void trier_aretes(cable *aretes_triees, lan const *g, double const *poids_arete);
void kruskal(lan const *g, double const *poids_arete, lan *acm);
