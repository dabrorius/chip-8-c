#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "load_rom.h"

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define PIXEL_SIZE 16

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

  free(program);

  bool screen[SCREEN_WIDTH][SCREEN_HEIGHT] = {false};

  screen[1][1] = true;
  screen[2][1] = true;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("Chippy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * PIXEL_SIZE, SCREEN_HEIGHT * PIXEL_SIZE, 0);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_Event event;
  int running = 1;

  while (running)
  {
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
