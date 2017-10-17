#!/bin/bash
bridgeName="lxcbr0"

echo $HOME

if [ "$UID" -ne "0" ]; then
  echo "Installation de container pour utilisateur non-privilégié!"
  echo "Variable \$HOME est : $HOME. Si elle est incorrect, le script ne fonctionnera pas."
  echo "veuillez patienter, le premier container est en cours de de création"

if [ `uname -m | grep 64 | wc -l` = "0" ];then
  lxc-create -n ordinateur0 -t download -- -d debian -r jessie -a i386 > /dev/null 2> /dev/null
else
  lxc-create -n ordinateur0 -t download -- -d debian -r jessie -a amd64 > /dev/null 2> /dev/null
fi

  echo "vos containers sont en cours de création, veuillez patienter..."

  echo "lxc.include = /usr/share/lxc/config/debian.common.conf" > $HOME/.local/share/lxc/ordinateur0/config
  echo "lxc.include = /usr/share/lxc/config/debian.userns.conf" >> $HOME/.local/share/lxc/ordinateur0/config
  echo "lxc.arch = x86" >> $HOME/.local/share/lxc/ordinateur0/config
  
  echo "" >> $HOME/.local/share/lxc/ordinateur0/config
  
  echo "lxc.id_map = u 0 100000 65536" >> $HOME/.local/share/lxc/ordinateur0/config
  echo "lxc.id_map = g 0 100000 65536" >> $HOME/.local/share/lxc/ordinateur0/config

  echo "" >> $HOME/.local/share/lxc/ordinateur0/config
  
  echo "lxc.rootfs = $HOME/.local/share/lxc/ordinateur0/rootfs" >> $HOME/.local/share/lxc/ordinateur0/config
  echo "lxc.rootfs.backend = dir" >> $HOME/.local/share/lxc/ordinateur0/config
  echo "lxc.utsname = ordinateur0" >> $HOME/.local/share/lxc/ordinateur0/config
  
  echo "" >> $HOME/.local/share/lxc/ordinateur0/config

  echo "lxc.network.type = veth" >> $HOME/.local/share/lxc/ordinateur0/config
  echo "lxc.network.name = eth0" >> $HOME/.local/share/lxc/ordinateur0/config
  echo "lxc.network.flags = up" >> $HOME/.local/share/lxc/ordinateur0/config
  echo "lxc.network.link = $bridgeName" >> $HOME/.local/share/lxc/ordinateur0/config

  lxc-copy -n ordinateur0 -N passerelle0 > /dev/null 2> /dev/null

  echo "lxc.include = /usr/share/lxc/config/debian.common.conf" > $HOME/.local/share/lxc/passerelle0/config
  echo "lxc.include = /usr/share/lxc/config/debian.userns.conf" >> $HOME/.local/share/lxc/passerelle0/config
  echo "lxc.arch = x86" >> $HOME/.local/share/lxc/passerelle0/config
  echo "" >> $HOME/.local/share/lxc/passerelle0/config

  echo "lxc.id_map = u 0 100000 65536" >> $HOME/.local/share/lxc/passerelle0/config
  echo "lxc.id_map = g 0 100000 65536" >> $HOME/.local/share/lxc/passerelle0/config

  echo "" >> $HOME/.local/share/lxc/passerelle0/config
  echo "lxc.rootfs = $HOME/.local/share/lxc/passerelle0/rootfs" >> $HOME/.local/share/lxc/passerelle0/config
  echo "lxc.rootfs.backend = dir" >> $HOME/.local/share/lxc/passerelle0/config
  echo "lxc.utsname = passerelle0" >> $HOME/.local/share/lxc/passerelle0/config
  echo "" >> $HOME/.local/share/lxc/passerelle0/config
  for i in {0..3}; do
    echo "lxc.network.type = veth" >> $HOME/.local/share/lxc/passerelle0/config
    echo "lxc.network.name = eth$i" >> $HOME/.local/share/lxc/passerelle0/config
    echo "lxc.network.flags = up" >> $HOME/.local/share/lxc/passerelle0/config
    echo "lxc.network.link = $bridgeName" >> $HOME/.local/share/lxc/passerelle0/config
    echo "" >> $HOME/.local/share/lxc/passerelle0/config
  done

  for i in {1..9}; do
    lxc-copy -n ordinateur0 -N ordinateur$i > /dev/null 2> /dev/null &
  done

  for i in {1..4}; do
    lxc-copy -n passerelle0 -N passerelle$i > /dev/null 2> /dev/null &
  done
#
  list="0"
  pos=0
#  while [ "$list" != "" ]; do
#    list=$(ps | grep lxc-copy)
#    sleep 0.5
#    clear
#    echo -n "vos containers sont en cours de création, veuillez patienter"
#    i=0
#    while [ $i -lt $pos ]; do
#      echo -n "."
#      i=$((i+1))
#    done
#    echo
#    pos=$((($pos+1)%4))
#  done
 # clear
 echo "containers en cours de création"
  exit
fi
clear

echo "Installation des containers privilégiés"

echo "veuillez patienter, le premier container est en cours de de création"

if [ `uname -m | grep 64 | wc -l` = "0" ];then
  lxc-create -n ordinateur0 -t download -- -d debian -r jessie -a i386 > /dev/null 2> /dev/null
else
  lxc-create -n ordinateur0 -t download -- -d debian -r jessie -a amd64 > /dev/null 2> /dev/null
fi

echo "lxc.include = /usr/share/lxc/config/debian.common.conf" > /var/lib/lxc/ordinateur0/config
echo "lxc.arch = x86" >> /var/lib/lxc/ordinateur0/config
echo "" >> /var/lib/lxc/ordinateur0/config
echo "lxc.rootfs = /var/lib/lxc/ordinateur0/rootfs" >> /var/lib/lxc/ordinateur0/config
echo "lxc.rootfs.backend = dir" >> /var/lib/lxc/ordinateur0/config
echo "lxc.utsname = ordinateur0" >> /var/lib/lxc/ordinateur0/config
echo "" >> /var/lib/lxc/ordinateur0/config
echo "lxc.network.type = none" >> /var/lib/lxc/ordinateur0/config
cp /etc/resolv.conf /var/lib/lxc/ordinateur0/rootfs/etc/resolv.conf
echo "installez tout ce dont vous avez besoins dans ce container."
lxc-start -n ordinateur0 > /dev/null
xterm -hold -e "lxc-attach -n ordinateur0; kill \$PPID" &
a=""
while [ "$a" != "ok" ]; do
  echo -n "fermez le xterm et tapez 'ok' quand vous avez terminé : "
  read a
done
lxc-stop -n ordinateur0 > /dev/null

echo "vos containers sont en cours de création, veuillez patienter..."

echo "lxc.include = /usr/share/lxc/config/debian.common.conf" > /var/lib/lxc/ordinateur0/config
echo "lxc.arch = x86" >> /var/lib/lxc/ordinateur0/config
echo "" >> /var/lib/lxc/ordinateur0/config
echo "lxc.rootfs = /var/lib/lxc/ordinateur0/rootfs" >> /var/lib/lxc/ordinateur0/config
echo "lxc.rootfs.backend = dir" >> /var/lib/lxc/ordinateur0/config
echo "lxc.utsname = ordinateur0" >> /var/lib/lxc/ordinateur0/config
echo "" >> /var/lib/lxc/ordinateur0/config
echo "lxc.network.type = veth" >> /var/lib/lxc/ordinateur0/config
echo "lxc.network.name = eth0" >> /var/lib/lxc/ordinateur0/config
echo "lxc.network.flags = up" >> /var/lib/lxc/ordinateur0/config

lxc-copy -n ordinateur0 -N passerelle0 > /dev/null 2> /dev/null

echo "lxc.include = /usr/share/lxc/config/debian.common.conf" > /var/lib/lxc/passerelle0/config
echo "lxc.arch = x86" >> /var/lib/lxc/passerelle0/config
echo "" >> /var/lib/lxc/passerelle0/config
echo "lxc.rootfs = /var/lib/lxc/passerelle0/rootfs" >> /var/lib/lxc/passerelle0/config
echo "lxc.rootfs.backend = dir" >> /var/lib/lxc/passerelle0/config
echo "lxc.utsname = passerelle0" >> /var/lib/lxc/passerelle0/config
echo "" >> /var/lib/lxc/passerelle0/config
for i in {0..3}; do
  echo "lxc.network.type = veth" >> /var/lib/lxc/passerelle0/config
  echo "lxc.network.name = eth$i" >> /var/lib/lxc/passerelle0/config
  echo "lxc.network.flags = up" >> /var/lib/lxc/passerelle0/config
  echo "" >> /var/lib/lxc/passerelle0/config
done

for i in {1..9}; do
  lxc-copy -n ordinateur0 -N ordinateur$i > /dev/null 2> /dev/null &
done

for i in {1..4}; do
  lxc-copy -n passerelle0 -N passerelle$i > /dev/null 2> /dev/null &
done

list="0"
pos=0
while [ "$list" != "" ]; do
  list=$(ps | grep lxc-copy)
  sleep 0.5
  clear
  echo -n "vos containers sont en cours de création, veuillez patienter"
  i=0
  while [ $i -lt $pos ]; do
    echo -n "."
    i=$((i+1))
  done
  echo
  pos=$((($pos+1)%4))
done
clear
