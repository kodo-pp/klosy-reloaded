#!/usr/bin/env bash

QEMU_PARAMS="-m 256"

iso_name="klosy-reloaded.iso"

# Please, don't replace 'a' with 'x' here (I mean the first character of the string)
if [ "a${KR_DEBUG}" == 'ayes' ]; then
    QEMU_PARAMS="${QEMU_PARAMS} -s"
fi

if [ "x$1" == "x-f" ] || ! [ -f "${iso_name}" ]; then
    ./iso.sh $1 || exit 1
fi

qemu-system-i386 ${QEMU_PARAMS} -cdrom "${iso_name}"
