#include <stdio.h>
#include "graphe.h"
#include "algos.h"
#include "lan.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define TAILLE_MAX 1000

int main()
{
	FILE* file = fopen("../texte.txt", "r");
	char chaine[TAILLE_MAX] = ""; //un tableau de taille 1000
	if(file != NULL)
	{
		printf("le fichier est ouvert\n");
		printf("lecture par chaine\n");

		//initialisation du graphe et de la lan
		//partie graphe
		lan l;
		printf("init lan\n");
		init_lan(&l);


		size_t cpt = 0;

		while(fgets(chaine, TAILLE_MAX, file) != NULL)
		{
			//printf("%s", chaine);
			if(cpt != 0){
				if(chaine[0] == '2'){
					printf("switch\n");
					switche sw;
					

				}else if(chaine[0] == '1'){
					printf("station\n");
				}else{
					printf("cable\n");
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
	return 0;
}