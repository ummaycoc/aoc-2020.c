static void computeFile() {
  FILE *f = fopen("input.raw", "r");
  if (f == NULL) {
    printf("File Open Error!\n");
    exit(1);
  }

  int inited = 0;
  long num = 0;
  int building = 0;

  for (int c = fgetc(f); c != EOF; c = fgetc(f)) {
    if (!inited) {
      BEGIN;
      inited = 1;
    }

    if (isdigit(c)) {
      building = 1;
      num = (num * 10) + (c - '0');
      continue;
    }

    if (building) {
      LOAD(num);
      building = 0;
      num = 0;
    }

    switch (c) {
    case '+':
      ADD;
      break;
    case '*':
      MUL;
      break;
    case '(':
      START;
      break;
    case ')':
      END;
      break;
    case '\n':
      COMPUTE;
      inited = 0;
      break;
    case ' ':
      break;
    default:
      printf("Unknown character %c [%d]\n", (char) c, c);
      exit(1);
    }
  }

  if (ferror(f)) {
    printf("Error reading from file!\n");
    exit(1);
  }

  fclose(f);
}
