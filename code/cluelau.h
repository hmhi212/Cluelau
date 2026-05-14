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

void initialiserCartes();
void combinaisonSecrete(Game *games);
void creerDeck(Game *games);
void melangerCartes(Game *games);
int estDanssolution(Game *games, Card carte);
void distribuerCartes(Game *games);

#endif