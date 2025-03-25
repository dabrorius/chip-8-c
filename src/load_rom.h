#ifndef LOAD_ROM_H
#define LOAD_ROM_H

#define INSTRUCTION_SIZE 2

typedef struct
{
  unsigned char code[4];
} Chip8Instruction;

void loadRom(const char *fileName, unsigned char **program, int *programSize);

#endif