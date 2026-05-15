#ifndef CLUELAU_H
#define CLUELAU_H

typedef struct {
    char nom[50]; 
    int type; // 0 = suspect, 1 = arme, 2 = piece

}Card;

typedef struct{
    char nom[50];
    int type; // 0 = humain,1 = IA facile ou 2 = IA difficile
    int elimine; // 0 = actif ou 1 = elimine
    int x;
    int y;
    Card cartes[10]; // cartes du joueurs
    int nbCartes;

}Player;

typedef struct {
    char nom[50];
    int xMin; 
    int xMax; 
    int yMin; 
    int yMax; 
    int secretRoom; // -1 = pas de passage secret, 0 = piece reliee, 1= autre piece reliee

}Room;

typedef struct {
    Player joueurs[6];
    int nbJoueurs;
    Card solution[3];
    Room rooms[6];
    int joueurCourant;
    Card deck[18];

}Game;

// initialise toutes les cartes du jeu donc supects, armes et pieces
void initialiserCartes();
//genere aleatoirement la combinaison secrete
void combinaisonSecrete(Game *games);
// creer le paquet de cartes
void creerDeck(Game *games);
// melange aleatoirement le paquet
void melangerCartes(Game *games);
// verifie si une des cartes appartient a la combinaison secrete
int estDanssolution(Game *games, Card carte);
// distribue les carte aux joueurs
void distribuerCartes(Game *games);
// verifie si un joueur possede une carte
int joueurPossedeCarte(Player *joueur, Card carte);
// cherche le premier joueur pouvant repondre a une hypothese
Player * trouverJoueurCarte(Game * games, int joueurCourant, Card suspect, Card arme, Card piece);
// revele une carte de l'hypothese
Card *revelerCarte(Player *joueur, Card suspect, Card arme, Card piece);
// verifie si accusation finale est correcte ou pas
int accusationFinale(Game *games, Card suspect, Card arme, Card piece);
// verifie la victoire ou la defaite d'une accusation
int veridierVictoireDefaite(Game *games, Player *joueur, Card suspect, Card arme, Card piece);
// gere le deroulement principale de la partie
void boucleJeu(Game * games);
// gere une hypothese et retourne la carte revelee
Card * faireHypothese(Game * games, int joueurCourant, Card suspects, Card arme, Card piece);
// passer au joueur suivant
void joueurSuivant(Game *games); 
// initialise le début d'une partie 
void initialiserPartie(Game *games);

#endif