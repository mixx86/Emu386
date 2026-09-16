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

const int buf_size = 128;

int main(int argc, char *argv[]) {
  enum { CHARACTER_MODE, WORD_MODE, LINE_MODE } mode = CHARACTER_MODE;

  int opt;
  while ((opt = getopt(argc, argv, "ilw")) != -1) {
    switch (opt) {
    case 'i':
      printf("-i option!!!!");
      break;
    case 'l':
      mode = LINE_MODE;
      break;
    case 'w':
      mode = WORD_MODE;
      break;
    default:
      fprintf(stderr, "Usage: %s [-ilw] [file...]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  if (optind >= argc) {
    fprintf(stderr, "Usage: %s [-ilw] <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *filename = argv[optind];

  char *pwd = getcwd(NULL, 0);

  int path_size = snprintf(NULL, 0, "%s/%s", pwd, filename) + 1;

  char path[path_size];

  snprintf(path, path_size, "%s/%s", pwd, filename);

  if (access(path, F_OK) != 0) {
    fprintf(stderr, "Usage: %s [file...]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  CPU cpu = {0};
  FILE *f = fopen(path, "r");

  if (f == NULL) {
    printf("Failed to read the file.\n");
    return 1;
  }
  char buf[buf_size];
  size_t n = fread(buf, 1, sizeof(buf), f);

  cpu.memory = buf;
  cpu.eip = 0;

  for (int i = 0; i < n; i++) {
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
