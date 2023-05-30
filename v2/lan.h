#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void init_lan(lan *l);
void free_lan(lan *l);
void ajouter_switch(lan *l, switche sw);
void ajouter_station(lan *l, station st);

void ajouter_lien(lan *l, sommet s1, sommet s2, size_t poid);

void afficher_lan(lan *l);
void afficher_lan_humain(lan *l);
void afficher_trame_humain(lan *l, trame t);

void test1(lan *l);
void init_trame(trame *t);
