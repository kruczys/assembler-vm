#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    MOV,
    PSH,
    ADD,
    DIV,
    POP,
    SET,
    HLT
} InstructionSet;

typedef enum {
    A, B, C, D, E, F,
    NUM_OF_REGISTERS
} Registers;

const int program[] = {
    PSH, 6,
    PSH, 7,
    ADD,
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
            int val_popped = stack[sp--];\
            printf("popped %d\n", val_popped);
            break;
        }
        case ADD: {
            int a = stack[sp--];
            int b = stack[sp--];
            int result = a + b;
            sp++;
            stack[sp] = result;
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
