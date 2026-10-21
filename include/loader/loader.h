#ifndef LOADER_H
#define LOADER_H
#include <stdbool.h>
#include <memory.h>
#include <stdio.h>
#include "loader/binary.h"

bool loader_load_binary(const char *path, Memory *mem, size_t *bytes_loaded, Binary *bin);

#endif /* LOADER_H */
