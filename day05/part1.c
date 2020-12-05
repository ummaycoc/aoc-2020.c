#include <stdio.h>
#include <stdlib.h>

static const char *passes[] = {
#include "input.h"
};
static const int numPasses = sizeof(passes)/sizeof(char *);

static int calcNum(const char *s, int n, char h) {
  int start = 0;
  for (int r = 1 << n; n >= 0; --n, ++s)
    start += (*s == h) * (r >>= 1);
  return start;
}

static int seatId(const char *pass) {
  return calcNum(pass, 7, 'B') * 8 + calcNum(pass + 7, 3, 'R');
}

static int max(int a, int b) {
  return a > b ? a : b;
}

int main(int argc, char **argv) {
  int maxId = 0;
  for (int i = 0; i < numPasses; ++i)
    maxId = max(maxId, seatId(passes[i]));
  printf("%d\n", maxId);
}
