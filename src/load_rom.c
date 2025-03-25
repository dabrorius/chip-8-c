#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    memcpy(*program + *programSize, instruction, bytesRead);
    *programSize += bytesRead;
  }

  fclose(file);
}