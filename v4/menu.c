#include "graphe.h"
#include "algos.h"
#include "lan.h"
#include <stdio.h>





void affichage_action()
{
	printf("\n\nQuelle action voulez vous faire : \n");
	printf("\t1 - Sortir du programme\n");
	printf("\t2 - Affiché votre configuration\n");
	printf("\t3 - Crée un nouvelle tram\n");
	printf("\t4 - affiché une trame\n");
	printf("\t5 - R'envoi d'une trame\n");
	printf("\t6 - Afficher les tables de commutations\n");
}


void affichage_menu()
{
	//declaration des variable
    trame trames[16];
	size_t nb_trames = 0;


    lan l;
    char fichier[64];
	int reponse = 0;

	//les scanf font un warning si on utilise pas leurs resultat
	size_t poubelle;

	//initialisationde et affichage de la lan
    init_lan(&l);
    printf("Bonjour, \nVoici le projet de SAE 2.3 fait par Elies, Elea et Gaël\n");
	printf("ceci est actuellement la version 451 !\n\n");
    printf("Pour commencer, veuillez rentrer le chemin du fichier de configuration de votre LAN : ");
    poubelle = scanf("%s", fichier);
	//pour les devs
	if(strcmp(fichier, "9") == 0){
		lecture(&l, "../texte.txt");
		test_tram1(&l);
		afficher_commutation_switches(&l);
		return;
	}
    lecture(&l, fichier);
	

	//demande quelle action on veut faire 
	affichage_action();
	poubelle = scanf("%d", &reponse);

	while(reponse != 1)
	{
		if(reponse == 2){
			printf("\nVoici se que donne la LAN de votre fichier :\n");
    		afficher_lan_humain(&l);
		}

		else if(reponse == 3)
		{
			//permet de crée et afficher un trame
			//printf("vous avez crée un tram\n");
			if(nb_trames + 1 == 16){
				printf("trop de trames crées\n");
			}else{
				trame t;
				trames[nb_trames] = t;
				creation_trame(&trames[nb_trames], &l);
				envoi_tram(&l, &trames[nb_trames]);
				nb_trames ++;
			}
		}

		else if(reponse == 4){
			if(nb_trames == 0){
				printf("aucune trame crée\n");
			}else{
				printf("Quel trame voulez vous afficher : (de 0 a %zu)", nb_trames-1);
				size_t tr;
				poubelle = scanf("%zu", &tr);
				if(tr < nb_trames){
					affichage_trame(&trames[tr]);
				}else{
					printf("nombre trop elevé\n");
				}
			}
			
		}
		
        else if(reponse == 5)
		{
			if(nb_trames == 0){
				printf("aucune trame crée\n");
			}else{
							printf("Quel trame voulez vous envoyer : (de 0 a %zu)", nb_trames-1);
				size_t tr;
				poubelle = scanf("%zu", &tr);
				if(tr < nb_trames){
					//test_tram1(&l);
					envoi_tram(&l, &trames[tr]);
				}else{
					printf("nombre trop elevé\n");
				}
			}
		}

		else if(reponse == 6){
			afficher_commutation_switches(&l);
		}

		else
		{
			//si on c'est trompé d'action
			printf("\n\nVous vosu etes trompé, il n'y a pas d'action pour ce nombre, veuillez réesayer.");
			affichage_action();
			poubelle = scanf("%d", &reponse);
		}

		//demande quelle action on veut faire 
		affichage_action();
		poubelle = scanf("%d", &reponse);
	}
}