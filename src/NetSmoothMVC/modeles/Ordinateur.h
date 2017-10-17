#ifndef MACHINE_DEF
#define MACHINE_DEF

#include <iostream>
#include <sstream>
#include <lxc/lxccontainer.h>

class Ordinateur;

#include "modeles/Machine.h"

class Ordinateur : public Machine
{
	public:
		/*	Ordinateur(struct lxc_container* container)
		 *
		 *	constructeur de la classe, il initialise le container
		 *	associé a la machine, et appelle le constructeur de
		 *	parrent
		 *	
		 *	ARGS
		 *	-container:
		 *		container a associer a la machine
		 */
		Ordinateur(int id);

        ~Ordinateur(void);
};

#endif
