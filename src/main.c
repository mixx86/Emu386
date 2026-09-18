#include "args.h"
#include "config.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  uint32_t eax;
  uint32_t ebx;
  uint32_t ecx;
  uint32_t edx;
  uint32_t eip;
  uint32_t eflags;

  uint8_t *memory;
} CPU;

typedef struct Instruction {
  uint8_t opcode[15];
  void (*exec)(CPU *, struct Instruction *);
} Instruction;

void exec_nop(CPU *cpu, Instruction *ins) {
  // NOP does nothing
  (void)cpu;
  (void)ins;
}

uint8_t fetch8(CPU *cpu) { return cpu->memory[cpu->eip++]; }

Instruction decode(CPU *cpu) {
  Instruction ins = {0};

  ins.opcode[0] = fetch8(cpu);

  switch (ins.opcode[0]) {
  case 0x90:
    ins.exec = &exec_nop;
    break;
  }

  return ins;
}

int main(int argc, char *argv[]) {
  struct EmuConfig *conf = read_args(argc, argv);
  CPU cpu = {0};
  FILE *f = fopen(conf->bin_path, "r");

  if (f == NULL) {
    printf("Failed to read the file.\n");
    return 1;
  }
  uint8_t buf[conf->mem_size];
  size_t n = fread(buf, 1, sizeof(buf), f);

  cpu.memory = buf;
  cpu.eip = 0;

  for (size_t i = 0; i < n; i++) {
    Instruction ins = decode(&cpu);
    if (ins.exec == NULL) {
      printf("Unknown opcode: 0x%02X at EIP=0x%08X\n", ins.opcode[0],
             cpu.eip - 1);
      return 1;
    }
    ins.exec(&cpu, &ins);
  }

  return 0;
}
