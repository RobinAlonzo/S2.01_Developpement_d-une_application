#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include <QTimer>

#include "modele.h"


class ChifoumiVue;
class Param;
class Db;
class Identification;
class Scores;
class Presentation : public QObject
{
    Q_OBJECT
public:    
    enum Modejoueur {login, host};

    //Initialisaitons
    explicit Presentation(Modele* m, ChifoumiVue *v, Param *p, Db *db, Identification *id, Scores *score, QObject* parent = nullptr);

    //Getters / Setters
    Modele* getModele();            //Récupere le modèle
    ChifoumiVue* getVue();          //Récupere la vue
    void setModele(Modele *m);      //Associe le modèle à la présentation
    QString getNomJoueur() const;
    unsigned int getScoreFin() const;
    unsigned int getTempsPartie() const;

    //Evenements
    void jouer(Modele::UnCoup);     //Joue en fonction du coup de l utilisateur

    //Gardes
    bool scoreAtteint();            //Indique si la partie est terminée par le score atteint
    bool tempsEpuise();             //Indique si la partie est terminée par le temps (timer = 0)

    //Affichages
    void affichageFin();            //Affiche un dialog indiquant le gagnant avec son score et le temps restant
    void demarrerAffichage();       //Demarre l affichage

public slots:
    //Slots externes (activés par la vue)
    void demanderNouvellePartie();  //Signal demandant une nouvelle partie
    void demanderCiseau();          //Slot demandant de jouer le ciseau
    void demanderPierre();          //Slot demandant de jouer la pierre
    void demanderPapier();          //Slot demandant de jouer le papier
    void start_stop_timer();        //Slot activé par le bouton pause qui met en pause ou redémarre le timer
    void clicParametres();          //Slot activé par le bouton des parametres, lance la fenetre des parametres
    void modifParametres();         //Slot activé par le bouton valider dans les parametres, modifie les parametres de la presentation en consequent
    void clicResultats();           //Slot activé par le bouton Resultats, affiche les scores et initialise le tableau en consequent

    void analyseIdentifiants(QString, QString); //Interroge la base de donnee et met a jour les elements graphiques en fonction de la validite des identifiants
    void setHostMode();             //Met le mode du joueur en host
private slots:
    //Slots internes (activés par la presentation)
    void gererTimer();                                //Slot activé par la clock qui met a jour les elements en fonction du temps (maj graphique, pause du jeux du le temps utilisé...)

private:
    //Composantes
    Modele *_leModele;                  //Le modèle
    ChifoumiVue *_laVue;                //La vue
    Param *_lesParam;                   //Le dialog
    Db *_laDb;                          //La base de donnee
    Identification *_identification;    //La page d identification
    Scores *_lesScores;                 //Les scores

    //Timer
    QTimer *timer;              //Timer redemarre des que la durée est atteintewq<
    float tempsRestant;         //Temps restant (mis a jour a chaque fois de cycle du timer)

    //Proprietes
    QString nomJoueur;          //Nom du joueur
    unsigned int scoreFin;      //Score défini a l'avance au bout duquel la partie se termine si un des joueur l'atteint
    unsigned int tempsPartie;   //Temps de départ du temps restant
    Modejoueur modeJoueur;      //Mode du joueur : login ou heberge
};

#endif // PRESENTATION_H
