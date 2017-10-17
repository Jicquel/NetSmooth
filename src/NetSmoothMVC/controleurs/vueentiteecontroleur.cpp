#include "vueentiteecontroleur.h"

VueEntiteeControleur::VueEntiteeControleur(VueEntitee* v,QObject *parent) : QObject(parent)
{
        this->vue = v;
        this->connect(this->vue,SIGNAL(moveLeftButton()),this,SLOT(actionMoveLeftButton()));
        this->connect(this->vue,SIGNAL(leftClick()),this,(SLOT(actionLeftClick())));
}

void VueEntiteeControleur::actionMoveLeftButton()
{
        this->vue->moveOnCursor();
}

void VueEntiteeControleur::actionLeftClick()
{
        if(Selection::getEnSelection()==SUPPRIMER)
        {
                if(this->vue->getModele()->getEtatEntitee()==MACHINE_STOPEE)
                {
                        VuePrincipale* vp = VuePrincipale::getInstanceOf();
                        if(this->vue->getModele()->getType() == TYPE_ORDINATEUR)
                        {
                                vp->setNombreOrdinateurs(vp->getNombreOrdinateurs()-1);
                        }
                        else if(this->vue->getModele()->getType() == TYPE_PASSERELLE)
                        {
                                vp->setNombrePasserelles(vp->getNombrePasserelles()-1);
                        }

                        this->vue->detruire();
                }
        }
        else if(Selection::getEnSelection()==CABLE)
        {
                VueEntitee* ve1 = VueCable::getPremiereSelection();
                VueEntitee* ve2 = this->vue;

                if(ve1==NULL)
                {
                        VueCable::setPremiereSelection(ve2);
                }
                else if(ve1->getModele()->getType()==TYPE_HUB && ve2->getModele()->getType()!=TYPE_HUB ||
                                ve1->getModele()->getType()!=TYPE_HUB && ve2->getModele()->getType()==TYPE_HUB)
                {
                        if(ve1->getModele()->testCreateCable(this->vue->getModele()))
                        {
                                VueHub* vh = (ve1->getModele()->getType() == TYPE_HUB)?(VueHub*)ve1:(VueHub*)ve2;
                                VueMachine* vm = (ve1->getModele()->getType() == TYPE_HUB)?(VueMachine*)ve2:(VueMachine*)ve1;

                                VueCable* vc = new VueCable(vh, vm);

                                new VueCableControleur(vc);
                                VueCable::setPremiereSelection(NULL);
                                Selection::setEnSelection(SOURIS);
                        }
                }
                else
                {
                        VueCable::setPremiereSelection(NULL);
                        Selection::setEnSelection(SOURIS);
                }
        }
        else if(VueEntitee::getLabelEnSelection()!=this->vue)
        {
                Selection::setEnSelection(SOURIS);
                VueEntitee::setLabelEnSelection(this->vue);
                VueInformation::getInstanceOf()->refresh(this->vue);
        }

}

