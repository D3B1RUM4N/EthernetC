#include "graphe.h"
#include "algos.h"
#include "lan.h"
#include "menu.h"
#include <stdio.h>



void creation_trame(trame *t, lan *l)
{
	//à regarde pour fair un malhoc, mais il faut voir comment gere la taille avant de rentrer la chaine
    char data[64];
    size_t dep = 0;
    size_t dest = 0;    

	//on demanded a l'utilisateur d'entrer les donné necessaire pour faire la trame
    printf("De quelle destination voulez vous partir ? (rentrer le numeros de la station, maximum :%d) : ", l->nb_stations);
    scanf("%d", &dep);
	while(dep > l->nb_stations)
	{
		printf("Vous vous etes trompé, vous avez mis une station inexistante ! (rentrer le numeros de la station, maximum :%d) : ", l->nb_stations);
		scanf("%d", &dep);
	}

    printf("Quelle est vottre station d'arriver ? (rentrer le numeros de la station, maximum :%d) : ", l->nb_stations);
    scanf("%d", &dest);
	while(dest > l->nb_stations)
	{
		printf("Vous vous etes trompé, vous avez mis une station inexistante ! (rentrer le numeros de la station, maximum :%d) : ", l->nb_stations);
		scanf("%d", &dest);
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
	memcpy(t->data, "Voici l'affichage d'un trame", 64);
}

void affichebin(size_t n)
{
	size_t bit = 0 ;
	size_t mask = 1 ;
	for (int i = 0 ; i< 32 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit);
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

void affichage_action()
{
	printf("\n\nQuelle action voulez vous faire : \n");
	printf("\t1 - Sortir du programme\n");
	printf("\t2 - Crée un nouvelle tram\n");
	printf("\t3 - Teste d'une trame\n");
}


void affichage_menu()
{
	//declaration des variable
    trame t;
    lan l;
    char fichier[64];
	int reponse = 0;

	//initialisationde et affichage de la lan
    init_lan(&l);
    printf("Bonjour, \nVoici le projet de SAE 2.3 fait par Elies, Elea et Gaël\n\n");
    printf("Pour commencer, veuillez rentrer le chemin du fichier de configuration de votre LAN : ");
    scanf("%s", fichier);
    lecture(&l, fichier);
	printf("\nVoici se que donne la LAN de votre fichier :\n");
    afficher_lan_humain(&l);

	//demande quelle action on veut faire 
	affichage_action();
	scanf("%d", &reponse);

	while(reponse != 1)
	{
		if(reponse == 2)
		{
			//permet de crée et afficher un trame
			//printf("vous avez crée un tram\n");
			creation_trame(&t, &l);
			affichage_trame(&t);
		}
		
        else if(reponse == 3)
		{
			test_tram1(&l);
		}

		else
		{
			//si on c'est trompé d'action
			printf("\n\nVous vosu etes trompé, il n'y a pas d'action pour ce nombre, veuillez réesayer.");
			affichage_action();
			scanf("%d", &reponse);
		}

		//demande quelle action on veut faire 
		affichage_action();
		scanf("%d", &reponse);
	}
}