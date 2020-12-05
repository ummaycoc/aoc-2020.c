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

static int icmp(int a, int b) {
  return a < b ? -1 : a > b ? 1 : 0;
}

static int cmp(const void *a, const void *b) {
  return icmp(*((int *)a), *((int *)b));
}

int main(int argc, char **argv) {
  int *ids = malloc(sizeof(int) * numPasses);
  if (ids == NULL) {
    printf("Memory!");
    exit(0);
  }
  for (int i = 0; i < numPasses; ++i)
    ids[i] = seatId(passes[i]);
  qsort(ids, numPasses, sizeof(int), cmp);
  for (int i = 1; i < numPasses; ++i)
    if (ids[i] - ids[i-1] == 2) {
      printf("%d - %d => %d\n", ids[i-1], ids[i], ids[i] - 1);
      break;
    }
  free(ids);
  return 0;
}
