#!/usr/bin/env bash

function assign() {
  sed -e 's/\] = /, /' -e 's/^mem\[\(.*\)/assign(\1)/' -e 's/$/;/'
}

function andsOrs() {
  sed -e 's/^mask[[:space:]]*=[[:space:]]*\([10X]*\)/and = 0b\1;or = 0b\1/' | tr ';' '\n'
}

function multiAddrs() {
  sed -e 's/^mask[[:space:]]*=[[:space:]]*\([10X]*\)/m0 = 0b\1;m1 = 0b\1;mX = 0b\1/' | tr ';' '\n'
}

function andsOrsMask() {
  awk '/and/ { gsub(/X/, "1", $3) }; /or/ { gsub(/X/, "0", $3) }; { print $0 }'
}

function multiAddrsMask() {
  awk '/m0/ { gsub(/X/, "1", $3) }; /m1/ { gsub(/X/, "0", $3) }; /mX/ { gsub(/1/, "0", $3); gsub(/X/, "1", $3) }; { print $0 }'
}

< input.raw andsOrs | andsOrsMask | assign > commands.h
< input.raw multiAddrs | multiAddrsMask | assign > commands2.h

gcc -o part1.out part1.c
gcc -o part2.out part2.c
echo -n 'Part 1: '
./part1.out
echo -n 'Part 2: '
./part2.out
rm -f *.h *.out
