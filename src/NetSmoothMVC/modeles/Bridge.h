#ifndef BRIDGE_DEF
#define BRIDGE_DEF

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

class Bridge
{
	public:
		/*	static void creerBridge(char* nomPont)
		 *
		 *	permet de créer un bridge sur la machine hote
		 *
		 *	ARGS
		 *	-nomPont:
		 *		nom du bridge a créer
		 */
		static void creerBridge(const char* nomPont);

		/*	static void detruireBridge(char* nomPont)
		 *
		 *	permet de détruire un bridge sur la machine hote
		 *
		 *	ARGS
		 *	-nomPont:
		 *		nom du bridge a détruire
		 */
		static void detruireBridge(const char* nomPont);

	private:
};

#endif
