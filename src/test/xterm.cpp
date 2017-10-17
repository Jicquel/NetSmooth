#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <lxc/lxccontainer.h>

using namespace std;

int lancerContainer(struct lxc_container* cnt)
{
	int tst;

	tst = cnt->start(cnt, 0, NULL);
	if(!tst)
	{
		cout << "Failed to start the container" << endl;
		return -1;
	}
	cout << "container succefully started" << endl;
	return 0;
}

int stoperContainer(struct lxc_container* cnt)
{
	int tst;

	tst = cnt->shutdown(cnt, 10);
	if(!tst)
	{
		printf("Failed to cleanly stop the container, forcing.\n");
		tst = cnt->stop(cnt);
		if(!tst) {
			cout << "Failed to stop the container, forcing even more" << endl;
			pid_t pid = cnt->init_pid(cnt);
			tst = kill(pid, SIGINT);
			if(tst==-1)
			{
				cout << "impossible to close the container, I give up" << endl;
				exit(1);
			}
		}
	}
	cout << "container succefully stopped" << endl;
	return 0;
}

int main(void)
{
	int tst;

	struct lxc_container* cnt=lxc_container_new("apicontainer", NULL);
	if(!cnt)
	{
		cout << "Failed to setup lxc_container struct" << endl;
		exit(1);
	}

	tst = cnt->is_defined(cnt);
	if(!tst)
	{
		cout << "apicontainer does not exist, create it first" << endl;
		exit(1);
	}
	
	
	if(cnt->state(cnt)[0]=='S')	/*si le container est arete (state = "STOPPED")*/
	{
		tst=lancerContainer(cnt);
		if(tst==-1)
			exit(1);
	}
	else if(cnt->state(cnt)[0]=='R')	/*si le container tourne (state = "RUNNING")*/
		cout << "container already launched" << endl;
	
	
	int x=fork();
	if(x==0)
		execl("./launchXtermRoot.sh", "launchCnt", "apicontainer", NULL);

	sleep(1);

	cout << "appuyez sur une touche pour terminer" << endl;
	int sertarien;
	cin >> sertarien;
	tst=stoperContainer(cnt);
	if(tst==-1)
		exit(1);

}
