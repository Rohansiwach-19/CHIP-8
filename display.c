#include "display.h"




bool displayInit (Display *display) {
    if (!SDL_Init(SDL_FLAG)) {
        fprintf(stderr, "Couldn't initialize the SDL: %s\n", SDL_GetError());
        return false;
    }

    display->window = SDL_CreateWindow("CHIP 8", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!display->window)
    {
        fprintf(stderr, "Couldn't initialize the Window or renderer: %s\n", SDL_GetError());
        return false;
    }

    display->renderer = SDL_CreateRenderer(display->window, NULL);
    if (!display->renderer)
    {
        fprintf(stderr, "Couldn't initialize the Renderer: %s\n", SDL_GetError());
        return false;
    }

    display->texture = SDL_CreateTexture(display->renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display->texture)
    {
        fprintf(stderr, "Couldn't initiate the texture: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool displayDraw(Display *display, Chip8 *chip8) {
    uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
    int pitch = SCREEN_WIDTH * sizeof(uint32_t);
    int const size = SCREEN_WIDTH * SCREEN_HEIGHT;

    for (int i = 0; i < size; i++) {
        pixels[i] = chip8->video[i] ? 0xFFFFFFFF : 0x000000FF;
    }

    SDL_UpdateTexture(display->texture, NULL, pixels, pitch);
    SDL_RenderClear(display->renderer);
    SDL_RenderCopy(display->renderer, display->texture, NULL, NULL);
    SDL_RenderPresent(display->renderer);
}


bool displayDestroy(Display *display) {
    SDL_DestroyTexture(display->texture);
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
    SDL_Quit();
}
