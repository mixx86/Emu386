#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>

#include <cpu/cpu.h>

typedef struct Instruction {
  uint8_t opcode[15];
  void (*exec)(CPU *, struct Instruction *);
} Instruction;

Instruction decode(CPU *cpu);

#endif /* DECODE_H */
