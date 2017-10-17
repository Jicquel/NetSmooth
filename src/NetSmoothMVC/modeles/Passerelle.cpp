#include "Passerelle.h"

Passerelle::Passerelle(int id)
        :Machine(id, TYPE_PASSERELLE, "passerelle")
{
    for(int numInterface = 0; numInterface < NOMBRE_INTERFACES_PASSERELLE ; numInterface++)
    {
        std::ostringstream convert;
        convert << numInterface;

        struct paramIp* ip = new paramIp();
        ip->interface="eth"+convert.str();
        ip->ipv4="";
        ip->ipv6="";
        ip->maskv4="";

        this->addIpConfig(ip);
    }
}

Passerelle::~Passerelle()
{
    DataBase::detruirePasserelle(this);
}
