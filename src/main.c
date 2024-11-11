#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

// TODO SET, MOV, DIV, Branching

typedef enum {
    MOV,
    PSH,
    ADD,
    DIV,
    MUL,
    SUB,
    POP,
    SET,
    HLT
} InstructionSet;

typedef enum {
    IP, SP, AX, BX, CX, DX, EX, FX, QX1, QX2, RX,
    NUM_OF_REGISTERS
} Registers;

const int program[] = {
    SET, AX, 10,
    PSH, AX, 
    SET, BX, 20,
    PSH, BX, 
    ADD,
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
            registers[program[++registers[IP]]] = registers[program[++registers[IP]]];
            break;
        }
        case SET: {
            registers[program[++registers[IP]]] = program[++registers[IP]];
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
            registers[QX1] = stack[registers[SP]--];
            registers[QX2] = stack[registers[SP]--];
            registers[RX] = registers[QX1] + registers[QX2];
            registers[SP]++;
            stack[registers[SP]] = registers[RX];
            break;
        }
        case SUB: {
            registers[QX1] = stack[registers[SP]--];
            registers[QX2] = stack[registers[SP]--];
            registers[RX] = registers[QX2] - registers[QX1];
            registers[SP]++;
            stack[registers[SP]] = registers[RX];
            break;
        }
        case MUL: {
            registers[QX1] = stack[registers[SP]--];
            registers[QX2] = stack[registers[SP]--];
            registers[RX] = registers[QX1] * registers[QX2];
            registers[SP]++;
            stack[registers[SP]] = registers[RX];
            break;
        }
        case DIV : {
            registers[QX1] = stack[registers[SP]--];
            registers[QX2] = stack[registers[SP]--];
            if (registers[QX1] > registers[QX2] || registers[QX1] == 0) {
                printf("Pamietaj cholero! Nie dziel przez zero!\n");
                exit(EXIT_SUCCESS);
            }
            else {
                registers[RX] = registers[QX2] / registers[QX1];
                registers[SP]++;
                stack[registers[SP]] = registers[RX];
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
