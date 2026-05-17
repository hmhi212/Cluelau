#include "cluelau.h"
#include <stdio.h>
#include <stdlib.h>

void creerPlateau(char plateau[34][82]) {
    char modele[34][82] = {
        "|-------------------------------------------------------------------------------|",
        "|                    |                        |                                 |",
        "|                    |                                                          |",
        "|                    |                                                          |",
        "|                    |                        |                                 |",
        "|                    |                        |                                 |",
        "|                    |                        |                                 |",
        "|                    |                        |                                 |",
        "|-------------    ---|                                                          |",
        "|                                                                               |",
        "|                                             |                                 |",
        "|                                             |------    -----------------    --|",
        "|                                                                               |",
        "|-------------------|                                                           |",
        "|                   |                                                           |",
        "|                                                                               |",
        "|                                                        |----------------------|",
        "|                   |                                    |                      |",
        "|                   |                                                           |",
        "|                   |                                                           |",
        "|-------------------|                                    |                      |",
        "|                                                        |                      |",
        "|                                                        |                      |",
        "|                                                        |                      |",
        "|                             |--------    -------|      |                      |",
        "|-----------    |             |                   |      |                      |",
        "|               |             |                   |      |                      |",
        "|               |             |                          |----------------    --|",
        "|               |             |                                                 |",
        "|               |             |                   |                             |",
        "|               |             |                   |                             |",
        "|               |             |                   |                             |",
        "|               |             |                   |                             |",
        "|-------------------------------------------------------------------------------|"
    };

    for(int y = 0; y < 34; y++){
        for(int x = 0; x < 82; x++){
            plateau[y][x] = modele[y][x];
        }
    }
}

void afficherPlateau(char plateau[34][82]) {
    for(int y = 0; y < 34; y++){
        printf("%s\n", plateau[y]);
    }
}

int lancerDes() {
    int de1 = rand() % 6 + 1;
    int de2 = rand() % 6 + 1;
    int total = de1 + de2;

    printf("De 1 : %d\n", de1);
    printf("De 2 : %d\n", de2);
    printf("Total deplacement : %d\n", total);

    return total;
}

void initialiserPositions(Game *games) {
    if (games==NULL){
        return;
    }

    for (int i=0; i<games->nbJoueurs; i++){
        games->joueurs[i].x=32+(i*3);
        games->joueurs[i].y=30;
    }
}

void afficherPositionsJoueurs(Game *games) {
    if(games==NULL) {
        return ;
    }

    printf("\nPositions des joueurs :\n");

    for (int i =0; i<games->nbJoueurs; i++) {
        printf("Joueur %d : x=%d, y=%d\n",
               i+1,
               games->joueurs[i].x,
               games->joueurs[i].y);
    }
}

void placerJoueurs(Game *games, char plateau[34][82]) {
    if (games== NULL){
        return;
    }

    for (int i=0; i<games->nbJoueurs; i++){
        int x=games->joueurs[i].x;
        int y =games->joueurs[i].y;

        plateau[y][x] = '1' + i;
    }
}

void deplacerJoueur(Game *games, char plateau[34][82], int joueurIndex, int deplacement) {

    if(games == NULL){
        return;
    }

    char direction;

    while(deplacement > 0){

        afficherPlateau(plateau);

        printf("\nDeplacements restants : %d\n", deplacement);
        printf("Direction (zqsd) : ");

        scanf(" %c", &direction);

        int ancienX = games->joueurs[joueurIndex].x;
        int ancienY = games->joueurs[joueurIndex].y;

        if(direction == 'z'){
            games->joueurs[joueurIndex].y -= 1;
        }

        else if(direction == 's'){
            games->joueurs[joueurIndex].y += 1;
        }

        else if(direction == 'q'){
            games->joueurs[joueurIndex].x -= 3;
        }

        else if(direction == 'd'){
            games->joueurs[joueurIndex].x += 3;
        }

        plateau[ancienY][ancienX] = ' ';

        int nouveauX = games->joueurs[joueurIndex].x;
        int nouveauY = games->joueurs[joueurIndex].y;

        plateau[nouveauY][nouveauX] = '1' + joueurIndex;

        deplacement--;
    }
}