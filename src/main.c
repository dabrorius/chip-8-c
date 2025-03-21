#include <stdio.h>
#include <stdlib.h>

#include "load_rom.h"

int main()
{
  printf("Welcome to Chippy!\n");

  Chip8Instruction *program = NULL;
  int programSize = 0;

  loadRom("./roms/1-chip8-logo.ch8", &program, &programSize);

  for (int instructionNumber = 0; instructionNumber < programSize; instructionNumber++)
  {

    for (int instructionCharNumber = 0; instructionCharNumber < INSTRUCTION_SIZE; instructionCharNumber++)
    {
      printf("%02x", program[instructionNumber].code[instructionCharNumber]);
    }

    printf("\n");
  }

  return 0;
}
