#pragma once

#include <stdint.h>

#define KEYBOARD_REPORT_ID 2

#define KEY_A 0x04
#define KEY_B 0x05
#define KEY_C 0x06
#define KEY_D 0x07
#define KEY_E 0x08
#define KEY_F 0x09
#define KEY_G 0x0A
#define KEY_H 0x0B
#define KEY_I 0x0C
#define KEY_J 0x0D
#define KEY_K 0x0E
#define KEY_L 0x0F
#define KEY_M 0x10
#define KEY_N 0x11
#define KEY_O 0x12
#define KEY_P 0x13
#define KEY_Q 0x14
#define KEY_R 0x15
#define KEY_S 0x16
#define KEY_T 0x17
#define KEY_U 0x18
#define KEY_V 0x19
#define KEY_W 0x1A
#define KEY_X 0x1B
#define KEY_Y 0x1C
#define KEY_Z 0x1D

#define KEY_1 0x1E
#define KEY_2 0x1F
#define KEY_3 0x20
#define KEY_4 0x21
#define KEY_5 0x22
#define KEY_6 0x23
#define KEY_7 0x24
#define KEY_8 0x25
#define KEY_9 0x26
#define KEY_0 0x27

#define KEY_EQUAL 0x2E
#define KEY_SEMICOLON 0x33
#define KEY_COMMA 0x36
#define KEY_DOT 0x37
#define KEY_SPC 0x2C
#define KEY_ENT 0x28

#define KEY_ESCAPE 0x29
#define KEY_BS 0x2A
#define KEY_GRAVE 0x35 // Hankaku / Zenkaku

void sendKeyPush(uint8_t code, bool shift);
void sendHex(int16_t in);

void sendKeys(uint8_t *codes, bool shift);
