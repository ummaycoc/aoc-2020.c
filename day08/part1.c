#include <stdio.h>
#include <stdlib.h>

enum op {
  nop,
  acc,
  jmp
};

static int program[] = {
#include "input.h"
};
static const int commands = (sizeof program)/(2*sizeof(int));

static void execute(int opcode, int oparg, int *accum, int *ins) {
  switch (opcode) {
  case acc:
    *accum += oparg;
  case nop:
    ++*ins;
    break;
  case jmp:
    *ins += oparg;
    break;
  default:
    printf("ERROR!\n");
    exit(1);
  }
}

static void run(int *accum) {
  char seen[commands] = { 0 };
  int ins = 0;
  int opcode = 0;
  int oparg = 0;
  while (!seen[ins]) {
    opcode = program[2 * ins];
    oparg = program[2 * ins + 1];
    seen[ins] += 1;
    execute(opcode, oparg, accum, &ins);
  }
}

int main(int argc, char **argv) {
  int accum = 0;
  run(&accum);
  printf("%d\n", accum);
  return 0;
}
