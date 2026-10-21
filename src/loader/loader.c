#include <loader/loader.h>
#include <memory/memory.h>
#include <loader/binary.h>

#include <string.h>
#include <errno.h>
#include <stdio.h>

bool loader_load_binary(const char *path, Memory *mem, size_t *bytes_loaded, Binary *bin) {
    if (path == NULL || mem == NULL ||
        mem->data == NULL || mem->size == 0) {
        fprintf(stderr, "loader: invalid arguments\n");
        return false;
    }

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "loader: cannot open '%s': %s\n",
            path, strerror(errno));
        return false;
    }

    size_t n = fread(mem->data, 1, mem->size, file);

    if (ferror(file)) {
        fprintf(stderr, "loader: read error on '%s'\n", path);
        fclose(file);
        return false;
    }

    if (n == mem->size) {
        int c = fgetc(file);

        if (c != EOF || ferror(file)) {
            fprintf(stderr, "loader: binary exceeds memory size\n");
            fclose(file);
            return false;
        }
    }

    if (fclose(file) != 0) {
        fprintf(stderr, "loader: error closing '%s'\n", path);
        return false;
    }

    if (bytes_loaded != NULL) {
        *bytes_loaded = n;
        bin->size = n;
    }

    bin->data = mem->data;

    return true;
}
