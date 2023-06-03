#include <stdio.h>
#include "graphe.h"
#include "algos.h"
#include "lan.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>


#define TAILLE_MAX 1000



void lecture(lan *l, char* nom_fichier){
    FILE* file = fopen(nom_fichier, "r");
	char chaine[TAILLE_MAX] = ""; //un tableau de taille 1000
	size_t nbStation;
	if(file != NULL)
	{
		printf("le fichier est ouvert\n");
		printf("lecture par chaine\n");


		size_t cpt = 0;
		size_t x = 0;

		while(fgets(chaine, TAILLE_MAX, file) != NULL)
		{
			//printf("%s", chaine);
			if(cpt != 0){
				if(chaine[0] == '2' && x < nbStation){
					x++;
					printf("%ld",x);
					//printf("switch\n");
					switche sw;
					//printf("chaine : %s\n", chaine);
					char *p = chaine;
					int i = 0;
					while (p != NULL) {
						char *delimiter = strchr(p, ';');
						if (delimiter != NULL) {
							*delimiter = '\0'; // Place un caractère nul pour terminer la sous-chaîne
						}

						//printf("i : %d // p : %s\n", i, p);
						if (i == 0) {
							// on ne fait rien car c'est le 2
						} else if (i == 1) {
							// on a l'adresse mac
							// on peut utiliser directement sscanf pour extraire les octets de l'adresse MAC
							sscanf(p, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
								&sw.mac[0], &sw.mac[1], &sw.mac[2],
								&sw.mac[3], &sw.mac[4], &sw.mac[5]);
						} else if (i == 2) {
							// convertir char vers size_t
							//printf("nb ports : %s\n", p);
							sw.ports_capacite = (size_t)strtoull(p, NULL, 10);
						} else if (i == 3) {
							sw.id = (size_t)strtoull(p, NULL, 10);
						}

						i++;
						//deplacer le pointeur
						if(delimiter != NULL){
							p = delimiter + 1;
						}else{
							p = NULL;
						}
					}

					//printf("ajout switch\n");
					ajouter_switch(l, sw);

				}else if(chaine[0] == '1' && x < nbStation){
					x++;
					//printf("station\n");
					//printf("chaine : %s\n", chaine);
					station st;
					char *p = chaine;
					int i = 0;
					while (p != NULL) {
						char *delimiter = strchr(p, ';');
						if (delimiter != NULL) {
							*delimiter = '\0'; // Place un caractère nul pour terminer la sous-chaîne
						}

						//printf("i : %d // p : %s\n", i, p);
						if (i == 0) {
							// on ne fait rien car c'est le 2
						} else if (i == 1) {
							// on a l'adresse mac
							// on peut utiliser directement sscanf pour extraire les octets de l'adresse MAC
							sscanf(p, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
								&st.mac[0], &st.mac[1], &st.mac[2],
								&st.mac[3], &st.mac[4], &st.mac[5]);
						} else if (i == 2) {
							//IP
							char *p2 = strtok(p, ".");
							int j = 0;
							while (p2 != NULL) {
								//printf("j : %d // p2 : %s\n", j, p2);
								strncpy(st.ip[j], p2, sizeof(st.ip[j])-1);
								st.ip[j][sizeof(st.ip[j])-1] = '\0';  // Assurer la terminaison de la chaîne								printf("ip[%d] : %s\n", j, st.ip[j]);
								p2 = strtok(NULL, ".");
								j++;
							}
						}

						i++;
						//deplacer le pointeur
						if(delimiter != NULL){
							p = delimiter + 1;
						}else{
							p = NULL;
						}
					}
					ajouter_station(l, st);
				}else{
					//printf("cable\n");
					sommet s1 = (size_t)strtoull(strtok(chaine, ";"), NULL, 10);
					sommet s2 = (size_t)strtoull(strtok(NULL, ";"), NULL, 10);
					size_t poid = (size_t)strtoull(strtok(NULL, ";"), NULL, 10);
					ajouter_lien(l, s1, s2, poid);
				}
			}

			else if(cpt == 0)
			{
				char *p = chaine;
				int i = 0;
				char chaine2[TAILLE_MAX];
				while(chaine[i] != ' ')
				{
					chaine2[i] = chaine[i];
					//printf("%c\n", chaine[i]);
					i++;
									
					nbStation = atoi(chaine2); //convertie en int 
					//printf("%ld", nbStation);
				}

			}

			cpt++;
		}

		fclose(file);
	}

	else
	{
		printf("votre fichier n'est pas accesible, ou inexistant.\n");
		fclose(file);
	}
}



int main()
{
	/*//partie graphe
    lan l;
    printf("init lan\n");
    init_lan(&l);

	lecture(&l, "./../texte.txt");

	afficher_lan_humain(&l);

	//afficher lan

	//Test de trame
	test_tram1(&l);

	//affichage des commutation
	afficher_commutation_switches(&l);


	affichage_menu();

	return 0;
}