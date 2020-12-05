#!/usr/bin/env bash

< input.raw tr 'FLBR' '0011' |
  ( echo 'ibase=2'; cat - ) |
  bc |
  sort -n |
  tail -n 1
