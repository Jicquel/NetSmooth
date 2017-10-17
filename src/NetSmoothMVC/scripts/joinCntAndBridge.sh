#!/bin/bash

#	permet de relier un container a un
#	bridge

if [ $# -ne 3 ] ; then
	echo "USAGE = $0 <container name> <bridge name> <port number>"
	echo "you wrote $0 $@" > ~/PD
	exit
fi


inter=$(lxc-info -n $1 | grep "Link" | awk {'print $2'} | tr '\n' ' ' | awk {'print $'$(($3+1))})

echo "inter = $inter"

/sbin/brctl addif $2 $inter

echo joinCntAndBridge.sh run
