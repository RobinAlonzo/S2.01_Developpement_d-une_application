#ifndef PARAMETRES_H
#define PARAMETRES_H

#include "presentation.h"

#include <QDialog>

namespace Ui {class Param;}

class Param : public QDialog
{
    Q_OBJECT

public:
    explicit Param(QWidget *parent = nullptr);
    ~Param();
    void connexionPresentation(Presentation *, QString nomJoueur, unsigned int scoreFin, unsigned int tempsPartie);                                      //Connexion à la présentation
    void deconnexionPresentation(Presentation *);                                    //Deconnexion de la présentation
    void afficherDialog();

    QString getNom() const;
    unsigned int getScore() const;
    unsigned int getTemps() const;

    bool nomModifie() const;            //retourne true si le nom a ete modifie
    bool scoreFinModifie() const;       //retourne true si le score de fin a ete modifie
    bool tempsPartieModifie() const;    //retourne true si le temps de la partie a ete modifie

private slots:
    void param1modifie();               //SLOT permettant de modifier l'etat de _nomModifie
    void param2modifie();               //SLOT permettant de modifier létat de _pointsModifies
    void param3modifie();               //SLOT permettant de modifier l'état de _tempsModifie

private:
    Ui::Param *ui;

    bool _nomModifie;                   //Permet de voir si le nom a ete modifie
    bool _pointsModifies;               //Permet de voir si les points ont ete modifies
    bool _tempsModifie;                 //Permet de voir si le temps a ete modifie

};

#endif // PARAMETRES_H
