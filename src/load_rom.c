#include <stdio.h>
#include <stdlib.h>
#include "load_rom.h"

void loadRom(const char *fileName, unsigned char **program, int *programSize)
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

    *program = realloc(*program, (*programSize + bytesRead));

    for (int instructionCharNumber = 0; instructionCharNumber < bytesRead; instructionCharNumber++)
    {
      *(*program + *programSize) = instruction[instructionCharNumber];
      *programSize = *programSize + 1;
    }
  }

  fclose(file);
}