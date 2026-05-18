#ifndef CLUELAU_H
#define CLUELAU_H

// =========================================================================
// STRUCTURES DE DONNÉES DE BASE (Logique Amal & Louis)
// =========================================================================

typedef struct {
    char nom[50]; 
    int type; // 0 = suspect, 1 = arme, 2 = piece
} Card;

typedef struct {
    char nom[50];
    int type; // 0 = humain, 1 = IA facile ou 2 = IA difficile
    int elimine; // 0 = actif ou 1 = elimine
    int x;
    int y;
    Card cartes[10]; // cartes du joueur
    int nbCartes;
} Player;

typedef struct {
    char nom[50];
    int xMin; 
    int xMax; 
    int yMin; 
    int yMax; 
    int secretRoom; // -1 = pas de passage secret, 0 = piece reliee, 1 = autre piece reliee
} Room;

typedef struct {
    Player joueurs[6];
    int nbJoueurs;
    Card solution[3];
    Room rooms[6];
    int joueurCourant;
    Card deck[18];
} Game;

// =========================================================================
// FONCTIONS DE LOGIQUE ET DE CARTES (Amal - cards.c / game.c)
// =========================================================================

// Initialise toutes les cartes du jeu donc suspects, armes et pieces
void initialiserCartes();
// Genere aleatoirement la combinaison secrete
void combinaisonSecrete(Game *games);
// Creer le paquet de cartes
void creerDeck(Game *games);
// Melange aleatoirement le paquet
void melangerCartes(Game *games);
// Verifie si une des cartes appartient a la combinaison secrete
int estDanssolution(Game *games, Card carte);
// Distribue les cartes aux joueurs
void distribuerCartes(Game *games);
// Verifie si l'accusation finale est correcte ou pas
int accusationFinale(Game *games, Card suspect, Card arme, Card piece);
// Verifie la victoire ou la defaite d'une accusation
int veridierVictoireDefaite(Game *games, Player *joueur, Card suspect, Card arme, Card piece);
// Gere le deroulement principal de la partie
void boucleJeu(Game *games);
// Gere une hypothese et retourne la carte revelee
Card *faireHypothese(Game *games, int joueurCourant, Card suspects, Card arme, Card piece);
// Passer au joueur suivant
void joueurSuivant(Game *games); 
// Initialise le debut d'une partie 
void initialiserPartie(Game *games);
// Verifie si tous les joueurs sont elimines (1 = tous elimines, 0 = encore actif)
int tousJoueursElimines(Game *games); 

// =========================================================================
// FONCTIONS DE MAP ET PLATEAU GRAPHIQUE (Louis - board.c / notes.c)
// =========================================================================

// Cree et affiche le plateau
void creerPlateau(char plateau[34][82]);
void afficherPlateau(char plateau[34][82]);
// Lance les des
int lancerDes();
// Definit les positions initiales des pions
void initialiserPositions(Game *games);
// Affiche les pions sur le plateau (positions joueurs)
void placerJoueurs(Game *games, char plateau[34][82]);
// Deplacer un joueur sur la grille
void deplacerJoueur(Game *games, char plateau[34][82], int joueurIndex, int deplacement);
// Gère le tour complet des déplacements des joueurs
void tourDeplacementJoueurs(Game *games, char plateau[34][82]);



// Fonctions de configuration des profils (player.c)
void configurerConfigurationPartie(int *nbHumains, int *nbIAFacile, int *nbIADifficile);
void configurerJoueursPartie(Game *games, int nbHumains, int nbIAFacile, int nbIADifficile);

// Fonctions d'affichage textuel et interaction menus (ui.c)
void afficherMenuPrincipal();
void afficherRegles();
void afficherInfosTour(Game *games);
void afficherCartesJoueur(Player *joueur);
int recupererChoixAction(Player *joueur);
void choisirElementsHypothese(Card *suspect, Card *arme, Card *piece);
void afficherResultatHypothese(Player *demandeur, Player *repondeur, Card *carteDejouee);
void afficherResultatAccusation(int succes, Card s, Card a, Card p);

#endif
