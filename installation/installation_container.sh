#!/bin/bash

if [ "$UID" -ne "0" ]; then
	echo "Installation non privilégiée!"
else
	echo "Installation privilégiée!"
fi
#on vide le fichier de configuration par défaut.

echo "" > /etc/lxc/default.conf 

./moveScripts.sh

./delAllContainers.sh

./creerContainers.sh

./configContainers.sh clean

./configContainers.sh
