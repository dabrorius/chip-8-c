#include <stdbool.h>
#include "ins_clear_screen.h"

// Clear screen
// Instruction format: 00E0
bool INS_clearScreen(char *c1, char *c2, char *c3, char *c4, bool screen[][SCREEN_HEIGHT])
{
  if (*c1 == 0 && *c2 == 0 && *c3 == 0xE && *c4 == 0)
  {
    for (int column = 0; column < SCREEN_WIDTH; column++)
    {
      for (int row = 0; row < SCREEN_HEIGHT; row++)
      {
        screen[column][row] = false;
      }
    }

    return true;
  }

  return false;
}
