#include "cluelau.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Card suspects[6];
Card armes[6];
Card pieces[6];

void initialiserCartes(){
    // initialise tous les suspects : 
    strcpy(suspects[0].nom, "Rose");
    suspects[0].type = 0;
    strcpy(suspects[1].nom, "Violet");
    suspects[1].type = 0;
    strcpy(suspects[2].nom, "Olive");
    suspects[2].type = 0;
    strcpy(suspects[3].nom, "Le_Noir");
    suspects[3].type = 0;
    strcpy(suspects[4].nom, "Pervenche");
    suspects[4].type = 0;
    strcpy(suspects[5].nom, "Moutarde");
    suspects[5].type = 0;

    // initalise les armes :
    strcpy(armes[0].nom, "Revolver");
    armes[0].type = 1;
    strcpy(armes[1].nom, "Chandelier");
    armes[1].type = 1;
    strcpy(armes[2].nom, "Corde");
    armes[2].type = 1;
    strcpy(armes[3].nom, "Couteau");
    armes[3].type = 1;
    strcpy(armes[4].nom, "Cle anglaise");
    armes[4].type = 1;
    strcpy(armes[5].nom, "Cric");
    armes[5].type = 1;

    //initialise les pieces :
    strcpy(pieces[0].nom, "Cuisine");
    pieces[0].type = 2;
    strcpy(pieces[1].nom, "Salle de bain");
    pieces[1].type = 2;
    strcpy(pieces[2].nom, "Salon");
    pieces[2].type = 2;
    strcpy(pieces[3].nom, "Bureau");
    pieces[3].type = 2;
    strcpy(pieces[4].nom, "Bibliotheque");
    pieces[4].type = 2;
    strcpy(pieces[5].nom, "Hall");
    pieces[5].type = 2;

}


void combinaisonSecrete(Game *games){
    if (games == NULL){
        return;
    }

    int s = rand() % 6 ;
    int a = rand() % 6;
    int p = rand() % 6;

    games->solution[0] = suspects[s];
    games->solution[1] = armes[a];
    games->solution[2] = pieces[p];
    
}


void creerDeck(Game *games){
    if(games == NULL){
        return;
    }
    
    for(int i = 0; i < 6; i++){
        games->deck[i] = suspects[i];
    }
    for(int i = 6; i < 12; i++ ){
        games->deck[i] = armes[i - 6 ];
    }
    for(int i = 12; i< 18; i++){
        games->deck[i] = pieces[i - 12];
    }

}

void melangerCartes(Game *games){
    if( games == NULL){
        return;
    }

    for(int i = 0; i < 18; i++){
        int idx = rand() % 18;
        Card temp = games->deck[i];
        games->deck[i] = games->deck[idx];
        games->deck[idx] = temp;

    }

}

int estDanssolution(Game *games, Card carte){
    if(games == NULL){
        return 0;
    }

    for(int i = 0; i < 3; i++){
        if(strcmp(carte.nom, games->solution[i].nom) == 0){ //comparer les chaines de caracteres si elles sont identiques avec strcmp 
            return 1;
        }
    }

    return 0;
    
}

void distribuerCartes(Game *games){
    if(games == NULL){
        return;
    }

    if(games->nbJoueurs <= 0){ // verifie qu'on ne divise pas par 0
        return;
    }

    for(int i = 0; i < games->nbJoueurs; i++){
        games->joueurs[i].nbCartes = 0;  // on remets les cartes a 0 pour chaque joueurs
    }

    int joueurActuel = 0;

    for(int i = 0; i < 18; i++){

        if(estDanssolution(games, games->deck[i]) == 0){ // ignore les cartes de la combinaison secrete
            Player *joueur = &games->joueurs[joueurActuel]; // pointeur vers le joueur actuel
            joueur->cartes[joueur->nbCartes] = games->deck[i]; // ajoute la carte du deck dans les cartes du joueur 
            joueur->nbCartes ++; // augmente les cartes du joeur
            joueurActuel = (joueurActuel + 1) % games->nbJoueurs; // passe au joueur suivant
        }
    }
}