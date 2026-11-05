#include <stdio.h>
#include "display.h"
#include "chip.h"

int main(int argc, char **argv) {

    char filename = **argv;
    Chip8 chip8;
    Display display;

    diplayInit(&display);

    initCHIP8(&chip8);
    loadROM(&chip8, &filename);

    bool done = false;
    while (!done) {
        while (SDL_PollEvent(&display.event)) {
            if (display.event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
        displayDraw(&display, &chip8);
    }

   displayDestroy(&display);
   return 0;
}
