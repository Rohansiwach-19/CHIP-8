#include <stdio.h>
#include <stdint.h>
#include <string.h>
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
};

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

    char c;
    int i = 0;
    while (c = fgetc(fp) != EOF ) {
        if (START_ADDRESS + i > MEMORY_SIZE) {
            fprintf(stderr, "ROM size is too large\n");
            fclose(fp);
            return;
        }
        chip8->memory[START_ADDRESS + i] = c;
        i++;
    }

    fclose(fp);
}

void emulateCycle (Chip8 *chip8){

        // here << is bitwise left, used to occupy upper half 8 bits then | merges the two bytes together
        chip8->opcode = (chip8->memory[chip8->pc] << 8) | chip8->memory[chip8->pc + 1];
        uint16_t opcode = chip8->opcode;
        chip8->pc += 2;

        // imp variables to be used in instructions.
        uint16_t nnn = opcode & 0x0FFF; // last 12 bits, usually an address
        uint8_t n = opcode & 0x000F; // forth nibble, 4 bits
        uint8_t x = opcode & 0x0F00 >> 8; // second nibble, usually a register index
        uint8_t y = opcode & 0x00F0 >> 4; // third nibble, usually a register index
        uint8_t nn = opcode & 0x00FF; // last two nibbles, lower byte

        switch (opcode & 0xF000) // gives us the first nibble
        {
            case 0x000:
                switch (opcode & 0x00F) {
                    case 0x0000: // 0x00E0 clears the screen, we got the last nibble from it.
                        memset(chip8->video, 0, SCREEN_HEIGHT * SCREEN_WIDTH);
                        break;
                    case 0x000E: // 0x00EE return from subroutine
                        chip8->pc = chip8->stack[--chip8->sp];
                        break;
                    default:
                        fprintf(stderr, "Unknown opcode [0x000]: 0x%X\n", opcode);
                }
                break;

            case 0x1000: // 0x1NNN jmp to address nnn
                chip8->pc = nnn;
                break;

            case 0x6000: // 0x6XNN set register VX
                chip8->registers[x] = nn;
                break;

            case 0x7000:
                chip8->registers[x] += nn;
                break;

            case 0xA000: // 0xANNN, set index register I
                chip8->index = nnn;
                break;

            case 0xD000: // 0xDXYN display/Draw
                uint8_t spriteByte;
                uint8_t height = n; // number of rows, got it from the last nibble.
                uint8_t x_loc = chip8->registers[x]; // get the value of Vx for the coordinates
                uint8_t y_loc = chip8->registers[y];

                for (int rows = 0; rows < n; rows++) {
                    spriteByte = chip8->memory[chip8->index + rows];
                   for (int col = 0; col < 8; col++) {
                       uint8_t spritePixel = spriteByte & (0x80 >> col);
                       uint32_t *screenPixel = &chip8->video[(x_loc + col + ((y_loc + rows) * 64))];

                       if (spritePixel) {
                           if (*screenPixel == 0xFFFFFFFF) {
                               chip8->registers[0xF] = 1; // collision
                           }

                           *screenPixel ^= 1;
                       }
                   }
                }
                chip8->drawFlag = true;
                chip8->pc += 2;
                break;
        }
    }
}
