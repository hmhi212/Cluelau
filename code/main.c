#include "cluelau.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
    srand(time(NULL));

    Game games;
    initialiserCartes();
    combinaisonSecrete(&games);

    printf("Suspect secret : %s\n", games.solution[0].nom);
    printf("Piece secrete : %s\n", games.solution[1].nom);
    printf("Arme secrete : %s\n", games.solution[2].nom);

    creerDeck(&games);

    for(int i = 0; i < 18; i++){

    printf("%s\n", games.deck[i].nom);
    }

    return 0;
}