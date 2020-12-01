#!/usr/bin/env bash

< input.raw sort -n | sed -e 's/^/  /' -e 's/$/,/' > input.h
gcc -o part1.out part1.c
gcc -o part2.out part2.c
gcc -o part2-quadratic.out part2-quadratic.c
echo -n 'Part 1: '
./part1.out
echo -n 'Part 2: '
./part2.out
echo -n 'Quadratic: '
./part2-quadratic.out
rm -f *.h *.out
