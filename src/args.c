#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *read_args(int argc, char *argv[]) {
  enum { CHARACTER_MODE, WORD_MODE, LINE_MODE } mode = CHARACTER_MODE;

  int opt;
  while ((opt = getopt(argc, argv, "ilw")) != -1) {
    switch (opt) {
    case 'i':
      printf("-i option!!!!");
      break;
    case 'l':
      mode = LINE_MODE;
      break;
    case 'w':
      mode = WORD_MODE;
      break;
    default:
      fprintf(stderr, "Usage: %s [-ilw] [file...]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  if (optind >= argc) {
    fprintf(stderr, "Usage: %s [-ilw] <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *filename = argv[optind];

  char *pwd = getcwd(NULL, 0);

  int path_size = snprintf(NULL, 0, "%s/%s", pwd, filename) + 1;

  char *path = malloc(path_size);

  snprintf(path, path_size, "%s/%s", pwd, filename);

  if (access(path, F_OK) != 0) {
    fprintf(stderr, "Usage: %s [file...]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  free(pwd);

  return path;
}
