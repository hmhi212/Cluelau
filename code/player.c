#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cluelau.h"

// Fonction utilitaire interne pour sécuriser la saisie des nombres entiers
static int saisirNombre(int min, int max) {
    int valeur;
    int valide = 0;
    while (!valide) {
        if (scanf("%d", &valeur) == 1) {
            if (valeur >= min && valeur <= max) {
                valide = 1;
            } else {
                printf("Entree hors limites. Veuillez choisir entre %d et %d : ", min, max);
            }
        } else {
            printf("Saisie incorrecte. Veuillez entrer un chiffre : ");
            while (getchar() != '\n'); // Vide le buffer
        }
    }
    return valeur;
}

// Récupère les paramètres de la partie demandés à l'utilisateur
void configurerConfigurationPartie(int *nbHumains, int *nbIAFacile, int *nbIADifficile) {
    int total = 0;
    
    printf("\n=================================================\n");
    printf("         CONFIGURATION DES ENQUETEURS            \n");
    printf("=================================================\n");
    
    do {
        printf(" -> Nombre de joueurs humains (0 a 6) : ");
        *nbHumains = saisirNombre(0, 6);
        
        printf(" -> Nombre d'IAs faciles (0 a 6) : ");
        *nbIAFacile = saisirNombre(0, 6);
        
        printf(" -> Nombre d'IAs difficiles (0 a 6) : ");
        *nbIADifficile = saisirNombre(0, 6);
        
        total = *nbHumains + *nbIAFacile + *nbIADifficile;
        
        if (total < 2 || total > 6) {
            printf("\n[ATTENTION] Le ClueLau se joue de 2 a 6 joueurs total (Actuellement : %d).\n", total);
            printf("Veuillez rééquilibrer vos effectifs.\n\n");
        }
    } while (total < 2 || total > 6);
    
    printf("\n[OK] Configuration validee : %d Humain(s) | %d IA(s) Facile | %d IA(s) Expert.\n", *nbHumains, *nbIAFacile, *nbIADifficile);
}

// Initialise le tableau des joueurs présent dans la structure Game
void configurerJoueursPartie(Game *games, int nbHumains, int nbIAFacile, int nbIADifficile) {
    int index = 0;
    games->nbJoueurs = nbHumains + nbIAFacile + nbIADifficile;

    // 1. Les Humains
    for (int i = 0; i < nbHumains; i++) {
        sprintf(games->joueurs[index].nom, "Joueur_%d", i + 1);
        games->joueurs[index].type = 0; // 0 = humain selon cluelau.h
        games->joueurs[index].elimine = 0;
        games->joueurs[index].nbCartes = 0;
        index++;
    }
    
    // 2. Les IA Faciles
    for (int i = 0; i < nbIAFacile; i++) {
        sprintf(games->joueurs[index].nom, "IA_Facile_%d", i + 1);
        games->joueurs[index].type = 1; // 1 = IA facile selon cluelau.h
        games->joueurs[index].elimine = 0;
        games->joueurs[index].nbCartes = 0;
        index++;
    }
    
    // 3. Les IA Difficiles
    for (int i = 0; i < nbIADifficile; i++) {
        sprintf(games->joueurs[index].nom, "IA_Expert_%d", i + 1);
        games->joueurs[index].type = 2; // 2 = IA difficile selon cluelau.h
        games->joueurs[index].elimine = 0;
        games->joueurs[index].nbCartes = 0;
        index++;
    }
}
