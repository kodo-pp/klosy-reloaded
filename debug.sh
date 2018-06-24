#!/usr/bin/env bash

# Runs a debugger

case "$1" in
    gdb)
        gdb -s klosy-reloaded.elf
        ;;
    cgdb)
        cgdb -- -s klosy-reloaded.elf
        ;;
    *)
        echo "Unknown debugger: $1."
        echo "Possible options: gdb, cgdb"
        exit 1
esac
