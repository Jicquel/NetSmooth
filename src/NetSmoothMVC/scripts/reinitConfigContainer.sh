#!/bin/bash


echo -n > /var/lib/lxc/$1/rootfs/.networkInfo/ipConfig.info
echo -n > /var/lib/lxc/$1/rootfs/.networkInfo/route4Config.info
echo -n > /var/lib/lxc/$1/rootfs/.networkInfo/route6Config.info
echo reinitConfigContainer.sh run
