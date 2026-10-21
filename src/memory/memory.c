#include <memory/memory.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>

bool memory_init(Memory *mem, size_t size) {
    if (mem == NULL || size == 0) {
        return false;
    }

    mem->data = calloc(size, sizeof(*mem->data));
    if (mem->data == NULL) {
        mem->size = 0;
        return false;
    }

    mem->size = size;
    return true;
}

bool memory_destroy(Memory *mem) {
    if (mem == NULL) return false;

    free(mem->data);
    mem->size = 0;

    return true;
}
