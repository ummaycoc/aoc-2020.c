#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BEGIN init();
#define LOAD(n) pushNumber((long)(n));
#define MUL pushMul();
#define ADD pushAdd();
#define START startSub();
#define END endSub();
#define COMPUTE compute();

struct expr;
struct expr {
  long value;
  int add;
  int mul;
  struct expr *below;
};

static struct expr *calc = NULL;

static struct expr *allocate() {
  struct expr *ptr = malloc(sizeof(struct expr));
  if (!ptr) {
    printf("Allocation error!\n");
    exit(1);
  }
  memset(ptr, 0, sizeof(struct expr));
  return ptr;
}

static void deallocate() {
  struct expr *next = calc->below;
  free(calc);
  calc = next;
}

static void init() {
  calc = allocate();
}

static void pushNumber(long val) {
  if (calc->add) {
    calc->value += val;
    calc->add = 0;
  } else if (calc->mul) {
    calc->value *= val;
    calc->mul = 0;
  } else {
    calc->value = val;
  }
}

static void pushMul() {
  calc->mul = 1;
}

static void pushAdd() {
  calc->add = 1;
}

static void startSub() {
  struct expr *next = allocate();
  next->below = calc;
  calc = next;
}

static void endSub() {
  long value = calc->value;
  deallocate();
  pushNumber(value);
}

static long sum = 0;

static void compute() {
  sum += calc->value;
  deallocate();
}

#include "read.hh"

int main(int argc, char **argv) {
#include "commands.h"
  printf("%ld\n", sum);
  return 0;
}
