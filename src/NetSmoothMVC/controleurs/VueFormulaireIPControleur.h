#ifndef VUEFORMULAIREIPCONTROLEUR_H
#define VUEFORMULAIREIPCONTROLEUR_H

#include <QObject>
#include <iostream>

class VueFormulaireIPControleur;

#include "vues/VueFormulaireIP.h"

class VueFormulaireIPControleur : public QObject
{
    Q_OBJECT
public:
    explicit VueFormulaireIPControleur(VueFormulaireIP* vue, QPushButton* valider, QObject *parent = 0);

private:
    VueFormulaireIP* vue;

signals:

public slots:
    void appliquerModif();

};

#endif
