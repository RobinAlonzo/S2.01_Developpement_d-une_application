#include "presentation.h"
#include "chifoumivue.h"
#include "parametres.h"
#include "db.h"
#include "identification.h"
#include "scores.h"
#include <QDebug>


#include <QMessageBox>

Presentation::Presentation(Modele *m, ChifoumiVue *v, Param *p, Db *db, Identification *id, Scores *scores, QObject *parent)
    : QObject{parent}
    , _leModele(m)
    , _laVue(v)
    , _lesParam(p)
    , _laDb(db)
    , _identification(id)
    , _lesScores(scores)
{
    // -- Initialisations --
    //Initialisation nom
    nomJoueur = "Vous";
    _laVue->majNomJoueur(nomJoueur);

    //Initialisation score max
    scoreFin = 3;
    _laVue->initScoreFin(scoreFin);

    //initialisation timer
    tempsPartie = 20;
    tempsRestant = tempsPartie;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gererTimer()));
    _laVue->majTimer(tempsRestant);
    timer->setInterval(100);

    // -- Conexions --
    connect(_identification, SIGNAL(validationId(const QString &, const QString &)), this, SLOT(analyseIdentifiants( const QString &, const QString &)));  //Identification --> Db
    _identification->conexionPresentation(this);
    _laVue->connexionPresentation(this);                                            //Vue --> Presentation
    _lesParam->connexionPresentation(this, nomJoueur, scoreFin, tempsPartie);       //parametres --> Presentation
    connect(_lesScores, SIGNAL(demandeEffacement()), _laDb, SLOT(effacerScores())); //Scores --> Db
}



Modele *Presentation::getModele()
{
    return _leModele;
}
ChifoumiVue *Presentation::getVue()
{
    return _laVue;
}


void Presentation::jouer(Modele::UnCoup c)
{
    switch (_leModele->getEtatJeu())
    {
        case Modele::partieEnCours:
            // Activite 2
            // -- mise a jour du modele --
            _leModele->setCoupJoueur(c);
            _leModele->setCoupMachine(_leModele->genererUnCoup());
            _leModele->majScores(_leModele->determinerGagnant());


            if (scoreAtteint())
            {
                // -- mise a jour du modele --
                timer->stop();
                // -- changement d'état --
                _leModele->setEtatJeu(Modele::partieTerminee);
                // -- mise à jour de l'interface --
                _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());
                _laVue->setJoueurEnBleu(false);
                _laVue->setFocusBJouer();

                _laVue->setEtatsBJeu(false);
                _laVue->setEtatBPause(false);
                _laVue->setEtatActionParam(true);
                _laVue->setEtatActionScores(true);
                affichageFin();
                if (modeJoueur == login)
                {
                    _laDb->insererResultat(_laVue->getNomJoueur(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
                }
            }
            else
            {
                //Score non atteint
                // -- mise a jour du modele --
                // -- changement d'état --
                _leModele->setEtatJeu(Modele::partieEnCours);
                // -- mise à jour de l'interface --
                _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());
                _laVue->setJoueurEnBleu(false);
                _laVue->setFocusBJouer();
            }
        break;
        case Modele::partieTerminee:
            // Activite X
            // -- mise a jour du modele --
            // -- changement d'état --
            // -- mise à jour de l'interface --
        break;
        case Modele::horsPartie:
            // Activite X
            // -- mise a jour du modele --
            // -- changement d'état --
            // -- mise à jour de l'interface --
        break;
    }
}


bool Presentation::scoreAtteint()
{
    if ((_leModele->getScoreJoueur() == scoreFin) ||
        (_leModele->getScoreMachine() == scoreFin))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Presentation::tempsEpuise()
{
    if (tempsRestant <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Presentation::affichageFin()
{
    unsigned int scoreJoueur =_leModele->getScoreJoueur();
    unsigned int scoreMachine =_leModele->getScoreMachine();

    // -- Maj de l interface --
    QMessageBox boiteFin(_laVue);
    boiteFin.setWindowTitle("Game over");
    QString messageFin;

    //Gestion du temps final
    if (tempsRestant <= 0)
    {
        //Temps ecoule
        messageFin.append("Temps ecoulé :");
    }
    else
    {
        //Temps non ecoule
        messageFin.append("Au bout de " + QString::number(static_cast<float>(static_cast<unsigned int>((tempsPartie - tempsRestant)*10))/10) + " seconde :");
    }

    //Gestion des scores finaux
    if (scoreJoueur > scoreMachine)
    {
        //Joueur gagne
        messageFin.append(" joueur gagne avec " + QString::number(scoreJoueur) + " points.");
    }
    else if (scoreJoueur < scoreMachine)
    {
        //Machine gagne
        messageFin.append(" machine gagne avec " + QString::number(scoreMachine) + " points.");
    }
    else
    {
        //Aucun gagnant (scores egaux)
        messageFin.append(" aucun gagnant.");
    }

    boiteFin.setText(messageFin);
    boiteFin.exec();
}

void Presentation::demarrerAffichage()
{
    _identification->show();
}

void Presentation::demanderNouvellePartie()
{
    switch (_leModele->getEtatJeu())
    {
        case Modele::horsPartie:
            // Hors partie
            // Activite 1
            // -- mise a jour du modele --
tempsRestant = tempsPartie;
            // -- changement d'état --
            _leModele->setEtatJeu(Modele::partieEnCours);
            timer->start();
            // -- mise à jour de l'interface --
            _laVue->setEtatsBJeu(true);
            _laVue->setFocusBJouer();
            _laVue->setJoueurEnBleu(true);
            _laVue->setEtatBPause(true);
            _laVue->setEtatActionParam(false);
            _laVue->setEtatActionScores(false);
        break;
        case Modele::partieEnCours:
            // Partie en cours
            // Activite 3
            // -- mise a jour du modele --
            _leModele->initCoups();
            _leModele->initScores();
            tempsRestant = tempsPartie;
            // -- changement d'état --
            _leModele->setEtatJeu(Modele::partieEnCours);
            timer->start();
            // -- mise à jour de l'interface --
            _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());   //Maj des elements graphiques et coloration en bleu
            _laVue->setJoueurEnBleu(true);
            _laVue->setFocusBJouer();
        break;
        default:
            //Partie terminee
            // Activite 4
            // -- mise a jour du modele --
            _leModele->initCoups();
            _leModele->initScores();
            tempsRestant = tempsPartie;
            // -- changement d'état --
            _leModele->setEtatJeu(Modele::partieEnCours);
            timer->start();
            // -- mise à jour de l'interface --
            _laVue->majScoresCoups(_leModele->getScoreJoueur(), _leModele->getScoreMachine(), _leModele->getCoupJoueur(), _leModele->getCoupMachine());   //Maj des elements graphiques et coloration en bleu
            _laVue->setJoueurEnBleu(true);
            _laVue->setEtatsBJeu(true);
            _laVue->setFocusBJouer();
            _laVue->setEtatBPause(true);
        break;
    }
}
void Presentation::demanderCiseau()
{
    jouer(Modele::ciseau);
}
void Presentation::demanderPierre()
{
    jouer(Modele::pierre);
}
void Presentation::demanderPapier()
{
    jouer(Modele::papier);
}


void Presentation::gererTimer()
{
    if (_leModele->getEtatJeu() == Modele::partieEnCours)
    {
        // Activite 5
        // -- mise a jour du modele --
        tempsRestant -= 0.1 ;
        // -- mise à jour de l'interface --
        _laVue->majTimer(tempsRestant+1);       //+1 pour que le temps se decremente sur l'interface seulement lorsque la seconde est entierement ecoulée

        if (tempsEpuise())
        {
            // -- mise a jour du modele --
            timer->stop();
            // -- changement d'état --
            _leModele->setEtatJeu(Modele::partieTerminee);
            // -- mise à jour de l'interface --
            _laVue->setEtatsBJeu(false);
            _laVue->setEtatBPause(false);
            _laVue->setEtatActionParam(true);
            _laVue->setEtatActionScores(true);
            affichageFin();
            if (modeJoueur == login)
            {
                _laDb->insererResultat(_laVue->getNomJoueur(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
            }
        }
    }
}

void Presentation::start_stop_timer()
{
    if (timer->isActive())
    {
        //Arrete le timer
        timer->stop();                          //Stop le timer
        _laVue->setEtatsBJeu(false);            //Desactive les boutons pour jouer
        _laVue->setEtatBPartie(false);          //Desactive le bouton pour recommencer une partie
        _laVue->setEtatActionScores(true);      //Re actuve le bouton des resultats
        _laVue->majLabelBPause("Reprendre");    //Change le nom du bouton en "reprendre"
        _laVue->setFocusBPause();               //Met le focus sur le bouton de pause
    }
    else
    {
        //Redemarre le timer
        timer->start();                         //Démarre le timer
        _laVue->setEtatsBJeu(true);             //Re active les boutons de jeux
        _laVue->setEtatBPartie(true);           //Re active le bouton de partie
        _laVue->setEtatActionScores(false);     //Re actuve le bouton des resultats
        _laVue->majLabelBPause("Pause");        //Change le nom du bouton en "Pause"
        _laVue->setFocusBJouer();               //Met le focus sur le bouton de partie
    }
}

void Presentation::clicParametres()
{    
    //Hors partie ou partie terminee
    _lesParam->afficherDialog();
}

void Presentation::modifParametres()
{

    switch (_leModele->getEtatJeu())
    {
    case Modele::horsPartie:

        if (_lesParam->nomModifie())
        {
            //Modification faite sur le nom du joueur
            nomJoueur = _lesParam->getNom();
            _laVue->majNomJoueur(nomJoueur);
        }

        if (_lesParam->scoreFinModifie())
        {
            //Modification faite sur le nombre de points max
            scoreFin = _lesParam->getScore();
            _laVue->initScoreFin(scoreFin);
        }

        if (_lesParam->tempsPartieModifie())
        {
            //Modification faite sur le temps de la partie
            tempsPartie =_lesParam->getTemps();
            tempsRestant = tempsPartie;
            _laVue->majTimer(tempsPartie);
        }
        break;

    case Modele::partieTerminee:

        if (_lesParam->nomModifie())
        {
            //Modification faite sur le nom du joueur
            nomJoueur = _lesParam->getNom();
            _laVue->majNomJoueur(nomJoueur);
        }

        if (_lesParam->scoreFinModifie())
        {
            //Modification faite sur le nombre de points max
            scoreFin = _lesParam->getScore();
            _laVue->initScoreFin(scoreFin);
        }

        if (_lesParam->tempsPartieModifie())
        {
            //Modification faite sur le temps de la partie
            tempsPartie =_lesParam->getTemps();
        }

        if (_lesParam->nomModifie() || _lesParam->scoreFinModifie() || _lesParam->tempsPartieModifie())
        {
            // -- Changement d'etat vers hors partie --
            //Reinitialisations des scores, coups
            _leModele->initCoups();
            _leModele->initScores();

            //Changement d etat
            _leModele->setEtatJeu(Modele::horsPartie);

            //Maj des elements graphiques lies
            _laVue->majTimer(tempsPartie);
            _laVue->majScoresCoups(0, 0, Modele::rien, Modele::rien);
        }
        break;

    default:
        break;
    }
}

void Presentation::analyseIdentifiants(QString id, QString mdp)
{
    switch (_laDb->analyseIdentifiants(id, mdp))
    {
    case 0:
        //Identifiants correctes
        modeJoueur = login;
        _identification->close();
        _laVue->show();
        break;
    case 1:
        //Identifiant inexistant
        _identification->majIdFaux();
        break;
    case 2:
        //Mot de passe incorrecte
        _identification->majMdpFaux();
        break;
    case 3:
        //Db inaccessible
        _identification->majDbInaccessible();
        break;
    default:
        break;
    }
}

void Presentation::setHostMode()
{
    modeJoueur = host;
    nomJoueur = "Host";
    _laVue->majNomJoueur(nomJoueur);

    //Ouverture vue
    _identification->close();
    _laVue->show();

}

void Presentation::clicResultats()
{
    //Db --> Valeurs
    QList<QString> nomJoueur;
    QList<QString> scoreJoueur;
    QList<QString> nomMachine;
    QList<QString> scoreMachine;
    _laDb->getScores(nomJoueur, scoreJoueur, nomMachine, scoreMachine);

    //Valeurs --> Tableau resultats
    _lesScores->majValeurs(nomJoueur, scoreJoueur, nomMachine, scoreMachine);

    //Affichage fenetre
    _lesScores->show();
}

