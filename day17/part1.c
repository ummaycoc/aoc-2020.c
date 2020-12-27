#include <stdio.h>
#include <string.h>

#include "rows.h"
#include "cols.h"

static int initial[INIT_ROWS][INIT_COLS] = {
#include "state.h"
};

#define Z (1 + 12)
#define Y (INIT_ROWS + 12)
#define X (INIT_COLS + 12)

static int state[Z][Y][X];
static int update[Z][Y][X];

static int isValid(int z, int y, int x) {
  return z >= 0 && y >= 0 && x >= 0 && z < Z && y < Y && x < X;
}

static int check(int z, int y, int x) {
  int count = 0;
  for (int cz = z-1; cz <= z+1; ++cz)
    for (int cy = y-1; cy <= y+1; ++cy)
      for (int cx = x-1; cx <= x+1; ++cx)
        count += isValid(cz, cy, cx) && (cz != z || cy != y || cx != x) && state[cz][cy][cx];
  return count;
}

static void cycle() {
  memcpy(state, update, sizeof(update));
  for (int z = 0; z < Z; ++z)
    for (int y = 0; y < Y; ++y)
      for (int x = 0; x < X; ++x) {
        int active = check(z, y, x);
        update[z][y][x] = active == 3 || (state[z][y][x] && active == 2);
      }
}

int main(int argc, char **argv) {
  int sum = 0;
  for (int r = 0; r < INIT_ROWS; ++r)
    for (int c = 0; c < INIT_COLS; ++c)
      update[6][r+6][c+6] = initial[r][c];
  for (int c = 0; c < 6; ++c)
    cycle();
  memcpy(state, update, sizeof(update));
  for (int z = 0; z < Z; ++z)
    for (int y = 0; y < Y; ++y)
      for (int x = 0; x < X; ++x)
        sum += state[z][y][x];
  printf("%d\n", sum);
  return 0;
}
