#ifndef DECODE_H
#define DECODE_H

#include "memory/memory.h"
#include <stdint.h>
#include <cpu/cpu.h>

typedef struct Instruction {
  uint8_t opcode[15];
  void (*exec)(CPU *, struct Instruction *);
} Instruction;

Instruction decode(CPU *cpu, Memory *mem);

#endif /* DECODE_H */
