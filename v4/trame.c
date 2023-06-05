#include "graphe.h"
#include "lan.h"
#include "algos.h"
#include <stdlib.h>
#include <stdio.h>




void creation_trame(trame *t, lan *l)
{
	//à regarde pour fair un malhoc, mais il faut voir comment gere la taille avant de rentrer la chaine
    char data[64];
    size_t dep = 0;
    size_t dest = 0;    

	//on demanded a l'utilisateur d'entrer les donné necessaire pour faire la trame
    printf("De quelle destination voulez vous partir ? (rentrer le numeros de la station, maximum :%zu) : ", l->nb_stations);
    scanf("%zu", &dep);
	while(dep > l->nb_stations)
	{
		printf("Vous vous etes trompé, vous avez mis une station inexistante ! (rentrer le numeros de la station, maximum :%zu) : ", l->nb_stations);
		scanf("%zu", &dep);
	}

    printf("Quelle est vottre station d'arriver ? (rentrer le numeros de la station, maximum :%zu) : ", l->nb_stations);
    scanf("%zu", &dest);
	while(dest > l->nb_stations)
	{
		printf("Vous vous etes trompé, vous avez mis une station inexistante ! (rentrer le numeros de la station, maximum :%zu) : ", l->nb_stations);
		scanf("%zu", &dest);
	}
    
	//rempli les addresse mac de la trame 
    for(size_t i = 0; i<6; i++){
        t->src[i] = l->stations[dep].mac[i];   
        t->dest[i] = l->stations[dest].mac[i];
    }

	//rempli le reste de la trame 
    init_trame(t);
    t->type = 0x0800;
    t->fcs = 0xABCD;
	memcpy(t->data, "Hello World", 12);
}

void init_trame(trame *t){
    //preambule en bit
    t->preambule = 0xAAAAAAA;
    //SFD
    t->sfd = 0xAB;
}

//test d'envoi de tram de la station 1 à la station 2
void test_tram1(lan *l){
    trame t1;
    init_trame(&t1);

    trame t2;
    init_trame(&t2);

    for(size_t i = 0; i<6; i++){
        t1.src[i] = l->stations[0].mac[i];   
        t1.dest[i] = l->stations[1].mac[i];
    }

    for(size_t i = 0; i<6; i++){
        t2.src[i] = l->stations[1].mac[i];   
        t2.dest[i] = l->stations[0].mac[i];
    }


    t1.type = 0x0800;
    strcat(t1.data, "ceci est un test\0");
    t1.fcs = 0xABCD;

    t2.type = 0x0800;
    strcat(t2.data, "Hello world\0");
    t2.fcs = 0xABCD;
    
    
    envoi_tram(l, &t1);
    envoi_tram(l, &t2);
}


// a appeler pour envoyé une tram
void envoi_tram(lan *l, trame *t){
    //trouver quel appareil est la source et destination
    appareil src = trouver_appareil_mac(l, t->src);

    appareil dest = trouver_appareil_mac(l, t->dest);
    if(sont_connectes(&l->g, src.id, dest.id)){
        printf("les appareils sont connectés\n");
    }else{
        printf("les appareils ne sont pas connectés\n");
    }
    //1er cable
    sommet sa[degre(&l->g, src.id)];
    if(sommets_adjacents(&l->g, src.id, sa) == 0){
        return;
    }
    //parcourire la lan
    printf("\n\nParcour de la Trame : \n\n");
    size_t destruct = nb_aretes(&l->g) + 1;
    parcour_tram_commutation(l, t, src, &l->cables[index_arete(&l->g, (arete){src.id, sa[0]})], &destruct);
    if(destruct <= 1){
        printf("destruction de la trame\n_____________________________________\n");
    }else{
        printf("_____________________________________\n");
    }


}

//1er essai sans table de commutation
bool parcour_tram(lan *l, trame *t, appareil a, bool *visite){
    appareil src = trouver_appareil_mac(l, t->src);
    //appareil dest = trouver_appareil_mac(l, t->dest);
    printf("appareil actuel : ");
    if(a.type == SWITCH){
        printf("\tswitch n° %zu\n",a.index);
    }else{
        printf("\tdepart !\n");
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
bool parcour_tram_commutation(lan *l, trame *t, appareil a, cable *c, size_t *destruct){
    
    if(*destruct <= 1){
        return false;
    }
    printf("\ndestruct : %zu\n", *destruct);
    (*destruct) --;


    printf("\tappareil actuel : ");
    if(a.type == SWITCH){
        printf("switch n° %zu\n",a.index);
    }else{
        printf("Station n° : %zu\n", a.index);
    }

    size_t deg = degre(&l->g, a.id);

    sommet sa[deg];
    printf("nb voisin : %zu\n",sommets_adjacents(&l->g, a.id, sa));

    if(a.type == SWITCH){
        if(chercher_commutation(l, l->switches[a.index], t->src) == -1){
            //printf("source introuvable dans la table de commutation\n");
            for(size_t i = 0; i<deg; i++){
                if(l->switches[a.index].ports[i].arete.s1 == c->arete.s1 && l->switches[a.index].ports[i].arete.s2 == c->arete.s2){
                    //printf("trouver cable");
                    ajouter_commutation(l, &l->switches[a.index], t->src, i);
                    i = deg;
                }
            }
        }
        // on verifie la table de commutation
        if(chercher_commutation(l, l->switches[a.index], t->dest) >= 0 && *destruct > 1){
            printf("destinataire trouvé\n");
            printf("sa : %zu", sa[l->switches[a.index].commutations[chercher_commutation(l, l->switches[a.index], t->dest)].num_port]);
            if(parcour_tram_commutation(l, t, l->appareils[sa[l->switches[a.index].commutations[chercher_commutation(l, l->switches[a.index], t->dest)].num_port]], &l->switches[a.index].ports[l->switches[a.index].commutations[chercher_commutation(l, l->switches[a.index], t->dest)].num_port], destruct)){
                return true;
            }
        }


        // pas dans la table, on broadcast
        else if(*destruct > 1){
            for(size_t i = 0; i<deg; i++){
                printf("type : %zu,    id : %zu\n", l->appareils[sa[i]].type, l->appareils[sa[i]].id);
                cable tempC = l->cables[index_arete(&l->g, (arete){a.id, sa[i]})];
                if((tempC.arete.s1 != c->arete.s1 || tempC.arete.s2 != c->arete.s2) && parcour_tram_commutation(l, t, l->appareils[sa[i]], &tempC, destruct)){
                    return true;
                }
            }
        }

    }

    // si c'est station
    
    else{
        if(compare_mac(l->stations[a.index].mac, t->dest)){
            printf("Trame reçue et lue : %s\n", t->data);
        }else if(compare_mac(l->stations[a.index].mac, t->src)){
            printf("Appareil source !\n");
            parcour_tram_commutation(l, t, l->appareils[sa[0]], &l->cables[index_arete(&l->g, (arete){a.id, sa[0]})], destruct);
        }else{
            printf("Trame reçue et ignorée\n");
        }
    }

    return false;
    
}






void affichebin(size_t n)
{
	size_t bit = 0 ;
	size_t mask = 1 ;
	for (int i = 0 ; i< 32 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%zu", bit);
		mask <<= 1 ;
	}    
}

void afficherCodeBinaireSt(size_t nombre) {
    // Rechercher le bit le plus significatif non nul
    int nb = sizeof(size_t) * 8 - 1;
    while (((nombre >> nb) & 1) == 0) {
        nb--;
    }
    // Parcourir chaque bit à partir du bit le plus significatif non nul et les afficher en ordre inverse
    for (int i = nb; i >= 0; i--) {
        // Vérifier si le bit à la position i est à 1 ou à 0
        int bit = (nombre >> i) & 1;

        // Afficher le bit
        printf("%d", bit);
    } 
}

void afficherCodeBinaireUint(uint64_t nombre) {
    // Rechercher le bit le plus significatif non nul
    int nb = sizeof(uint64_t) * 8 - 1;
    while (((nombre >> nb) & 1) == 0) {
        nb--;
    }
    // Parcourir chaque bit à partir du bit le plus significatif non nul et les afficher en ordre inverse
    for (int i = nb; i >= 0; i--) {
        // Vérifier si le bit à la position i est à 1 ou à 0
        int bit = (nombre >> i) & 1;

        // Afficher le bit
        printf("%d", bit);
    }
}

void affichage_trame(trame *t)
{
	printf("\nVoici votre trame : \n");
    printf("Preambule\t\t\tSFD\t\tSource\t\t\tDestination\t\tType\t\tDonnée\t\t\t\tFCS\n");
	
	afficherCodeBinaireUint(t->preambule);
	printf("\t");
	afficherCodeBinaireSt(t->sfd);
	printf("\t");

    for (size_t j = 0; j < 6; j++) {
        printf("%02hhx", t->dest[j]);
        if (j != 5) {
            printf(":");
        }
    }
    printf("\t");
    for (size_t j = 0; j < 6; j++) {
        printf("%02hhx", t->src[j]);
        if (j != 5) {
            printf(":");
        }
    }
	printf("\t");

	afficherCodeBinaireUint(t->type);
    printf("\t%s\t", t->data);
	afficherCodeBinaireUint(t->fcs);
}