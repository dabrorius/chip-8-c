#ifndef LOAD_ROM_H
#define LOAD_ROM_H

#define INSTRUCTION_SIZE 2

void loadRom(const char *fileName, unsigned char **program, int *programSize);

#endif