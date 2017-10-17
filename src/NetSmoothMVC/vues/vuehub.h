#ifndef VUEHUB_H
#define VUEHUB_H

class VueHub;

#include "vues/vueentitee.h"

class VueHub : public VueEntitee
{
	Q_OBJECT
	public:
        explicit VueHub(VueEntitee *parent = 0);
        Entitee* getModele();
        void setHub(Hub* hub0);
	private:
        Hub* hub;
};

#endif // VUEHUB_H
