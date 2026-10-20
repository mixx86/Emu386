#include <decode/decode.h>

#include <execute/dispatch.h>
#include <memory/fetch.h>

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
