#include "lan.h"
#include <stdlib.h>
#include <stdio.h>



void init_lan(lan *l)
{
    graphe g;
    init_graphe(&g);

    l->stations_capacite = 8;
    l->switches_capacite = 8;
    l->appareils_capacite = 16;
    l->cables_capacite = 16;
    l->nb_stations = 0;
    l->nb_switches = 0;
    l->nb_appareils = 0;
    l->nb_cables = 0;
    l->g = g;

    l->stations = malloc(l->stations_capacite * sizeof(station));
    l->switches = malloc(l->switches_capacite * sizeof(switche));
    l->appareils = malloc(l->appareils_capacite * sizeof(appareil));
    l->cables = malloc(l->cables_capacite * sizeof(cable));

}

void free_lan(lan *l)
{
    free_graphe(&l->g);
    free(l->stations);
    free(l->switches);
    free(l->appareils);

}

void ajouter_switch(lan *l, switche sw){
    //Verifier la capacité de la lan
    if(l->nb_switches == l->switches_capacite){
        l->switches_capacite *= 2;
        l->switches = realloc(l->switches, l->switches_capacite * sizeof(switche));
    }
    //commutation
    sw.commutations_capacite = 8;
    sw.commutations = malloc(sw.commutations_capacite * sizeof(commutation));
    sw.nb_commutations = 0;
    //ports
    sw.ports = malloc(sw.ports_capacite * sizeof(cable));
    sw.nb_ports = 0;

    //ajouter le switch
    l->switches[l->nb_switches] = sw;
    l->nb_switches ++;

    //ajouter l'appareil a la lan
    appareil a;
    a.type = SWITCH;
    a.id = l->g.ordre;
    a.index = l->nb_switches - 1;

    if(l->nb_appareils == l->appareils_capacite){
        l->appareils_capacite *= 2;
        l->appareils = realloc(l->appareils, l->appareils_capacite * sizeof(appareil));
    }
    l->appareils[l->nb_appareils] = a;
    l->nb_appareils ++;

    ajouter_sommet(&l->g);
}

void ajouter_station(lan *l, station st){
    if(l->nb_stations == l->stations_capacite){
        l->stations_capacite *= 2;
        l->stations = realloc(l->stations, l->stations_capacite * sizeof(station));
    }
    /*l->stations[l->nb_stations][0] = st[0];
    l->stations[l->nb_stations][1] = st[1];
    l->stations[l->nb_stations][2] = st[2];
    l->stations[l->nb_stations][3] = st[3];*/
    l->stations[l->nb_stations] = st;
    
    //l->stations[l->nb_stations] = &st;
    l->nb_stations ++;

    appareil a;
    a.type = STATION;
    a.id = l->g.ordre;
    a.index = l->nb_stations - 1;    


    if(l->nb_appareils == l->appareils_capacite){
        l->appareils_capacite *= 2;
        l->appareils = realloc(l->appareils, l->appareils_capacite * sizeof(appareil));
    }
    l->appareils[l->nb_appareils] = a;
    l->nb_appareils ++;


    ajouter_sommet(&l->g);
}



void ajouter_lien(lan *l, sommet s1, sommet s2, size_t poid){
    arete a;
    a.s1 = s1;
    a.s2 = s2;

    size_t swch1 = 0;
    size_t swch2 = 0;


    if(l->appareils[s1].type == SWITCH){
        if(l->switches[l->appareils[s1].index].nb_ports + 1 == l->switches[l->appareils[s1].index].ports_capacite){
            printf("plus de port disponible pour le switch n° %zu\n", l->appareils[s1].index);
            return;
        }
        swch1 = 1;
    }
    if(l->appareils[s2].type == SWITCH){
        if(l->switches[l->appareils[s2].index].nb_ports + 1 == l->switches[l->appareils[s2].index].ports_capacite){
            printf("plus de port disponible pour le switch n° %zu\n", l->appareils[s2].index);
            return;
        }
        swch2 = 1;
    }

    if(ajouter_arete(&l->g, a)){
        if(l->nb_cables == l->cables_capacite){
            l->cables_capacite *= 2;
            l->cables = realloc(l->cables, l->cables_capacite * sizeof(cable));
        }
        l->cables[l->nb_cables].poid = poid;
        l->cables[l->nb_cables].arete = a;
        l->nb_cables ++;


        //on traite le cas des switch
        if(swch1 == 1){
            l->switches[l->appareils[s1].index].ports[l->switches[l->appareils[s1].index].nb_ports] = l->cables[l->nb_cables-1];
            l->switches[l->appareils[s1].index].nb_ports ++;
        }
        if(swch2 == 1){
            l->switches[l->appareils[s2].index].ports[l->switches[l->appareils[s2].index].nb_ports] = l->cables[l->nb_cables-1];
            l->switches[l->appareils[s2].index].nb_ports ++;
        }
    }
}





appareil trouver_appareil_mac(lan *l, addMac mac){
    //parcourire les appareils
    //printf("\tOn cherche l'appareil avec %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    for(size_t i = 0; i<l->nb_appareils; i++){
        //verifier le type
        if(l->appareils[i].type == STATION){
            if(compare_mac(l->stations[l->appareils[i].index].mac, mac)){
                return l->appareils[i];
            }
        }else{
            if(compare_mac(l->switches[l->appareils[i].index].mac, mac)){
                return l->appareils[i];
            }
        }
    }

    printf("\tERREUR - appareil introuvable\n");
}




int chercher_commutation(lan *l, switche sw, addMac mac){
    // cherche l'adresse dans la table de commutation, return l'index
    size_t comparaison = 1;
    //printf("nb commutation: %zu\n", sw.nb_commutations);
    for(size_t i = 0; i<sw.nb_commutations; i++){
        if(compare_mac(sw.commutations[i].mac, mac)){
            return i;
        }
    }
    return -1;
}

void ajouter_commutation(lan *l, switche *sw, addMac mac, size_t port){
    if(sw->nb_commutations == sw->commutations_capacite){
        sw->commutations_capacite *= 2;
        sw->commutations = realloc(sw->commutations, sw->commutations_capacite * sizeof(commutation));
    }
    sw->commutations[sw->nb_commutations].num_port = port;
    for(size_t i = 0; i<6; i++){
        sw->commutations[sw->nb_commutations].mac[i] = mac[i];
    }
    sw->nb_commutations ++;    

}

bool compare_mac(addMac mac1, addMac mac2){
    size_t comparaison = 1;
    for(size_t k = 0; k<6; k++){
        if(mac1[k] != mac2[k]){
            comparaison = 0;
            k = 6;
        }
    }
    if(comparaison == 1){
        return true;
    }else{
        return false;
    }
}














    
void afficher_lan(lan *l){
    printf("LAN:\n");
    printf("%zu %zu\n", l->nb_appareils, l->g.nb_aretes);
    //s'occuper des switchs
    for (size_t i = 0; i < l->nb_switches; i++) {
        printf("%u;", SWITCH);

        for (size_t j = 0; j < 6; j++) {
            printf("%02hhx", l->switches[i].mac[j]);
            if (j != 5) {
                printf(":");
            }
        }
        printf(";%zu;%zu\n", l->switches[i].nb_ports, l->switches[i].id);
    }

    //s'occuper des stations
    for(size_t i = 0; i < l->nb_stations; i++){
        printf("%u;", STATION);
        for(size_t j = 0; j < 6; j++){
            printf("%02hhx", l->stations[i].mac[j]);
            if(j != 5){
                printf(":");
            }
        }
        //l'ip
        printf(";");
        for(size_t k = 0; k < 4; k++){
            printf("%s", l->stations[i].ip[k]);
            if(k != 4 - 1){
                printf(".");
            }
        }
    }
    
    //s'occuper des liens
    for(size_t i = 0; i<l->nb_cables; i++){
        printf("%zu;%zu;%zu\n", l->cables[i].arete.s1, l->cables[i].arete.s2, l->cables[i].poid);
    }


}
void afficher_lan_humain(lan *l){
    printf("LAN:\n\n");
    printf("Nombre d'appareils : %zu Nombre de cable : %zu\n\n", l->nb_appareils, l->g.nb_aretes);
    //s'occuper des switchs
    for (size_t i = 0; i < l->nb_switches; i++) {
        printf("Switch N°%ld :\n",i+1);

        printf("\t- @mac :");

        for (size_t j = 0; j < 6; j++) {
            printf("%02hhx", l->switches[i].mac[j]);
            if (j != 5) {
                printf(":");
            }
        }
        printf("\n\t- Nombre de ports branchés : %zu\n\t- Identifiant : %zu\n\n", l->switches[i].nb_ports, l->switches[i].id);
    }

    //s'occuper des stations
    for(size_t i = 0; i < l->nb_stations; i++){
        printf("Station N°%ld :\n", i+1);

        printf("\t- @mac : ");

        for(size_t j = 0; j < 6; j++){
            printf("%02hhx", l->stations[i].mac[j]);
            if(j != 5){
                printf(":");
            }
        }
        printf("\n\t- Adresse ip : ");
        //l'ip
        for(size_t k = 0; k < 4; k++){
            printf("%s", l->stations[i].ip[k]);
            if(k != 4 - 1){
                printf(".");
            }
        }
        printf("\n");
    }
    
    //s'occuper des liens
    for(size_t i = 0; i<l->nb_cables; i++){
      //  printf("Liaison de %zu à %zu\n\t- Poids :%zu\n", l->cables[i].arete.s1, l->cables[i].arete.s2, l->cables[i].poid);
        printf("\nLiaison ");
        if(l->appareils[l->cables[i].arete.s1].type ==2) {printf("switch %zu", l->appareils[l->cables[i].arete.s1].index); }
        else{ printf("appareil %zu", l->appareils[l->cables[i].arete.s1].index);}
        printf(" à ");
        if(l->appareils[l->cables[i].arete.s2].type == 2) {printf("switch %zu", l->appareils[l->cables[i].arete.s2].index); }
        else{ printf("appareil %zu", l->appareils[l->cables[i].arete.s2].index);}
        

        printf(":\n\t- Poids : %zu\n", l->cables[i].poid);
    }


}

void afficher_commutation_switches(lan *l){
    printf("\nCommutation : \n");

    for(size_t i = 0; i<l->nb_switches; i++){
        printf("Switch n°%zu\n", i);
        for(size_t j = 0; j<l->switches[i].nb_commutations; j++){
            printf("\t- @mac : ");
            for(size_t k = 0; k<6; k++){
                printf("%02hhx", l->switches[i].commutations[j].mac[k]);
                if(k != 5){
                    printf(":");
                }
            }
            printf("\t\t- Port : %zu\n", l->switches[i].commutations[j].num_port);
        }
    }

}




