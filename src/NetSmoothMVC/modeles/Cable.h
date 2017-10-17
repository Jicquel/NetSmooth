#ifndef CABLE_DEF
#define CABLE_DEF

#include <iostream>
#include <vector>

class Cable;

#include "modeles/Entitee.h"
#include"vues/vuecable.h"

class Cable
{

public:
        Cable(Hub* h, Machine *m);
        ~Cable();

        Machine *getMachine() const;
        Hub* getHub() const;

        int getPort();
        void setPort(int p);

        VueCable* getVue();
        void setVue(VueCable* vue);

        bool isActive();

        static Cable* creerCable(Hub* h, Machine *m);

private:
        Machine* m_mac;
        Hub* m_hub;
        int m_port;
        VueCable* m_vue;
};

#endif
