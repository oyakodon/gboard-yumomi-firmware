#include <Keyboard.h>
#include <Mouse.h>

#include "hid_keyboard.hpp"
#include "yunomi.hpp"
#include "keymap.hpp"

KeyMap keymap;
Yunomi yunomi;

void setup()
{
  Keyboard.begin();
  Mouse.begin();

  yunomi.reset();
  delay(100);
}

void sendUnicode(uint16_t code, bool isEmoji)
{
  if (code == 0x00)
    return;

  sendKeyPush(KEY_U, true);
  sendKeyPush(KEY_SEMICOLON, true);

  if (isEmoji)
  {
    sendKeyPush(KEY_1, false);
  }
  sendHex(code);

  sendKeyPush(KEY_SPC, false);
  sendKeyPush(KEY_SPC, false);
  sendKeyPush(KEY_ENT, false);
}

void sendKeyCode(const KeyCode &code, bool shift = false)
{
  if (code.isUnicode)
  {
    sendUnicode(code.unicode, code.isEmoji);
    return;
  }

  for (int i = 0; i < 2; i++)
  {
    if (code.codes[i] != 0x00)
    {
      sendKeyPush(code.codes[i], shift);
    }
  }
}

const uint16_t THD_LongPress_SPKEY = 1500; // [ms]
const uint16_t THD_LongPress = 500;        // [ms]

InputMode mode = InputMode::KANJI;
bool cancel_kana = false;
bool pressing, long_pressed, pressed;
long pressed_duration;
long keys_pressed[60] = {-1};

bool mc_mode = false;
void performMinecraft(int idx, bool pressing);

int idx, r, c;

void loop()
{
  delay(10);

  for (r = 0; r < ROWS; r++)
  {
    for (c = 0; c < COLS; c++)
    {
      idx = yunomi.getIndex(r, c);
      pressing = yunomi.readKey(r, c);

      pressed = keys_pressed[idx] == -1 && pressing;
      pressed_duration = keys_pressed[idx] < 0 ? 0 : millis() - keys_pressed[idx];
      long_pressed = pressing && pressed_duration >= THD_LongPress;

      if (!mc_mode && (pressed || long_pressed))
      {
        if (keymap.isSpecialKey(idx))
        {
          SpecialKey key = keymap.getSpecialKey(idx);
          switch (key)
          {
          case SpecialKey::KANA:
            if (pressed || (!cancel_kana && pressed_duration >= THD_LongPress_SPKEY))
            {
              if (!pressed)
              {
                sendKeyPush(KEY_GRAVE, false);
              }

              cancel_kana = !pressed;
              mode = mode == InputMode::KANA ? InputMode::KANJI : InputMode::KANA;
            }
            break;
          case SpecialKey::MO:
            if (pressed)
            {
              if (mode == InputMode::KANJI)
              {
                sendKeyCode(keymap.getSpecialKeyCode(key), false);
              }
              else
              {
                sendKeyPush(KEY_A + 12, false); // m
                sendKeyPush(KEY_A + 14, false); // o
              }
            }
            if (pressed_duration >= THD_LongPress_SPKEY && mode != InputMode::ALPHABET)
            {
              mode = InputMode::ALPHABET;
            }
            if (pressed_duration >= THD_LongPress_SPKEY * 2 && !mc_mode)
            {
              mc_mode = true;
              sendUnicode(0x1F607, true);
            }
            break;
          case SpecialKey::PROLONGED:
          case SpecialKey::EXCLAMATION:
          case SpecialKey::QUESTION:
          {
            sendKeyCode(keymap.getSpecialKeyCode(key), key != SpecialKey::PROLONGED);
            if (mode != InputMode::ALPHABET)
            {
              sendKeyPush(KEY_ENT, false);
            }
            break;
          }
          default:
            sendKeyCode(keymap.getSpecialKeyCode(key), false);
            break;
          }
        }
        else if (keymap.isCharKey(mode, idx))
        {
          sendKeyCode(keymap.getKeyCode(mode, idx));
        }

        delay(75);
      }

      if (mc_mode)
      {
        if (idx == 56 && pressed)
        {
          mc_mode = false;
        }

        performMinecraft(idx, pressing);
      }

      if (pressing ^ keys_pressed[idx] != -1)
        keys_pressed[idx] = pressing ? millis() : -1;

      yunomi.reset();
    }
  }
}

void performMinecraft(int idx, bool pressing)
{
  static uint8_t key_states[6] = {0x00};
  static uint8_t map[5][2] = {
      {31, KEY_A + 22}, // W
      {35, KEY_A},      // A
      {36, KEY_A + 18}, // S
      {37, KEY_A + 3},  // D
      {38, KEY_SPC},    // Space
  };
  static bool state_changed = false;

  for (int i = 0; i < 5; i++)
  {
    if (idx != map[i][0])
      continue;

    if (!key_states[i] && pressing)
    {
      key_states[i] = map[i][1];
      state_changed = true;
    }
    else if (key_states[i] && !pressing)
    {
      key_states[i] = 0x00;
      state_changed = true;
    }
  }

  if (state_changed)
  {
    sendKeys(key_states, false);
  }

  switch (idx)
  {
  case 15:
    // left
    if (pressing)
      Mouse.move(-15, 0, 0);
    break;
  case 19:
    // right
    if (pressing)
      Mouse.move(15, 0, 0);
    break;
  case 33:
    if (pressing)
      Mouse.press(MOUSE_LEFT);
    else if (Mouse.isPressed(MOUSE_LEFT))
      Mouse.release(MOUSE_LEFT);
    break;
  case 34:
    if (pressing)
      Mouse.press(MOUSE_RIGHT);
    else if (Mouse.isPressed(MOUSE_RIGHT))
      Mouse.release(MOUSE_RIGHT);
    break;
  default:
    break;
  }
}
