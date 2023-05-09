#include "graphe.h"
#include "algos.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>




int main(){
    srand(time(NULL));

    lan l;
    generer_complet(&l, 5);

    //affichage
    affichage(&l);



    
    



    return 0;
}