#!/usr/bin/env bash


kernel_name="klosy-reloaded.elf"
iso_name="klosy-reloaded.iso"

echo 'Removing object files...'
find . -name '*.o' -delete
echo 'Done'
rm -vf "${iso_name}"

if [ "x$1" == "x--no-keep-kernel" ]; then
     rm -vf "${kernel_name}"
 fi
