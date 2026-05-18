#include "cluelau.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

        int nouveauX = ancienX;
        int nouveauY = ancienY;

        if(direction == 'z'){
            nouveauY -= 1;
        }

        else if(direction == 's'){
            nouveauY += 1;
        }

        else if(direction == 'q'){
            nouveauX -= 3;
        }

        else if(direction == 'd'){
            nouveauX += 3;
        }

        else{
            printf("Direction invalide.\n");
            continue;
        }

        if(caseAccessible(plateau, nouveauX, nouveauY) == 1){

            plateau[ancienY][ancienX] = ' ';

            games->joueurs[joueurIndex].x = nouveauX;
            games->joueurs[joueurIndex].y = nouveauY;

            plateau[nouveauY][nouveauX] = '1' + joueurIndex;

            int pieceIndex = joueurDansPiece(games, &games->joueurs[joueurIndex]);

            if(pieceIndex != -1){
                printf("Le joueur est dans la piece : %s\n",
                       games->rooms[pieceIndex].nom);
            }

            deplacement--;
        }

        else{
            printf("Deplacement impossible.\n");
        }
    }
}

void tourDeplacementJoueurs(Game *games, char plateau[34][82]) {
    if (games==NULL){
        return;
    }

    for (int i=0; i<games->nbJoueurs; i++) {

        printf("\n===== Tour du joueur %d =====\n", i+1);

        int deplacement = lancerDes();

        deplacerJoueur(games, plateau, i, deplacement);
    }
}

int caseAccessible(char plateau[34][82], int x, int y) {
    if (x<0 || x >=81 || y<0 || y>= 34){
        return 0 ;
    }

    if (plateau[y][x]=='|' || plateau[y][x]=='-'){
        return 0;

    }

    return 1;
}

void initialiserPieces (Game *games) {
    if (games == NULL) {
        return;
    }

    strcpy(games->rooms[0].nom, "Cuisine");
    games->rooms[0].xMin = 1;
    games->rooms[0].xMax = 20;
    games->rooms[0].yMin = 1;
    games->rooms[0].yMax = 8;
    games->rooms[0].secretRoom = 2;

    strcpy(games->rooms[1].nom, "Salle de bain");
    games->rooms[1].xMin = 1;
    games->rooms[1].xMax = 19;
    games->rooms[1].yMin = 14;
    games->rooms[1].yMax = 20;
    games->rooms[1].secretRoom = 3;

    strcpy(games->rooms[2].nom, "Salon");
    games->rooms[2].xMin = 1;
    games->rooms[2].xMax = 15;
    games->rooms[2].yMin = 26;
    games->rooms[2].yMax = 32;
    games->rooms[2].secretRoom = 0;

    strcpy(games->rooms[3].nom, "Hall");
    games->rooms[3].xMin = 31;
    games->rooms[3].xMax = 51;
    games->rooms[3].yMin = 25;
    games->rooms[3].yMax = 32;
    games->rooms[3].secretRoom = 1;

    strcpy(games->rooms[4].nom, "Bibliotheque");
    games->rooms[4].xMin = 58;
    games->rooms[4].xMax = 79;
    games->rooms[4].yMin = 17;
    games->rooms[4].yMax = 27;
    games->rooms[4].secretRoom = 5;

    strcpy(games->rooms[5].nom, "Bureau");
    games->rooms[5].xMin = 48;
    games->rooms[5].xMax = 79;
    games->rooms[5].yMin = 1;
    games->rooms[5].yMax = 11;
    games->rooms[5].secretRoom = 4;
}

int joueurDansPiece(Game *games, Player *joueur) {
    if(games==NULL || joueur ==NULL){
        return -1;
    }

    for (int i=0; i<6; i++){
        if(joueur->x >= games->rooms[i].xMin &&
           joueur->x <= games->rooms[i].xMax &&
           joueur->y >= games->rooms[i].yMin &&
           joueur->y <= games->rooms[i].yMax){

            return i;
        }
    }
    return -1;
}
