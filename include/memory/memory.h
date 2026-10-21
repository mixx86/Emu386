#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t *data;
    size_t size;
} Memory;

bool memory_init(Memory *mem, size_t size);
bool memory_destroy(Memory *mem);

#endif /* MEMORY_H */
