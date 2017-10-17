#include "vuemachine.h"

VueMachine::VueMachine(VueEntitee *parent) : VueEntitee(parent)
{
    this->ordinateur = DataBase::getNewOrdinateur();
	etat = false;

	QPixmap* img = new QPixmap();
    img->load(Fenetre::getImagesPath()+"ordinateuroff.png");
    *img = img->scaled(130,130);
    this->setPixmap(*img);
    this->ordinateur->setVue(this);
}

Entitee *VueMachine::getModele()
{
  return this->ordinateur;
}

void VueMachine::terminal()
{
    if (this->etat == true)
        ((Machine*)this->getModele())->lancerXterm();
}

