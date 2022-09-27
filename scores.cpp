#include "scores.h"
#include "ui_scores.h"

#include <QDebug>
#include <QStandardItemModel>

Scores::Scores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Scores)
{
    ui->setupUi(this);

    //Mise des noms de colonnes
    QStringList header;                                             //nom des colonnes
    header << "Joueur" << "Score joueur" << "Machine" << "Score machine";
    ui->tableau->setColumnCount(header.size());                     // On fixe le nombre de colonnes
    ui->tableau->setHorizontalHeaderLabels(header);                 //On applique les noms des colonnes

    //Redimensionnement
    QHeaderView * horizontalHeaderView = ui->tableau->horizontalHeader();
    horizontalHeaderView->setSectionResizeMode(QHeaderView::Stretch);

    setModal(true);                 //Met la fenetre en modale
    setWindowTitle("Resultats");    //Change le nom de la fenetre
    connect(ui->bEffacer, SIGNAL(clicked()), this, SIGNAL(demandeEffacement()));    //Redirection du signal du clic sur effacer en dehors du widget
}

Scores::~Scores()
{
    delete ui;
}

void Scores::majValeurs(QList<QString> &nomJoueur, QList<QString> &scoreJoueur, QList<QString> &nomMachine, QList<QString> &scoreMachine)
{
    ui->tableau->setRowCount(0);                //On efface toutes les lignes du tableau
    //Replissage des enregistrements un à uns
    for (int i =0; i<nomJoueur.length(); i++)
    {
        QString Joueur = nomJoueur[i];
        QString sJoueur = scoreJoueur[i];
        QString Machine = nomMachine[i];
        QString sMachine = scoreMachine[i];

        ui->tableau->insertRow(i);  //Rajout d une ligne d enregistrement

        //Ajout de l enregistrement element par element
        QTableWidgetItem *nJoueur = new QTableWidgetItem(Joueur);
        ui->tableau->setItem(i,0,nJoueur);
        QTableWidgetItem *sjoueur = new QTableWidgetItem(sJoueur);
        ui->tableau->setItem(i,1,sjoueur);
        QTableWidgetItem *nMachine = new QTableWidgetItem(Machine);
        ui->tableau->setItem(i,2,nMachine);
        QTableWidgetItem *smachine = new QTableWidgetItem(sMachine);
        ui->tableau->setItem(i,3,smachine);
    }
}
