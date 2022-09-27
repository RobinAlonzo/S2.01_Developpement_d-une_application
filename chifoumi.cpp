/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe m�tier (= mod�le) Chifoumi-v1
 **************************************************************/
#include "chifoumi.h"

#include <cstdlib>
#include <ctime>


    ///* ---- PARTIE MOD�LE ---------------------------

Chifoumi::Chifoumi()
{
    (*this).initScores();
    (*this).initCoups();
}

Chifoumi::~Chifoumi()
{}

        // Getters

Chifoumi::UnCoup Chifoumi::getCoupJoueur() {
	return (*this).coupJoueur;
}

Chifoumi::UnCoup Chifoumi::getCoupMachine() {
    return (*this).coupMachine;
}

unsigned int Chifoumi::getScoreJoueur() {
    return (*this).scoreJoueur;
}

unsigned int Chifoumi::getScoreMachine() {
    return (*this).scoreMachine;
}

char Chifoumi::determinerGagnant()
{
    char gagnantARetourner;

    if ((*this).coupJoueur == (*this).coupMachine) 
        gagnantARetourner = 'N';
    else
    {
        if ((*this).coupMachine == ciseau)
        {
            if ((*this).coupJoueur == pierre)
                gagnantARetourner = 'J';
            else if ((*this).coupJoueur == papier)
                gagnantARetourner = 'M';
        }
        else if ((*this).coupMachine == pierre)
        {
            if ((*this).coupJoueur == papier)
                gagnantARetourner = 'J';
            else if ((*this).coupJoueur == ciseau)
                gagnantARetourner = 'M';
        }
        else if ((*this).coupMachine == papier)
        {
            if ((*this).coupJoueur == ciseau)
                gagnantARetourner = 'J';
            else if ((*this).coupJoueur == pierre)
                gagnantARetourner = 'M';
        }
    }
    
    return gagnantARetourner;
}


         ///* M�thodes utilitaires du Mod�le

int randMinMax(int min, int max){
    /* pr�-condition : min<max ;
       Le nbre al�atoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

Chifoumi::UnCoup Chifoumi::genererUnCoup()
{
    UnCoup coupCorrespondant;   // valeur � retourner
    unsigned short int valeurGeneree;
    valeurGeneree = randMinMax(0, 3);

    switch (valeurGeneree)
    {
    case 0: coupCorrespondant = pierre;  break;
    case 1: coupCorrespondant = papier;  break;
    case 2: coupCorrespondant = ciseau;  break;
    }

    return coupCorrespondant;
}

        /// Setters

void Chifoumi::setCoupJoueur(UnCoup p_coup) 
{
    (*this).coupJoueur = p_coup;
}

void Chifoumi::setCoupMachine(UnCoup p_coup) 
{
    (*this).coupMachine = p_coup;
}

void Chifoumi::setScoreJoueur(unsigned int p_score)
{
    (*this).scoreJoueur = p_score;
}

void Chifoumi::setScoreMachine(unsigned int p_score)
{
    (*this).scoreMachine = p_score;
}

void Chifoumi::majScores(char p_gagnant) 
{
    switch (p_gagnant)
    {
    case 'J': (*this).scoreJoueur++; break;
    case 'M': (*this).scoreMachine++; break;
    case 'N': break; //Case 'N' ou default ?
    }
}

void Chifoumi::initScores()
{
    (*this).scoreJoueur = 0;
    (*this).scoreMachine = 0;
}

void Chifoumi::initCoups() 
{
    (*this).coupJoueur = rien;
    (*this).coupMachine = rien;
}

