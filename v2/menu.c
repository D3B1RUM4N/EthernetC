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
    printf("De quelle destination voulez vous partir ? (rentrer le numeros de la station) : ");
    scanf("%d", &dep);
    printf("Quelle est vottre station d'arriver ? (rentrer le numeros de la station) : ");
    scanf("%d", &dest);
    //printf("quel message voulez vou passé ? : ");
    //scanf("%s", data);
    
	//rempli les addresse mac de la trame 
    for(size_t i = 0; i<6; i++){
        t->src[i] = l->switches[dep].mac[i];   
        t->dest[i] = l->switches[dest].mac[i];
    }

	//rempli le reste de la trame 
    init_trame(t);
    t->type = 0x0800;
    t->fcs = 0xABCD;
	memcpy(t->data, "ceci est un teste", 64);
}

void affichage_trame(trame *t)
{
	printf("\nVoici votre trame : \n");
    printf("Preambule\tSFD\tSource\t\t\tDestination\t\tType\tDonnée\t\t\tFCS\n");

    /*for(size_t i = 0; i < sizeof(t->type); i++)
    {
        char byte = ((char*)&t->type)[i];
        for(size_t j = 0; j < 8; j--)
        {
            char bit = (byte >> j) & 1;
            printf("%hhd", bit);
        }
        printf(" ");
    }
    printf("\n");*/


    printf("%02hhx \t%02hhx\t", t->preambule, t->sfd);

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

    printf("\t%d \t%s \t%02hhx\n", t->type, t->data, t->fcs);
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
	printf("\n\n\nQuelle action voulez vous faire : \n");
	printf("\t1 - Sortir du programme\n");
	printf("\t2 - Crée un nouvelle tram\n");
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
		
		else
		{
			//si on c'est trompé d'action
			printf("\n\n\nVous vous etes trompé d'action, veuillez recommencer : \n");
			printf("\t1 - Sortir du programme\n");
			printf("\t2 - Crée un nouvelle tram\n");
			scanf("%d", &reponse);
		}

		//demande quelle action on veut faire 
		printf("\n\n\nQuelle action voulez vous faire : \n");
		printf("\t1 - Sortir du programme\n");
		printf("\t2 - Crée un nouvelle tram\n");
		scanf("%d", &reponse);
	}
}