#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct {
  uint32_t eax;
  uint32_t ebx;
  uint32_t ecx;
  uint32_t edx;
  uint32_t eip;
  uint32_t eflags;
} CPU;

void cpu_init(CPU *cpu);

#endif /* CPU_H */
