#include <stdio.h>
#include <string.h>

static int input[] = { 11, 0, 1, 10, 5, 19 };
static int numInput = sizeof(input) / sizeof(int);
static int last[2020];
static int recent = 0;

static void speak(int turn) {
  int lastSpoken = last[recent];
  last[recent] = turn - 1;
  recent = lastSpoken == -1 ? 0 : turn - lastSpoken - 1;
}

int main(int argc, char **argv) {
  memset(last, -1, sizeof(last));
  for (int i = 0; i < numInput; ++i)
    last[input[i]] = i;
  recent = input[numInput - 1];
  last[recent] = -1;
  for (int i = 0; i < numInput - 1; ++i)
    if (input[i] == recent)
      last[recent] = i;
  for (int i = numInput; i < 2020; ++i)
    speak(i);
  printf("%d\n", recent);
  return 0;
}
