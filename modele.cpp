/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe m�tier (= mod�le) Chifoumi-v1
 **************************************************************/
#include "modele.h"

#include <cstdlib>
#include <ctime>


    ///* ---- PARTIE MOD�LE ---------------------------

Modele::Modele()
{
    (*this).initScores();
    (*this).initCoups();
    etatJeu = horsPartie;
}

Modele::~Modele()
{}

Modele::UnEtat Modele::getEtatJeu()
{
    return etatJeu;
}

void Modele::setEtatJeu(UnEtat etat)
{
    etatJeu = etat;
}

Modele::UnCoup Modele::getCoupJoueur() {
    return (*this).coupJoueur;
}

Modele::UnCoup Modele::getCoupMachine() {
    return (*this).coupMachine;
}

unsigned int Modele::getScoreJoueur() {
    return (*this).scoreJoueur;
}

unsigned int Modele::getScoreMachine() {
    return (*this).scoreMachine;
}

char Modele::determinerGagnant()
{
    char gagnantARetourner;

    if (coupJoueur == coupMachine)
        gagnantARetourner = 'N';
    else
    {
        if (coupMachine == ciseau)
        {
            if (coupJoueur == pierre)
                gagnantARetourner = 'J';
            else
                //Papier
                gagnantARetourner = 'M';
        }
        else if (coupMachine == pierre)
        {
            if (coupJoueur == papier)
                gagnantARetourner = 'J';
            else
                //ciseau
                gagnantARetourner = 'M';
        }
        else
        {
            //Papier
            if (coupJoueur == ciseau)
                gagnantARetourner = 'J';
            else
                //Pierre
                gagnantARetourner = 'M';
        }
    }

    return gagnantARetourner;
}


         ///* Methodes utilitaires du Modele

int randMinMax(int min, int max){
    /* pr�-condition : min<max ;
       Le nbre al�atoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

Modele::UnCoup Modele::genererUnCoup()
{
    UnCoup coupCorrespondant;   // valeur a retourner

    unsigned short int valeurGeneree;
    valeurGeneree = randMinMax(0, 3);   //Valeur aleatoire entre 0 et 2

    switch (valeurGeneree)
    {
    case 0: coupCorrespondant = pierre;  break;
    case 1: coupCorrespondant = papier;  break;
    case 2: coupCorrespondant = ciseau;  break;
    default: coupCorrespondant = rien;   break;
    }

    return coupCorrespondant;
}

        /// Setters

void Modele::setCoupJoueur(UnCoup p_coup)
{
    (*this).coupJoueur = p_coup;
}

void Modele::setCoupMachine(UnCoup p_coup)
{
    (*this).coupMachine = p_coup;
}

void Modele::setScoreJoueur(unsigned int p_score)
{
    (*this).scoreJoueur = p_score;
}

void Modele::setScoreMachine(unsigned int p_score)
{
    (*this).scoreMachine = p_score;
}

void Modele::majScores(char p_gagnant)
{
    switch (p_gagnant)
    {
    case 'J': (*this).scoreJoueur++; break;
    case 'M': (*this).scoreMachine++; break;
    case 'N': break; //Case 'N' ou default ?
    }
}

void Modele::initScores()
{
    (*this).scoreJoueur = 0;
    (*this).scoreMachine = 0;
}

void Modele::initCoups()
{
    (*this).coupJoueur = rien;
    (*this).coupMachine = rien;
}

