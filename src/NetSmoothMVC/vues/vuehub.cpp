#include "vuehub.h"

VueHub::VueHub(VueEntitee *parent) : VueEntitee(parent)
{
    this->hub=DataBase::getNewHub();
    this->etat = false;
    QPixmap* img = new QPixmap();
    img->load(Fenetre::getImagesPath()+"Huboff.png");
    *img = img->scaled(130,130);
    this->setPixmap(*img);
    this->hub->setVue(this);
}

Entitee *VueHub::getModele()
{
    return this->hub;
}

void VueHub::setHub(Hub* hub0)
{
  this->hub=hub0;
}
