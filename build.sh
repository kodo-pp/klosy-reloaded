#!/usr/bin/env bash

kernel_name="klosy-reloaded.elf"

CC="i686-elf-gcc"
CXX="i686-elf-g++"
AS="nasm"
LD="i686-elf-gcc"

CFLAGS="-std=gnu99"
CXXFLAGS="-std=gnu++11 -Ilibkc++/include -fno-exceptions -fno-rtti"
ASFLAGS="-I kernel/include/asm/ -f elf"
LDFLAGS="-T kernel/linker.ld -ffreestanding -O2 -nostdlib -static"

LIBS="-lgcc"
LDFLAGS="${LDFLAGS} ${LIBS}"

FLAGS="-Wall -Wextra -pedantic -Ikernel/include -Ilibkc/include -ffreestanding"
if [[ "${HARDENED}" != 'no' ]]; then
    FLAGS="${FLAGS} -fstack-protector-strong"
fi 

if [[ -z ${KLOSY_MARCH} ]]; then
    KLOSY_MARCH='i686'
fi

echo "Building Klosy for arch ${KLOSY_MARCH}"
FLAGS="${FLAGS} -march=${KLOSY_MARCH} -mtune=generic"

if [ ".${DEBUG}" == '.yes' ]; then
    FLAGS="${FLAGS} -g -Og"
else
    FLAGS="${FLAGS} -O2 -g -funroll-loops -ftree-vectorize"  # TODO: maybe change these flags
fi

CFLAGS="${CFLAGS} ${FLAGS}"
CXXFLAGS="${CXXFLAGS} ${FLAGS}"

function run_command() {
    dump_command "$@"
    shift
    "$@"
    e="$?"
    if [ "$e" -ne 0 ]; then
        echo -e "\e[1;31mError: exit status $e\e[0m"
        kill $$
    fi
}

function dump_command() {
    case $1 in
    cc)
        #echo -ne '\e[1;34m[ CC ]  \e[0m'
        echo -n "  -> Building C source:    "
        ;;
    cxx)
        echo -n "  -> Building C++ source:  "
        ;;
    as)
        echo -n "  -> Building NASM source: "
        ;;
    link)
        echo -n "  -> Linking ELF:          "
        ;;
    esac

    case $1 in
    cc|cxx|as)
        # The last function argument, see https://stackoverflow.com/questions/1853946/getting-the-last-argument-passed-to-a-shell-script
        local src_file="${!#}"
        echo "$src_file"
        ;;
    link)
        local final_elf="${!#}"
        echo "-> $final_elf"
    esac
}

function build_file() {
    if ! [ -f "$1" ]; then
        echo "\e[1;31mError: file '$1' not found\e[0m" >&2
        kill $$
    fi

    objname="$(echo "$1" | sed 's/[.][^.]*$/.o/g')"

    echo "${objname}"

    case $1 in
    *.c)
        run_command cc "${CC}" ${CFLAGS} -c -o "${objname}" "$1" >&2
        ;;
    *.C|*.cpp|*.c++)
        run_command cxx "${CXX}" ${CXXFLAGS} -c -o "${objname}" "$1" >&2
        ;;
    *.asm)
        run_command as "${AS}" ${ASFLAGS} -o "${objname}" "$1" >&2
        ;;
    *)
        echo -e "\e[1;31mError: unable to build file '$1'\e[0m" >&2
        kill $$
        ;;
    esac
}

echo '==> Building...'

objects=''

for i in $(find . -regex '.*[.]\(asm\|c\|C\|cpp\|c++\)' -type f | grep -vF 'NOBUILD'); do
    objects="${objects} $(build_file "$i")"
done

crtbegin_obj="$(${CXX} ${CXXFLAGS} -print-file-name=crtbegin.o)"
crtend_obj="$(${CXX} ${CXXFLAGS} -print-file-name=crtend.o)"

crti_obj="$(build_file "libkc/NOBUILD/crti.asm")"
crtn_obj="$(build_file "libkc/NOBUILD/crtn.asm")"

run_command link "${LD}" ${crti_obj} ${crtbegin_obj} ${objects} ${crtend_obj} ${crtn_obj} \
    ${LDFLAGS} -o "${kernel_name}"
