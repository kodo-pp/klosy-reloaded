#!/usr/bin/env bash

set -e
shopt -s nullglob

echo -n "Building initrd... "

cd initrd.d/
tar -cf ../initrd.tar *

echo -e "\e[1;32mDone\e[0m"
