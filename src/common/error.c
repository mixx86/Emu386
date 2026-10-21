#include <common/error.h>

const char *emu_error_string(EmuError error)
{
    switch (error) {
    case EMU_ERROR_NONE:
        return "no error";

    case EMU_ERROR_INVALID_ARGUMENT:
        return "invalid argument";

    case EMU_ERROR_MEMORY_INIT:
        return "failed to initialize memory";

    case EMU_ERROR_BINARY_LOAD:
        return "failed to load binary";

    case EMU_ERROR_FILE_OPEN:
        return "failed to open file";

    case EMU_ERROR_OUT_OF_MEMORY:
        return "out of memory";

    case EMU_ERROR_INVALID_INSTRUCTION:
        return "invalid instruction";

    case EMU_ERROR_UNKNOWN:
    default:
        return "unknown error";
    }
}
