#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#define REGISTERS_NUMS 16 // creates a unchangable variable of value 16 before compile time
#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define NUM_KEYS 16
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define FONT_SIZE 80
#define START_ADDRESS 0x200
#define FONT_ADDRESS 0x050

typedef struct {
    uint8_t registers[REGISTERS_NUMS];
    uint8_t memory[MEMORY_SIZE];
    uint16_t index;
    uint16_t pc;
    uint16_t stack[STACK_SIZE];
    uint8_t sp;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t keypad[NUM_KEYS];
    uint32_t video[SCREEN_WIDTH*SCREEN_HEIGHT];
    uint16_t opcode;

}Chip8;
