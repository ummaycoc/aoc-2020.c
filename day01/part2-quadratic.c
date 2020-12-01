// Inspired by a comment from a coworker about her husband's solution.
#include <stdio.h>

static int data[] = {
#include "input.h"
};
static const int SIZE=sizeof(data)/sizeof(int);

static int checkFirst(int first, int *second, int *third) {
  *second = first + 1;
  *third = SIZE-1;
  while (*second < *third) {
    int sum = data[first] + data[*second] + data[*third];
    if (sum == 2020)
      return 1;
    if (sum < 2020)
      ++*second;
    else
      --*third;
  }
  return 0;
}

int main(int argc, char **argv) {
  int first = 0;
  int second = 0;
  int third = 0;
  for (; first < SIZE-2; ++first)
    if (checkFirst(first, &second, &third))
      break;
  printf(
    "%d * %d * %d = %d\n",
    data[first], data[second], data[third],
    data[first] * data[second] * data[third]
  );
}
