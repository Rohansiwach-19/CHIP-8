#ifndef DISPLAY_H
#define DISPLAY_H


#include "chip.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>


#define SDL_FLAG (SDL_INIT_VIDEO | SDL_INIT_AUDIO)


typedef struct Display {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;
} Display;


bool diplayInit(Display *display);
bool displayDraw(Display *display, Chip8 *chip8);

bool displayDestroy(Display *display);

#endif
