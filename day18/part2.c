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
  long *factors;
  int add;
  int cap;
  int n;
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
  free(calc->factors);
  free(calc);
  calc = next;
}

static void allocateFactors() {
  if (calc->n < calc->cap)
    return;
  calc->cap = calc->n ? calc->n * 2 : 32;
  calc->factors = realloc(calc->factors, sizeof(long) * calc->cap);
  if (!calc->factors) {
    printf("Factor allocation error!\n");
    exit(1);
  }
}

static long mulFactors() {
  long qty = 1;
  for (int i = 0; i < calc->n; ++i)
    qty *= calc->factors[i];
  return qty;
}

static void pushFactor(long val) {
  allocateFactors();
  calc->factors[calc->n++] = val;
}

static void init() {
  calc = allocate();
}

static void pushNumber(long val) {
  if (calc->add) {
    calc->factors[calc->n - 1] += val;
    calc->add = 0;
  } else {
    pushFactor(val);
  }
}

static void pushMul() {
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
  long qty = mulFactors();
  deallocate();
  pushNumber(qty);
}

static long sum = 0;

static void compute() {
  sum += mulFactors();
  deallocate();
}

#include "read.hh"

int main(int argc, char **argv) {
#include "commands.h"
  printf("%ld\n", sum);
  return 0;
}
