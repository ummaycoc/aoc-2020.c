#include <stdio.h>
#include <stdlib.h>

static int data[] = {
#include "input.h"
};
static const int SIZE=sizeof(data)/sizeof(int);

static int icmp(int a, int b) {
  return a < b ? -1 : a > b ? 1 : 0;
}

static int cmp(const void *key, const void *item) {
  return icmp(2020 - *((int *)key), *((int *)item));
}

int main(int argc, char **argv) {
  int *head = data;
  for (; !bsearch(head, data, SIZE, sizeof(int), cmp); ++head)
    ;
  printf("%d * %d = %d\n", *head, 2020-*head, *head * (2020-*head));
  return 0;
}
