#ifndef SCORES_H
#define SCORES_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {class Scores;}

class Scores : public QDialog
{
    Q_OBJECT

public:
    explicit Scores(QWidget *parent = nullptr);
    ~Scores();

    void majValeurs(QList<QString> &nomJoueur, QList<QString> &scoreJoueur, QList<QString> &nomMachine, QList<QString> &scoreMachine);

signals:
    void demandeEffacement();
private:
    Ui::Scores *ui;
};

#endif // SCORES_H
