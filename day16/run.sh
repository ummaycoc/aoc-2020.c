#!/usr/bin/env bash

< input.raw awk '/ticket/ { exit }; /:/ { print $0 }' | cut -d: -f 2 | tr -s 'or -' , | cut -c 2- | sed -e 's/$/,/' > ranges.h
< input.raw sed -n '/nearby/,$p' | awk 'NR > 1' | sed -e 's/^/{/' -e 's/$/},/' > nearby.h
< nearby.h wc -l | xargs | sed -e 's/^/#define NEARBY_COUNT /' > nearby-count.h
< ranges.h wc -l | xargs | sed -e 's/^/#define TICKET_FIELDS /' > ticket-fields.h
< input.raw awk '/your ticket/ { getline; print $0; exit }' > my-ticket.h

gcc -o part1.out part1.c
gcc -o part2.out part2.c
echo -n 'Part 1: '
./part1.out
echo -n 'Part 2: '
./part2.out
rm -f *.h *.out
