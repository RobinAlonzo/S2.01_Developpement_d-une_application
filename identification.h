#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include <QDialog>
#include "presentation.h"

namespace Ui {class Identification;}

class Identification : public QDialog
{
    Q_OBJECT

public:
    explicit Identification(QWidget *parent = nullptr);
    ~Identification();
    void conexionPresentation(Presentation*);

signals:
    void validationId(const QString& id, const QString& mdp);    //Renvoie un signal demandant la verification des identifiants mis en parametre
    void hostMode();            //Indique si le joueur se connecte en mode host

public slots:
    void majIdFaux();           //Met a jour les elements graphiques en consequence a l identifiant faux
    void majMdpFaux();          //Met a jour les elements graphiques en consequence au mdp faux
    void majDbInaccessible();   //Met a jour les elements graphiques en consequence a la base de donnees inaccessible

private slots:
    void demandeVerif();

private:
    Ui::Identification *ui;
};

#endif // IDENTIFICATION_H
