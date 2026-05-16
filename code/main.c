#include "cluelau.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
    creerPlateau();
    srand(time(NULL));

    Game games;
    initialiserCartes();
    combinaisonSecrete(&games);

    printf("Suspect secret : %s\n", games.solution[0].nom);
    printf("Arme secrete : %s\n", games.solution[1].nom);
    printf("Piece secrete : %s\n", games.solution[2].nom);

    creerDeck(&games);
    printf("Avant mélange : \n");
    for(int i = 0; i < 18; i++){

    printf("%s\n", games.deck[i].nom);
    }

    melangerCartes(&games);
    printf("Apres melange : \n");

    for(int i = 0; i < 18; i++){

    printf("%s\n", games.deck[i].nom);
    }

    int deplacement = lancerDes();
    printf("Le joueur peut avancer de %d cases.\n", deplacement);

    games.nbJoueurs = 4;
    initialiserPositions(&games);


    """TEST POSITIONS INITIALES""";

    //for(int i = 0; i < games.nbJoueurs; i++){

    //printf("Joueur %d : x=%d y=%d\n",
    //i,
    //games.joueurs[i].x,
    //games.joueurs[i].y);

    //};

    return 0;
}