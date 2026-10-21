#include <cpu/cpu.h>
#include <assert.h>
#include <stddef.h>

void cpu_init(CPU *cpu) {
    assert(cpu != NULL);

    *cpu = (CPU) {
        .eflags = 0x2
    };
}
