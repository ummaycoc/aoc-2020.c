#include <stdio.h>
#include <stdlib.h>

enum nav { N, E, S, W, L, R, F };
static int data[] = {
#include "input.h"
};
static const int dataLen = sizeof(data) / sizeof(int);

static enum nav direction = E;
static long x = 0;
static long y = 0;

static void move(enum nav dir, int amt) {
  switch (dir) {
  case N:
    y += amt;
    break;
  case S:
    y -= amt;
    break;
  case E:
    x += amt;
    break;
  case W:
    x -= amt;
    break;
  default:
    printf("Invalid direction for move!\n");
    exit(1);
  }
}

static void steer(enum nav command, int amt) {
  switch (command) {
  case N:
  case S:
  case E:
  case W:
    move(command, amt);
    break;
  case L:
    amt = 360 - amt;
  case R:
    direction += amt / 90;
    direction %= 4;
    break;
  case F:
    move(direction, amt);
    break;
  default:
    printf("Invalid direction for steering!\n");
    exit(1);
  }
}

int main(int argc, char **argv) {
  for (int i = 0; i < dataLen; i += 2)
    steer(data[i], data[i+1]);
  printf("(%ld, %ld) = %ld\n", x, y, labs(x) + labs(y));
  return 0;
}
