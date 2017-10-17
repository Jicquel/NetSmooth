#!/bin/bash

#add the bridge if not present
/sbin/brctl addbr lxcbr0

#containers need lxcbr0 to start
lxc-start -n $1

#get interfaces of the container
interfaces=`lxc-info -n $1 | grep "Link" | sed -e s/Link://`

#unjoin the interfaces from the bridge lxcbr0
for i in $interfaces; do
  /sbin/brctl delif lxcbr0 $i
done

echo lancerContainer.sh run

