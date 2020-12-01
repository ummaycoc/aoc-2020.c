#include <stdio.h>
#include <stdlib.h>

static int data[] = {
#include "input.h"
};
static const int SIZE=sizeof(data)/sizeof(int);

static void swap(int *a, int *c) {
  int b = *a;
  *a = *c;
  *c = b;
}

static int icmp(int a, int b) {
  return a < b ? -1 : a > b ? 1 : 0;
}

static int cmp(const void *second, const void *item) {
  return icmp(2020 - *data - *((int *)second), *((int *)item));
}

static int checkForSum(int *second) {
  for (int i = 1; i < SIZE; ++i)
    if (bsearch(data + i, data + 1, SIZE-1, sizeof(int), cmp)) {
      *second = data[i];
      return 1;
    }
  return 0;
}

int main(int argc, char **argv) {
  int second = 0;
  for (int idx = 1; idx < SIZE; ++idx) {
    if (checkForSum(&second))
      break;
    swap(data, data + idx);
  }
  int first = *data;
  int third = 2020 - first - second;
  printf("%d * %d * %d = %d\n", first, second, third, first * second * third);
  return 0;
}
