#include <memory/fetch.h>
#include <memory/memory.h>

uint8_t fetch8(CPU *cpu, Memory *mem) { return mem->data[cpu->eip++]; }
