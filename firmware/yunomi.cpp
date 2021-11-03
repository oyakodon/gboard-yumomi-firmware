#include "yunomi.hpp"

#include <Arduino.h>

void Yunomi::selectRow(Pin p)
{
  bool col = !!(COL & p);
  byte mask = 1 << (p & B01111111);
  if (col)
  {
    DDRD = mask;
    PORTD = ~mask;
  }
  else
  {
    DDRB = mask;
    PORTB = ~mask;
  }
}

bool Yunomi::readCol(Pin p)
{
  bool col = !!(COL & p);
  byte mask = 1 << (p & B01111111);
  return ((col ? PIND : PINB) & mask) == 0;
}

void Yunomi::reset()
{
  DDRD = 0;
  PORTD = B00111111;
  DDRB = 0;
  PORTB = B00011111;
}

bool Yunomi::readKey(int row, int col)
{
  static Pin keyPins[5][12][2] = {
      {
          {C0, R4},
          {C1, R0},
          {C2, R1},
          {C3, R2},
          {C4, R3},
          {C5, R4},
          {R0, C0},
          {R1, C1},
          {R2, C2},
          {R3, C3},
          {R4, C4},
          {R0, C5},
      },
      {
          {C0, R3},
          {C1, R4},
          {C2, R0},
          {C3, R1},
          {C4, R2},
          {C5, R3},
          {R4, C0},
          {R0, C1},
          {R1, C2},
          {R2, C3},
          {R3, C4},
          {R4, C5},
      },
      {
          {C0, R2},
          {C1, R3},
          {C2, R4},
          {C3, R0},
          {C4, R1},
          {C5, R2},
          {R3, C0},
          {R4, C1},
          {R0, C2},
          {R1, C3},
          {R2, C4},
          {R3, C5},
      },
      {
          {C0, R1},
          {C1, R2},
          {C2, R3},
          {C3, R4},
          {C4, R0},
          {C5, R1},
          {R2, C0},
          {R3, C1},
          {R4, C2},
          {R0, C3},
          {R1, C4},
          {R2, C5},
      },
      {
          {C0, R0},
          {C1, R1},
          {C2, R2},
          {C3, R3},
          {C4, R4},
          {C5, R0},
          {R1, C0},
          {R2, C1},
          {R3, C2},
          {R4, C3},
          {R0, C4},
          {R1, C5},
      },
  };

  Pin *key = keyPins[row][col];
  selectRow(key[0]);
  delayMicroseconds(10);
  return readCol(key[1]);
}

int Yunomi::getIndex(int row, int col)
{
  static int keyIndexes[5][12] = {
      {26, 21, 16, 11, 6, 1, 59, 54, 49, 44, 39, 34},
      {27, 22, 17, 12, 7, 2, 55, 50, 45, 40, 35, 30},
      {28, 23, 18, 13, 8, 3, 56, 51, 46, 41, 36, 31},
      {29, 24, 19, 14, 9, 4, 57, 52, 47, 42, 37, 32},
      {25, 20, 15, 10, 5, 0, 58, 53, 48, 43, 38, 33},
  };

  return keyIndexes[row][col];
}
