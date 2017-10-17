#include "controleurs/VueCableControleur.h"

VueCableControleur::VueCableControleur(VueCable* v,QObject *parent) : QObject(parent)
{
    this->vue = v;
    this->connect(this->vue,SIGNAL(deleteCableSignal()),this,SLOT(actionDeleteCable()));
}

void VueCableControleur::actionDeleteCable()
{
    delete(this->vue);
    Selection::setEnSelection(SOURIS);
}
