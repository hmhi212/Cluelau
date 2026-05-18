#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cluelau.h"

// Tableaux de correspondance pour traduire les ID des cartes d'Amal en texte propre
static const char* TEXTE_SUSPECTS[] = {"Rose", "Violet", "Olive", "Le_Noir", "Pervenche", "Moutarde"};
static const char* TEXTE_ARMES[] = {"Revolver", "Chandelier", "Corde", "Couteau", "Cle anglaise", "Cric"};
static const char* TEXTE_PIECES[] = {"Cuisine", "Salle de bain", "Salon", "Bureau", "Bibliotheque", "Hall"};

static int saisirChoixUI(int min, int max) {
    int valeur;
    int valide = 0;
    while (!valide) {
        if (scanf("%d", &valeur) == 1) {
            if (valeur >= min && valeur <= max) {
                valide = 1;
            } else {
                printf("Option invalide. Choisissez entre %d et %d : ", min, max);
            }
        } else {
            printf("Format invalide. Entrez un nombre entier : ");
            while (getchar() != '\n');
        }
    }
    return valeur;
}

void afficherMenuPrincipal() {
    printf("\n=================================================\n");
    printf("             * BIENVENUE SUR CLUELAU * \n");
    printf("=================================================\n");
    printf("  1. Lancer une partie d'enquete\n");
    printf("  2. Consulter le livret des regles\n");
    printf("  3. Quitter le terminal\n");
    printf("=================================================\n");
    printf("Votre choix : ");
}

void afficherRegles() {
    printf("\n--- LIVRET DES REGLES DE CLUELAU ---\n");
    printf("But : Decouvrir qui a tue, avec quelle arme et dans quelle piece.\n");
    printf("Deplacements : Lancez les des pour vous deplacer vers les pieces.\n");
    printf("Hypotheses : Faites une suggestion dans une piece pour verifier les cartes des autres.\n");
    printf("Accusation : Si vous pensez avoir trouve, portez une accusation finale (Quitte ou double !).\n");
    printf("------------------------------------\n");
}

void afficherInfosTour(Game *games) {
    Player actuel = games->joueurs[games->joueurCourant];
    printf("\n-------------------------------------------------\n");
    printf(" C'EST AU TOUR DE : %s ", actuel.nom);
    if (actuel.type == 0) printf("[HUMAIN]\n");
    else if (games->joueurs[games->joueurCourant].type == 1) printf("[IA FACILE]\n");
    else printf("[IA EXPERT]\n");
    printf("-------------------------------------------------\n");
}

void afficherCartesJoueur(Player *joueur) {
    printf("\n[VOS CARTES EN MAIN] :\n");
    if (joueur->nbCartes == 0) {
        printf("  -> Vous n'avez aucune carte en main.\n");
        return;
    }
    for (int i = 0; i < joueur->nbCartes; i++) {
        // Adaptation stricte aux types d'Amal (0=suspect, 1=arme, 2=piece)
        if (joueur->cartes[i].type == 0) {
            printf("  - [Suspect] %s\n", joueur->cartes[i].nom);
        } else if (joueur->cartes[i].type == 1) {
            printf("  - [Arme]    %s\n", joueur->cartes[i].nom);
        } else if (joueur->cartes[i].type == 2) {
            printf("  - [Piece]   %s\n", joueur->cartes[i].nom);
        }
    }
    printf("\n");
}

int recupererChoixAction(Player *joueur) {
    if (joueur->elimine == 1) {
        printf("[INFO] Vous êtes elimine. Vous pouvez observer ou consulter vos notes.\n");
        printf(" 1. Passer votre tour (Laisser jouer les autres)\n");
        printf(" 2. Consulter votre Bloc-notes individuel\n");
        printf("Choix : ");
        int c = saisirChoixUI(1, 2);
        return (c == 1) ? 5 : 4; // Codes d'actions internes
    }

    printf("=== QUE VOULEZ-VOUS FAIRE ? ===\n");
    printf(" 1. Lancer le de et se deplacer\n");
    printf(" 2. Emettre une hypothese (Doit etre dans une piece)\n");
    printf(" 3. Porter une ACCUSATION FINALE\n");
    printf(" 4. Ouvrir le Bloc-notes secret\n");
    printf("Choix : ");
    return saisirChoixUI(1, 4);
}

void choisirElementsHypothese(Card *suspect, Card *arme, Card *piece) {
    printf("\n--- FORMULATION DE L'HYPOTHESE ---\n");
    
    printf("Selectionnez un suspect suspecte :\n");
    for(int i = 0; i < 6; i++) printf("  %d. %s\n", i + 1, TEXTE_SUSPECTS[i]);
    printf("Index : ");
    int sSel = saisirChoixUI(1, 6) - 1;
    suspect->type = 0;
    strcpy(suspect->nom, TEXTE_SUSPECTS[sSel]);

    printf("\nSelectionnez l'arme du crime :\n");
    for(int i = 0; i < 6; i++) printf("  %d. %s\n", i + 1, TEXTE_ARMES[i]);
    printf("Index : ");
    int aSel = saisirChoixUI(1, 6) - 1;
    arme->type = 1;
    strcpy(arme->nom, TEXTE_ARMES[aSel]);

    printf("\nSelectionnez la piece du delit :\n");
    for(int i = 0; i < 6; i++) printf("  %d. %s\n", i + 1, TEXTE_PIECES[i]);
    printf("Index : ");
    int pSel = saisirChoixUI(1, 6) - 1;
    piece->type = 2;
    strcpy(piece->nom, TEXTE_PIECES[pSel]);
}

void afficherResultatHypothese(Player *demandeur, Player *repondeur, Card *carteDejouee) {
    printf("\n[RAPPORT D'HYPOTHESE]\n");
    if (repondeur == NULL) {
        printf("-> Silence radio... Aucun joueur ne peut contrer l'hypothese de %s.\n", demandeur->nom);
    } else {
        printf("-> %s a montre une carte a %s pour invalider son hypothese.\n", repondeur->nom, demandeur->nom);
        
        // Regle de confidentialite : Seul l'emetteur humain voit la carte
        if (demandeur->type == 0) {
            printf("[SECRET] La carte qui vous a ete revelee est : %s\n", carteDejouee->nom);
        } else {
            printf("[INFO] La carte revelee reste secrete pour vous car l'hypothese provient d'une IA.\n");
        }
    }
}

void afficherResultatAccusation(int succes, Card s, Card a, Card p) {
    printf("\n=================================================\n");
    printf("               VERDICT DE LA COUR                \n");
    printf("=================================================\n");
    printf("Accusation : %s | %s | %s\n", s.nom, a.nom, p.nom);
    
    if (succes) {
        printf("\n[VICTOIRE] L'accusation est vraie ! L'enquete se cloture sur un succes.\n");
    } else {
        printf("\n[ECHEC] L'accusation est fausse ! Le coupable court toujours. L'enqueteur est disqualifie.\n");
    }
    printf("=================================================\n");
}
 Player *choisirJoueurCible(Game *games) {
    printf("\n--- CIBLE DE L'ENQUETE ---\n");
    printf("Choisissez le joueur a interroger :\n");

    int choixValides[6];
    int compteurOptions = 1;

    for (int i = 0; i < games->nbJoueurs; i++) {
        if (i == games->joueurCourant) {
            continue;
        }

        printf("  %d. %s", compteurOptions, games->joueurs[i].nom);
       
        if (games->joueurs[i].type == 0) printf(" [HUMAIN]\n");
        else printf(" [IA]\n");

        choixValides[compteurOptions] = i;
        compteurOptions++;
    }

    if (compteurOptions == 1) {
        printf("Aucun autre joueur disponible.\n");
        return NULL;
    }

    printf("Votre choix : ");
   


    int selection = saisirChoixUI(1, compteurOptions - 1);

   
    int indexJoueurCible = choixValides[selection];

    return &games->joueurs[indexJoueurCible];
}

Card *choisirCarteAReveler(Player *joueur,Card *cartesPossibles[],int nbCartesPossibles){

    if(joueur == NULL || nbCartesPossibles <= 0){
        return NULL;
    }

    printf("\n--- CHOIX DE LA CARTE A REVELER ---\n");

    for(int i = 0; i < nbCartesPossibles; i++){

        printf(
            "%d. %s\n",
            i + 1,
            cartesPossibles[i]->nom
        );
    }

    printf("Choisissez une carte : ");

    int choix =
        saisirChoixUI(1, nbCartesPossibles);

    return cartesPossibles[choix - 1];
}