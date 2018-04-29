#!/usr/bin/env bash

kernel_name="klosy-reloaded.elf"
iso_name="klosy-reloaded.iso"
iso_tmp_dir="iso-dir"

if [ "$1" == "-f" ] || ! [ -f "${kernel_name}" ]; then
    ./build.sh || exit 1
fi

mkdir "${iso_tmp_dir}"
cp -v "${kernel_name}" "${iso_tmp_dir}"
cd "${iso_tmp_dir}"
mkdir -p boot/grub
cd boot/grub
cat > grub.cfg << EOF
menuentry "Klosy Reloaded" {
	multiboot /klosy-reloaded.elf
}
EOF
cd ../../..

grub-mkrescue -o "${iso_name}" "${iso_tmp_dir}"

rm -rf "${iso_tmp_dir}"
