#include <memory/fetch.h>

uint8_t fetch8(CPU *cpu) { return cpu->memory[cpu->eip++]; }
