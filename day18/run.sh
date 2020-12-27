#!/usr/bin/env bash

< input.raw tr '()' '[]' |
  sed -e 's/\([[:digit:]][[:digit:]]*\)/ LOAD(\1) /g' \
      -e 's/\[/ START /g' \
      -e 's/]/ END /g' \
      -e 's/+/ ADD /g' \
      -e 's/\*/ MUL /g' \
      -e 's/$/ COMPUTE/' \
      -e 's/^/BEGIN /' |
  tr -s ' ' |
  sed -e 's/[[:space:]]*//' > commands.h

gcc -o part1.out part1.c
gcc -o part2.out part2.c
echo -n 'Part 1: '
./part1.out
echo -n 'Part 2: '
./part2.out
rm -f *.h *.out
