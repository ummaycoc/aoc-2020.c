#!/usr/bin/env bash

< input.raw sed -e 's/ /, /' -e 's/$/,/' -e 's/^/  /' > input.h
gcc -o part1.out part1.c
gcc -o part2.out part2.c
echo -n 'Part 1: '
./part1.out
echo -n 'Part 2: '
./part2.out
rm -f *.h *.out
