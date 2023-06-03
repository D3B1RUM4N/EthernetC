#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "graphe.h"
#include "algos.h"

#define SWITCH 2
#define STATION 1


void init_lan(lan *l);
void free_lan(lan *l);
void ajouter_switch(lan *l, switche sw);
void ajouter_station(lan *l, station st);

void ajouter_lien(lan *l, sommet s1, sommet s2, size_t poid);

void afficher_lan(lan *l);
void afficher_lan_humain(lan *l);
void afficher_trame_humain(lan *l, trame t);

void test_tram1(lan *l);
void init_trame(trame *t);
//void envoi_trame(graphe const *g, );
void envoi_tram(lan *l, trame *t);
appareil trouver_appareil_mac(lan *l, addMac mac);
bool parcour_tram(lan *l, trame *t, appareil a, bool *visite);

void creation_trame(trame *t, lan *l);
void afficherCodeBinaireSt(size_t nombre);
void afficherCodeBinaireUint(uint64_t nombre);
void affichage_trame(trame *t);
void affichage_action();
void affichage_menu();
bool parcour_tram_commutation(lan *l, trame *t, appareil a, bool *visite);
int chercher_commutation(lan *l, switche sw, addMac mac);
void ajouter_commutation(lan *l, switche sw, addMac mac);
bool compare_mac(addMac mac1, addMac mac2);
void afficher_commutation_switches(lan *l);

