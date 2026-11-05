#include "display.h"
#include "chip.h"

int main(int argc, char **argv) {

    Chip8 chip8;
    Display display;

    initCHIP8(&chip8);
    loadROM(&chip8, argv[1]);
    displayInit(&display);

    bool done = false;
    while (!done) {

        while (SDL_PollEvent(&display.event)) {
            if (display.event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        for (int i = 0; i < 10; i++) {
            emulateCycle(&chip8);
        }

        displayDraw(&display, &chip8);
    }

   displayDestroy(&display);
   return 0;
}
