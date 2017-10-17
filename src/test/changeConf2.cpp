#include <stdio.h>
#include <lxc/lxccontainer.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <lxc/utils.h>

int main(void) {
  struct lxc_container *c;
  int ret = 1;
  char *argv[] = {"ifconfig",NULL};
    lxc_attach_command_t command = {"ifconfig", argv};
  lxc_attach_options_t options = LXC_ATTACH_OPTIONS_DEFAULT;
  lxc_attach_exec_t salut;
  pid_t pid;
  /* Setup container struct */
  c = lxc_container_new("ordinateur0", NULL);
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

  if(c->attach(c,lxc_attach_run_command,&command,&options,&pid)!=0){
    printf("dommage ça marche pas");
  }
  printf("%d",pid);
//  while(waitpid(pid,0,WNOHANG)>0);
wait_for_pid(pid);




  


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
