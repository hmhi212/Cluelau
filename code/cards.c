#include "cluelau.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Card suspects[6];
Card armes[6];
Card pieces[6];
char plateau[34][82];

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

int joueurPossedeCarte(Player *joueur, Card carte){
    if(joueur == NULL){
        return 0;
    }

    for(int i = 0; i < joueur->nbCartes; i++){
        if(strcmp(joueur->cartes[i].nom, carte.nom) == 0){ // comparer les cartes du joeurs avec celle rechercer
            return 1;
        }
    }

    return 0;

}


Card *revelerCarte(Player *joueur, Card suspect, Card arme, Card piece){

    if(joueur == NULL){
        return NULL;
    }

    Card *cartesPossibles[3];
    int nbCartesPossibles = 0;

    for(int i = 0; i < joueur->nbCartes; i++){
        if(strcmp(joueur->cartes[i].nom, suspect.nom) == 0){
            cartesPossibles[nbCartesPossibles] = &joueur->cartes[i];
            nbCartesPossibles++;
        }

        else if(strcmp(joueur->cartes[i].nom, arme.nom) == 0){
            cartesPossibles[nbCartesPossibles] = &joueur->cartes[i];
            nbCartesPossibles++;
        }

        else if(strcmp(joueur->cartes[i].nom, piece.nom) == 0){
            cartesPossibles[nbCartesPossibles] = &joueur->cartes[i];
            nbCartesPossibles++;
        }
    }

    if(nbCartesPossibles == 0){
        return NULL;
    }

    return cartesPossibles[0];
}

int accusationFinale(Game *games, Card suspect, Card arme, Card piece){
    if(games == NULL){
        return 0;
    }

    if(strcmp(games->solution[0].nom, suspect.nom) == 0 && strcmp(games->solution[1].nom, arme.nom) == 0 && strcmp(games->solution[2].nom, piece.nom) == 0){
        return 1;
    }

    return 0;
}


int veridierVictoireDefaite(Game *games, Player *joueur, Card suspect, Card arme, Card piece){
    if(games == NULL || joueur == NULL){
        return 0;
    }

    if(accusationFinale(games, suspect, arme, piece) == 1){
        return 1;
    }

    else{
        joueur->elimine = 1;
        return 0;
    }
}

Card * faireHypothese(Player *joueurCible, Card suspect, Card arme, Card piece){
    if(joueurCible == NULL){
        return NULL;
    }

    return releverCarte(joueurCible, suspect, arme, piece);
}   


void joueurSuivant(Game *games){
    if(games == NULL){
        return;
    }

    games->joueurCourant = (games->joueurCourant + 1) % games->nbJoueurs; // on a l'int du joueur courant on fait + 1 pour avoir le suivant mais % nb de joueur comme ça quand on arrive au dernier joueur on repasse a 0, on a comme une boucle 

}


void initialiserPartie(Game *games){
    if(games == NULL){
        return;
    }

    initialiserCartes();
    combinaisonSecrete(games);
    creerDeck(games);
    melangerCartes(games);
    distribuerCartes(games);
    games->joueurCourant = 0; // on commence par le premier joueur 


}


int tousJoueursElimines(Game *games){
    if(games == NULL){
        return 0;
    }

    for(int i = 0; i < games->nbJoueurs; i++){
        if(games->joueurs[i].elimine == 0){
            return 0;
        }
        
    }
    return 1;
}


void boucleJeu(Game *games){

    if(games == NULL){
        return;
    }

    creerPlateau(plateau);
    initialiserPositions(games);
    placerJoueurs(games, plateau);
    initialiserPieces(games);

    int partieFinie = 0;

    while(partieFinie == 0){
        Player *joueur = &games->joueurs[games->joueurCourant];

        if(joueur->elimine == 1){
            joueurSuivant(games);
            continue;
        }

        afficherInfosTour(games);

        int deplacement = lancerDes();

        deplacerJoueur(games,plateau,games->joueurCourant,deplacement);

        int dansPiece = joueurDansPiece(games, joueur);
        int choix = recupererChoixAction(joueur);
        if(choix == 1 && dansPiece != -1){

            Card suspect;
            Card arme;
            Card piece;

            choisirElementsHypothese(
                &suspect,
                &arme,
                &piece
            );

            Player *joueurCible = choisirJoueurCible(games);
            Card *carteRevelee = faireHypothese(joueurCible, suspect, arme, piece);

            afficherResultatHypothese(joueur, joueurCible, carteRevelee );
        }

        else if(choix == 2){

            Card suspect;
            Card arme;
            Card piece;

            choisirElementsHypothese(&suspect,&arme,&piece);

            int succes = veridierVictoireDefaite(games, joueur, suspect, arme, piece);

            afficherResultatAccusation(succes,suspect,arme,piece);

            if(succes == 1){
                partieFinie = 1;
            }
        }

        if(tousJoueursElimines(games) == 1){
            partieFinie = 1;
        }

        joueurSuivant(games);
    }
}