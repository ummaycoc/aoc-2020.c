#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *map[] = {
#include "input.h"
};

int main(int argc, char **argv) {
  int h = sizeof(map) / sizeof(char *);
  int w = strlen(map[0]);
  int trees = 0;
  for (int x = 0, y = 0; y < h; ++y, x = (x + 3) % w)
    trees += map[y][x] == '#';
  printf("%d\n", trees);
  return 0;
}
