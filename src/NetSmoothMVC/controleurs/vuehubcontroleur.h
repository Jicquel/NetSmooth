#ifndef VUEHUBCONTROLEUR_H
#define VUEHUBCONTROLEUR_H

#include <QObject>

class VueHubControleur;

#include "vues/vuehub.h"
#include "controleurs/vuehubcontroleur.h"
#include "controleurs/vueentiteecontroleur.h"

class VueHubControleur : public VueEntiteeControleur
{
    Q_OBJECT
public:
    explicit VueHubControleur(VueHub* vue, VueEntiteeControleur *parent = 0);

private:
    VueHub* vue;

public slots:
};

#endif // VUEHUBCONTROLEUR_H
