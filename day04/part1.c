#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char *lines[] = {
#include "input.h"
};

const int byr = 1 << 7;
const int iyr = 1 << 6;
const int eyr = 1 << 5;
const int hgt = 1 << 4;
const int hcl = 1 << 3;
const int ecl = 1 << 2;
const int pid = 1 << 1;
const int cid = 1 << 0;

static int isPrefix(const char *line, const char *prefix) {
  return !memcmp(line, prefix, strlen(prefix));
}

#define check(field) (isPrefix(line, #field ":") * field)

static int getMask(const char *line) {
  return (
    check(byr) |
    check(iyr) |
    check(eyr) |
    check(hgt) |
    check(hcl) |
    check(ecl) |
    check(pid) |
    check(cid)
  );
}

int main(int argc, char **argv) {
  int numLines = sizeof(lines) / sizeof(char *);
  int lineNo = 0;
  int count = 0;
  while (lineNo < numLines) {
    for (; lineNo < numLines && !strlen(lines[lineNo]); ++lineNo)
      ;
    int mask = 0;
    for (; lineNo < numLines && strlen(lines[lineNo]); ++lineNo)
      mask |= getMask(lines[lineNo]);
    count += mask >= (byr | iyr | eyr | hgt | hcl | ecl | pid);
  }
  printf("%d\n", count);
  return 0;
}
