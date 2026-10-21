#ifndef FETCH_H
#define FETCH_H

#include <stdint.h>

#include <memory/memory.h>
#include <cpu/cpu.h>

uint8_t fetch8(CPU *cpu, Memory *mem);

#endif /* FETCH_H */
