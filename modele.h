/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe m�tier (= Mod�le) Chifoumi-v1
 **************************************************************/
#ifndef CHIFOUMI_H
#define CHIFOUMI_H
#include <iostream>

using namespace std;

class Modele
{
    ///* ---- PARTIE MOD�LE ---------------------------

        ///* Une definition de type enumere
    public:
        enum UnCoup {pierre, papier, ciseau, rien};
        enum UnEtat {horsPartie, partieEnCours, partieTerminee};

        ///* Methodes du Mod�le
    public:
        Modele();
        virtual ~Modele();

        // Getters
        UnEtat getEtatJeu();                //Retourne l'état du jeu
        UnCoup getCoupJoueur();             //Retourne le dernier coup jou� par le joueur
        UnCoup getCoupMachine();            //Retourne le dernier coup jou� par le joueur
        unsigned int getScoreJoueur();      //Retourne le score du joueur
        unsigned int getScoreMachine();     //Retourne le score de la machine
        char determinerGagnant();           //Determine le gagnant 'J' pour joueur, 'M' pour machine, 'N' pour match nul en fonction du dernier coup joue par chacun d'eux

         ///* Methodes utilitaires du Mod�le

        UnCoup genererUnCoup();             //Retourne une valeur aleatoire = pierre, papier ou ciseau. Utilisee pour faire jouer la machine

        // Setters
        void setEtatJeu(UnEtat);            //Initialise l'état du jeu
        void setCoupJoueur(UnCoup);         //initialise l'attribut coupJoueur avec la valeur du parametre
        void setCoupMachine(UnCoup);        //Initialise l'attribut coupmachine avec la valeur du parametre
        void setScoreJoueur(unsigned int);  //Initialise l'attribut scoreJoueur avec la valeur  du parametre
        void setScoreMachine(unsigned int); //Initialise l'attribut coupMachine avec la valeur du parametre

        // Autres modificateurs
         void majScores(char);              //Mise a jour des scores en fonction des regles de gestion actuelles :
                                            //- 1 point pour le gagnant lorsqu'il y a un gagnant
                                            //- 0 point en cas de match nul
        void initScores();                  //Initialise a 0 les attributs scoreJoueur et scoreMachine
        void initCoups();                   //Initialise a rien les attributs coupJoueur et coupMachine

         ///* Attributs du Mod�le
     private:
        unsigned int scoreJoueur;   // score actuel du joueur
        unsigned int scoreMachine;  // score actuel de la Machine
        UnCoup coupJoueur;          // dernier coup joue par le joueur
        UnCoup coupMachine;         // dernier coup joue par la machine
        UnEtat etatJeu;             //état du jeu // Initialisé à horsPartie
};

#endif // CHIFOUMI_H
