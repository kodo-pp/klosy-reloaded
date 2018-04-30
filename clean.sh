#!/usr/bin/env bash


kernel_name="klosy-reloaded.elf"
iso_name="klosy-reloaded.iso"

echo -e '\e[1;33m[ RM ]  \e[0mRemoving object files'
find . -name '*.o' -delete
echo -e "\e[1;33m[ RM ]  \e[0mRemoving ${iso_name}"
rm -f "${iso_name}"

if [ "x$1" == "x--no-keep-kernel" ]; then
    echo -e "\e[1;33m[ RM ]  \e[0mRemoving ${kernel_name}"
     rm -f "${kernel_name}"
fi
