#include "keymap.hpp"

#include "hid_keyboard.hpp"

const uint16_t sakanaCodes[10][5] = {
    {
        0x9BF5, // 鯵 (あ)
        0x9C2F, // 鰯 (い)
        0x9C3B, // 鰻 (う)
        0x9C4F, // 鱏 (え)
        0x9C27, // 鰧 (お)
    },
    {
        0x9C39, // 鰹 (か)
        0x9C5A, // 鱚 (き)
        0x9BE8, // 鯨 (く)
        0x9B5D, // 魝 (け)
        0x9BC9, // 鯉 (こ)
    },
    {
        0x9BD6, // 鯖 (さ)
        0x9BF1, // 鯱 (し)
        0x9C78, // 鱸 (す)
        0x9BAC, // 鮬 (せ)
        0x9BFC, // 鯼 (そ)
    },
    {
        0x9BDB, // 鯛 (た)
        0x9C58, // 鱘 (ち)
        0x9C41, // 鱁 (つ)
        0x9BF3, // 鯳 (て)
        0x9C0C, // 鰌 (と)
    },
    {
        0x9C60, // 鱠 (な)
        0x9C0A, // 鰊 (に)
        0x9C56, // 鱖 (ぬ)
        0x9BF0, // 鯰 (ね)
        0x9B76, // 魶 (の)
    },
    {
        0x9C30, // 鰰 (は)
        0x9C2D, // 鰭 (ひ)
        0x9C24, // 鰤 (ふ)
        0x9B83, // 鮃 (へ)
        0x9BD4, // 鯔 (ほ)
    },
    {
        0x9BAA, // 鮪 (ま)
        0x9BAB, // 鮫 (み)
        0x9BE5, // 鯥 (む)
        0x9BB4, // 鮴 (め)
        0x9B79  // 魹 (も)
    },
    {
        0x9C25, // 鰥 (や)
        0x309B, // ゛
        0x9B77, // 魷 (ゆ)
        0x309C, // ゜
        0x9C29, // 鰩 (よ)
    },
    {
        0x9C73, // 鱳 (ら)
        0x9BDA, // 鯚 (り)
        0x9BCD, // 鯍 (る)
        0x9C7A, // 鱺 (れ)
        0x9B6F, // 魯 (ろ)
    },
    {
        0x9C19, // 鰙 (わ)
        0x3001, // 、
        0x9B5A, // 魚 (を)
        0x3002, // 。
        0x9C77, // 鱷 (ん)
    },
};

bool KeyMap::isCharKey(InputMode mode, int idx)
{
    if (isSpecialKey(idx))
        return false;

    if (mode != InputMode::ALPHABET)
        return true;

    return idx < (KEY_ENT - KEY_A);
}

KeyCode KeyMap::getKeyCode(InputMode mode, int idx)
{
    static uint8_t vowols[5] = {
        KEY_A,
        KEY_I,
        KEY_U,
        KEY_E,
        KEY_O,
    };
    static uint8_t consonants[9] = {
        KEY_A,
        KEY_K, // K
        KEY_S, // S
        KEY_T, // T
        KEY_N, // N
        KEY_H, // H
        KEY_M, // M
        KEY_Y, // Y
        KEY_R, // R
    };
    static uint8_t row_wa[5][2] = {
        {KEY_W, KEY_A},    // わ
        {0x00, KEY_COMMA}, // 、 (,)
        {KEY_W, KEY_O},    // を
        {0x00, KEY_DOT},   // 。 (.)
        {KEY_N, KEY_N},    // ん
    };

    switch (mode)
    {
    case InputMode::ALPHABET:
        return KeyCode{0, {0, static_cast<uint8_t>(KEY_A + idx)}, false, false};
    case InputMode::KANA:
        if (idx / 5 < 9)
        {
            return KeyCode{0, {idx < 5 ? (uint8_t)0x00 : consonants[idx / 5], vowols[idx % 5]}, false, false};
        }
        return KeyCode{0, {row_wa[idx % 5][0], row_wa[idx % 5][1]}, false, false};
    case InputMode::KANJI:
        return KeyCode{sakanaCodes[idx / 5][idx % 5], {0, 0}, true, false};
    default:
        break;
    }
}

SpecialKey KeyMap::getSpecialKey(int idx)
{
    return static_cast<SpecialKey>(idx - 50);
}

KeyCode KeyMap::getSpecialKeyCode(SpecialKey key)
{
    static KeyCode SpecialKeyCodes[]{
        {0, {0, KEY_BS}, false, false},     // BACKSPACE
        {0, {0, 0x2D}, false, false},       // PROLONGED
        {0, {0, KEY_1}, false, false},      // EXCLAMATION
        {0, {0, 0x38}, false, false},       // QUESTION
        {0x1F38F, {0, 0}, true, true},      // CARP
        {0, {0, 0}, false, false},          // KANA
        {0x85FB, {0, 0}, true, false},      // MO
        {0, {0, KEY_SPC}, false, false},    // SPACE
        {0, {0, KEY_ENT}, false, false},    // ENTER
        {0, {0, KEY_ESCAPE}, false, false}, // ESCAPE
    };

    return SpecialKeyCodes[static_cast<int>(key)];
}
