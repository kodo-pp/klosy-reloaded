#!/usr/bin/env bash

QEMU_PARAMS="-m 256"

iso_name="klosy-reloaded.iso"

if [ "$1" == "-f" ] || ! [ -f "${iso_name}" ]; then
    ./iso.sh $1 || exit 1
fi

qemu-system-i386 ${QEMU_PARAMS} -cdrom "${iso_name}"
