#include <core/main.h>

#include <config/args.h>
#include <config/config.h>
#include <cpu/cpu.h>
#include <decode/decode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
