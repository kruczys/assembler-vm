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
    IP, SP, AX, BX, CX, DX, EX, FX, 
    NUM_OF_REGISTERS
} Registers;

const int program[] = {
    PSH, 13,
    PSH, 11,
    DIV,
    POP,
    HLT
};

int stack[256];
int registers[NUM_OF_REGISTERS];
bool running = true;

int fetch() {
    return program[registers[IP]];
}

void eval(int instruction) {
    switch (instruction) {
        case HLT: {
            running = false;
            break;
        }
        case MOV: {
            break;
        }
        case SET: {
            break;
        }
        case PSH: {
            registers[SP]++;
            stack[registers[SP]] = program[++registers[IP]];
            break;
        }
        case POP: {
            registers[AX] = stack[registers[SP]--];\
            printf("popped %d\n", registers[AX]);
            break;
        }
        case ADD: {
            registers[AX] = stack[registers[SP]--];
            registers[BX] = stack[registers[SP]--];
            registers[CX] = registers[AX] + registers[BX];
            registers[SP]++;
            stack[registers[SP]] = registers[CX];
            break;
        }
        case MUL: {
            registers[AX] = stack[registers[SP]--];
            registers[BX] = stack[registers[SP]--];
            registers[CX] = registers[AX] * registers[BX];
            registers[SP]++;
            stack[registers[SP]] = registers[CX];
            break;
        }
        case DIV : {
            registers[AX] = stack[registers[SP]--];
            registers[BX] = stack[registers[SP]--];
            if (registers[AX] > registers[BX] || registers[AX] == 0) {
                printf("Pamietaj cholero! Nie dziel przez zero!\n");
                exit(EXIT_SUCCESS);
            }
            else {
                registers[CX] = registers[BX] / registers[AX];
                registers[SP]++;
                stack[registers[SP]] = registers[CX];
            }
            break;
        }
    }
}

int main() {
    registers[IP] = 0;
    registers[SP] = -1;
    while (running) {
        eval(fetch());
        registers[IP]++;
    }
    exit(EXIT_SUCCESS);
}
