#include <stdio.h>
#include <stdint.h>
#include "chip.h"

const uint8_t fontset[FONT_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
}

void initCHIP8(Chip8 *chip8) {

    chip8->pc = START_ADDRESS; // STARTED THE PC FROM THE 0x200.
    chip8->opcode = 0;
    chip8->index = 0;
    chip8->sp = 0;

    // clear stack
    for (int i = 0; i < STACK_SIZE; i++) {
        chip8->stack[i] = 0;
    }

    // clear registers
    for (int i = 0; i < REGISTERS_NUMS; i++) {
        chip8->registers[i] = 0;
    }

    // clear memory
    for (int i = 0; i < MEMORY_SIZE; i++) {
        chip8->memory[i] = 0;
    }

    // clear Display
    for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
        chip8->video[i] = 0;
    }

    // loading fontset
    for (int i = 0; i < 80; i++) {
        chip8->memory[FONT_ADDRESS + i] = fontset[i];
    } 

    // reset timers
}

void loadROM(Chip8 *chip8, char *filename) {
    FILE *fp;
    fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Error couldn't open ROM %s\n", filename);
    }

    
    for (int i = 0; i < ) {
        
    }
}
