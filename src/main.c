#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("Welcome to Chippy!\n");

  FILE *file = fopen("./roms/1-chip8-logo.ch8", "rb");

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
    for (int i = 0; i < bytesRead; i++)
    {
      printf("%02x", instruction[i]);
    }

    printf("\n");
  }

  fclose(file);
  return 0;
}