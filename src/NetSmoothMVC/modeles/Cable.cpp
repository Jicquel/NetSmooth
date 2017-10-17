#include "modeles/Cable.h"

Cable::Cable(Hub* h, Machine* m)
        :m_hub(h), m_mac(m)
{
        this->m_port=this->m_mac->getCables()->size();
        //VueInformation::getInstanceOf()->refresh();
}

Cable::~Cable()
{
        this->m_hub->deleteCable(this);
        this->m_mac->deleteCable(this);
}

Machine* Cable::getMachine() const
{
        return this->m_mac;
}

Hub* Cable::getHub() const
{
        return this->m_hub;
}

int Cable::getPort()
{
        return this->m_port;
}

void Cable::setPort(int p)
{
        this->m_port = p;
}

VueCable* Cable::getVue()
{
        return this->m_vue;
}

bool Cable::isActive()
{
        return (this->m_hub->getEtatEntitee()==MACHINE_LANCEE &&
                this->m_mac->getEtatEntitee()==MACHINE_LANCEE);
}

void Cable::setVue(VueCable* vue)
{
        this->m_vue=vue;
}

Cable* Cable::creerCable(Hub *h, Machine* m)
{
        Cable* c = new Cable(h, m);
        h->addCable(c);
        m->addCable(c);

        return c;
}

