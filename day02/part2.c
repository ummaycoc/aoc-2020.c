#include <stdio.h>
#include <stdlib.h>

void checkError(FILE *f, char *topic) {
  if (ferror(f)) {
    printf("Error %s: %d\n", topic, ferror(f));
    exit(1);
  }
}

static int scanPolicy(FILE *f, int *a, int *b, char *r) {
  switch (fscanf(f, "%d-%d %c: ", a, b, r)) {
  case 3:
    return 1;
  case EOF:
    checkError(f, "reading policy");
  }
  return 0;
}

static int readPasswordChar(FILE *f, int *c) {
  *c = fgetc(f);
  return *c != EOF && *c != 10 && *c != 13;
}

static int readPassword(FILE *f) {
  int min = 0;
  int max = 0;
  char r = '\0';
  int found = 0;
  if (!scanPolicy(f, &min, &max, &r))
    return 0;
  --min;
  --max;
  for (int i = 0, c = 0; readPasswordChar(f, &c); ++i)
    found += (i == min || i == max) && c == r;
  checkError(f, "reading password");
  return found == 1;
}

static int countPasswords(FILE *f) {
  int count = 0;
  while (!feof(f))
    count += readPassword(f);
  return count;
}

int main(int argc, char **argv) {
  FILE *f = fopen("input.raw", "r");
  if (f == NULL) {
    printf("Error opening file!\n");
    return 0;
  }
  const int count = countPasswords(f);
  fclose(f);
  printf("Count: %d\n", count);
  return 0;
}
