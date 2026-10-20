#include <execute/dispatch.h>

void exec_nop(CPU *cpu, Instruction *ins) {
  // NOP does nothing
  (void)cpu;
  (void)ins;
}
