#!/usr/bin/env bash

< input.raw tr 'FLBR' '0011' | # FBFBFLRL -> 01010010
  ( echo 'ibase=2'; cat - ) | # prepend line with 'ibase=2'
  bc | # binary to decimal
  sort -n | # sort by numeric value
  tail -n 1 # last item.
