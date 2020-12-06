#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *data[] = {
#include "input.h"
};
static const int numLines = sizeof(data)/sizeof(char *);

static void parseLine(int *stats, const char *line) {
  for (; *line; ++line)
    ++stats[*line - 'a'];
}

static int parseGroup(int *stats, int group) {
  int count = 0;
  for (int i = 0; i < 26; ++i)
    count += stats[i] == group;
  return count;
}

int main(int argc, char **argv) {
  int stats[26] = { 0 };
  int lineNo = 0;
  int count = 0;
  while (lineNo < numLines) {
    for (; lineNo < numLines && !strlen(data[lineNo]); ++lineNo)
      ;
    memset(stats, 0, sizeof(int) * 26);
    int group = 0;
    for (; lineNo < numLines && strlen(data[lineNo]); ++lineNo) {
      parseLine(stats, data[lineNo]);
      ++group;
    }
    if (group)
      count += parseGroup(stats, group);
  }
  printf("%d\n", count);
  return 0;
}
