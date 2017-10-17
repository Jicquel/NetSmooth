# Installation
## Required softwares

* Qt version 5.5.1
* LXC (https://linuxcontainers.org/fr/lxc/downloads/)
* package icu
* package lxcfs
* package bridge-utils
* package net-tools

## Installation for a root utilisation

	cd ~/
	git clone https://github.com/Jicquel/Netsmooth.git
	cd ~/NetSmooth/installation/  
	sudo ./installation_container.sh
	cd ~/NetSmooth/src/NetSmoothMVC/  
	qmake
	make

#### WARNING
*./installation_container.sh* will empty file */etc/lxc/default.conf*

## Installation for an unprivileged utilisation

Create the directory ~/.config/lxc if it doesn't exist

Check if everything is enabled with 

	lxc-checkconfig
if not, you will have to clone or rebuild the kernel.

	sudo chmod -R a+rw /sys/fs/cgroup

	su
	echo `whoami`:100000:65536 >> /etc/subuid   
	echo `whoami`:100000:65536 >> /etc/subgid
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
