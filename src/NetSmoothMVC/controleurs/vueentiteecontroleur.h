#ifndef VUEENTITEECONTROLEUR_H
#define VUEENTITEECONTROLEUR_H

#include <QPoint>
#include <QObject>

class VueEntiteeControleur;

class VuePasserelleControleur;
class VueHubControleur;
class VueMachineControleur;

#include "vues/vueinformation.h"
#include "vues/selection.h"
#include "vues/vueprincipale.h"
#include "vues/vuecable.h"
#include "controleurs/VueCableControleur.h"
#include "vues/vueentitee.h"

#include "modeles/Constantes.h"

class VueEntiteeControleur : public QObject
{
        Q_OBJECT
public:
        explicit VueEntiteeControleur(VueEntitee* vue, QObject *parent = 0);

private:
        VueEntitee *vue;

signals:

public slots:
        void actionMoveLeftButton();
        void actionLeftClick();
};

#include "controleurs/vuepasserellecontroleur.h"
#include "controleurs/vuehubcontroleur.h"
#include "controleurs/vuemachinecontroleur.h"

#endif // VUEENTITEECONTROLEUR_H
