#include "db.h"
#include "qdebug.h"
#include "qsqlquery.h"

#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>

Db::Db(QString nomDb, QObject *parent)
    : QObject{parent}
    , DB_NAME(nomDb)
{
    //Initialisation des informations de la BDD
    db= QSqlDatabase::addDatabase(CONNECT_TYPE);
    db.setDatabaseName(DB_NAME);
}


void Db::insererResultat(QString nomJoueur, unsigned int scoreJoueur, unsigned int scoreMachine)
{
    //Ouverture de la BDD
    if (!db.open())
    {
        qDebug() << "Connexion ratée, impossible d ajouter des scores";
    }
    else
    {
        QSqlQuery createTable;
        createTable.exec("CREATE TABLE Resultat (id INT PRIMARY KEY NOT NULL AUTO_INCREMENT, nomJoueur VARCHAR(20), scoreJoueur INT(10), nomMachine VARCHAR(20), scoreMachine INT(10))");
        QSqlQuery insertResultat;
        insertResultat.prepare("INSERT INTO Resultat (nomJoueur, scoreJoueur, nomMachine, scoreMachine) VALUES (:Joueur, :scoreJ, :Machine, :scoreM)");
        insertResultat.bindValue(":Joueur", nomJoueur);
        insertResultat.bindValue(":scoreJ", scoreJoueur);
        insertResultat.bindValue(":Machine", "Machine");
        insertResultat.bindValue(":scoreM", scoreMachine);
        insertResultat.exec();
        db.close();
    }
}



unsigned short int Db::analyseIdentifiants(QString id, QString mdp)
{
    //Ouverture de la BDD

    if (db.open())
    {
        QSqlQuery req;
        req.prepare("SELECT motDePasse FROM Utilisateur WHERE nom = ?");
        req.addBindValue(id);
        req.exec();
        if (!req.next())
        {
            //Identifiant inexistant
            return 1;
        }
        else if (req.value(0).toString() == mdp)
        {
            //Mot de passe correspondant a l identfiant
            return 0;
        }
        else
        {
            //Mot de passe incorrecte
            return 2;
        }

        db.close(); //Fermeture de la BDD après requête
    }
    else
    {
        //Conexion ratee
        return 0;
    }
}

void Db::getScores(QList<QString> &nomJoueur, QList<QString> &scoreJoueur, QList<QString> &nomMachine, QList<QString> &scoreMachine)
{
    if (db.open())
    {
        QSqlQuery query;
        query.exec("SELECT * FROM Resultat ORDER BY scoreJoueur DESC, scoreMachine ASC LIMIT 10");

        while(query.next())
        {
            nomJoueur.append(query.value(1).toString());
            scoreJoueur.append(query.value(2).toString());
            nomMachine.append(query.value(3).toString());
            scoreMachine.append(query.value(4).toString());
        }
        db.close();
    }
    else
    {
        qDebug() << "Impossible de recuperer les scores de la DB";
    }
}

void Db::effacerScores()
{
    if (db.open())
    {
        QSqlQuery query;
        query.exec("DELETE FROM Resultat");
        qDebug() << "Yooo";

        db.close();
    }
    else
    {
        qDebug() << "Impossible de supprimer des elements à la DB";
    }
}


