#include "vueprincipalecontroleur.h"

VuePrincipaleControleur::VuePrincipaleControleur(VuePrincipale *vue0,QObject *parent) : QObject(parent)
{
    vue = vue0;

    connect(vue,SIGNAL(clickSouris(QPoint)),this,SLOT(actionClickSouris(QPoint)));
    connect(vue->getView(),SIGNAL(drop(QPoint)),this,SLOT(actionClickSouris(QPoint)));
}

void VuePrincipaleControleur::actionClickSouris(QPoint pos)
{
    if(Selection::getEnSelection() == MACHINE )
        if(vue->getNombreOrdinateurs() >= NBR_MACHINE_MAX)
        {
            VueErreur::getInstanceOf()->setText("Nombre limite d'ordinateurs atteint");
            Selection::setEnSelection(SOURIS);
        }
        else
        {
            vue->setNombreOrdinateurs(vue->getNombreOrdinateurs()+1);
            vue->paintEntitee(pos);
        }

    else if(Selection::getEnSelection() == PASSERELLE)
        if(vue->getNombrePasserelles() >= NBR_PASSERELLE_MAX)
        {
            VueErreur::getInstanceOf()->setText("Nombre limite de passerelles atteint");
            Selection::setEnSelection(SOURIS);
        }
        else
        {
            vue->setNombrePasserelles(vue->getNombrePasserelles()+1);
            vue->paintEntitee(pos);
        }
    else
        vue->paintEntitee(pos);
}
