#ifndef VUEPASSERELLE_H
#define VUEPASSERELLE_H

class VuePasserelle;

#include "vues/vueentitee.h"

class VuePasserelle : public VueEntitee
{
    Q_OBJECT
public:
    explicit VuePasserelle(VueEntitee *parent = 0);
    Entitee* getModele(void);
    void setPasserelle(Passerelle* passerelle0);
    void terminal();

private:
    Passerelle* passerelle;

};

#endif // VUEPASSERELLE_H
