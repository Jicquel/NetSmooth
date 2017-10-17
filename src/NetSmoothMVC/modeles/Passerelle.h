#ifndef PASSERELLE_DEF
#define PASSERELLE_DEF

#include <iostream>
#include <sstream>
#include <lxc/lxccontainer.h>

class Passerelle;

#include "modeles/Machine.h"


class Passerelle : public Machine
{
	public:
		/*	Passerelle(struct lxc_container* container)
		 *
		 *	constructeur de la classe, initialise le container
		 *	et appelle le constructeur de son parent
		 *	
		 *	ARGS
		 *	-container:
		 *		adresse du container associé a la
		 *		Passerelle
		 */
		Passerelle(int id);

		~Passerelle();

};

#endif
