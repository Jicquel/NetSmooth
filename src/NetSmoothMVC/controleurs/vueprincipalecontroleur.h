#ifndef VUEPRINVCPALECONTROLEUR_H
#define VUEPRINVCPALECONTROLEUR_H

#include <QObject>
#include <iostream>

class VuePrincipaleControleur;


#include "vues/vueprincipale.h"
#include "vues/selection.h"
#include "vues/VueErreur.h"

using namespace std;

class VuePrincipaleControleur : public QObject
{
    Q_OBJECT
public:
    explicit VuePrincipaleControleur(VuePrincipale *vue, QObject *parent = 0);

private:
    VuePrincipale *vue;

signals:

public slots:
    void actionClickSouris(QPoint pos);
};

#endif // VUEPRINCIPALECONTROLEUR_H
