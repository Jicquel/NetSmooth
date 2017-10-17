#!/bin/bash

/sbin/ifconfig $1 down
/sbin/brctl delbr $1

echo "bridge destroyed : '$1'"
echo detruireBridge.sh run
