#include <common/error.h>
#include <core/emulator.h>
#include <config/config.h>
#include <decode/decode.h>
#include <memory/memory.h>
#include <loader/loader.h>
#include <stdbool.h>
#include <stdio.h>

int emu_run(Emulator *emu)
{
    if (emu == NULL) {
        return EMU_ERROR_INVALID_ARGUMENT;
    }

    while (!emu->halted) {
        Instruction ins = decode(&emu->cpu, &emu->memory);

        if (ins.exec == NULL) {
            fprintf(stderr,
                    "error: %s at eip: 0x%08X\n",
                    emu_error_string(EMU_ERROR_INVALID_INSTRUCTION),
                    emu->cpu.eip);
            return EMU_ERROR_INVALID_INSTRUCTION;
        }

        ins.exec(&emu->cpu, &ins);

        if (emu->cpu.eip >= emu->current_binary.size) {
            emu->halted = true;
        }
    }

    return EMU_RUN_STOPPED;
}

bool emu_setup(
    Emulator *emu,
    const EmuConfig *conf
) {
    if (emu == NULL || conf == NULL) {
        return false;
    } 

    *emu = (Emulator){0};
    emu->error = EMU_ERROR_NONE;

    if (!memory_init(&emu->memory, conf->mem_size)) {
        emu->error = EMU_ERROR_MEMORY_INIT;
        return false;
    }

    size_t bytes_loaded = 0;

    if (!loader_load_binary(
            conf->bin_path,
            &emu->memory,
            &bytes_loaded,
            &emu->current_binary)) {
        memory_destroy(&emu->memory);

        emu->error = EMU_ERROR_BINARY_LOAD;
        return false;
    }

    cpu_init(&emu->cpu);
    emu->cpu.eip = 0;
    emu->halted = false;

    return true;
}
