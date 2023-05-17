#pragma once

#include <stdlib.h>
#include <stdbool.h>


void init_lan(lan *l);
void free_lan(lan *l);
void ajouter_switch(lan *l, switche sw);
void ajouter_station(lan *l, station st);

void ajouter_lien(lan *l, sommet s1, sommet s2);
