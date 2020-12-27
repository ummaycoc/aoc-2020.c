#!/usr/bin/env bash

< input.raw wc -l | xargs | sed -e 's/^/#define INIT_ROWS /' > rows.h
cols=$( < input.raw head -n 1 )
echo "#define INIT_COLS ${#cols}" > cols.h
< input.raw tr '#.' '10' | sed -e 's/0/0, /g' -e 's/1/1, /g' -e 's/^/{ /' -e 's/$/},/' > state.h

gcc -o part1.out part1.c
gcc -o part2.out part2.c
echo -n 'Part 1: '
./part1.out
echo -n 'Part 2: '
./part2.out
rm -f *.h *.out
