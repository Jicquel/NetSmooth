#!/bin/bash

#	permet de créer un bridge dont 
#	le nom est le premier argument
/sbin/brctl addbr $1

/sbin/ifconfig $1 up 2> /dev/null

echo "bridge created : '$1'"
echo creerBridge.sh run
