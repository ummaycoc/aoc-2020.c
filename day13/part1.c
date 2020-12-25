#include <stdio.h>

static const int timestamp =
#include "timestamp.h"
;

static int routes[] = {
#include "routes.h"
};
static const int numRoutes = sizeof(routes) / sizeof(int);

static int wait(int bus) {
  return bus - (timestamp % bus);
}

int main(int argc, char **argv) {
  int bus = timestamp - 1;
  for (int i = 0; i < numRoutes; ++i)
    if (wait(routes[i]) < wait(bus))
      bus = routes[i];
  printf(
    "bus %d wait is %d minutes: %d\n",
    bus,
    wait(bus),
    bus * wait(bus)
  );
  return 0;
}
