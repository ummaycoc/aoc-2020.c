#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *map[] = {
#include "input.h"
};

static unsigned long countTrees(int dx, int dy) {
  int h = sizeof(map) / sizeof(char *);
  int w = strlen(map[0]);
  unsigned long trees = 0;
  for (int x = 0, y = 0; y < h; y += dy, x = (x + dx) % w)
    trees += map[y][x] == '#';
  return trees;
}

int main(int argc, char **argv) {
  const unsigned long s11 = countTrees(1, 1);
  const unsigned long s31 = countTrees(3, 1);
  const unsigned long s51 = countTrees(5, 1);
  const unsigned long s71 = countTrees(7, 1);
  const unsigned long s12 = countTrees(1, 2);
  printf(
    "%lu * %lu * %lu * %lu * %lu = %lu\n",
    s11, s31, s51, s71, s12,
    s11 * s31 * s51 * s71 * s12
  );
  return 0;
}
