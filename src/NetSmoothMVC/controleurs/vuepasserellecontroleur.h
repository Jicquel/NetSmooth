#ifndef VUEPASSERELLECONTROLEUR_H
#define VUEPASSERELLECONTROLEUR_H

#include <QObject>

class VuePasserelleControleur;

#include "vues/vuepasserelle.h"
#include "controleurs/vueentiteecontroleur.h"

class VuePasserelleControleur : public VueEntiteeControleur
{
    Q_OBJECT
public:
    explicit VuePasserelleControleur(VuePasserelle* vue, VueEntiteeControleur *parent = 0);

private:
    VuePasserelle* vue;

public slots:
    void actionDoubleClick();

};

#endif // VUEPASSERELLECONTROLEUR_H
