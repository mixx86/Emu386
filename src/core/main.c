#include <core/main.h>

#include <config/args.h>
#include <config/config.h>
#include <core/emulator.h>
#include <common/error.h>

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  struct EmuConfig *conf = read_args(argc, argv);

  Emulator emu = {0};
  bool ok = emu_setup(&emu, conf);
  if (!ok) {
      fprintf(stderr, "error: %s\n", emu_error_string(emu.error));
      return 1;
  }

  return emu_run(&emu);
}
