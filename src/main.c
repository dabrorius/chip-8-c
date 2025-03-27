#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "load_rom.h"
#include "instructions/ins_clear_screen.h"

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define PIXEL_SIZE 16
#define PROGRAM_LOAD_POSITION 0x200

int main()
{
  printf("Welcome to Chippy!\n");

  unsigned char memory[4096] = {0};

  // Load ROM into a variable
  unsigned char *program = NULL;
  int programSize = 0;
  loadRom("./roms/1-chip8-logo.ch8", &program, &programSize);

  // Load ROM into Chip-8 memory starting at position 0x200
  memcpy(&memory[PROGRAM_LOAD_POSITION], program, programSize);
  free(program);

  // Print out state of memory
  printf("Memory:\n");
  for (int i = 0; i < 4096; i++)
  {
    if (i % 16 == 0)
    {
      printf("\n%04x: ", i);
    }

    printf("%02x", memory[i]);

    if ((i + 1) % 2 == 0)
    {
      printf(" ");
    }
  }
  printf("\n---- ---- ----\n");

  // Initialize Chip-8 screen
  bool screen[SCREEN_WIDTH][SCREEN_HEIGHT] = {false};
  screen[1][1] = true;
  screen[2][1] = true;

  int pc = PROGRAM_LOAD_POSITION;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("Chippy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * PIXEL_SIZE, SCREEN_HEIGHT * PIXEL_SIZE, 0);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_Event event;
  int running = 1;

  unsigned char currentInstruction[INSTRUCTION_SIZE];

  while (running)
  {
    memcpy(&currentInstruction, &memory[pc], INSTRUCTION_SIZE);
    pc += INSTRUCTION_SIZE;

    char c1 = currentInstruction[0] / 0x10;
    char c2 = currentInstruction[0] % 0x10;
    char c3 = currentInstruction[1] / 0x10;
    char c4 = currentInstruction[1] % 0x10;

    char matchedHandler = false;
    matchedHandler = matchedHandler || INS_clearScreen(&c1, &c2, &c3, &c4, screen, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!matchedHandler)
    {
      fprintf(stderr, "Unknown instruction '%x%x%x%x'!\n", c1, c2, c3, c4);
      exit(1);
    }

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = 0;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int column = 0; column < SCREEN_WIDTH; column++)
    {
      for (int row = 0; row < SCREEN_HEIGHT; row++)
      {
        if (screen[column][row])
        {
          SDL_Rect square = {column * PIXEL_SIZE, row * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE};
          SDL_RenderFillRect(renderer, &square);
        }
      }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
