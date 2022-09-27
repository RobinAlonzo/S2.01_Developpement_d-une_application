#include "parametres.h"
#include "ui_parametres.h"


Param::Param(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Param)
{
    ui->setupUi(this);
    QObject::connect(ui->bAnnuler,SIGNAL(clicked()),this,SLOT(close())); //Permet de fermer la fenetre de dialog lorsque le joueur clique sur annuler
    QObject::connect(ui->bValider,SIGNAL(clicked()),this,SLOT(close())); //Permet de fermer la fenetre de dialog lorsque le joueur clique sur valider
    QObject::connect(ui->lineEditNom, SIGNAL(editingFinished()), this, SLOT(param1modifie()));
    QObject::connect(ui->lineEditPoints, SIGNAL(editingFinished()), this, SLOT(param2modifie()));
    QObject::connect(ui->lineEditTemps, SIGNAL(editingFinished()), this, SLOT(param3modifie()));

    setWindowTitle("Paramètres");
}

Param::~Param()
{
    delete ui;
}

void Param::connexionPresentation(Presentation *p, QString nomJoueur, unsigned int scoreFin, unsigned int tempsPartie)
{
    //pour se connecter avec la presentation
    QObject::connect(ui->bValider,SIGNAL(clicked()),p,SLOT(modifParametres())); //Connexion à la présentation lorsque le joueur valide les paramètres
    //Initialisation des noms, score final et temps de partie de la présentation
    ui->lineEditNom->setText(nomJoueur);
    ui->lineEditPoints->setText(QString::number(scoreFin));
    ui->lineEditTemps->setText(QString::number(tempsPartie));
}
void Param::deconnexionPresentation(Presentation *p)
{
    //pour se deconnecter de la presentation
     QObject::disconnect(ui->bValider,SIGNAL(clicked()),p,SLOT(modifierParametres())); //Deconnexion de la présentation
}

void Param::afficherDialog()
{
    //Initialisation des booleens
    _nomModifie = false;
    _pointsModifies = false;
    _tempsModifie = false;
    ui->bValider->setFocus();
    show();
}

QString Param::getNom() const
{
    return ui->lineEditNom->text();
}

unsigned int Param::getScore() const
{
    return ui->lineEditPoints->text().toInt();
}

unsigned int Param::getTemps() const
{
    return ui->lineEditTemps->text().toInt();
}

bool Param::nomModifie() const
{
    return _nomModifie;
}

bool Param::scoreFinModifie() const
{
    return _pointsModifies;
}

bool Param::tempsPartieModifie() const
{
    return _tempsModifie;
}



//Slots internes
void Param::param1modifie()
{
    _nomModifie = true;
}
void Param::param2modifie()
{
    _pointsModifies = true;
}

void Param::param3modifie()
{
    _tempsModifie = true;
}






