#!/bin/bash
if [ "$UID" -ne "0" ]; then
  echo "You must be root to execute this script"
  exit
fi

if ! [ -e /usr/share/NetSmooth ]; then
  mkdir /usr/share/NetSmooth/

fi
if ! [ -e /usr/share/NetSmooth/scripts ]; then
  mkdir /usr/share/NetSmooth/scripts/
fi
list=`ls ../src/NetSmoothMVC/scripts/`


for i in $list;do
  echo $i
  `cp ../src/NetSmoothMVC/scripts/$i /usr/share/NetSmooth/scripts/$i`
done

