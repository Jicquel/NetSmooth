#include "VueFormulaireIPControleur.h"

VueFormulaireIPControleur::VueFormulaireIPControleur(VueFormulaireIP* vue0, QPushButton* valider,QObject *parent) : QObject(parent)
{
    this->vue = vue0;
    connect(valider,SIGNAL(clicked()),this,SLOT(appliquerModif()));
}

void VueFormulaireIPControleur::appliquerModif()
{
    this->vue->appliquerModification();
    this->vue->getModele()->majIpContainer();
    this->vue->getModele()->majRouteContainer();
}
