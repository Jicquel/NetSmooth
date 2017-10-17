#!/bin/bash

xterm -T "$2" -e "lxc-attach -n $1; kill \$PPID"
echo launchXtermRoot.sh run
