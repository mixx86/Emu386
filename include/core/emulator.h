#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdbool.h>
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "config/config.h"
#include "common/error.h"
#include "loader/binary.h"

typedef struct Emulator {
    CPU cpu;
    Memory memory;
    bool halted;
    EmuError error;
    Binary current_binary;
} Emulator;

typedef enum {
    EMU_RUN_STOPPED,
    EMU_RUN_WAITING,
    EMU_RUN_ERROR
} EmuRunResult;

bool emu_setup(Emulator *emu, const EmuConfig *conf);
int emu_run(Emulator *emu);

#endif
