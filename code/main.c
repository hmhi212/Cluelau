#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cluelau.h"

// Prototypes des fonctions de Hatem présentes dans player.c et ui.c
void configurerConfigurationPartie(int *nbHumains, int *nbIAFacile, int *nbIADifficile);
void configurerJoueursPartie(Game *games, int nbHumains, int nbIAFacile, int nbIADifficile);
void afficherMenuPrincipal();
void afficherRegles();

int main() {
    // Initialisation du generateur de nombres aleatoires
    srand((unsigned int)time(NULL));

    char plateau[34][82];
    Game games;
    int choixMenu = 0;

    do {
        afficherMenuPrincipal();
        if (scanf("%d", &choixMenu) != 1) {
            while (getchar() != '\n'); // Securisation
            continue;
        }

        if (choixMenu == 1) {
            int humains = 0, iaFaciles = 0, iaDifficiles = 0;
            
            // 1. Hatem recupere les effectifs de la partie
            configurerConfigurationPartie(&humains, &iaFaciles, &iaDifficiles);
            
            // 2. Hatem injecte ces profils dans la structure de jeu
            configurerJoueursPartie(&games, humains, iaFaciles, iaDifficiles);
            
            // 3. Amal prend le relais pour initialiser l'enquete (cartes, secret, distribution)
            initialiserPartie(&games);
            
            // 4. Initialisations et affichages de Louis pour la map graphique
            // creerPlateau(plateau);
            // initialiserPositions(&games);
            // placerJoueurs(&games, plateau);
            
            // // Petit debug d'affichage de la solution (a commenter en jeu reel !)
            // printf("\n[DEVELOPPEUR] Solution cachee : %s | %s | %s\n", 
            //        games.solution[0].nom, games.solution[1].nom, games.solution[2].nom);
            
            // afficherPlateau(plateau);

            // // 5. Demarrage de la grande boucle de jeu d'Amal
            // boucleJeu(&games);
            
            printf("\nFin de la partie en cours. Retour au menu...\n");

        } else if (choixMenu == 2) {
            afficherRegles();
        }

    } while (choixMenu != 3);

    printf("\nFermeture du systeme ClueLau. A bientot !\n");
    return 0;
}
