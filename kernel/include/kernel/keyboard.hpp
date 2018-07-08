#ifndef KERNEL_KEYBOARD_HPP
#define KERNEL_KEYBOARD_HPP

#include <buffer.hpp>
extern kstd::buffer <char> keyboard_buffer;

const uint32_t NO_KEY     = (1 << 8);
const uint32_t WITH_SHIFT = (1 << 9);
const uint32_t WITH_CTRL  = (1 << 10);
const uint32_t WITH_ALT   = (1 << 11);
const uint32_t RELEASED   = (1 << 12);

uint32_t key_translate(uint8_t scancode);

#endif // end of include guard: KERNEL_KEYBOARD_HPP
