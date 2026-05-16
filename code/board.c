#include "cluelau.h"
#include <stdio.h>
#include <stdlib.h>

void creerPlateau() {
    printf("|-------------------------------------------------------------------------------|\n");
    printf("|                    |                        |                                 |\n");
    printf("|                    |                                                          |\n");
    printf("|                    |                                                          |\n");
    printf("|                    |                        |                                 |\n");
    printf("|                    |                        |                                 |\n");
    printf("|                    |                        |                                 |\n");
    printf("|                    |                        |                                 |\n");
    printf("|-------------    ---|                                                          |\n");
    printf("|                                                                               |\n");
    printf("|                                             |                                 |\n");
    printf("|                                             |------    -----------------    --|\n");
    printf("|                                                                               |\n");
    printf("|-------------------|                                                           |\n");
    printf("|                   |                                                           |\n");
    printf("|                                                                               |\n");
    printf("|                                                        |----------------------|\n");
    printf("|                   |                                    |                      |\n");
    printf("|                   |                                                           |\n");
    printf("|                   |                                                           |\n");
    printf("|-------------------|                                    |                      |\n");
    printf("|                                                        |                      |\n");
    printf("|                                                        |                      |\n");
    printf("|                                                        |                      |\n");
    printf("|                             |--------    -------|      |                      |\n");
    printf("|-----------    |             |                   |      |                      |\n");
    printf("|               |             |                   |      |                      |\n");
    printf("|               |             |                          |----------------    --|\n");
    printf("|               |             |                                                 |\n");
    printf("|               |             |                   |                             |\n");
    printf("|               |             |                   |                             |\n");
    printf("|               |             |                   |                             |\n");
    printf("|               |             |                   |                             |\n");
    printf("|-------------------------------------------------------------------------------|\n");

    return;
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
        games->joueurs[i].x=2+i;
        games->joueurs[i].y=2;
    }
}