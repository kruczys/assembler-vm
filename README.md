# CPU Virtual Machine
Simple C program that simulates CPU registers, stack and Instructions.

# Structure

| Instruction | Description |
|:-----------:|-------------|
| MOV, R1, R2      | Copies value from register (R2) to another (R1)|
| XCHG, R1, R2     | Swaps values of two registers|
| PSH, R1          | Pushes value of register onto stack |
| SADD             | Adds two top values of stack and puts the result onto stack |
| XADD, R1, R2     | Adds two registers and saves result in R1, non-destructive for R2 |
| DIV              | Divides second from the top value from stack by the top value and puts result onto stack |
| MUL              | Multiplies two top values from stack and puts result onto stack |
| SUB              | Subtracts top value from second value from stack and puts result onto stack |
| POP              | Pops value from stack |
| CMP, R1, VAL, IP | Compares register R1 to VALue if R1 is less than VALue sets InstructionPointer to IP value else InstructionPointer is incremented by one (program moves onto next Instruction) |
| HLT              | Halts execution and exits |

