#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

enum nav { N, E, S, W, L, R, F };
static int data[] = {
#include "input.h"
};
static const int dataLen = sizeof(data) / sizeof(int);

static double complex waypoint = 10 + I;
static double complex ship = 0;
static double complex rots[4] = {1, -I, -1, I};

static void steer(enum nav command, int amt) {
  switch (command) {
  case N:
    waypoint += amt * I;
    break;
  case S:
    waypoint -= amt * I;
    break;
  case E:
    waypoint += amt;
    break;
  case W:
    waypoint -= amt;
    break;
  case L:
    amt = 360 - amt;
  case R:
    waypoint *= rots[amt / 90];
    break;
  case F:
    ship += waypoint * amt;
    break;
  default:
    printf("Invalid direction for steering!\n");
    exit(1);
  }
}

int main(int argc, char **argv) {
  for (int i = 0; i < dataLen; i += 2)
    steer(data[i], data[i+1]);
  long x = (long) creal(ship);
  long y = (long) cimag(ship);
  printf("(%ld, %ld) = %ld\n", x, y, labs(x) + labs(y));
  return 0;
}
