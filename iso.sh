#!/usr/bin/env bash

set -e

kernel_name="klosy-reloaded.elf"
iso_name="klosy-reloaded.iso"
iso_tmp_dir="iso-dir"

if [ "$1" == "-f" ] || ! [ -f "${kernel_name}" ]; then
    ./build.sh || exit 1
fi

mkdir "${iso_tmp_dir}"
cp "${kernel_name}" "${iso_tmp_dir}"
cd "${iso_tmp_dir}"
mkdir -p boot/grub
cd boot/grub
cat > grub.cfg << EOF
menuentry "Klosy Reloaded" {
	multiboot /klosy-reloaded.elf
    module /initrd
}
EOF

cd ../..
cat > initrd << EOF
This is a test initrd file, created on host OS and usable by Klosy. This file
sould preferably have some structure and be something like a TAR archive.
EOF
cd ..

echo -e "\e[1;35m[GRUB]  \e[0m${iso_tmp_dir} -> ${iso_name}"
grub-mkrescue -o "${iso_name}" "${iso_tmp_dir}" 2>/dev/null

echo -e "\e[1;33m[ RM ]  \e[0mRemoving ${iso_tmp_dir}"
rm -rf "${iso_tmp_dir}"
