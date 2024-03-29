#include "graphe.h"
#include "lan.h"
#include "algos.h"
#include <stdlib.h>
#include <stdio.h>


void init_trame(trame *t){
    //preambule en bit
    t->preambule = 0xAAAAAAA;
    //SFD
    t->sfd = 0xAB;
}

//test d'envoi de tram de la station 1 à la station 2
void test_tram1(lan *l){
    trame t;
    init_trame(&t);

    for(size_t i = 0; i<6; i++){
        t.src[i] = l->stations[0].mac[i];   
        t.dest[i] = l->stations[7].mac[i];
    }


    t.type = 0x0800;
    strcat(t.data, "ceci est un test\0");
    t.fcs = 0xABCD;
    
    envoi_tram(l, &t);
}


// a appeler pour envoyé une tram
void envoi_tram(lan *l, trame *t){
    //trouver quel appareil est la source et destination
    appareil src = trouver_appareil_mac(l, t->src);
    appareil dest = trouver_appareil_mac(l, t->dest);
    bool visite[ordre(&l->g)];

    for(size_t i = 0; i<ordre(&l->g); i++){
        visite[i] = false;
    }

    /*if(sont_connectes(&l->g, src.id, dest.id)){
        printf("les appareils sont connectés\n");
    }else{
        printf("les appareils ne sont pas connectés\n");
    }*/

    //parcourire la lan
    printf("\n\nParcour de la Trame : \n\n");
    if(parcour_tram_commutation(l, t, src, visite)){
        printf("destinataire trouvé\n");
    }else{
        printf("appareil introuvable !\n");
    }
    

}

//1er essai sans table de commutation
bool parcour_tram(lan *l, trame *t, appareil a, bool *visite){
    appareil src = trouver_appareil_mac(l, t->src);
    //appareil dest = trouver_appareil_mac(l, t->dest);
    printf("appareil actuel : ");
    if(a.type == SWITCH){
        printf("switch n° %zu\n",a.index);
    }else{
        printf("depart !\n");
    }

    sommet sa[degre(&l->g, a.id)];
    printf("nb voisin : %zu, degre : %zu\n",sommets_adjacents(&l->g, a.id, sa), degre(&l->g, a.id));

    //faire la methode tableau de bool
    for(size_t i = 0; i<degre(&l->g, a.id); i++){
        size_t same = 1;
        if(l->appareils[sa[i]].type == SWITCH && !visite[sa[i]]){
            visite[sa[i]]=true;
            if(parcour_tram(l, t, l->appareils[sa[i]], visite)){
                return true;
            }
        }else if(l->appareils[sa[i]].type == STATION && !visite[sa[i]]){
            for(size_t j = 0; j<6; j++){
                if(l->stations[l->appareils[sa[i]].index].mac[j] != t->dest[j]){
                    same = 0;
                    j = 6;
                }
            }
            if(same == 1){
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}



// avec commutation
bool parcour_tram_commutation(lan *l, trame *t, appareil a, bool *visite){
    appareil src = trouver_appareil_mac(l, t->src);
    //appareil dest = trouver_appareil_mac(l, t->dest);
    printf("appareil actuel : ");
    if(a.type == SWITCH){
        printf("switch n° %zu\n",a.index);
    }else{
        printf("depart !\n");
    }



    sommet sa[degre(&l->g, a.id)];
    printf("nb voisin : %zu, degre : %zu\n",sommets_adjacents(&l->g, a.id, sa), degre(&l->g, a.id));



    //verification de la table de commutation
    if(a.type == SWITCH){
        //verif de la source dans la table de commutation
        if(chercher_commutation(l, l->switches[a.index], t->src) < 0){
            printf("\tsource introuvable dans la table de commutation\n");
            ajouter_commutation(l, l->switches[a.index], t->src);
        }
        if(chercher_commutation(l, l->switches[a.index], t->dest) > 0){
            for(size_t j = 0; j<l->switches[a.index].nb_ports; j++){
                if(compare_mac(t->dest, l->switches[a.index].commutations[j].mac)){
                    if(l->switches[a.index].ports[l->switches[a.index].commutations[j].num_port].arete.s1 == a.id){
                        if(parcour_tram_commutation(l, t, l->appareils[l->switches[a.index].ports[l->switches[a.index].commutations[j].num_port].arete.s2], visite)){
                            printf("trouver dans table de commutation\n");
                            return true;
                        }
                    }else{
                        if(parcour_tram_commutation(l, t, l->appareils[l->switches[a.index].ports[l->switches[a.index].commutations[j].num_port].arete.s1], visite)){
                            printf("trouver dans table de commutation\n");
                            return true;
                        }
                    }
                }
            }
        }       
    }

    //faire la methode tableau de bool
    for(size_t i = 0; i<degre(&l->g, a.id); i++){
        size_t same = 1;
        if(l->appareils[sa[i]].type == SWITCH && !visite[sa[i]]){
            visite[sa[i]]=true;
            if(parcour_tram_commutation(l, t, l->appareils[sa[i]], visite)){
                return true;
            }
        }else if(l->appareils[sa[i]].type == STATION && !visite[sa[i]]){
            if(compare_mac(l->stations[l->appareils[sa[i]].index].mac, t->dest)){
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}



