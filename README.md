# NetSmooth

## Installation
### Required softwares

* Qt version 5.5.1
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
Command with *sudo* **MUST** executed with *sudo*. Command with *su* **MUST** also be executed with *su*.  

Create the directory ~/.config/lxc if it doesn't exist
	
	mkdir ~/.config/lxc
	touch ~/.config/lxc/default.conf
	sudo `whoami` veth lxcbr0 100 >> /etc/lxc/lxc-usernet
	echo lxc.network.type = veth >> ~/.config/lxc/default.conf
	echo lxc.id_map = u 0 100000 65536 >> ~/.config/lxc/default.conf
	echo lxc.id_map = g 0 100000 65536 >> ~/.config/lxc/default.conf
	
Check if everything is enabled with 

	lxc-checkconfig
if not, you will have to clone or rebuild the kernel.

	
	
	sudo chmod -R a+rw /sys/fs/cgroup
	sudo echo `whoami`:100000:65536 >> /etc/subuid   
	sudo echo `whoami`:100000:65536 >> /etc/subgid
	
	su	
	echo 1 > /sys/fs/cgroup/cpuset/cgroup.clone_children
	echo 1 > /proc/sys/kernel/unprivileged_userns_clone  
	exit
	
	sudo chmod u+s /sbin/ifconfig
	sudo chmod u+s /sbin/brctl
	
	cd ~/
	git clone https://github.com/Jicquel/Netsmooth.git   
	cd ~/NetSmooth/installation/  
	./creerContainers.sh
	sudo ./moveScripts.sh
	sudo ./configContainers_unprivileged.sh $HOME
 	cd ~/NetSmooth/src/NetSmoothMVC/  
	qmake  
	make

The following commands have to be executed at the start of the computer :  

	sudo chmod -R a+rw /sys/fs/cgroup
	su
	echo 1 > /sys/fs/cgroup/cpuset/cgroup.clone_children
	echo 1 > /proc/sys/kernel/unprivileged_userns_clone  
	exit

## Execution
### Unprivileged version

	~/NetSmooth/src/NetSmoothMVC/NetSmooth	
### Root version
	
	sudo ~/NetSmooth/src/NetSmoothMVC/NetSmooth	

## Help for LXC's users
### Containers root
Containers are by default in the directory /var/lib/lxc/\<container name>  
The file system is in /var/lib/lxc/\<container name>/rootfs/  
The configuration file is /var/lib/lxc/\<container name>/config  
	
The path "/var/lib/lxc/" is set in /etc/lxc/lxc.conf with lxc.lxcpath=\<path>  
  
Configuration file of a container *"ordinateur"* :

	lxc.include = /usr/share/lxc/config/debian.common.conf
	lxc.arch = x86
	lxc.network.type = veth
	lxc.network.name = eth0
	lxc.network.flags = up
	lxc.rootfs = /var/lib/lxc/<container's name>/rootfs
	lxc.utsname = <container's name>


Configuration file of a container *"passerelle"* :

	lxc.include = /usr/share/lxc/config/debian.common.conf
	lxc.arch = x86
	lxc.network.type = veth
	lxc.network.name = eth0
	lxc.network.flags = up  
	lxc.network.type = veth
	lxc.network.name = eth1
	lxc.network.flags = up  
	lxc.network.type = veth
	lxc.network.name = eth2
	lxc.network.flags = up  
	lxc.network.type = veth
	lxc.network.name = eth3
	lxc.network.flags = up
	lxc.rootfs = /var/lib/lxc/<container's name>/rootfs
	lxc.utsname = <container's name>

## Tips
To connect a container to the internet :
* set lxc.network.type to "none"
* start the container
* copy /etc/resolv.conf of the host host in the /etc/resolv.conf of the container
