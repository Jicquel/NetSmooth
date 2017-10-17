#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <lxc/lxccontainer.h>

using namespace std;

void lancerXterm(lxc_container* c)
{
    int x=fork();

	if(x==-1)
	{
		perror("fork");
		exit(1);
	}
	if(x==0)
	{
		char cntName[20];
		c->get_config_item(c, "lxc.utsname", cntName, 20);
		execl("../NetSmoothMVC/scripts/launchXtermRoot.sh", "launchCnt", cntName, NULL);
		exit(0);
	}
}


int main(void) {
	struct lxc_container *c;
	int ret = 1;
	lxc_attach_options_t options = LXC_ATTACH_OPTIONS_DEFAULT;
	lxc_attach_exec_t salut;
	pid_t pid;

	c = lxc_container_new("ordinateur0", NULL);
	if (!c) {
		fprintf(stderr, "Failed to setup lxc_container struct\n");
		goto out;
	}

	while(1)
	{
		cout << "creating snapshot" << endl;
		if (c->snapshot(c, NULL) != 0)
		{
			cout << "failed to create the snapshot" << endl;
			exit(1);
		}

		cout << "starting the container" << endl;
		if (!c->start(c, 0, NULL)) {
			fprintf(stderr, "Failed to start the container\n");
			goto out;
		}
		
		cout << "launching Xterm" << endl;
		lancerXterm(c);
		
		cout << "stopping the container" << endl;
		if (!c->shutdown(c, 30)) {
			printf("Failed to cleanly shutdown the container, forcing.\n");
			if (!c->stop(c)) {
				fprintf(stderr, "Failed to kill the container.\n");
				goto out;
			}
		}


		cout << "restoring the snapshot" << endl;
		if (!c->snapshot_restore(c, "snap0", "snap0")) 
		{
			fprintf(stderr, "%s: %d: failed to restore snapshot\n", __FILE__, __LINE__);
			exit(1);
		}
	}


	ret = 0;
out:
	lxc_container_put(c);
	return ret;
}
