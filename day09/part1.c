#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long int data[] = {
#include "input.h"
};
static const int dataSize = sizeof(data)/sizeof(long);

static int lcmp(long int a, long int b) {
  return a < b ? -1 : a > b ? 1 : 0;
}

static int cmp(const void *a, const void *b) {
  return lcmp(*((long int *)a), *((long int *)b));
}

static int isValid(int index) {
  long target = data[index];
  long run[25] = { 0 };
  memcpy(run, (data + index) - 25, sizeof(long int) * 25);
  qsort(run, 25, sizeof(long int), cmp);
  int low = 0;
  int high = 24;
  while (low < high) {
    long int sum = run[low] + run[high];
    if (sum < target)
      ++low;
    else if (sum == target)
      return 1;
    else
      --high;
  }
  return 0;
}

int main(int argc, char **argv) {
  int i = 0;
  for (i = 25; i < dataSize && isValid(i); ++i)
    ;
  printf("%ld\n", data[i]);
  return 0;
}
