#include "graphe.h"
#include "algos.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    graphe g;
    generer_complet(&g, 5);
    
    printf("ordre = %zu\n",ordre(&g));
    //free_graphe(&g);

    printf("AFFICHER GRAPHE\n");
    printf("===============\n");
    afficher(&g);

    free_graphe(&g);

    return EXIT_SUCCESS;
}

