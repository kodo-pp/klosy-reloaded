#include <kernel/keyboard.hpp>

static bool shift = false;
static bool ctrl = false;
static bool alt = false;

uint32_t key_translate(uint8_t scancode)
{
    if (16 <= scancode && scancode <= 25) {
        return static_cast <uint32_t> ("qwertyuiop"[scancode - 16]);
    } else if (30 <= scancode && scancode <= 38) {
        return static_cast <uint32_t> ("asdfghjkl"[scancode - 30]);
    } else if (44 <= scancode && scancode <= 50) {
        return static_cast <uint32_t> ("zxcvbnm"[scancode - 44]);
    } else if (2 <= scancode && scancode <= 11) {
        return static_cast <uint32_t> ("1234567890"[scancode - 2]);
    } else if (144 <= scancode && scancode <= 153) {
        return static_cast <uint32_t> ("qwertyuiop"[scancode - 144]) | RELEASED | NO_KEY;
    } else if (158 <= scancode && scancode <= 166) {
        return static_cast <uint32_t> ("asdfghjkl"[scancode - 158]) | RELEASED | NO_KEY;
    } else if (172 <= scancode && scancode <= 178) {
        return static_cast <uint32_t> ("zxcvbnm"[scancode - 172]) | RELEASED | NO_KEY;
    } else if (130 <= scancode && scancode <= 139) {
        return static_cast <uint32_t> ("1234567890"[scancode - 130]) | RELEASED | NO_KEY;
    } else {
        switch (scancode) {
            case 57: return static_cast <uint32_t> (' ');
            case 28: return static_cast <uint32_t> ('\n');
            case 14: return static_cast <uint32_t> ('\b');
            case 15: return static_cast <uint32_t> ('\t');
            case 185: return static_cast <uint32_t> (' ')  | RELEASED | NO_KEY;
            case 156: return static_cast <uint32_t> ('\n') | RELEASED | NO_KEY;
            case 142: return static_cast <uint32_t> ('\b') | RELEASED | NO_KEY;
            case 143: return static_cast <uint32_t> ('\t') | RELEASED | NO_KEY;
        }
        return NO_KEY;
    }
}
