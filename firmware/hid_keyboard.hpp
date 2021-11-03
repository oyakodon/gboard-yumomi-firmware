#pragma once

#include <stdint.h>

#define KEYBOARD_REPORT_ID 2

#define KEY_0 0x27
#define KEY_1 0x1e
#define KEY_2 0x1f
#define KEY_3 0x20
#define KEY_4 0x21
#define KEY_5 0x22
#define KEY_6 0x23
#define KEY_7 0x24
#define KEY_8 0x25
#define KEY_9 0x26

#define KEY_A 0x04
#define KEY_B 0x05
#define KEY_C 0x06
#define KEY_D 0x07
#define KEY_E 0x08
#define KEY_F 0x09
#define KEY_U 0x18
#define KEY_EQUAL 0x2e
#define KEY_SEMICOLON 0x33
#define KEY_SPC 0x2c
#define KEY_ENT 0x28

#define KEY_ESCAPE 0x29
#define KEY_BS 0x2A
#define KEY_GRAVE 0x35 // Hankaku / Zenkaku

void sendKeyPush(uint8_t code, bool shift);
void sendHex(int16_t in);

void sendKeys(uint8_t *codes, bool shift);
