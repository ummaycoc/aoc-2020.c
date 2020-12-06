#include <stdio.h>
#include <stdlib.h>

static const char *passes[] = {
#include "input.h"
};
static const int numPasses = sizeof(passes)/sizeof(char *);

static int seatId(const char *pass) {
  int result = 0;
  for (; *pass; ++pass)
    result = (result << 1) + (*pass == 'B' || *pass == 'R');
  return result;
}

int main(int argc, char **argv) {
  int min = 0;
  int max = 0;
  int sum = 0;
  for (int i = 0; i < numPasses; ++i) {
    int id = seatId(passes[i]);
    if (!i || id < min)
      min = id;
    if (!i || id > max)
      max = id;
    sum += id;
  }
  printf("%d\n", (max*(max+1))/2 - (min*(min-1))/2 - sum);
}
