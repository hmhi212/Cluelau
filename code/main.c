#include "cluelau.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    srand(time(NULL));

    Game games;
    initialiserCartes();
    combinaisonSecrete(&games);

    printf("%s\n", games.solution[0].nom);
    printf("%s\n", games.solution[1].nom);
    printf("%s\n", games.solution[2].nom);


    return 0;
}