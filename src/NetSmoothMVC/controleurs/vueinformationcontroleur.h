#ifndef VUEINFORMATIONCONTROLEUR_H
#define VUEINFORMATIONCONTROLEUR_H

#include <QObject>
#include <iostream>

class VueInformationControleur;

#include "vues/vueinformation.h"

using namespace std;

class VueInformationControleur : public QObject
{
    Q_OBJECT
public:
    explicit VueInformationControleur(VueInformation* vue, QPushButton* all, QPushButton* rafr, QPushButton* name, QObject *parent = 0);

private:
    VueInformation* vue;

signals:

public slots:
    void actionClickAllumer();
    void rafraichir();
    void rename();
};

#endif // VUEINFORMATIONCONTROLEUR_H
