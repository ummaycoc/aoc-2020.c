#include <stdio.h>
#include <stdlib.h>

static unsigned long m0 = 0;
static unsigned long m1 = 0;
static unsigned long mX = 0;

static const unsigned long HI = 41;
static const unsigned long LO = 43;

struct addr {
  unsigned long address;
  unsigned long value;
};

struct lo_bucket {
  struct addr *data;
  int cap;
  int n;
};

struct hi_bucket {
  struct lo_bucket subs[LO];
};

struct map {
  struct hi_bucket buckets[HI];
};

static struct map memory = { 0 };
static void assignToMem(unsigned long address, unsigned long value) {
  int idx = 0;
  struct lo_bucket *b = &memory.buckets[address % HI].subs[address % LO];
  for (; idx < b->n && b->data[idx].address != address; ++idx)
    ;
  if (idx == b->n) {
    if (b->n == b->cap) {
      b->cap = (b->n + 1) * 2;
      b->cap = b->cap < 64 ? 64 : b->cap;
      b->data = realloc(b->data, b->cap * sizeof(struct addr));
      if (!b->data) {
        printf("ERROR! Memory!\n");
        exit(1);
      }
    }
    idx = b->n++;
  }
  b->data[idx].address = address;
  b->data[idx].value = value;
}

static void assignRec(unsigned long address, unsigned long value, char bit) {
  unsigned long mask = 1L << bit;
  if (bit == 36) {
    assignToMem(address, value);
  } else if (mask & mX) {
    assignRec(address | mask, value, bit + 1);
    assignRec(address & ~mask, value, bit + 1);
  } else {
    assignRec(address, value, bit + 1);
  }
}

static void assign(unsigned long address, unsigned long value) {
  assignRec((address & ~m0) | m1, value, 0);
}

int main(int argc, char **argv) {
#include "commands2.h"
  unsigned long sum = 0;
  for (int hi = 0; hi < HI; ++hi)
    for (int lo = 0; lo < LO; ++lo) {
      for (int a = 0; a < memory.buckets[hi].subs[lo].n; ++a)
        sum += memory.buckets[hi].subs[lo].data[a].value;
      free(memory.buckets[hi].subs[lo].data);
    }
  printf("%lu\n", sum);
}
