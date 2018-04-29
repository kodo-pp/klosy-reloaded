#!/usr/bin/env bash

kernel_name="klosy-reloaded.elf"

CC="i686-elf-gcc"
CXX="i686-elf-g++"
AS="i686-elf-as"
LD="i686-elf-gcc"

CFLAGS="-Wall -Wextra -std=c99 -pedantic -Ikernel/include -Ilibkc/include -ffreestanding"
CXXFLAGS="-Wall -Wextra -std=c99 -pedantic -Ikernel/include -Ilibkc/include -ffreestanding -fno-exceptions -fno-rtti"
ASFLAGS=""
LDFLAGS="-T kernel/linker.ld -ffreestanding -O2 -nostdlib"

LIBS="-lgcc"
LDFLAGS="${LDFLAGS} ${LIBS}"

function run_command() {
    echo "RUN" "$@" >&2
    "$@"
    e="$?"
    if [ "$e" -ne 0 ]; then
        echo "Error: exit status $e"
        kill $$
    fi
}

function build_file() {
    if ! [ -f "$1" ]; then
        echo "Error: file '$1' not found" >&2
        kill $$
    fi

    objname="$(echo "$i" | sed 's/[.][^.]*$/.o/g')"

    echo "${objname}"

    case $1 in
    *.c)
        run_command "${CC}" ${CFLAGS} -c -o "${objname}" "$1" >&2
        ;;
    *.C|*.cpp|*.c++)
        run_command "${CXX}" ${CXXFLAGS} -c -o "${objname}" "$1" >&2
        ;;
    *.s|*.S)
        run_command "${AS}" ${ASFLAGS} -c -o "${objname}" "$1" >&2
        ;;
    *)
        echo "Error: unable to build file '$1'" >&2
        kill $$
        ;;
    esac
}

objects=''

for i in $(find . -regex '.*[.]\(s\|S\|c\|C\|cpp\|c++\)' -type f); do
    objects="${objects} $(build_file "$i")"
done

run_command "${LD}" ${LDFLAGS} ${objects} -o "${kernel_name}"
