#!/usr/bin/env bash

set -e
shopt -s nullglob

echo "==> Building initrd... "

echo "  -> Running pre-build hooks..."
./font.py

cd initrd.d/
tar -cf ../initrd.tar *
