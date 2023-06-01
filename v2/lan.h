#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
bool parcour_tram_commutation(lan *l, trame *t, appareil a, bool *visite);
int sw_commutation(lan *l, switche sw, addMac mac);
