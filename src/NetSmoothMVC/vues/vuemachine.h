#ifndef VUEMACHINE_H
#define VUEMACHINE_H

#include <iostream>

class VueMachine;

#include "vues/vueentitee.h"
#include "fenetre.h"

using namespace std;

class VueMachine : public VueEntitee
{
	Q_OBJECT
	public:
        explicit VueMachine(VueEntitee *parent = 0);
        Entitee* getModele(void);
        void terminal();
	private:
		Ordinateur* ordinateur=NULL;

};

#endif // VUEMACHINE_H
