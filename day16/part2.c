#include <stdio.h>
#include <stdlib.h>

#include "nearby-count.h"
#include "ticket-fields.h"

static int ranges[] = {
#include "ranges.h"
};
static const int points = sizeof(ranges) / sizeof(int);

static int nearby[NEARBY_COUNT][TICKET_FIELDS] = {
#include "nearby.h"
};

static int invalid[TICKET_FIELDS][TICKET_FIELDS] = { 0 };

static int myTicket[] = {
#include "my-ticket.h"
};

static int ordered(int a, int b, int c) {
  return a <= b && b <= c;
}

static int isValidField(int value) {
  for (int i = 0; i < points; i += 2)
    if (ordered(ranges[i], value, ranges[i+1]))
      return 1;
  return 0;
}

static int isValidTicket(int ticket) {
  for (int i = 0; i < TICKET_FIELDS; ++i)
    if (!isValidField(nearby[ticket][i]))
      return 0;
  return 1;
}

static int inFieldRange(int value, int range) {
  int *r = ranges + (4*range);
  return ordered(r[0], value, r[1]) || ordered(r[2], value, r[3]);
}

struct state {
  int count;
  int set;
  int consumed;
  int solution;
};

// Mutually recursive.
static void rsolve(struct state *s, int rem, void (*process)(struct state *));
static void assign(struct state *s, int dst, int src, int rem, void (*process)(struct state *));

void assign(struct state *s, int dst, int src, int rem, void (*process)(struct state *)) {
  s[src].consumed = 1;
  s[dst].set = 1;
  s[dst].solution = src;
  for (int field = 0; field < TICKET_FIELDS; ++field)
    s[field].count -= !invalid[field][src];
  rsolve(s, rem - 1, process);
  for (int field = 0; field < TICKET_FIELDS; ++field)
    s[field].count += !invalid[field][src];
  s[dst].solution = 0;
  s[dst].set = 0;
  s[src].consumed = 0;
}

void rsolve(struct state *s, int rem, void (*process)(struct state *)) {
  int min = -1;
  if (!rem) {
    process(s);
    return;
  }
  for (int i = 0; i < TICKET_FIELDS; ++i)
    if (!s[i].set && (min == -1 || s[i].count < s[min].count))
      min = i;
  for (int range = 0; range < TICKET_FIELDS; ++range)
    if (!invalid[min][range] && !s[range].consumed)
      assign(s, min, range, rem, process);
}

static void solve(int *counts, void (*process)(struct state *)) {
  struct state s[TICKET_FIELDS] = { 0 };
  for (int i = 0; i < TICKET_FIELDS; ++i)
    s[i].count = counts[i];
  rsolve(s, TICKET_FIELDS, process);
}

static void processor(struct state *s) {
  long prod = 1;
  for (int i = 0; i < TICKET_FIELDS; ++i)
    if (s[i].solution < 6)
      prod *= (long) myTicket[i];
  printf("%ld\n", prod);
}

int main(int argc, char **argv) {
  int counts[TICKET_FIELDS] = { 0 };
  int indices[TICKET_FIELDS] = { -1 };
  for (int ticket = 0; ticket < NEARBY_COUNT; ++ticket)
    if (isValidTicket(ticket))
      for (int field = 0; field < TICKET_FIELDS; ++field)
        for (int range = 0; range < TICKET_FIELDS; ++range)
          invalid[field][range] |= !inFieldRange(nearby[ticket][field], range);
  for (int field = 0; field < TICKET_FIELDS; ++field)
    for (int range = 0; range < TICKET_FIELDS; ++range)
      counts[field] += !invalid[field][range];
  for (int field = 0; field < TICKET_FIELDS; ++field)
    if (!counts[field]) {
      printf("Unsolvable, nothing available for %d\n", field);
      exit(1);
    }
  solve(counts, processor);
  return 0;
}
