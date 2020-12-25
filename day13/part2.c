#include <stdio.h>
#include <stdlib.h>

static int routes[] = {
#include "routes-offset.h"
};
static const int routesLen = sizeof(routes) / sizeof(int);

static long inverse(long num, long mod) {
  if (num == 1)
    return 1;
  if (num == 0) {
    printf("Error, inverse!\n");
    exit(1);
  }
  num %= mod;
  long class = -(mod / num) * inverse(mod % num, mod);
  return ((class % mod) + mod) % mod;
}

// Assumes (m, n) = 1
static long combine(long a, long m, long b, long n) {
  // x ~ a mod m, x ~ b mod n
  // x = mk+a for some k
  //    mk+a ~ b mod n
  // => mk ~ b-a mod n
  // => k ~ m^-1 (b-a) mod n
  const long b_a = (((b - a) % n) + n) % n;
  const long minv = inverse(m, n);
  const long k = (minv * b_a) % n;
  // k was found mod n, using m and a gives the answer.
  return a + m*k;
}

int main(int argc, char **argv) {
  long class = routes[1] - routes[0];
  for (long i = 2, mod = routes[1]; i < routesLen; mod *= routes[i+1], i += 2)
    class = combine(class, mod, routes[i+1] - routes[i], routes[i+1]);
  printf("%ld\n", class + 1);
}
