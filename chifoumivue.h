#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include "modele.h"
#include "presentation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class ChifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    //initialisation
    ChifoumiVue (QWidget *parent = nullptr);        //Constructeur du chifoumiVue
    ~ChifoumiVue ();                                //Destructeur du chifoumiVue
    void connexionPresentation(QObject *);          //Connexion à la présentation
    void deconnexionPresentation(QObject *);        //Deconnexion de la présentation

    //Getters
    QString getNomJoueur() const;

    //Setter avec parametre booleen
    void setEtatsBJeu(bool);                        //Active/Desactive les boutons de jeu
    void setEtatBPause(bool);                       //Active/Desactive le bouton de pause
    void setEtatBPartie(bool);                      //Active/Desactive le bouton de partie
    void setJoueurEnBleu(bool);                     //Met la partie du joueur en bleu ou en noir en fonction du booleen
    void setEtatActionParam(bool);                  //Active / desactive l action de parametre
    void setEtatActionScores(bool);                 //Active / desactive l action des resultats


    //Maj des labels
    void majImageCoupMachine(Modele::UnCoup);       //Met à jour l image du coup de la machine en fonction du coup en parametre
    void majImageCoupJoueur(Modele::UnCoup);        //Met à jour l image du coup du joueur en fonction du coup en parametre
    void majLabelScoreMachine(unsigned int);        //Met à jour le label représentant le score de la machine en fonction du nombre en parametre
    void majLabelScoreJoueur(unsigned int);         //Met à jour le label représentant le score du joueur en fonction du nombre en parametre
    void majScoresCoups(unsigned int, unsigned int, Modele::UnCoup, Modele::UnCoup);    //Met a jour l ensemble des elements graphiques de scores et de coups en fonction des parametres.
    void initScoreFin(unsigned int);                //Initialise le score de fin
    void majTimer(unsigned int);                    //Met a jour le label du temps restant en fonction du parametre
    void majLabelBPause(QString);                   //Change le label du bouton de pause
    void majNomJoueur(QString);                   //Change le label du nom du joueur

    //Focus
    void setFocusBJouer();                          //Met le focus sur le bouton de parties
    void setFocusBPause();                          //Met le focus sur le bouton de pause

private slots:
    //Slots internes
    void aPropos();             //Affiche une box indiquant la version et les créateurs

private:
    Ui::ChifoumiVue *ui;
};
#endif // CHIFOUMIVUE_H
