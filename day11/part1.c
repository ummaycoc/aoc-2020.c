#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **keep = NULL;
static char **update = NULL;

static char *data[] = {
#include "input.h"
};
static const int numRows = sizeof(data)/sizeof(char*);
static int numCols = 0;

static int min(int a, int b) {
  return a < b ? a : b;
}

static int max(int a, int b) {
  return a > b ? a : b;
}

static int countOcc(int row, int col) {
  int occ = 0;
  for (int r = max(0, row-1); r < min(numRows, row+2); ++r)
    for (int c = max(0, col-1); c < min(numCols, col+2); ++c)
      occ += (r != row || c != col) && keep[r][c] == '#';
  return occ;
}

static int iterate() {
  int count = 0;
  for (int r = 0; r < numRows; ++r)
    for (int c = 0; c < numCols; ++c)
      if (keep[r][c] == 'L' && countOcc(r, c) == 0) {
        update[r][c] = '#';
        ++count;
      } else if (keep[r][c] == '#' && countOcc(r, c) >= 4) {
        update[r][c] = 'L';
        ++count;
      }
  return count;
}

static void copy(char **dst, char **src) {
  for (int r = 0; r < numRows; ++r)
    memcpy(dst[r], src[r], numCols);
}

char **allocData() {
  int rlen = numCols + 1;
  int total = numRows * (sizeof(char *) + rlen);
  char **res = malloc(total);
  if (!res) {
    printf("Error!\n");
    exit(1);
  }
  memset(res, 0, total);
  char *mem = (char *)(res + numRows);
  for (int i = 0; i < numRows; res[i] = mem, ++i, mem += rlen)
    ;
  copy(res, data);
  return res;
}

int main(int argc, char **argv) {
  numCols = strlen(data[0]);
  keep = allocData();
  update = allocData();
  while (1)
    if (!iterate())
      break;
    else
      copy(keep, update);
  int count = 0;
  for (int row = 0; row < numRows; ++row)
    for (int col = 0; col < numCols; ++col)
      count += keep[row][col] == '#';
  free(keep);
  free(update);
  printf("%d\n", count);
  return 0;
}
