#!/bin/bash

#on vide le fichier de configuration par défaut.
echo "" > /etc/lxc/default.conf 

./moveScripts.sh

./delAllContainers.sh

./creerContainers.sh

./configContainers.sh clean

./configContainers.sh
