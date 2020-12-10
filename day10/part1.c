#include <stdio.h>
#include <stdlib.h>

static int adapters[] = {
#include "input.h"
};
static int numAdapters = sizeof(adapters)/sizeof(int);

int main(int argc, char **argv) {
  int counts[3] = { 0 };
  for (int i = 1; i < numAdapters; ++i)
    ++counts[adapters[i]-adapters[i-1]-1];
  printf("%d\n", (counts[0] + 1) * (counts[2] + 1));
  return 0;
}
