#pragma once

#include <stdint.h>

enum class SpecialKey : int
{
  BACKSPACE = 0,
  PROLONGED,
  EXCLAMATION,
  QUESTION,
  CARP,
  KANA,
  MO,
  SPACE,
  ENTER,
  ESCAPE,
};

enum class InputMode
{
  KANJI,
  KANA,
  ALPHABET
};

struct KeyCode
{
  uint16_t unicode;
  uint8_t codes[2];

  bool isUnicode;
  bool isEmoji;
};

class KeyMap
{
public:
  bool isCharKey(InputMode mode, int idx);
  KeyCode getKeyCode(InputMode mode, int idx);

  SpecialKey getSpecialKey(int idx);
  KeyCode getSpecialKeyCode(SpecialKey key);
  inline bool isSpecialKey(int idx)
  {
    return idx >= 50;
  }
};
