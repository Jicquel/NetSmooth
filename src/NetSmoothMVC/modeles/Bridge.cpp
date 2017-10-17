#include "Bridge.h"

using namespace std;

void Bridge::creerBridge(const char* nomPont)
{
	int x=fork();

	if(x==-1)
	{
		perror("fork");
		exit(1);
	}
	if(x==0)
	{
        execl("../NetSmoothMVC/scripts/creerBridge.sh", "createBridge", nomPont, NULL);

		exit(0);
	}
	int useless;
	while(wait(&useless)<0);
}

void Bridge::detruireBridge(const char* nomPont)
{
	int x=fork();

	if(x==-1)
	{
		perror("fork");
		exit(1);
	}
	if(x==0)
	{
        execl("../NetSmoothMVC/scripts/detruireBridge.sh", "destroyBridge", nomPont, NULL);
		exit(0);
	}
	int useless;
	while(wait(&useless)<0);
}
