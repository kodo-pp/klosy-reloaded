#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from os import access, R_OK

null_char = ('.' * 8 + '\n') * 8

def cat(filename):
    try:
        with open(filename) as f:
            return f.read()
    except Exception:
        return None

def to_byte(s):
    bits = ''.join(['1' if i == '#' else '0' for i in s])
    return int(bits, 2)

def main():
    print('  -> Building font for graphical mode...')

    temp = [cat('font/{}'.format(i)) for i in range(256)]
    chars_count = sum((0 if i is None else 1 for i in temp))
    raw_font = [null_char if i is None else i for i in temp]
    del temp

    print('    -> Found {} char(s)'.format(chars_count))

    split_raw_font = [i.split() for i in raw_font]
    del raw_font
    
    font_array = [reversed([to_byte(i).to_bytes(1, 'little') for i in j]) for j in split_raw_font] 

    font = b''
    for i in font_array:
        for j in i:
            font += j

    with open('initrd.d/default_font.bin', 'wb') as f:
        f.write(font)

if __name__ == '__main__':
    main()
