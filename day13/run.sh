#!/usr/bin/env bash

< input.raw head -n 1 > timestamp.h
< input.raw tail -n 1 | tr x , | sed -e 's/,,*/,/g' > routes.h
< input.raw tail -n 1 | tr , '\n' | nl | grep -v 'x' | sort -n -k2 | tail -r | xargs | tr ' ' , > routes-offset.h
gcc -o part1.out part1.c
gcc -o part2.out part2.c
echo -n 'Part 1: '
./part1.out
echo -n 'Part 2: '
./part2.out
rm -f *.h *.out
