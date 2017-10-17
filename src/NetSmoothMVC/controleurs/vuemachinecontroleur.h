#ifndef VUEMACHINECONTROLEUR_H
#define VUEMACHINECONTROLEUR_H

#include <QObject>
#include <iostream>

class VueMachineControleur;

#include "vues/vuemachine.h"
#include "controleurs/vueentiteecontroleur.h"

class VueMachineControleur : public VueEntiteeControleur
{
        Q_OBJECT
public:
        explicit VueMachineControleur(VueMachine* vue, VueEntiteeControleur *parent = 0);

private:
        VueMachine* vue;

signals:

public slots:
        void actionDoubleClick();
};

#endif // VUEMACHINECONTROLEUR_H
