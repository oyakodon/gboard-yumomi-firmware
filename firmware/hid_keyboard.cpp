#include "hid_keyboard.hpp"
#include <Keyboard.h>

void sendKeyPush(uint8_t code, bool shift)
{
  KeyReport keys;
  keys.keys[0] = 0;
  keys.keys[1] = 0;
  keys.keys[2] = 0;
  keys.keys[3] = 0;
  keys.keys[4] = 0;
  keys.keys[5] = 0;
  keys.modifiers = 0x00;
  if (shift)
  {
    keys.modifiers = 0x02;
    HID().SendReport(KEYBOARD_REPORT_ID, &keys, sizeof(KeyReport));
  }
  keys.keys[0] = code;
  HID().SendReport(KEYBOARD_REPORT_ID, &keys, sizeof(KeyReport));
  keys.keys[0] = 0;
  HID().SendReport(KEYBOARD_REPORT_ID, &keys, sizeof(KeyReport));
  if (shift)
  {
    keys.modifiers = 0;
    HID().SendReport(KEYBOARD_REPORT_ID, &keys, sizeof(KeyReport));
  }
}

void sendKeys(uint8_t *codes, bool shift)
{
  KeyReport keys;
  keys.keys[0] = codes[0];
  keys.keys[1] = codes[1];
  keys.keys[2] = codes[2];
  keys.keys[3] = codes[3];
  keys.keys[4] = codes[4];
  keys.keys[5] = codes[5];
  keys.modifiers = shift ? 0x02 : 0x00;

  HID().SendReport(KEYBOARD_REPORT_ID, &keys, sizeof(KeyReport));
}

void sendHex(int16_t in)
{
  static const uint8_t codes[] = {
      KEY_0,
      KEY_1,
      KEY_2,
      KEY_3,
      KEY_4,
      KEY_5,
      KEY_6,
      KEY_7,
      KEY_8,
      KEY_9,
      KEY_A,
      KEY_B,
      KEY_C,
      KEY_D,
      KEY_E,
      KEY_F,
  };
  static const bool shifts[] = {
      false,
      false,
      false,
      false,
      false,
      false,
      false,
      false,
      false,
      false,
      true,
      true,
      true,
      true,
      true,
      true,
  };

  for (int i = 0; i < 4; i++)
  {
    byte f = (in >> ((3 - i) * 4)) & 0xf;
    sendKeyPush(codes[f], shifts[f]);
  }
}
