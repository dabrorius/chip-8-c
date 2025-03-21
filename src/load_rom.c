#include <stdio.h>
#include <stdlib.h>
#include "load_rom.h"

void loadRom(const char *fileName, Chip8Instruction **program, int *programSize)
{
  FILE *file = fopen(fileName, "rb");

  if (file == NULL)
  {
    fputs("File error", stderr);
    exit(1);
  }

  unsigned char instruction[INSTRUCTION_SIZE];
  size_t bytesRead;

  while ((bytesRead = fread(instruction, 1, sizeof(instruction), file)))
  {
    *programSize = *programSize + 1;

    *program = realloc(*program, *programSize * sizeof(Chip8Instruction));

    for (int instructionCharNumber = 0; instructionCharNumber < bytesRead; instructionCharNumber++)
    {
      (*program)[*programSize - 1].code[instructionCharNumber] = instruction[instructionCharNumber];
    }
  }

  fclose(file);
}