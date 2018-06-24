#!/usr/bin/env bash


kernel_name="klosy-reloaded.elf"
iso_name="klosy-reloaded.iso"

echo "==> Cleaning up..."

echo "  -> Removing object files"
find . -name '*.o' -delete

echo "  -> Removing ${iso_name}"
rm -f "${iso_name}"

if [ "x$1" == "x--no-keep-kernel" ]; then
    echo "  -> Removing ${kernel_name}"
    rm -f "${kernel_name}"
fi
