#include "encode7.h"

static char encode[16] = {
    0077,   // 0
    0006,   // 1
    0133,   // 2
    0117,   // 3
    0146,   // 4
    0155,   // 5
    0175,   // 6
    0007,   // 7
    0177,   // 8
    0157,   // 9
    0167,   // A
    0174,   // b
    0071,   // C
    0136,   // d
    0171,   // E
    0161,   // F
};

// encode hexadecimal digit for a seven-segment display
char Encode7segment(int digit, int point)
{
    char code = (digit >= 0 && digit < 16) ? encode[digit] : 0;
    return point ? code | 0x80 : code;
}
