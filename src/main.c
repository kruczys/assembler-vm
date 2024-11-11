#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// TODO SET, MOV, DIV, Branching

typedef enum {
    MOV,
    PSH,
    ADD,
    DIV,
    MUL,
    POP,
    SET,
    HLT
} InstructionSet;

typedef enum {
    AX, BX, CX, DX, EX, FX,
    NUM_OF_REGISTERS
} Registers;

const int program[] = {
    PSH, 5,
    PSH, 6,
    MUL,
    POP,
    HLT
};

int ip = 0;
int sp = -1;
int stack[256];
int registers[NUM_OF_REGISTERS];
bool running = true;

int fetch() {
    return program[ip];
}

void eval(int instruction) {
    switch (instruction) {
        case HLT: {
            running = false;
            break;
        }
        case PSH: {
            sp++;
            stack[sp] = program[++ip];
            break;
        }
        case POP: {
            registers[AX] = stack[sp--];\
            printf("popped %d\n", registers[AX]);
            break;
        }
        case ADD: {
            registers[AX] = stack[sp--];
            registers[BX] = stack[sp--];
            registers[CX] = registers[AX] + registers[BX];
            sp++;
            stack[sp] = registers[CX];
            break;
        }
        case MUL: {
            registers[AX] = stack[sp--];
            registers[BX] = stack[sp--];
            registers[CX] = registers[AX] * registers[BX];
            sp++;
            stack[sp] = registers[CX];
            break;
        }
    }
}

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }
    exit(EXIT_SUCCESS);
}
