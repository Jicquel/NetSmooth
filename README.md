# NetSmooth

## Installation
### Required softwares

* Qt version 5.5.1 or newer
* LXC (https://linuxcontainers.org/fr/lxc/downloads/)
* package icu
* package lxcfs
* package bridge-utils
* package net-tools
* package uidmap
* package libpam-cgfs


### Installation for a root utilisation

	cd ~/
	git clone https://github.com/Jicquel/Netsmooth.git
	cd ~/NetSmooth/installation/  
	sudo ./installation_container.sh
	cd ~/NetSmooth/src/NetSmoothMVC/  
	qmake
	make

#### WARNING
*./installation_container.sh* will empty file */etc/lxc/default.conf*

### Installation for an unprivileged utilisation
#### WARNING 
Command with *sudo* **MUST** be executed with *sudo*. Command with *su* **MUST** also be executed with *su*.  
If you don't have the permissions to write in a file, use chmod to change permissions.   

Create the directory ~/.config/lxc if it doesn't exist.
	
	mkdir ~/.config/lxc
	touch ~/.config/lxc/default.conf

  if ~/.config/lxc/default.conf already existed, **make sure that the following lines are not already written**.  


	sudo echo "`whoami` veth lxcbr0 100" >> /etc/lxc/lxc-usernet
	echo "lxc.network.type = veth" >> ~/.config/lxc/default.conf
	echo "lxc.id_map = u 0 100000 65536" >> ~/.config/lxc/default.conf
	echo "lxc.id_map = g 0 100000 65536" >> ~/.config/lxc/default.conf
	
Check if everything is enabled with 

	lxc-checkconfig
if not, you will have to clone or rebuild the kernel.

	
	
	sudo chmod -R a+rw /sys/fs/cgroup 

  **Make sure that the following lines are not already written**.  


	sudo echo `whoami`:100000:65536 >> /etc/subuid   
	sudo echo `whoami`:100000:65536 >> /etc/subgid
	
	su	
	echo 1 > /sys/fs/cgroup/cpuset/cgroup.clone_children
	echo 1 > /proc/sys/kernel/unprivileged_userns_clone  
	exit
	
	sudo chmod u+s /sbin/ifconfig
	sudo chmod u+s /sbin/brctl
	
	cd ~/
	git clone https://github.com/Jicquel/NetSmooth.git   
	cd ~/NetSmooth/installation/  
	./creerContainers.sh
	sudo ./moveScripts.sh
	sudo ./configContainers_unprivileged.sh $HOME
 	cd ~/NetSmooth/src/NetSmoothMVC/  
	qmake  
	make

**The following commands have to be executed at the start of the computer** :  

	sudo chmod -R a+rw /sys/fs/cgroup
	su
	echo 1 > /sys/fs/cgroup/cpuset/cgroup.clone_children
	echo 1 > /proc/sys/kernel/unprivileged_userns_clone  
	exit

#### Copy an executable in the containers (virtuals machines)

  If you want to have an executable, for example *ping* or *tcpdump* in a container. You will have to copy it into the file system of the container.  
                                                       
  To copy a privileged executable in containers, like *ifconfig* :  
   
    
  	for a in $(ls -d /var/lib/lxc/*); do cp /sbin/ifconfig $a/rootfs/sbin/; done


  To copy a non-privileged executable in containers, like *vim* :  
  
   
    	for a in $(ls -d ~/.locale/share/lxc/*); do cp /sbin/ifconfig $a/rootfs/sbin/; done


## Execution
### Root version
	
	sudo ~/NetSmooth/src/NetSmoothMVC/NetSmooth	

### Unprivileged version

	~/NetSmooth/src/NetSmoothMVC/NetSmooth	


## Resources

  Images and scripts used by the software are located in /usr/share/NetSmooth/ 
