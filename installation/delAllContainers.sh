#!/bin/bash

for i in `seq 0 9`;do
  lxc-destroy -n "ordinateur"$i
done

for i in `seq 0 4`;do
  lxc-destroy -n "passerelle"$i
done
