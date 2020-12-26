#include <stdio.h>

#include "nearby-count.h"
#include "ticket-fields.h"

static int ranges[] = {
#include "ranges.h"
};
static const int points = sizeof(ranges) / sizeof(int);

static int nearby[NEARBY_COUNT][TICKET_FIELDS] = {
#include "nearby.h"
};

int check(int value) {
  for (int i = 0; i < points; i += 2)
    if (ranges[i] <= value && value <= ranges[i+1])
      return 0;
  return value;
}

int main(int argc, char **argv) {
  long sum = 0;
  for (int ticket = 0; ticket < NEARBY_COUNT; ++ticket)
    for (int field = 0; field < TICKET_FIELDS; ++field)
      sum += check(nearby[ticket][field]);
  printf("%ld\n", sum);
  return 0;
}
