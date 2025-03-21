#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  unsigned char code[4];
} Chip8Instruction;

void readRomFile(const char *fileName, Chip8Instruction **program, int *programSize);

int main()
{
  printf("Welcome to Chippy!\n");

  Chip8Instruction *program = NULL;
  int programSize = 0;

  readRomFile("./roms/1-chip8-logo.ch8", &program, &programSize);

  for (int i = 0; i < programSize; i++)
  {

    for (int j = 0; j < 2; j++)
    {
      printf("%02x", program[i].code[j]);
    }

    printf("\n");
  }

  return 0;
}

void readRomFile(const char *fileName, Chip8Instruction **program, int *programSize)
{
  FILE *file = fopen(fileName, "rb");

  if (file == NULL)
  {
    fputs("File error", stderr);
    exit(1);
  }

  const int instructionSize = 2;
  unsigned char instruction[instructionSize];
  size_t bytesRead;

  while ((bytesRead = fread(instruction, 1, sizeof(instruction), file)))
  {
    *programSize = *programSize + 1;

    *program = realloc(*program, *programSize * sizeof(Chip8Instruction));

    for (int i = 0; i < bytesRead; i++)
    {
      // printf("%02x", instruction[i]);
      (*program)[*programSize - 1].code[i] = instruction[i];
    }

    // printf("\n");
  }

  fclose(file);
}