#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long int data[] = {
#include "input.h"
};
static const int dataSize = sizeof(data)/sizeof(long);

static const long int target = 144381670;

int main(int argc, char **argv) {
  long int current = data[0];
  int low = 0;
  int high = 0;
  while (current != target) {
    if (current < target)
      current += data[++high];
    else if (current > target)
      current -= data[low++];
    if (low > high)
      current -= data[high++];
  }
  long int min = data[low];
  long int max = data[low];
  for (int i = low; i < high; ++i) {
    min = data[i] < min ? data[i] : min;
    max = data[i] > max ? data[i] : max;
  }
  printf("%ld\n", min + max);
  return 0;
}
