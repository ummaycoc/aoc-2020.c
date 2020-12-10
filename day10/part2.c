#include <stdio.h>
#include <stdlib.h>

static int adapters[] = {
#include "input.h"
};
static int numAdapters = sizeof(adapters)/sizeof(int);
#include "max.h"
static long int mem[sizeof(adapters)/sizeof(int)][MaxAdapter] = { 0 };

static long int combos(int jolts, int i) {
  long int calculated = mem[i][jolts];
  int diff = adapters[i] - jolts;
  return mem[i][jolts] = calculated
    ? calculated
    : (i == numAdapters - 1)
      ? 1
      : diff <= 3
        ? combos(jolts, i+1) + combos(jolts + diff, i+1)
        : 0;
}

int main(int argc, char **argv) {
  printf("%lu\n", combos(0, 0));
  return 0;
}
