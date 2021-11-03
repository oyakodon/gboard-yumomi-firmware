#pragma once

#include <binary.h>

#define ROWS 5
#define COLS 12

// COLS = PD0, PD1, PD2, PD3, PD4, PD5
// ROWS = PB0, PB1, PB2, PB3, PB4

#define COL B10000000
#define ROW B00000000

class Yunomi
{
public:
  int getIndex(int row, int col);
  bool readKey(int row, int col);
  void reset();

private:
  typedef enum
  {
    C0 = COL + 0,
    C1 = COL + 1,
    C2 = COL + 2,
    C3 = COL + 3,
    C4 = COL + 4,
    C5 = COL + 5,

    R0 = ROW + 0,
    R1 = ROW + 1,
    R2 = ROW + 2,
    R3 = ROW + 3,
    R4 = ROW + 4,
  } Pin;

  void selectRow(Pin p);
  bool readCol(Pin p);
};
