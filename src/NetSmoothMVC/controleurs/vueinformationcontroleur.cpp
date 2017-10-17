#include "vueinformationcontroleur.h"

VueInformationControleur::VueInformationControleur(VueInformation* vue0, QPushButton* all, QPushButton* rafr, QPushButton* name, QObject *parent) : QObject(parent)
{
    vue = vue0;
    connect(all,SIGNAL(clicked(bool)),this,SLOT(actionClickAllumer()));
    connect(rafr,SIGNAL(clicked(bool)),this,SLOT(rafraichir()));
    connect(name,SIGNAL(clicked(bool)),this,SLOT(rename()));
}

void VueInformationControleur::actionClickAllumer()
{
        if(this->vue->getEtatBoutonAllumer() == true)
                this->vue->allumer();
}

void VueInformationControleur::rafraichir()
{
        this->vue->addNewInfos();
}

void VueInformationControleur::rename()
{
        if(VueEntitee::getLabelEnSelection() != NULL)
        {
                VueEntitee::getLabelEnSelection()->getModele()->setNom(this->vue->getName());
                VueEntitee::getLabelEnSelection()->update();
        }
}

