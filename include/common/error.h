#ifndef EMU_ERROR_H
#define EMU_ERROR_H

typedef enum {
    EMU_ERROR_NONE = 0,
    EMU_ERROR_INVALID_ARGUMENT,
    EMU_ERROR_MEMORY_INIT,
    EMU_ERROR_BINARY_LOAD,
    EMU_ERROR_FILE_OPEN,
    EMU_ERROR_OUT_OF_MEMORY,
    EMU_ERROR_INVALID_INSTRUCTION,
    EMU_ERROR_UNKNOWN
} EmuError;

const char *emu_error_string(EmuError error);

#endif
