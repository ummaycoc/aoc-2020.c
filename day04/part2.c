#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

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

static int isSuffix(const char *line, const char *suffix) {
  int n = strlen(line);
  int m = strlen(suffix);
  return n > m && !memcmp(line + (n - m), suffix, m);
}

static int isDigits(const char *line) {
  if (!*line)
    return 0;
  for (; *line && isdigit(*line); ++line)
    ;
  return !*line;
}

static int isHex(const char *line) {
  if (*line != '#')
    return 0;
  ++line;
  for (; *line && isxdigit(*line); ++line)
    ;
  return !*line;
}

static int scanDigits(const char *line, unsigned int *out) {
  return (
    isDigits(line) &&
    sscanf(line, "%u", out) == 1
  );
}

static int scanUnits(const char *line, const char *unit, unsigned int *out) {
  int read = 0;
  return (
    *line &&
    sscanf(line, "%u%n", out, &read) == 1 &&
    !strcmp(line + read, unit)
  );
}

static int between(unsigned int num, unsigned int lo, unsigned int hi) {
  return lo <= num && num <= hi;
}

static int isStr(const char *item, ...) {
  va_list argp;
  va_start(argp, item);
  char *elem = NULL;
  do {
    elem = va_arg(argp, char *);
  } while (elem != NULL && strcmp(item, elem));
  va_end(argp);
  return elem != NULL;
}

#define check(field, test) \
if (isPrefix(line, #field ":")) \
  return ( test ) * ( field )

#define checkSuffix(field, suffix, test) \
if (isPrefix(line, #field ":") && isSuffix(line, #suffix)) \
  return ( test ) * ( field )

static int getMask(const char *line) {
  unsigned int uint = 0;
  check(byr, scanDigits(line + 4, &uint) && between(uint, 1920, 2002));
  check(iyr, scanDigits(line + 4, &uint) && between(uint, 2010, 2020));
  check(eyr, scanDigits(line + 4, &uint) && between(uint, 2020, 2030));
  checkSuffix(hgt, cm, scanUnits(line + 4, "cm", &uint) && between(uint, 150, 193));
  checkSuffix(hgt, in, scanUnits(line + 4, "in", &uint) && between(uint, 59, 76));
  check(hcl, isHex(line + 4) && strlen(line + 4) == 7);
  check(ecl, isStr(line + 4, "amb", "blu", "brn", "gry", "grn", "hzl", "oth", NULL));
  check(pid, isDigits(line + 4) && strlen(line + 4) == 9);
  check(cid, 1);
  return 0;
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
