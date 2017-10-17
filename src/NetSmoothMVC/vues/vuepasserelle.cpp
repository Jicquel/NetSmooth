#include "vuepasserelle.h"

VuePasserelle::VuePasserelle(VueEntitee *parent) : VueEntitee(parent)
{
    this->passerelle=DataBase::getNewPasserelle();
    this->etat = false;
	QPixmap* img = new QPixmap();
    img->load(Fenetre::getImagesPath()+"passerelleoff.png");
    *img = img->scaled(130,130);
    this->setPixmap(*img);
    this->passerelle->setVue(this);
}

Entitee *VuePasserelle::getModele()
{
    return this->passerelle;
}

void VuePasserelle::setPasserelle(Passerelle *passerelle0)
{
    this->passerelle = passerelle0;
}

void VuePasserelle::terminal()
{
    if (this->etat == true)
            ((Passerelle*)this->getModele())->lancerXterm();
}
