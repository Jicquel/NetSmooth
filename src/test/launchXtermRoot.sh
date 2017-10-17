#!/bin/bash

xterm -hold -e "lxc-attach -n $1; kill \$PPID"
