#include <stdbool.h>

bool INS_clearScreen(char *c1, char *c2, char *c3, char *c4, bool screen[][32], int width, int height)
{
  // Recognize 00E0 instruction
  if (*c1 == 0 && *c2 == 0 && *c3 == 0xE && *c4 == 0)
  {
    for (int column = 0; column < width; column++)
    {
      for (int row = 0; row < height; row++)
      {
        screen[column][row] = false;
      }
    }

    return true;
  }

  return false;
}
