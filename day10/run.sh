#!/usr/bin/env bash

< input.raw sort -n | sed -e 's/^/  /' -e 's/$/,/' > input.h
< input.raw sort -n | tail -n 1 | sed -e 's/^/static const int MaxAdapter = '/ -e 's/$/;/' > max.h
gcc -o part1.out part1.c
gcc -o part2.out part2.c
echo -n 'Part 1: '
./part1.out
echo -n 'Part 2: '
./part2.out
rm -f *.h *.out
