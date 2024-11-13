#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

//TODO Fibonacci

typedef enum {
    MOV,
    XCHG,
    PSH,
    SADD,
    XADD,
    DIV,
    MUL,
    SUB,
    POP,
    SET,
    CMP,
    HLT
} InstructionSet;

typedef enum {
    IP, SP, RAX, RBX, RCX, RDX, REX, RFX, QX1, QX2, RX,
    NUM_OF_REGISTERS
} Registers;

const int program[] = {
    SET, RAX, 0,
    SET, RBX, 1,
    XADD, RAX, RBX,
    PSH, RAX,
    POP,
    MOV, RCX, RAX,
    CMP, RCX, 100, 2,
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
            registers[IP]++;
            registers[program[registers[IP]]] = registers[program[registers[IP] + 1]];
            registers[IP]++;
            break;
        }
        case XCHG: {
            registers[IP]++;
            registers[program[registers[IP]]] += registers[program[registers[IP] + 1]];
            registers[program[registers[IP] + 1]] = registers[program[registers[IP]]] - registers[program[registers[IP] + 1]];
            registers[program[registers[IP]]] -= registers[program[registers[IP] + 1]];
            registers[IP]++;
            break;
        }
        case SET: {
            registers[IP]++;
            registers[program[registers[IP]]] = program[registers[IP] + 1];
            registers[IP]++;
            break;
        }
        case CMP: {
            registers[IP]++;
            if (registers[program[registers[IP]]] < program[++registers[IP]])
                registers[IP] = program[++registers[IP]];
            else {
                registers[IP]++;
            }
            break;
        }
        case PSH: {
            registers[SP]++;
            stack[registers[SP]] = registers[program[++registers[IP]]];
            break;
        }
        case POP: {
            printf("popped %d\n", stack[registers[SP]--]);
            break;
        }
        case SADD: {
            registers[QX1] = stack[registers[SP]--];
            registers[QX2] = stack[registers[SP]--];
            registers[RX] = registers[QX1] + registers[QX2];
            registers[SP]++;
            stack[registers[SP]] = registers[RX];
            break;
        }
        case XADD: {
            registers[QX1] = registers[program[++registers[IP]]];
            registers[QX2] = registers[program[++registers[IP]]];
            registers[program[registers[IP] - 1]] = registers[QX1] + registers[QX2];
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
