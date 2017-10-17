#include <stdio.h>
#include <unistd.h>
#include <lxc/lxccontainer.h>

int funcTst(void* nom)
{
	lxc_attach_command_t* arg= (lxc_attach_command_t*)nom;
	char cmd[100];
	sprintf(cmd, "touch %s", arg->argv[0]);
	system(cmd);
	return 5;
}

int main(int argc, char ** argv) {
	int ret = 1, tst;
	pid_t pid;

	struct lxc_container *c;

	char *prog[]={"salut", "salot"};

	struct lxc_attach_command_t t = {"salut",prog};

	lxc_attach_options_t options = LXC_ATTACH_OPTIONS_DEFAULT;

	/* Setup container struct */
	c = lxc_container_new("passerelle1", NULL);
	if (!c) {
		fprintf(stderr, "Failed to setup lxc_container struct\n");
		goto out;
	}


	/* Start the container */
	if (!c->start(c, 0, NULL)) {
		fprintf(stderr, "Failed to start the container\n");
		goto out;
	}

	/* Query some information */
	printf("Container state: %s\n", c->state(c));
	printf("Container PID: %d\n", c->init_pid(c));
	
	int pipefd[2];
	ret=pipe(pipefd);

	pid=c->init_pid(c);
	tst=c->attach(c, funcTst, &t, &options, &pid);
	if(tst!=0){
		printf("dommage ça marche pas");
	}
	printf("tst = %d\n", tst);


	/* Stop the container */
	if (!c->shutdown(c, 30)) {
		printf("Failed to cleanly shutdown the container, forcing.\n");
		if (!c->stop(c)) {
			fprintf(stderr, "Failed to kill the container.\n");
			goto out;
		}
	}

	ret = 0;
out:
	lxc_container_put(c);
	return ret;
}
