#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

typedef struct EmuConfig {
  char *bin_path;
  int bin_size;
  size_t mem_size;
} EmuConfig;

#endif /* CONFIG_H */
